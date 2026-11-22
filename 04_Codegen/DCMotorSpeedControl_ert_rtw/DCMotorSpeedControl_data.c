/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: DCMotorSpeedControl_data.c
 *
 * Code generated for Simulink model 'DCMotorSpeedControl'.
 *
 * Model version                  : 1.3
 * Simulink Coder version         : 26.2 (R2026b) 22-May-2026
 * C/C++ source code generated on : Sun Nov 22 12:45:38 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "DCMotorSpeedControl.h"

/* Block parameters (default storage) */
P_DCMotorSpeedControl_T DCMotorSpeedControl_P = {
  /* Variable: Cur_AdcFullScale
   * Referenced by: '<S2>/AdcToVolt'
   */
  1023.0,

  /* Variable: Cur_AdcVref
   * Referenced by: '<S2>/AdcToVolt'
   */
  5.0,

  /* Variable: Cur_FilterCoef
   * Referenced by: '<S2>/LowPass'
   */
  0.2,

  /* Variable: Cur_Offset_V
   * Referenced by: '<S2>/RemoveOffset'
   */
  3.54,

  /* Variable: Cur_Sensitivity
   * Referenced by: '<S2>/VoltToAmp'
   */
  0.185,

  /* Variable: Enc_DirSign
   * Referenced by: '<S3>/CountsToRpm'
   */
  1.0,

  /* Variable: PI_Ki
   * Referenced by: '<S39>/Integral Gain'
   */
  0.46040515653775321,

  /* Variable: PI_Kp
   * Referenced by: '<S47>/Proportional Gain'
   */
  0.013167587476979742,

  /* Variable: PI_UMax
   * Referenced by:
   *   '<S49>/Saturation'
   *   '<S34>/DeadZone'
   */
  100.0,

  /* Variable: PI_UMin
   * Referenced by:
   *   '<S49>/Saturation'
   *   '<S34>/DeadZone'
   */
  -100.0,

  /* Variable: Spd_CalDivisor
   * Referenced by: '<S3>/CalDivide'
   */
  1.2034545454545453,

  /* Variable: Spd_RpmPerCount
   * Referenced by: '<S3>/CountsToRpm'
   */
  5.6818181818181817,

  /* Mask Parameter: SpeedReference_OutValues
   * Referenced by: '<S5>/Lookup'
   */
  { 1500.0, 1350.0, 1200.0, 1050.0, 900.0, 750.0, 600.0, 450.0, 300.0, 150.0,
    0.0, -150.0, -300.0, -450.0, -600.0, -750.0, -900.0, -1050.0, -1200.0,
    -1350.0, -1500.0, 0.0 },

  /* Mask Parameter: SpeedReference_TimeValues
   * Referenced by: '<S5>/Lookup'
   */
  { 0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 22.0, 24.0,
    26.0, 28.0, 30.0, 32.0, 34.0, 36.0, 38.0, 40.0, 42.0 },

  /* Mask Parameter: LimitedCounter_uplimit
   * Referenced by: '<S62>/FixPt Switch'
   */
  4200U,

  /* Expression: 255/100
   * Referenced by: '<S1>/Gain'
   */
  2.55,

  /* Expression: -255/100
   * Referenced by: '<S1>/Gain1'
   */
  -2.55,

  /* Expression: 0
   * Referenced by: '<S32>/Constant1'
   */
  0.0,

  /* Computed Parameter: SampleTimeMath_WtEt
   * Referenced by: '<S5>/Sample Time Math'
   */
  0.01,

  /* Computed Parameter: Integrator_gainval
   * Referenced by: '<S42>/Integrator'
   */
  0.01,

  /* Expression: 0
   * Referenced by: '<S42>/Integrator'
   */
  0.0,

  /* Expression: 100
   * Referenced by: '<Root>/DutyLimit'
   */
  100.0,

  /* Expression: -100
   * Referenced by: '<Root>/DutyLimit'
   */
  -100.0,

  /* Expression: 0
   * Referenced by: '<S1>/Switch'
   */
  0.0,

  /* Expression: [1 -(1-Cur_FilterCoef)]
   * Referenced by: '<S2>/LowPass'
   */
  { 1.0, -0.8 },

  /* Expression: 0
   * Referenced by: '<S2>/LowPass'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S32>/Clamping_zero'
   */
  0.0,

  /* Computed Parameter: CountWindowDelay_InitialConditi
   * Referenced by: '<S3>/CountWindowDelay'
   */
  0L,

  /* Computed Parameter: Saturation_UpperSat
   * Referenced by: '<S1>/Saturation'
   */
  255.0F,

  /* Computed Parameter: Saturation_LowerSat
   * Referenced by: '<S1>/Saturation'
   */
  0.0F,

  /* Computed Parameter: Constant4_Value
   * Referenced by: '<S1>/Constant4'
   */
  0.0F,

  /* Computed Parameter: Constant5_Value
   * Referenced by: '<S1>/Constant5'
   */
  0.0F,

  /* Computed Parameter: Saturation1_UpperSat
   * Referenced by: '<S1>/Saturation1'
   */
  255.0F,

  /* Computed Parameter: Saturation1_LowerSat
   * Referenced by: '<S1>/Saturation1'
   */
  0.0F,

  /* Computed Parameter: Constant2_Value
   * Referenced by: '<S1>/Constant2'
   */
  1.0F,

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S62>/Constant'
   */
  0U,

  /* Computed Parameter: Output_InitialCondition
   * Referenced by: '<S60>/Output'
   */
  0U,

  /* Computed Parameter: FixPtConstant_Value
   * Referenced by: '<S61>/FixPt Constant'
   */
  1U,

  /* Computed Parameter: Constant_Value_i
   * Referenced by: '<S32>/Constant'
   */
  1,

  /* Computed Parameter: Constant2_Value_g
   * Referenced by: '<S32>/Constant2'
   */
  -1,

  /* Computed Parameter: Constant3_Value
   * Referenced by: '<S32>/Constant3'
   */
  1,

  /* Computed Parameter: Constant4_Value_g
   * Referenced by: '<S32>/Constant4'
   */
  -1
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
