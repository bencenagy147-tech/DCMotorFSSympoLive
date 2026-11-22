/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: DCMotorOpenLoop.c
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
#include "MW_PWM.h"
#include "MW_ArduinoEncoder.h"
#include "MW_AnalogIn.h"
#include "MW_arduino_digitalio.h"
#include "DCMotorOpenLoop_private.h"
#include "rtwtypes.h"
#include <math.h>

/* Block signals (default storage) */
B_DCMotorOpenLoop_T DCMotorOpenLoop_B;

/* Block states (default storage) */
DW_DCMotorOpenLoop_T DCMotorOpenLoop_DW;

/* Real-time model */
static RT_MODEL_DCMotorOpenLoop_T DCMotorOpenLoop_M_;
RT_MODEL_DCMotorOpenLoop_T *const DCMotorOpenLoop_M = &DCMotorOpenLoop_M_;
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
void DCMotorOpenLoop_step(void)
{
  real_T y;
  real32_T rtb_Switch_idx_0;
  real32_T rtb_Switch_idx_1;
  uint16_T b_varargout_1;
  uint8_T tmp;

  /* Gain: '<Root>/DutyEnable' incorporates:
   *  DataTypeConversion: '<S3>/Data Type Conversion'
   *  Lookup_n-D: '<S3>/Lookup'
   *  SampleTimeMath: '<S3>/Sample Time Math'
   *  UnitDelay: '<S5>/Output'
   *
   * About '<S3>/Sample Time Math':
   *  y = u * K where K = ( w * Ts )
   *   */
  DCMotorOpenLoop_B.Duty_pct =
    DCMotorOpenLoop_P.DutyTestSequence_OutValues[plook_u32d_bincka((real_T)
    DCMotorOpenLoop_DW.Output_DSTATE * DCMotorOpenLoop_P.SampleTimeMath_WtEt,
    DCMotorOpenLoop_P.DutyTestSequence_TimeValues, 11UL)] *
    DCMotorOpenLoop_P.OL_DutyGain;

  /* Saturate: '<Root>/DutyLimit' */
  if (DCMotorOpenLoop_B.Duty_pct > DCMotorOpenLoop_P.DutyLimit_UpperSat) {
    /* Gain: '<Root>/DutyEnable' incorporates:
     *  Saturate: '<Root>/DutyLimit'
     */
    DCMotorOpenLoop_B.Duty_pct = DCMotorOpenLoop_P.DutyLimit_UpperSat;
  } else if (DCMotorOpenLoop_B.Duty_pct < DCMotorOpenLoop_P.DutyLimit_LowerSat)
  {
    /* Gain: '<Root>/DutyEnable' incorporates:
     *  Saturate: '<Root>/DutyLimit'
     */
    DCMotorOpenLoop_B.Duty_pct = DCMotorOpenLoop_P.DutyLimit_LowerSat;
  }

  /* End of Saturate: '<Root>/DutyLimit' */

  /* Switch: '<S1>/Switch' incorporates:
   *  Constant: '<S1>/Constant4'
   *  Constant: '<S1>/Constant5'
   */
  if (DCMotorOpenLoop_B.Duty_pct > DCMotorOpenLoop_P.Switch_Threshold) {
    /* Gain: '<S1>/Gain' */
    rtb_Switch_idx_0 = (real32_T)(DCMotorOpenLoop_P.Gain_Gain *
      DCMotorOpenLoop_B.Duty_pct);

    /* Saturate: '<S1>/Saturation' */
    if (rtb_Switch_idx_0 > DCMotorOpenLoop_P.Saturation_UpperSat) {
      rtb_Switch_idx_0 = DCMotorOpenLoop_P.Saturation_UpperSat;
    } else if (rtb_Switch_idx_0 < DCMotorOpenLoop_P.Saturation_LowerSat) {
      rtb_Switch_idx_0 = DCMotorOpenLoop_P.Saturation_LowerSat;
    }

    /* End of Saturate: '<S1>/Saturation' */
    rtb_Switch_idx_1 = DCMotorOpenLoop_P.Constant4_Value;
  } else {
    rtb_Switch_idx_0 = DCMotorOpenLoop_P.Constant5_Value;

    /* Gain: '<S1>/Gain1' incorporates:
     *  Constant: '<S1>/Constant5'
     */
    rtb_Switch_idx_1 = (real32_T)(DCMotorOpenLoop_P.Gain1_Gain *
      DCMotorOpenLoop_B.Duty_pct);

    /* Saturate: '<S1>/Saturation1' */
    if (rtb_Switch_idx_1 > DCMotorOpenLoop_P.Saturation1_UpperSat) {
      rtb_Switch_idx_1 = DCMotorOpenLoop_P.Saturation1_UpperSat;
    } else if (rtb_Switch_idx_1 < DCMotorOpenLoop_P.Saturation1_LowerSat) {
      rtb_Switch_idx_1 = DCMotorOpenLoop_P.Saturation1_LowerSat;
    }

    /* End of Saturate: '<S1>/Saturation1' */
  }

  /* End of Switch: '<S1>/Switch' */

  /* MATLABSystem: '<S1>/PWM' */
  DCMotorOpenLoop_DW.obj_a.PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle(10UL);
  if (rtb_Switch_idx_1 <= 255.0F) {
    y = rtb_Switch_idx_1;
  } else {
    y = 255.0;
  }

  if (!(y >= 0.0)) {
    y = 0.0;
  }

  MW_PWM_SetDutyCycle(DCMotorOpenLoop_DW.obj_a.PWMDriverObj.MW_PWM_HANDLE, y);

  /* End of MATLABSystem: '<S1>/PWM' */

  /* MATLABSystem: '<S1>/PWM1' */
  DCMotorOpenLoop_DW.obj_f.PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle(11UL);
  if (rtb_Switch_idx_0 <= 255.0F) {
    y = rtb_Switch_idx_0;
  } else {
    y = 255.0;
  }

  if (!(y >= 0.0)) {
    y = 0.0;
  }

  MW_PWM_SetDutyCycle(DCMotorOpenLoop_DW.obj_f.PWMDriverObj.MW_PWM_HANDLE, y);

  /* End of MATLABSystem: '<S1>/PWM1' */

  /* MATLABSystem: '<S4>/Encoder' */
  if (DCMotorOpenLoop_DW.obj_ox.TunablePropsChanged) {
    DCMotorOpenLoop_DW.obj_ox.TunablePropsChanged = false;
  }

  /* MATLABSystem: '<S4>/Encoder' */
  MW_EncoderRead(DCMotorOpenLoop_DW.obj_ox.Index, &DCMotorOpenLoop_B.EncCounts);

  /* Gain: '<S4>/CalDivide' incorporates:
   *  DataTypeConversion: '<S4>/ToDouble'
   *  Delay: '<S4>/CountWindowDelay'
   *  Gain: '<S4>/CountsToRpm'
   *  Sum: '<S4>/DeltaCount'
   */
  DCMotorOpenLoop_B.Speed_rpm = DCMotorOpenLoop_P.Spd_RpmPerCount *
    DCMotorOpenLoop_P.Enc_DirSign * (real_T)(DCMotorOpenLoop_B.EncCounts -
    DCMotorOpenLoop_DW.CountWindowDelay_DSTATE[0]) * (1.0 /
    DCMotorOpenLoop_P.Spd_CalDivisor);

  /* MATLABSystem: '<S2>/AnalogInput_A3' */
  DCMotorOpenLoop_DW.obj_j.AnalogInDriverObj.MW_ANALOGIN_HANDLE =
    MW_AnalogIn_GetHandle(17UL);
  MW_AnalogInSingle_ReadResult
    (DCMotorOpenLoop_DW.obj_j.AnalogInDriverObj.MW_ANALOGIN_HANDLE,
     &b_varargout_1, MW_ANALOGIN_UINT16);

  /* Gain: '<S2>/AdcToVolt' incorporates:
   *  DataTypeConversion: '<S2>/ToDouble'
   *  MATLABSystem: '<S2>/AnalogInput_A3'
   * */
  DCMotorOpenLoop_B.Sensor_V = DCMotorOpenLoop_P.Cur_AdcVref /
    DCMotorOpenLoop_P.Cur_AdcFullScale * (real_T)b_varargout_1;

  /* DiscreteFilter: '<S2>/LowPass' incorporates:
   *  Bias: '<S2>/RemoveOffset'
   *  Gain: '<S2>/VoltToAmp'
   */
  DCMotorOpenLoop_DW.LowPass_states = (1.0 / DCMotorOpenLoop_P.Cur_Sensitivity *
    (DCMotorOpenLoop_B.Sensor_V - DCMotorOpenLoop_P.Cur_Offset_V) -
    DCMotorOpenLoop_P.LowPass_DenCoef[1L] * DCMotorOpenLoop_DW.LowPass_states) /
    DCMotorOpenLoop_P.LowPass_DenCoef[0];

  /* DiscreteFilter: '<S2>/LowPass' */
  DCMotorOpenLoop_B.Current_A = DCMotorOpenLoop_P.Cur_FilterCoef *
    DCMotorOpenLoop_DW.LowPass_states;

  /* Sum: '<S6>/FixPt Sum1' incorporates:
   *  Constant: '<S6>/FixPt Constant'
   *  UnitDelay: '<S5>/Output'
   */
  DCMotorOpenLoop_DW.Output_DSTATE += DCMotorOpenLoop_P.FixPtConstant_Value;

  /* Switch: '<S7>/FixPt Switch' */
  if (DCMotorOpenLoop_DW.Output_DSTATE >
      DCMotorOpenLoop_P.LimitedCounter_uplimit) {
    /* Sum: '<S6>/FixPt Sum1' incorporates:
     *  Constant: '<S7>/Constant'
     */
    DCMotorOpenLoop_DW.Output_DSTATE = DCMotorOpenLoop_P.Constant_Value;
  }

  /* End of Switch: '<S7>/FixPt Switch' */

  /* MATLABSystem: '<S1>/Digital Output' incorporates:
   *  Constant: '<S1>/Constant2'
   */
  rtb_Switch_idx_0 = rt_roundf_snf(DCMotorOpenLoop_P.Constant2_Value);
  if (rtb_Switch_idx_0 < 256.0F) {
    if (rtb_Switch_idx_0 >= 0.0F) {
      tmp = (uint8_T)rtb_Switch_idx_0;
    } else {
      tmp = 0U;
    }
  } else {
    tmp = MAX_uint8_T;
  }

  writeDigitalPin(8, tmp);

  /* End of MATLABSystem: '<S1>/Digital Output' */

  /* MATLABSystem: '<S1>/Digital Output1' */
  if (rtb_Switch_idx_0 < 256.0F) {
    if (rtb_Switch_idx_0 >= 0.0F) {
      tmp = (uint8_T)rtb_Switch_idx_0;
    } else {
      tmp = 0U;
    }
  } else {
    tmp = MAX_uint8_T;
  }

  writeDigitalPin(9, tmp);

  /* End of MATLABSystem: '<S1>/Digital Output1' */

  /* Update for Delay: '<S4>/CountWindowDelay' */
  DCMotorOpenLoop_DW.CountWindowDelay_DSTATE[0] =
    DCMotorOpenLoop_DW.CountWindowDelay_DSTATE[1];
  DCMotorOpenLoop_DW.CountWindowDelay_DSTATE[1] =
    DCMotorOpenLoop_DW.CountWindowDelay_DSTATE[2];
  DCMotorOpenLoop_DW.CountWindowDelay_DSTATE[2] =
    DCMotorOpenLoop_DW.CountWindowDelay_DSTATE[3];
  DCMotorOpenLoop_DW.CountWindowDelay_DSTATE[3] =
    DCMotorOpenLoop_DW.CountWindowDelay_DSTATE[4];
  DCMotorOpenLoop_DW.CountWindowDelay_DSTATE[4] = DCMotorOpenLoop_B.EncCounts;

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.01, which is the step size
   * of the task. Size of "clockTick0" ensures timer will not overflow during the
   * application lifespan selected.
   */
  DCMotorOpenLoop_M->Timing.clockTick0++;
}

