/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: DCMotorSpeedControl.c
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
#include "MW_ArduinoEncoder.h"
#include "MW_PWM.h"
#include "MW_AnalogIn.h"
#include "MW_arduino_digitalio.h"
#include "DCMotorSpeedControl_private.h"
#include "rtwtypes.h"
#include <math.h>

/* Block signals (default storage) */
B_DCMotorSpeedControl_T DCMotorSpeedControl_B;

/* Block states (default storage) */
DW_DCMotorSpeedControl_T DCMotorSpeedControl_DW;

/* Real-time model */
static RT_MODEL_DCMotorSpeedControl_T DCMotorSpeedControl_M_;
RT_MODEL_DCMotorSpeedControl_T *const DCMotorSpeedControl_M =
  &DCMotorSpeedControl_M_;
uint32_T plook_u32d_bincka(real_T u, const real_T bp[], uint32_T maxIndex)
{
  uint32_T bpIndex;

  /* Prelookup - Index only
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u <= bp[0UL]) {
    bpIndex = 0UL;
  } else if (u < bp[maxIndex]) {
    bpIndex = binsearch_u32d(u, bp, maxIndex >> 1UL, maxIndex);
  } else {
    bpIndex = maxIndex;
  }

  return bpIndex;
}

uint32_T binsearch_u32d(real_T u, const real_T bp[], uint32_T startIndex,
  uint32_T maxIndex)
{
  uint32_T bpIdx;
  uint32_T bpIndex;
  uint32_T iRght;

  /* Binary Search */
  bpIdx = startIndex;
  bpIndex = 0UL;
  iRght = maxIndex;
  while (iRght - bpIndex > 1UL) {
    if (u < bp[bpIdx]) {
      iRght = bpIdx;
    } else {
      bpIndex = bpIdx;
    }

    bpIdx = (iRght + bpIndex) >> 1UL;
  }

  return bpIndex;
}

real32_T rt_roundf_snf(real32_T u)
{
  real32_T y;
  if ((real32_T)fabs(u) < 8.388608E+6F) {
    if (u >= 0.5F) {
      y = (real32_T)floor(u + 0.5F);
    } else if (u > -0.5F) {
      y = u * 0.0F;
    } else {
      y = (real32_T)ceil(u - 0.5F);
    }
  } else {
    y = u;
  }

  return y;
}

