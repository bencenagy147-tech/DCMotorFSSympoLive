/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: DCMotorOpenLoop_data.c
 *
 * Code generated for Simulink model 'DCMotorOpenLoop'.
 *
 * Model version                  : 1.2
 * Simulink Coder version         : 26.2 (R2026b) 22-May-2026
 * C/C++ source code generated on : Sun Nov 22 12:38:29 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "DCMotorOpenLoop.h"

/* Block parameters (default storage) */
P_DCMotorOpenLoop_T DCMotorOpenLoop_P = {
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
   * Referenced by: '<S4>/CountsToRpm'
   */
  1.0,

  /* Variable: OL_DutyGain
   * Referenced by: '<Root>/DutyEnable'
   */
  1.0,

  /* Variable: Spd_CalDivisor
   * Referenced by: '<S4>/CalDivide'
   */
  1.2034545454545453,

  /* Variable: Spd_RpmPerCount
   * Referenced by: '<S4>/CountsToRpm'
   */
  5.6818181818181817,

  /* Mask Parameter: DutyTestSequence_OutValues
   * Referenced by: '<S3>/Lookup'
   */
  { 0.0, 25.0, 50.0, 75.0, 100.0, 0.0, -25.0, -50.0, -75.0, -100.0, 0.0, 0.0 },

  /* Mask Parameter: DutyTestSequence_TimeValues
   * Referenced by: '<S3>/Lookup'
   */
  { 0.0, 1.0, 3.0, 5.0, 7.0, 10.0, 12.0, 14.0, 16.0, 18.0, 21.0, 23.0 },

  /* Mask Parameter: LimitedCounter_uplimit
   * Referenced by: '<S7>/FixPt Switch'
   */
  2300U,

  /* Expression: 255/100
   * Referenced by: '<S1>/Gain'
   */
  2.55,

  /* Expression: -255/100
   * Referenced by: '<S1>/Gain1'
   */
  -2.55,

  /* Computed Parameter: SampleTimeMath_WtEt
   * Referenced by: '<S3>/Sample Time Math'
   */
  0.01,

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

  /* Computed Parameter: CountWindowDelay_InitialConditi
   * Referenced by: '<S4>/CountWindowDelay'
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
   * Referenced by: '<S7>/Constant'
   */
  0U,

  /* Computed Parameter: Output_InitialCondition
   * Referenced by: '<S5>/Output'
   */
  0U,

  /* Computed Parameter: FixPtConstant_Value
   * Referenced by: '<S6>/FixPt Constant'
   */
  1U
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