/* Model initialize function */
void DCMotorOpenLoop_initialize(void)
{
  /* Registration code */
  rtmSetTFinal(DCMotorOpenLoop_M, 23.0);

  /* External mode info */
  DCMotorOpenLoop_M->Sizes.checksums[0] = (2126752927U);
  DCMotorOpenLoop_M->Sizes.checksums[1] = (4066823873U);
  DCMotorOpenLoop_M->Sizes.checksums[2] = (1798091070U);
  DCMotorOpenLoop_M->Sizes.checksums[3] = (3039797589U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[10];
    DCMotorOpenLoop_M->extModeInfo = (&rt_ExtModeInfo);
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
    rteiSetModelMappingInfoPtr(DCMotorOpenLoop_M->extModeInfo,
      &DCMotorOpenLoop_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(DCMotorOpenLoop_M->extModeInfo,
                        DCMotorOpenLoop_M->Sizes.checksums);
    rteiSetTFinalTicks(DCMotorOpenLoop_M->extModeInfo, 2300);
  }

  {
    int16_T i;

    /* InitializeConditions for Sum: '<S6>/FixPt Sum1' incorporates:
     *  UnitDelay: '<S5>/Output'
     */
    DCMotorOpenLoop_DW.Output_DSTATE = DCMotorOpenLoop_P.Output_InitialCondition;

    /* InitializeConditions for Delay: '<S4>/CountWindowDelay' */
    for (i = 0; i < 5; i++) {
      DCMotorOpenLoop_DW.CountWindowDelay_DSTATE[i] =
        DCMotorOpenLoop_P.CountWindowDelay_InitialConditi;
    }

    /* End of InitializeConditions for Delay: '<S4>/CountWindowDelay' */

    /* InitializeConditions for DiscreteFilter: '<S2>/LowPass' */
    DCMotorOpenLoop_DW.LowPass_states = DCMotorOpenLoop_P.LowPass_InitialStates;

    /* Start for MATLABSystem: '<S1>/PWM' */
    DCMotorOpenLoop_DW.obj_a.matlabCodegenIsDeleted = false;
    DCMotorOpenLoop_DW.obj_a.isInitialized = 1L;
    DCMotorOpenLoop_DW.obj_a.PWMDriverObj.MW_PWM_HANDLE = MW_PWM_Open(10UL, 0.0,
      0.0);
    DCMotorOpenLoop_DW.obj_a.isSetupComplete = true;

    /* Start for MATLABSystem: '<S1>/PWM1' */
    DCMotorOpenLoop_DW.obj_f.matlabCodegenIsDeleted = false;
    DCMotorOpenLoop_DW.obj_f.isInitialized = 1L;
    DCMotorOpenLoop_DW.obj_f.PWMDriverObj.MW_PWM_HANDLE = MW_PWM_Open(11UL, 0.0,
      0.0);
    DCMotorOpenLoop_DW.obj_f.isSetupComplete = true;

    /* Start for MATLABSystem: '<S4>/Encoder' */
    DCMotorOpenLoop_DW.obj_ox.Index = 0U;
    DCMotorOpenLoop_DW.obj_ox.matlabCodegenIsDeleted = false;
    DCMotorOpenLoop_DW.obj_ox.isInitialized = 1L;
    MW_EncoderSetup(2UL, 3UL, &DCMotorOpenLoop_DW.obj_ox.Index);
    DCMotorOpenLoop_DW.obj_ox.isSetupComplete = true;
    DCMotorOpenLoop_DW.obj_ox.TunablePropsChanged = false;

    /* InitializeConditions for MATLABSystem: '<S4>/Encoder' */
    MW_EncoderReset(DCMotorOpenLoop_DW.obj_ox.Index);

    /* Start for MATLABSystem: '<S2>/AnalogInput_A3' */
    DCMotorOpenLoop_DW.obj_j.matlabCodegenIsDeleted = false;
    DCMotorOpenLoop_DW.obj_j.isInitialized = 1L;
    DCMotorOpenLoop_DW.obj_j.AnalogInDriverObj.MW_ANALOGIN_HANDLE =
      MW_AnalogInSingle_Open(17UL);
    DCMotorOpenLoop_DW.obj_j.isSetupComplete = true;

    /* Start for MATLABSystem: '<S1>/Digital Output' */
    DCMotorOpenLoop_DW.obj_o.matlabCodegenIsDeleted = false;
    DCMotorOpenLoop_DW.obj_o.isInitialized = 1L;
    digitalIOSetup(8, 1);
    DCMotorOpenLoop_DW.obj_o.isSetupComplete = true;

    /* Start for MATLABSystem: '<S1>/Digital Output1' */
    DCMotorOpenLoop_DW.obj.matlabCodegenIsDeleted = false;
    DCMotorOpenLoop_DW.obj.isInitialized = 1L;
    digitalIOSetup(9, 1);
    DCMotorOpenLoop_DW.obj.isSetupComplete = true;
  }
}

/* Model terminate function */
void DCMotorOpenLoop_terminate(void)
{
  /* Terminate for MATLABSystem: '<S1>/PWM' */
  if (!DCMotorOpenLoop_DW.obj_a.matlabCodegenIsDeleted) {
    DCMotorOpenLoop_DW.obj_a.matlabCodegenIsDeleted = true;
    if ((DCMotorOpenLoop_DW.obj_a.isInitialized == 1L) &&
        DCMotorOpenLoop_DW.obj_a.isSetupComplete) {
      DCMotorOpenLoop_DW.obj_a.PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle
        (10UL);
      MW_PWM_SetDutyCycle(DCMotorOpenLoop_DW.obj_a.PWMDriverObj.MW_PWM_HANDLE,
                          0.0);
      DCMotorOpenLoop_DW.obj_a.PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle
        (10UL);
      MW_PWM_Close(DCMotorOpenLoop_DW.obj_a.PWMDriverObj.MW_PWM_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S1>/PWM' */

  /* Terminate for MATLABSystem: '<S1>/PWM1' */
  if (!DCMotorOpenLoop_DW.obj_f.matlabCodegenIsDeleted) {
    DCMotorOpenLoop_DW.obj_f.matlabCodegenIsDeleted = true;
    if ((DCMotorOpenLoop_DW.obj_f.isInitialized == 1L) &&
        DCMotorOpenLoop_DW.obj_f.isSetupComplete) {
      DCMotorOpenLoop_DW.obj_f.PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle
        (11UL);
      MW_PWM_SetDutyCycle(DCMotorOpenLoop_DW.obj_f.PWMDriverObj.MW_PWM_HANDLE,
                          0.0);
      DCMotorOpenLoop_DW.obj_f.PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle
        (11UL);
      MW_PWM_Close(DCMotorOpenLoop_DW.obj_f.PWMDriverObj.MW_PWM_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S1>/PWM1' */

  /* Terminate for MATLABSystem: '<S4>/Encoder' */
  if (!DCMotorOpenLoop_DW.obj_ox.matlabCodegenIsDeleted) {
    DCMotorOpenLoop_DW.obj_ox.matlabCodegenIsDeleted = true;
    if ((DCMotorOpenLoop_DW.obj_ox.isInitialized == 1L) &&
        DCMotorOpenLoop_DW.obj_ox.isSetupComplete) {
      MW_EncoderRelease();
    }
  }

  /* End of Terminate for MATLABSystem: '<S4>/Encoder' */

  /* Terminate for MATLABSystem: '<S2>/AnalogInput_A3' */
  if (!DCMotorOpenLoop_DW.obj_j.matlabCodegenIsDeleted) {
    DCMotorOpenLoop_DW.obj_j.matlabCodegenIsDeleted = true;
    if ((DCMotorOpenLoop_DW.obj_j.isInitialized == 1L) &&
        DCMotorOpenLoop_DW.obj_j.isSetupComplete) {
      DCMotorOpenLoop_DW.obj_j.AnalogInDriverObj.MW_ANALOGIN_HANDLE =
        MW_AnalogIn_GetHandle(17UL);
      MW_AnalogIn_Close
        (DCMotorOpenLoop_DW.obj_j.AnalogInDriverObj.MW_ANALOGIN_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S2>/AnalogInput_A3' */

  /* Terminate for MATLABSystem: '<S1>/Digital Output' */
  if (!DCMotorOpenLoop_DW.obj_o.matlabCodegenIsDeleted) {
    DCMotorOpenLoop_DW.obj_o.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S1>/Digital Output' */

  /* Terminate for MATLABSystem: '<S1>/Digital Output1' */
  if (!DCMotorOpenLoop_DW.obj.matlabCodegenIsDeleted) {
    DCMotorOpenLoop_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S1>/Digital Output1' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