/* Model step function */
void DCMotorSpeedControl_step(void)
{
  real_T rtb_DeadZone;
  real_T rtb_IntegralGain;
  real_T y;
  real32_T rtb_Switch_f_idx_0;
  real32_T rtb_Switch_f_idx_1;
  uint16_T b_varargout_1;
  int8_T tmp_0;
  int8_T tmp_1;
  uint8_T tmp;

  /* SignalConversion: '<S5>/Output' incorporates:
   *  DataTypeConversion: '<S5>/Data Type Conversion'
   *  Lookup_n-D: '<S5>/Lookup'
   *  SampleTimeMath: '<S5>/Sample Time Math'
   *  UnitDelay: '<S60>/Output'
   *
   * About '<S5>/Sample Time Math':
   *  y = u * K where K = ( w * Ts )
   *   */
  DCMotorSpeedControl_B.Output =
    DCMotorSpeedControl_P.SpeedReference_OutValues[plook_u32d_bincka((real_T)
    DCMotorSpeedControl_DW.Output_DSTATE *
    DCMotorSpeedControl_P.SampleTimeMath_WtEt,
    DCMotorSpeedControl_P.SpeedReference_TimeValues, 21UL)];

  /* MATLABSystem: '<S3>/Encoder' */
  if (DCMotorSpeedControl_DW.obj_ox.TunablePropsChanged) {
    DCMotorSpeedControl_DW.obj_ox.TunablePropsChanged = false;
  }

  /* MATLABSystem: '<S3>/Encoder' */
  MW_EncoderRead(DCMotorSpeedControl_DW.obj_ox.Index,
                 &DCMotorSpeedControl_B.EncCounts);

  /* Gain: '<S3>/CalDivide' incorporates:
   *  DataTypeConversion: '<S3>/ToDouble'
   *  Delay: '<S3>/CountWindowDelay'
   *  Gain: '<S3>/CountsToRpm'
   *  Sum: '<S3>/DeltaCount'
   */
  DCMotorSpeedControl_B.Speed_rpm = DCMotorSpeedControl_P.Spd_RpmPerCount *
    DCMotorSpeedControl_P.Enc_DirSign * (real_T)(DCMotorSpeedControl_B.EncCounts
    - DCMotorSpeedControl_DW.CountWindowDelay_DSTATE[0]) * (1.0 /
    DCMotorSpeedControl_P.Spd_CalDivisor);

  /* Sum: '<Root>/SpeedError' */
  rtb_IntegralGain = DCMotorSpeedControl_B.Output -
    DCMotorSpeedControl_B.Speed_rpm;

  /* Sum: '<S51>/Sum' incorporates:
   *  DiscreteIntegrator: '<S42>/Integrator'
   *  Gain: '<S47>/Proportional Gain'
   */
  rtb_DeadZone = DCMotorSpeedControl_P.PI_Kp * rtb_IntegralGain +
    DCMotorSpeedControl_DW.Integrator_DSTATE;

  /* Saturate: '<S49>/Saturation' */
  if (rtb_DeadZone > DCMotorSpeedControl_P.PI_UMax) {
    DCMotorSpeedControl_B.Duty_pct = DCMotorSpeedControl_P.PI_UMax;
  } else if (rtb_DeadZone < DCMotorSpeedControl_P.PI_UMin) {
    DCMotorSpeedControl_B.Duty_pct = DCMotorSpeedControl_P.PI_UMin;
  } else {
    DCMotorSpeedControl_B.Duty_pct = rtb_DeadZone;
  }

  /* Saturate: '<Root>/DutyLimit' */
  if (DCMotorSpeedControl_B.Duty_pct > DCMotorSpeedControl_P.DutyLimit_UpperSat)
  {
    /* Saturate: '<S49>/Saturation' incorporates:
     *  Saturate: '<Root>/DutyLimit'
     */
    DCMotorSpeedControl_B.Duty_pct = DCMotorSpeedControl_P.DutyLimit_UpperSat;
  } else if (DCMotorSpeedControl_B.Duty_pct <
             DCMotorSpeedControl_P.DutyLimit_LowerSat) {
    /* Saturate: '<S49>/Saturation' incorporates:
     *  Saturate: '<Root>/DutyLimit'
     */
    DCMotorSpeedControl_B.Duty_pct = DCMotorSpeedControl_P.DutyLimit_LowerSat;
  }

  /* End of Saturate: '<Root>/DutyLimit' */

  /* Switch: '<S1>/Switch' incorporates:
   *  Constant: '<S1>/Constant4'
   *  Constant: '<S1>/Constant5'
   */
  if (DCMotorSpeedControl_B.Duty_pct > DCMotorSpeedControl_P.Switch_Threshold) {
    /* Gain: '<S1>/Gain' */
    rtb_Switch_f_idx_0 = (real32_T)(DCMotorSpeedControl_P.Gain_Gain *
      DCMotorSpeedControl_B.Duty_pct);

    /* Saturate: '<S1>/Saturation' */
    if (rtb_Switch_f_idx_0 > DCMotorSpeedControl_P.Saturation_UpperSat) {
      rtb_Switch_f_idx_0 = DCMotorSpeedControl_P.Saturation_UpperSat;
    } else if (rtb_Switch_f_idx_0 < DCMotorSpeedControl_P.Saturation_LowerSat) {
      rtb_Switch_f_idx_0 = DCMotorSpeedControl_P.Saturation_LowerSat;
    }

    /* End of Saturate: '<S1>/Saturation' */
    rtb_Switch_f_idx_1 = DCMotorSpeedControl_P.Constant4_Value;
  } else {
    rtb_Switch_f_idx_0 = DCMotorSpeedControl_P.Constant5_Value;

    /* Gain: '<S1>/Gain1' incorporates:
     *  Constant: '<S1>/Constant5'
     */
    rtb_Switch_f_idx_1 = (real32_T)(DCMotorSpeedControl_P.Gain1_Gain *
      DCMotorSpeedControl_B.Duty_pct);

    /* Saturate: '<S1>/Saturation1' */
    if (rtb_Switch_f_idx_1 > DCMotorSpeedControl_P.Saturation1_UpperSat) {
      rtb_Switch_f_idx_1 = DCMotorSpeedControl_P.Saturation1_UpperSat;
    } else if (rtb_Switch_f_idx_1 < DCMotorSpeedControl_P.Saturation1_LowerSat)
    {
      rtb_Switch_f_idx_1 = DCMotorSpeedControl_P.Saturation1_LowerSat;
    }

    /* End of Saturate: '<S1>/Saturation1' */
  }

  /* End of Switch: '<S1>/Switch' */

  /* MATLABSystem: '<S1>/PWM' */
  DCMotorSpeedControl_DW.obj_a.PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle
    (10UL);
  if (rtb_Switch_f_idx_1 <= 255.0F) {
    y = rtb_Switch_f_idx_1;
  } else {
    y = 255.0;
  }

  if (!(y >= 0.0)) {
    y = 0.0;
  }

  MW_PWM_SetDutyCycle(DCMotorSpeedControl_DW.obj_a.PWMDriverObj.MW_PWM_HANDLE, y);

  /* End of MATLABSystem: '<S1>/PWM' */

  /* MATLABSystem: '<S1>/PWM1' */
  DCMotorSpeedControl_DW.obj_f.PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle
    (11UL);
  if (rtb_Switch_f_idx_0 <= 255.0F) {
    y = rtb_Switch_f_idx_0;
  } else {
    y = 255.0;
  }

  if (!(y >= 0.0)) {
    y = 0.0;
  }

  MW_PWM_SetDutyCycle(DCMotorSpeedControl_DW.obj_f.PWMDriverObj.MW_PWM_HANDLE, y);

  /* End of MATLABSystem: '<S1>/PWM1' */

  /* MATLABSystem: '<S2>/AnalogInput_A3' */
  DCMotorSpeedControl_DW.obj_j.AnalogInDriverObj.MW_ANALOGIN_HANDLE =
    MW_AnalogIn_GetHandle(17UL);
  MW_AnalogInSingle_ReadResult
    (DCMotorSpeedControl_DW.obj_j.AnalogInDriverObj.MW_ANALOGIN_HANDLE,
     &b_varargout_1, MW_ANALOGIN_UINT16);

  /* Gain: '<S2>/AdcToVolt' incorporates:
   *  DataTypeConversion: '<S2>/ToDouble'
   *  MATLABSystem: '<S2>/AnalogInput_A3'
   * */
  DCMotorSpeedControl_B.Sensor_V = DCMotorSpeedControl_P.Cur_AdcVref /
    DCMotorSpeedControl_P.Cur_AdcFullScale * (real_T)b_varargout_1;

  /* DiscreteFilter: '<S2>/LowPass' incorporates:
   *  Bias: '<S2>/RemoveOffset'
   *  Gain: '<S2>/VoltToAmp'
   */
  DCMotorSpeedControl_DW.LowPass_states = (1.0 /
    DCMotorSpeedControl_P.Cur_Sensitivity * (DCMotorSpeedControl_B.Sensor_V -
    DCMotorSpeedControl_P.Cur_Offset_V) - DCMotorSpeedControl_P.LowPass_DenCoef
    [1L] * DCMotorSpeedControl_DW.LowPass_states) /
    DCMotorSpeedControl_P.LowPass_DenCoef[0];

  /* DiscreteFilter: '<S2>/LowPass' */
  DCMotorSpeedControl_B.Current_A = DCMotorSpeedControl_P.Cur_FilterCoef *
    DCMotorSpeedControl_DW.LowPass_states;

  /* DeadZone: '<S34>/DeadZone' */
  if (rtb_DeadZone > DCMotorSpeedControl_P.PI_UMax) {
    rtb_DeadZone -= DCMotorSpeedControl_P.PI_UMax;
  } else if (rtb_DeadZone >= DCMotorSpeedControl_P.PI_UMin) {
    rtb_DeadZone = 0.0;
  } else {
    rtb_DeadZone -= DCMotorSpeedControl_P.PI_UMin;
  }

  /* End of DeadZone: '<S34>/DeadZone' */

  /* Gain: '<S39>/Integral Gain' */
  rtb_IntegralGain *= DCMotorSpeedControl_P.PI_Ki;

  /* Sum: '<S61>/FixPt Sum1' incorporates:
   *  Constant: '<S61>/FixPt Constant'
   *  UnitDelay: '<S60>/Output'
   */
  DCMotorSpeedControl_DW.Output_DSTATE +=
    DCMotorSpeedControl_P.FixPtConstant_Value;

  /* Switch: '<S62>/FixPt Switch' */
  if (DCMotorSpeedControl_DW.Output_DSTATE >
      DCMotorSpeedControl_P.LimitedCounter_uplimit) {
    /* Sum: '<S61>/FixPt Sum1' incorporates:
     *  Constant: '<S62>/Constant'
     */
    DCMotorSpeedControl_DW.Output_DSTATE = DCMotorSpeedControl_P.Constant_Value;
  }

  /* End of Switch: '<S62>/FixPt Switch' */

  /* MATLABSystem: '<S1>/Digital Output' incorporates:
   *  Constant: '<S1>/Constant2'
   */
  rtb_Switch_f_idx_0 = rt_roundf_snf(DCMotorSpeedControl_P.Constant2_Value);
  if (rtb_Switch_f_idx_0 < 256.0F) {
    if (rtb_Switch_f_idx_0 >= 0.0F) {
      tmp = (uint8_T)rtb_Switch_f_idx_0;
    } else {
      tmp = 0U;
    }
  } else {
    tmp = MAX_uint8_T;
  }

  writeDigitalPin(8, tmp);

  /* End of MATLABSystem: '<S1>/Digital Output' */

  /* MATLABSystem: '<S1>/Digital Output1' */
  if (rtb_Switch_f_idx_0 < 256.0F) {
    if (rtb_Switch_f_idx_0 >= 0.0F) {
      tmp = (uint8_T)rtb_Switch_f_idx_0;
    } else {
      tmp = 0U;
    }
  } else {
    tmp = MAX_uint8_T;
  }

  writeDigitalPin(9, tmp);

  /* End of MATLABSystem: '<S1>/Digital Output1' */

  /* Update for Delay: '<S3>/CountWindowDelay' */
  DCMotorSpeedControl_DW.CountWindowDelay_DSTATE[0] =
    DCMotorSpeedControl_DW.CountWindowDelay_DSTATE[1];
  DCMotorSpeedControl_DW.CountWindowDelay_DSTATE[1] =
    DCMotorSpeedControl_DW.CountWindowDelay_DSTATE[2];
  DCMotorSpeedControl_DW.CountWindowDelay_DSTATE[2] =
    DCMotorSpeedControl_DW.CountWindowDelay_DSTATE[3];
  DCMotorSpeedControl_DW.CountWindowDelay_DSTATE[3] =
    DCMotorSpeedControl_DW.CountWindowDelay_DSTATE[4];
  DCMotorSpeedControl_DW.CountWindowDelay_DSTATE[4] =
    DCMotorSpeedControl_B.EncCounts;

  /* Switch: '<S32>/Switch1' incorporates:
   *  Constant: '<S32>/Clamping_zero'
   *  Constant: '<S32>/Constant'
   *  Constant: '<S32>/Constant2'
   *  RelationalOperator: '<S32>/fix for DT propagation issue'
   */
  if (rtb_DeadZone > DCMotorSpeedControl_P.Clamping_zero_Value) {
    tmp_0 = DCMotorSpeedControl_P.Constant_Value_i;
  } else {
    tmp_0 = DCMotorSpeedControl_P.Constant2_Value_g;
  }

  /* Switch: '<S32>/Switch2' incorporates:
   *  Constant: '<S32>/Clamping_zero'
   *  Constant: '<S32>/Constant3'
   *  Constant: '<S32>/Constant4'
   *  RelationalOperator: '<S32>/fix for DT propagation issue1'
   */
  if (rtb_IntegralGain > DCMotorSpeedControl_P.Clamping_zero_Value) {
    tmp_1 = DCMotorSpeedControl_P.Constant3_Value;
  } else {
    tmp_1 = DCMotorSpeedControl_P.Constant4_Value_g;
  }

  /* Switch: '<S32>/Switch' incorporates:
   *  Constant: '<S32>/Clamping_zero'
   *  Constant: '<S32>/Constant1'
   *  Logic: '<S32>/AND3'
   *  RelationalOperator: '<S32>/Equal1'
   *  RelationalOperator: '<S32>/Relational Operator'
   *  Switch: '<S32>/Switch1'
   *  Switch: '<S32>/Switch2'
   */
  if ((DCMotorSpeedControl_P.Clamping_zero_Value != rtb_DeadZone) && (tmp_0 ==
       tmp_1)) {
    rtb_IntegralGain = DCMotorSpeedControl_P.Constant1_Value;
  }

  /* Update for DiscreteIntegrator: '<S42>/Integrator' incorporates:
   *  Switch: '<S32>/Switch'
   */
  DCMotorSpeedControl_DW.Integrator_DSTATE +=
    DCMotorSpeedControl_P.Integrator_gainval * rtb_IntegralGain;

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.01, which is the step size
   * of the task. Size of "clockTick0" ensures timer will not overflow during the
   * application lifespan selected.
   */
  DCMotorSpeedControl_M->Timing.clockTick0++;
}

