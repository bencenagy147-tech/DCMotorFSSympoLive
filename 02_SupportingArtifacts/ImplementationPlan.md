# DC Motor Speed Control – Arduino Uno + Pololu 4841 – Implementation Plan

Status: **PROPOSED – waiting for approval** (2026-11-22)

## 1. Starting point (what is in the project)

| Item | Found |
|---|---|
| MATLAB / Simulink | R2026b Update 1, Simulink Support Package for Arduino Hardware 26.2.4 |
| Project | `DCMotorFSSympoLive.prj` (open), cache → `03_Cache`, codegen → `04_Codegen` (both confirmed active) |
| Folders | `01_Implementation`, `02_SupportingArtifacts`, `03_Cache`, `04_Codegen` |
| Driver | `01_Implementation/DC7960MDriver.slx` – **Subsystem Reference file** |

### Driver subsystem (`DC7960MDriver.slx`) – read, not modified
- 1 input `In1` = duty command in **percent, −100 … +100** (gain 255/100, saturation 0…255).
- `In1 > 0` → PWM on **D11** (R_PWM side), D10 = 0; `In1 ≤ 0` → PWM on **D10** (L_PWM side), D11 = 0.
- **D8, D9** = enable pins (R_EN / L_EN), held at 1. PWM frequency 490.2 Hz (default).

### Motor / sensors
| Parameter | Value | Source |
|---|---|---|
| Motor | 4.4:1 Metal Gearmotor 25Dx63L HP 12 V, 48 CPR encoder | pololu.com/product/4841 |
| Gear ratio | 4.4 : 1 (22·24 / 12·10) | " |
| No-load speed | 2200 rpm @ 12 V | " |
| Stall current | 5.0 A (extrapolated) | " |
| Encoder | 48 counts/rev motor shaft (4× quadrature) → **211.2 counts/rev output shaft** | " |
| Encoder pins | A → D2, B → D3 (both external-interrupt pins on the Uno) | user |
| Current sensor | ACS712-5A on **A3**, 185 mV/A, 2.5 V offset @ 5 V | datasheet (optional, logging only) |

Encoder block to use: `arduinosensorlib/Encoder` (`arduino_RotaryEncoder`), InputA = 2, InputB = 3, outputs an int32 count.

## 2. Architecture

```
01_Implementation/
  DC7960MDriver.slx        (existing, untouched – used via Subsystem Reference block)
  EncoderSpeed.slx         Subsystem Reference: Encoder block → Δcount → rpm (+ low-pass)
  CurrentSense.slx         Subsystem Reference: Analog Input A3 → A (optional signal)
  SpeedController.slx      Subsystem Reference: PI controller (Discrete PID block, PI, anti-windup)
  DCMotorOpenLoop.slx      Milestone 1 – hardware, open-loop PWM tests
  DCMotorPlantSim.slx      Milestone 2 – desktop simulation: SpeedController + identified plant
  DCMotorSpeedControl.slx  Milestone 3 – hardware, closed loop (main model)
  DCMotorParams.m          all parameters (Ts, counts/rev, filter, sensor constants, PI gains)
02_SupportingArtifacts/
  ImplementationPlan.md    this file
  M1_OpenLoopCalibration.md, M2_PITuning.md, M3_ClosedLoopResults.md (+ plots)
```

The same `EncoderSpeed` and `SpeedController` files are used in simulation and on hardware, so what is tuned is what is deployed.

Key design numbers:
- Fixed-step discrete solver, base rate **Ts = 10 ms**, Arduino Uno target, run with **Monitor & Tune (External mode over serial)** to see and log signals.
- Speed: `rpm = Δcount · 60 / (211.2 · Ts)` → raw resolution 28.4 rpm per count at 10 ms; a low-pass / moving-average filter (≈ 30–50 ms) brings this to ≈ 5–10 rpm. Final filter set in M1.
- Max encoder rate at 2200 rpm ≈ 7 700 counts/s – OK for Uno interrupts.
- Controller output = duty % saturated at ±100 % (matches the driver input), clamping anti-windup.

## 3. Milestones and gates

### Milestone 1 – Open-loop model, speed measurement, sensor calibration (hardware)
Work:
1. Create `DCMotorParams.m`, `EncoderSpeed.slx`, `CurrentSense.slx`.
2. Build `DCMotorOpenLoop.slx`: duty test sequence → `DC7960MDriver` (Subsystem Reference); EncoderSpeed and CurrentSense logged.
   Sequence: 0 % → **+100 %** → 0 % → **−100 %** → 0 %, plus short +/−25/50/75 % steps for the gain/linearity check and for plant identification.
