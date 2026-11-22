%% DCMotorParams - parameters for the Pololu 4841 speed-control models
% Loaded by the PreLoadFcn/InitFcn of DCMotorOpenLoop and DCMotorSpeedControl.
% Hardware: Arduino Uno, BTS7960 driver (DC7960MDriver.slx), Pololu 4841
% (4.4:1, 12 V, 2200 rpm no-load, 48 CPR encoder), ACS712-5A on A3.

%% Timing
Ts = 0.01;                          % [s] base sample time of the controller

%% Motor (datasheet, pololu.com/product/4841)
Motor_GearRatio     = 4.4;          % [-] (22*24)/(12*10)
Motor_NoLoadRpm     = 2200;         % [rpm] at 12 V
Motor_SupplyVoltage = 12;           % [V]  driver supply (assumed, confirm)

%% Encoder / speed measurement
Enc_PinA          = 2;              % encoder channel A (interrupt pin)
Enc_PinB          = 3;              % encoder channel B (interrupt pin)
Enc_CPR_Motor     = 48;             % [counts/rev] motor shaft, 4x quadrature
Enc_CPR_Output    = Enc_CPR_Motor*Motor_GearRatio;   % 211.2 counts/rev output shaft
Enc_DirSign       = 1;              % +1/-1, M1 run 1: +duty -> +rpm confirmed
Spd_WindowN       = 5;              % [samples] counts difference window (5*Ts = 50 ms)
Spd_RpmPerCount   = 60/(Enc_CPR_Output*Spd_WindowN*Ts);  % [rpm/count]
% M1 calibration: raw speed at +/-100 % duty was +2632.2 / -2663.0 rpm
% (mean 2647.6 rpm); by decision it is scaled so that 100 % duty = 2200 rpm.
Spd_RawAt100      = (2632.2 + 2663.0)/2;          % [rpm] measured, uncalibrated
Spd_CalDivisor    = Spd_RawAt100/Motor_NoLoadRpm; % [-] = 1.2035, rpm_out = rpm_raw / divisor

%% Current sensor ACS712-5A
Cur_AdcPin        = 3;              % analog channel A3
Cur_AdcVref       = 5;              % [V]
Cur_AdcFullScale  = 1023;           % 10-bit ADC
Cur_Offset_V      = 3.54;           % [V] zero-current output, measured in M1 (datasheet 2.5 V)
Cur_Sensitivity   = 0.185;          % [V/A] datasheet, not verified (sensor reads supply current, unipolar)
Cur_FilterCoef    = 0.2;            % [-] 1st-order low-pass y += a*(u - y)

%% Open-loop test sequence (duty in percent, -100..100)
OL_DutyGain   = 1;                  % tunable in Monitor & Tune, 0 = stop motor
OL_SeqTime    = [0 1 3 5 7 10 12 14 16 18 21 23];        % [s] step instants
OL_SeqDuty    = [0 25 50 75 100 0 -25 -50 -75 -100 0 0];  % [%]
OL_StopTime   = OL_SeqTime(end);    % [s]

%% Speed controller (PI, pole-zero cancellation on identified P1D plant)
Plant_K   = 21.72;                  % [rpm/%]   identified in M1
Plant_Tau = 0.0286;                 % [s]
Spd_Tcl   = 0.10;                   % [s] desired closed-loop time constant
PI_Kp     = Plant_Tau/(Plant_K*Spd_Tcl);   % [%/rpm]
PI_Ki     = 1/(Plant_K*Spd_Tcl);           % [%/(rpm*s)]
PI_UMax   = 100;  PI_UMin = -100;           % [%] duty limits

%% Reference profile: 1500 -> -1500 rpm, -150 rpm every 2 s
Ref_StepTime = 2;                                  % [s]
Ref_Levels   = 1500:-150:-1500;                    % 21 levels
Ref_Time     = (0:numel(Ref_Levels))*Ref_StepTime; % [s]
Ref_Values   = [Ref_Levels 0];                     % end at 0 rpm
CL_StopTime  = Ref_Time(end) + 1;                  % [s] 43 s