/* Model initialize function */
void DCMotorSpeedControl_initialize(void)
{
  /* Registration code */
  rtmSetTFinal(DCMotorSpeedControl_M, 43.0);

  /* External mode info */
  DCMotorSpeedControl_M->Sizes.checksums[0] = (975176605U);
  DCMotorSpeedControl_M->Sizes.checksums[1] = (3358836438U);
  DCMotorSpeedControl_M->Sizes.checksums[2] = (1727880747U);
  DCMotorSpeedControl_M->Sizes.checksums[3] = (2901116194U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[14];
    DCMotorSpeedControl_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = &rtAlwaysEnabled;
    systemRan[7] = &rtAlwaysEnabled;
    systemRan[8] = &rtAlwaysEnabled;
    systemRan[9] = &rtAlwaysEnabled;
    systemRan[10] = &rtAlwaysEnabled;
    systemRan[11] = &rtAlwaysEnabled;
    systemRan[12] = &rtAlwaysEnabled;
    systemRan[13] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(DCMotorSpeedControl_M->extModeInfo,
      &DCMotorSpeedControl_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(DCMotorSpeedControl_M->extModeInfo,
                        DCMotorSpeedControl_M->Sizes.checksums);
    rteiSetTFinalTicks(DCMotorSpeedControl_M->extModeInfo, 4300);
  }

  {
    int16_T i;

    /* InitializeConditions for Sum: '<S61>/FixPt Sum1' incorporates:
     *  UnitDelay: '<S60>/Output'
     */
    DCMotorSpeedControl_DW.Output_DSTATE =
      DCMotorSpeedControl_P.Output_InitialCondition;

    /* InitializeConditions for Delay: '<S3>/CountWindowDelay' */
    for (i = 0; i < 5; i++) {
      DCMotorSpeedControl_DW.CountWindowDelay_DSTATE[i] =
        DCMotorSpeedControl_P.CountWindowDelay_InitialConditi;
    }

    /* End of InitializeConditions for Delay: '<S3>/CountWindowDelay' */

    /* InitializeConditions for DiscreteIntegrator: '<S42>/Integrator' */
    DCMotorSpeedControl_DW.Integrator_DSTATE =
      DCMotorSpeedControl_P.Integrator_IC;

    /* InitializeConditions for DiscreteFilter: '<S2>/LowPass' */
    DCMotorSpeedControl_DW.LowPass_states =
      DCMotorSpeedControl_P.LowPass_InitialStates;

    /* Start for MATLABSystem: '<S3>/Encoder' */
    DCMotorSpeedControl_DW.obj_ox.Index = 0U;
    DCMotorSpeedControl_DW.obj_ox.matlabCodegenIsDeleted = false;
    DCMotorSpeedControl_DW.obj_ox.isInitialized = 1L;
    MW_EncoderSetup(2UL, 3UL, &DCMotorSpeedControl_DW.obj_ox.Index);
    DCMotorSpeedControl_DW.obj_ox.isSetupComplete = true;
    DCMotorSpeedControl_DW.obj_ox.TunablePropsChanged = false;

    /* InitializeConditions for MATLABSystem: '<S3>/Encoder' */
    MW_EncoderReset(DCMotorSpeedControl_DW.obj_ox.Index);

    /* Start for MATLABSystem: '<S1>/PWM' */
    DCMotorSpeedControl_DW.obj_a.matlabCodegenIsDeleted = false;
    DCMotorSpeedControl_DW.obj_a.isInitialized = 1L;
    DCMotorSpeedControl_DW.obj_a.PWMDriverObj.MW_PWM_HANDLE = MW_PWM_Open(10UL,
      0.0, 0.0);
    DCMotorSpeedControl_DW.obj_a.isSetupComplete = true;

    /* Start for MATLABSystem: '<S1>/PWM1' */
    DCMotorSpeedControl_DW.obj_f.matlabCodegenIsDeleted = false;
    DCMotorSpeedControl_DW.obj_f.isInitialized = 1L;
    DCMotorSpeedControl_DW.obj_f.PWMDriverObj.MW_PWM_HANDLE = MW_PWM_Open(11UL,
      0.0, 0.0);
    DCMotorSpeedControl_DW.obj_f.isSetupComplete = true;

    /* Start for MATLABSystem: '<S2>/AnalogInput_A3' */
    DCMotorSpeedControl_DW.obj_j.matlabCodegenIsDeleted = false;
    DCMotorSpeedControl_DW.obj_j.isInitialized = 1L;
    DCMotorSpeedControl_DW.obj_j.AnalogInDriverObj.MW_ANALOGIN_HANDLE =
      MW_AnalogInSingle_Open(17UL);
    DCMotorSpeedControl_DW.obj_j.isSetupComplete = true;

    /* Start for MATLABSystem: '<S1>/Digital Output' */
    DCMotorSpeedControl_DW.obj_o.matlabCodegenIsDeleted = false;
    DCMotorSpeedControl_DW.obj_o.isInitialized = 1L;
    digitalIOSetup(8, 1);
    DCMotorSpeedControl_DW.obj_o.isSetupComplete = true;

    /* Start for MATLABSystem: '<S1>/Digital Output1' */
    DCMotorSpeedControl_DW.obj.matlabCodegenIsDeleted = false;
    DCMotorSpeedControl_DW.obj.isInitialized = 1L;
    digitalIOSetup(9, 1);
    DCMotorSpeedControl_DW.obj.isSetupComplete = true;
  }
}

/* Model terminate function */
void DCMotorSpeedControl_terminate(void)
{
  /* Terminate for MATLABSystem: '<S3>/Encoder' */
  if (!DCMotorSpeedControl_DW.obj_ox.matlabCodegenIsDeleted) {
    DCMotorSpeedControl_DW.obj_ox.matlabCodegenIsDeleted = true;
    if ((DCMotorSpeedControl_DW.obj_ox.isInitialized == 1L) &&
        DCMotorSpeedControl_DW.obj_ox.isSetupComplete) {
      MW_EncoderRelease();
    }
  }

  /* End of Terminate for MATLABSystem: '<S3>/Encoder' */

  /* Terminate for MATLABSystem: '<S1>/PWM' */
  if (!DCMotorSpeedControl_DW.obj_a.matlabCodegenIsDeleted) {
    DCMotorSpeedControl_DW.obj_a.matlabCodegenIsDeleted = true;
    if ((DCMotorSpeedControl_DW.obj_a.isInitialized == 1L) &&
        DCMotorSpeedControl_DW.obj_a.isSetupComplete) {
      DCMotorSpeedControl_DW.obj_a.PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle
        (10UL);
      MW_PWM_SetDutyCycle
        (DCMotorSpeedControl_DW.obj_a.PWMDriverObj.MW_PWM_HANDLE, 0.0);
      DCMotorSpeedControl_DW.obj_a.PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle
        (10UL);
      MW_PWM_Close(DCMotorSpeedControl_DW.obj_a.PWMDriverObj.MW_PWM_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S1>/PWM' */

  /* Terminate for MATLABSystem: '<S1>/PWM1' */
  if (!DCMotorSpeedControl_DW.obj_f.matlabCodegenIsDeleted) {
    DCMotorSpeedControl_DW.obj_f.matlabCodegenIsDeleted = true;
    if ((DCMotorSpeedControl_DW.obj_f.isInitialized == 1L) &&
        DCMotorSpeedControl_DW.obj_f.isSetupComplete) {
      DCMotorSpeedControl_DW.obj_f.PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle
        (11UL);
      MW_PWM_SetDutyCycle
        (DCMotorSpeedControl_DW.obj_f.PWMDriverObj.MW_PWM_HANDLE, 0.0);
      DCMotorSpeedControl_DW.obj_f.PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle
        (11UL);
      MW_PWM_Close(DCMotorSpeedControl_DW.obj_f.PWMDriverObj.MW_PWM_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S1>/PWM1' */

  /* Terminate for MATLABSystem: '<S2>/AnalogInput_A3' */
  if (!DCMotorSpeedControl_DW.obj_j.matlabCodegenIsDeleted) {
    DCMotorSpeedControl_DW.obj_j.matlabCodegenIsDeleted = true;
    if ((DCMotorSpeedControl_DW.obj_j.isInitialized == 1L) &&
        DCMotorSpeedControl_DW.obj_j.isSetupComplete) {
      DCMotorSpeedControl_DW.obj_j.AnalogInDriverObj.MW_ANALOGIN_HANDLE =
        MW_AnalogIn_GetHandle(17UL);
      MW_AnalogIn_Close
        (DCMotorSpeedControl_DW.obj_j.AnalogInDriverObj.MW_ANALOGIN_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S2>/AnalogInput_A3' */

  /* Terminate for MATLABSystem: '<S1>/Digital Output' */
  if (!DCMotorSpeedControl_DW.obj_o.matlabCodegenIsDeleted) {
    DCMotorSpeedControl_DW.obj_o.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S1>/Digital Output' */

  /* Terminate for MATLABSystem: '<S1>/Digital Output1' */
  if (!DCMotorSpeedControl_DW.obj.matlabCodegenIsDeleted) {
    DCMotorSpeedControl_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S1>/Digital Output1' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