3. Configure for Arduino Uno (fixed-step 10 ms, External mode), build and run on hardware **after you confirm the rig is ready** (motor clamped, supply on).
4. Calibrate from the logged data: direction sign (+duty → +rpm), counts/rev check against 2200 rpm no-load, filter choice, ACS712 zero offset.
5. Identify a first-order plant (gain K [rpm/%], time constant τ, dead-band) from the step data → saved for M2.

**Gate 1 (you approve):**
- Motor runs at ±100 % in both directions, measured speed has the correct sign in both directions.
- |speed| at ±100 % is plausible vs. 2200 rpm no-load (scaled by your supply voltage) and the two directions agree within ≈ 5 %.
- Speed signal noise at steady state ≤ ≈ ±20 rpm after filtering.
- `DCMotorOpenLoop.slx` + subsystems saved; `M1_OpenLoopCalibration.md` written with plots and calibrated constants.

### Milestone 2 – PI controller design and tuning in simulation
Work:
1. Build `SpeedController.slx` (Discrete PID Controller block, PI form, Ts = 10 ms, output limits ±100 %, clamping anti-windup).
2. Build `DCMotorPlantSim.slx`: reference profile + SpeedController + identified plant (incl. dead-band, saturation, speed quantization/filter) for realistic tuning.
3. Reference profile: **+1500 rpm, stepping down by 150 rpm every 2 s to −1500 rpm** (21 levels, 42 s) – a Repeating Sequence Stair / lookup in the model.
4. Tune Kp/Ki (pidtune on the identified plant, then checked against the nonlinear sim), store gains in `DCMotorParams.m`.
5. Verify with scripted simulation (and a Gherkin test via `model_test`) against the criteria below.

**Gate 2 (you approve the gains):**
- Simulated step response for 150 rpm steps: overshoot ≤ 10 %, settling (2 %) ≤ 0.5 s, steady-state error ≤ 1 % of 1500 rpm (15 rpm), no sustained limit cycling at the zero crossing.
- Controller output stays within ±100 %, no windup after saturation.
- `SpeedController.slx`, `DCMotorPlantSim.slx` saved; `M2_PITuning.md` with gains, plots and pass/fail table.

### Milestone 3 – Closed-loop speed control on hardware (main model)
Work:
1. Build `DCMotorSpeedControl.slx`: reference profile → SpeedController → DC7960MDriver, feedback from EncoderSpeed; CurrentSense logged only.
2. Deploy to the Uno in External mode **after you confirm the rig is ready**; log reference, speed, duty, current.
3. Compare hardware vs. simulation; fine-tune Kp/Ki if needed (via Monitor & Tune, then written back to `DCMotorParams.m`).

**Gate 3 (final acceptance):**
- Hardware tracks the full 1500 → −1500 rpm profile; per step: overshoot ≤ 15 %, settles ≤ 1 s, steady-state error ≤ ±25 rpm (hardware tolerance slightly wider than sim).
- Direction reversal through 0 rpm without lock-up.
- `DCMotorSpeedControl.slx` saved; `M3_ClosedLoopResults.md` with plots and final parameters.

Each approved milestone's models are saved in `01_Implementation` and added to the project. Commits are left to you.

## 4. Toolkit skills / tools used
- `building-simulink-models` + `model_edit` / `model_read` / `model_check` – all model creation and edits.
- `managing-simulink-projects` – adding files to the project.
- `simulating-simulink-models` – scripted sims and data extraction (M2).
- `control-systems:matlab-identify-linear-system` – plant identification from M1 data.
- `testing-simulink-models` + `model_test` – Gherkin check of M2 criteria.
- `test-and-measurement:matlab-connect-arduino` / Arduino support package – target configuration, build, External mode.

## 5. Notes / differences from the request
- Folder names are `01_…` – `04_…` (with leading zero) and the project file is `DCMotorFSSympoLive.prj`; the plan uses those actual names. Models go into `01_Implementation`, docs into `02_SupportingArtifacts`.
- The driver file is `DC7960MDriver.slx` (request mentioned `DC7950MDriver.slx`).
- The driver is a Subsystem Reference file, so it is placed in the models with a Subsystem Reference block (no change to the file or its ports). If you prefer a literal copy of its contents into each model, say so.
- Hardware runs move the motor; I will ask before every build/run on the board.
