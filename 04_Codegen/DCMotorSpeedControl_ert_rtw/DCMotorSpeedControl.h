/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: DCMotorSpeedControl.h
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

#ifndef DCMotorSpeedControl_h_
#define DCMotorSpeedControl_h_
#ifndef DCMotorSpeedControl_COMMON_INCLUDES_
#define DCMotorSpeedControl_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                /* DCMotorSpeedControl_COMMON_INCLUDES_ */

#include "DCMotorSpeedControl_types.h"
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWExtModeInfo
#define rtmGetRTWExtModeInfo(rtm)      ((rtm)->extModeInfo)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                (&)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T Output;                       /* '<S5>/Output' */
  real_T Speed_rpm;                    /* '<S3>/CalDivide' */
  real_T Duty_pct;                     /* '<Root>/DutyLimit' */
  real_T Sensor_V;                     /* '<S2>/AdcToVolt' */
  real_T Current_A;                    /* '<S2>/LowPass' */
  int32_T EncCounts;                   /* '<S3>/Encoder' */
} B_DCMotorSpeedControl_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  codertarget_arduinobase_block_T obj; /* '<S1>/Digital Output1' */
  codertarget_arduinobase_block_T obj_o;/* '<S1>/Digital Output' */
  codertarget_arduinobase_inter_T obj_f;/* '<S1>/PWM1' */
  codertarget_arduinobase_inter_T obj_a;/* '<S1>/PWM' */
  codertarget_arduinobase_int_i_T obj_j;/* '<S2>/AnalogInput_A3' */
  codertarget_arduinobase_in_if_T obj_ox;/* '<S3>/Encoder' */
  real_T Integrator_DSTATE;            /* '<S42>/Integrator' */
  real_T LowPass_states;               /* '<S2>/LowPass' */
  int32_T CountWindowDelay_DSTATE[5];  /* '<S3>/CountWindowDelay' */
  uint16_T Output_DSTATE;              /* '<S60>/Output' */
} DW_DCMotorSpeedControl_T;

/* Parameters (default storage) */
struct P_DCMotorSpeedControl_T_ {
  real_T Cur_AdcFullScale;             /* Variable: Cur_AdcFullScale
                                        * Referenced by: '<S2>/AdcToVolt'
                                        */
  real_T Cur_AdcVref;                  /* Variable: Cur_AdcVref
                                        * Referenced by: '<S2>/AdcToVolt'
                                        */
  real_T Cur_FilterCoef;               /* Variable: Cur_FilterCoef
                                        * Referenced by: '<S2>/LowPass'
                                        */
  real_T Cur_Offset_V;                 /* Variable: Cur_Offset_V
                                        * Referenced by: '<S2>/RemoveOffset'
                                        */
  real_T Cur_Sensitivity;              /* Variable: Cur_Sensitivity
                                        * Referenced by: '<S2>/VoltToAmp'
                                        */
  real_T Enc_DirSign;                  /* Variable: Enc_DirSign
                                        * Referenced by: '<S3>/CountsToRpm'
                                        */
  real_T PI_Ki;                        /* Variable: PI_Ki
                                        * Referenced by: '<S39>/Integral Gain'
                                        */
  real_T PI_Kp;                        /* Variable: PI_Kp
                                        * Referenced by: '<S47>/Proportional Gain'
                                        */
  real_T PI_UMax;                      /* Variable: PI_UMax
                                        * Referenced by:
                                        *   '<S49>/Saturation'
                                        *   '<S34>/DeadZone'
                                        */
  real_T PI_UMin;                      /* Variable: PI_UMin
                                        * Referenced by:
                                        *   '<S49>/Saturation'
                                        *   '<S34>/DeadZone'
                                        */
  real_T Spd_CalDivisor;               /* Variable: Spd_CalDivisor
                                        * Referenced by: '<S3>/CalDivide'
                                        */
  real_T Spd_RpmPerCount;              /* Variable: Spd_RpmPerCount
                                        * Referenced by: '<S3>/CountsToRpm'
                                        */
  real_T SpeedReference_OutValues[22];
                                     /* Mask Parameter: SpeedReference_OutValues
                                      * Referenced by: '<S5>/Lookup'
                                      */
  real_T SpeedReference_TimeValues[22];
                                    /* Mask Parameter: SpeedReference_TimeValues
                                     * Referenced by: '<S5>/Lookup'
                                     */
  uint16_T LimitedCounter_uplimit;     /* Mask Parameter: LimitedCounter_uplimit
                                        * Referenced by: '<S62>/FixPt Switch'
                                        */
  real_T Gain_Gain;                    /* Expression: 255/100
                                        * Referenced by: '<S1>/Gain'
                                        */
  real_T Gain1_Gain;                   /* Expression: -255/100
                                        * Referenced by: '<S1>/Gain1'
                                        */
  real_T Constant1_Value;              /* Expression: 0
                                        * Referenced by: '<S32>/Constant1'
                                        */
  real_T SampleTimeMath_WtEt;         /* Computed Parameter: SampleTimeMath_WtEt
                                       * Referenced by: '<S5>/Sample Time Math'
                                       */
  real_T Integrator_gainval;           /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S42>/Integrator'
                                        */
  real_T Integrator_IC;                /* Expression: 0
                                        * Referenced by: '<S42>/Integrator'
                                        */
  real_T DutyLimit_UpperSat;           /* Expression: 100
                                        * Referenced by: '<Root>/DutyLimit'
                                        */
  real_T DutyLimit_LowerSat;           /* Expression: -100
                                        * Referenced by: '<Root>/DutyLimit'
                                        */
  real_T Switch_Threshold;             /* Expression: 0
                                        * Referenced by: '<S1>/Switch'
                                        */
  real_T LowPass_DenCoef[2];           /* Expression: [1 -(1-Cur_FilterCoef)]
                                        * Referenced by: '<S2>/LowPass'
                                        */
  real_T LowPass_InitialStates;        /* Expression: 0
                                        * Referenced by: '<S2>/LowPass'
                                        */
  real_T Clamping_zero_Value;          /* Expression: 0
                                        * Referenced by: '<S32>/Clamping_zero'
                                        */
  int32_T CountWindowDelay_InitialConditi;
                          /* Computed Parameter: CountWindowDelay_InitialConditi
                           * Referenced by: '<S3>/CountWindowDelay'
                           */
  real32_T Saturation_UpperSat;       /* Computed Parameter: Saturation_UpperSat
                                       * Referenced by: '<S1>/Saturation'
                                       */
  real32_T Saturation_LowerSat;       /* Computed Parameter: Saturation_LowerSat
                                       * Referenced by: '<S1>/Saturation'
                                       */
  real32_T Constant4_Value;            /* Computed Parameter: Constant4_Value
                                        * Referenced by: '<S1>/Constant4'
                                        */
  real32_T Constant5_Value;            /* Computed Parameter: Constant5_Value
                                        * Referenced by: '<S1>/Constant5'
                                        */
  real32_T Saturation1_UpperSat;     /* Computed Parameter: Saturation1_UpperSat
                                      * Referenced by: '<S1>/Saturation1'
                                      */
  real32_T Saturation1_LowerSat;     /* Computed Parameter: Saturation1_LowerSat
                                      * Referenced by: '<S1>/Saturation1'
                                      */
  real32_T Constant2_Value;            /* Computed Parameter: Constant2_Value
                                        * Referenced by: '<S1>/Constant2'
                                        */
  uint16_T Constant_Value;             /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S62>/Constant'
                                        */
  uint16_T Output_InitialCondition;
                                  /* Computed Parameter: Output_InitialCondition
                                   * Referenced by: '<S60>/Output'
                                   */
  uint16_T FixPtConstant_Value;       /* Computed Parameter: FixPtConstant_Value
                                       * Referenced by: '<S61>/FixPt Constant'
                                       */
  int8_T Constant_Value_i;             /* Computed Parameter: Constant_Value_i
                                        * Referenced by: '<S32>/Constant'
                                        */
  int8_T Constant2_Value_g;            /* Computed Parameter: Constant2_Value_g
                                        * Referenced by: '<S32>/Constant2'
                                        */
  int8_T Constant3_Value;              /* Computed Parameter: Constant3_Value
                                        * Referenced by: '<S32>/Constant3'
                                        */
  int8_T Constant4_Value_g;            /* Computed Parameter: Constant4_Value_g
                                        * Referenced by: '<S32>/Constant4'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_DCMotorSpeedControl_T {
  const char_T *errorStatus;
  RTWExtModeInfo *extModeInfo;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block parameters (default storage) */
extern P_DCMotorSpeedControl_T DCMotorSpeedControl_P;

/* Block signals (default storage) */
extern B_DCMotorSpeedControl_T DCMotorSpeedControl_B;

/* Block states (default storage) */
extern DW_DCMotorSpeedControl_T DCMotorSpeedControl_DW;

/* Model entry point functions */
extern void DCMotorSpeedControl_initialize(void);
extern void DCMotorSpeedControl_step(void);
extern void DCMotorSpeedControl_terminate(void);

/* Real-time Model object */
extern RT_MODEL_DCMotorSpeedControl_T *const DCMotorSpeedControl_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S5>/Data Type Propagation' : Unused code path elimination
 * Block '<S60>/Data Type Propagation' : Unused code path elimination
 * Block '<S61>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S62>/FixPt Data Type Duplicate1' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'DCMotorSpeedControl'
 * '<S1>'   : 'DCMotorSpeedControl/BTS7960_Driver'
 * '<S2>'   : 'DCMotorSpeedControl/CurrentSense'
 * '<S3>'   : 'DCMotorSpeedControl/EncoderSpeed'
 * '<S4>'   : 'DCMotorSpeedControl/PI_SpeedController'
 * '<S5>'   : 'DCMotorSpeedControl/SpeedReference'
 * '<S6>'   : 'DCMotorSpeedControl/PI_SpeedController/Anti-windup'
 * '<S7>'   : 'DCMotorSpeedControl/PI_SpeedController/D Gain'
 * '<S8>'   : 'DCMotorSpeedControl/PI_SpeedController/External Derivative'
 * '<S9>'   : 'DCMotorSpeedControl/PI_SpeedController/Filter'
 * '<S10>'  : 'DCMotorSpeedControl/PI_SpeedController/Filter ICs'
 * '<S11>'  : 'DCMotorSpeedControl/PI_SpeedController/I Gain'
 * '<S12>'  : 'DCMotorSpeedControl/PI_SpeedController/Ideal P Gain'
 * '<S13>'  : 'DCMotorSpeedControl/PI_SpeedController/Ideal P Gain Fdbk'
 * '<S14>'  : 'DCMotorSpeedControl/PI_SpeedController/Integrator'
 * '<S15>'  : 'DCMotorSpeedControl/PI_SpeedController/Integrator ICs'
 * '<S16>'  : 'DCMotorSpeedControl/PI_SpeedController/N Copy'
 * '<S17>'  : 'DCMotorSpeedControl/PI_SpeedController/N Gain'
 * '<S18>'  : 'DCMotorSpeedControl/PI_SpeedController/P Copy'
 * '<S19>'  : 'DCMotorSpeedControl/PI_SpeedController/Parallel P Gain'
 * '<S20>'  : 'DCMotorSpeedControl/PI_SpeedController/Reset Signal'
 * '<S21>'  : 'DCMotorSpeedControl/PI_SpeedController/Saturation'
 * '<S22>'  : 'DCMotorSpeedControl/PI_SpeedController/Saturation Fdbk'
 * '<S23>'  : 'DCMotorSpeedControl/PI_SpeedController/Sum'
 * '<S24>'  : 'DCMotorSpeedControl/PI_SpeedController/Sum Fdbk'
 * '<S25>'  : 'DCMotorSpeedControl/PI_SpeedController/Tracking Mode'
 * '<S26>'  : 'DCMotorSpeedControl/PI_SpeedController/Tracking Mode Sum'
 * '<S27>'  : 'DCMotorSpeedControl/PI_SpeedController/Tsamp - Integral'
 * '<S28>'  : 'DCMotorSpeedControl/PI_SpeedController/Tsamp - Ngain'
 * '<S29>'  : 'DCMotorSpeedControl/PI_SpeedController/postSat Signal'
 * '<S30>'  : 'DCMotorSpeedControl/PI_SpeedController/preInt Signal'
 * '<S31>'  : 'DCMotorSpeedControl/PI_SpeedController/preSat Signal'
 * '<S32>'  : 'DCMotorSpeedControl/PI_SpeedController/Anti-windup/Disc. Clamping Parallel'
 * '<S33>'  : 'DCMotorSpeedControl/PI_SpeedController/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S34>'  : 'DCMotorSpeedControl/PI_SpeedController/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S35>'  : 'DCMotorSpeedControl/PI_SpeedController/D Gain/Disabled'
 * '<S36>'  : 'DCMotorSpeedControl/PI_SpeedController/External Derivative/Disabled'
 * '<S37>'  : 'DCMotorSpeedControl/PI_SpeedController/Filter/Disabled'
 * '<S38>'  : 'DCMotorSpeedControl/PI_SpeedController/Filter ICs/Disabled'
 * '<S39>'  : 'DCMotorSpeedControl/PI_SpeedController/I Gain/Internal Parameters'
 * '<S40>'  : 'DCMotorSpeedControl/PI_SpeedController/Ideal P Gain/Passthrough'
 * '<S41>'  : 'DCMotorSpeedControl/PI_SpeedController/Ideal P Gain Fdbk/Disabled'
 * '<S42>'  : 'DCMotorSpeedControl/PI_SpeedController/Integrator/Discrete'
 * '<S43>'  : 'DCMotorSpeedControl/PI_SpeedController/Integrator ICs/Internal IC'
 * '<S44>'  : 'DCMotorSpeedControl/PI_SpeedController/N Copy/Disabled wSignal Specification'
 * '<S45>'  : 'DCMotorSpeedControl/PI_SpeedController/N Gain/Disabled'
 * '<S46>'  : 'DCMotorSpeedControl/PI_SpeedController/P Copy/Disabled'
 * '<S47>'  : 'DCMotorSpeedControl/PI_SpeedController/Parallel P Gain/Internal Parameters'
 * '<S48>'  : 'DCMotorSpeedControl/PI_SpeedController/Reset Signal/Disabled'
 * '<S49>'  : 'DCMotorSpeedControl/PI_SpeedController/Saturation/Enabled'
 * '<S50>'  : 'DCMotorSpeedControl/PI_SpeedController/Saturation Fdbk/Disabled'
 * '<S51>'  : 'DCMotorSpeedControl/PI_SpeedController/Sum/Sum_PI'
 * '<S52>'  : 'DCMotorSpeedControl/PI_SpeedController/Sum Fdbk/Disabled'
 * '<S53>'  : 'DCMotorSpeedControl/PI_SpeedController/Tracking Mode/Disabled'
 * '<S54>'  : 'DCMotorSpeedControl/PI_SpeedController/Tracking Mode Sum/Passthrough'
 * '<S55>'  : 'DCMotorSpeedControl/PI_SpeedController/Tsamp - Integral/TsSignalSpecification'
 * '<S56>'  : 'DCMotorSpeedControl/PI_SpeedController/Tsamp - Ngain/Passthrough'
 * '<S57>'  : 'DCMotorSpeedControl/PI_SpeedController/postSat Signal/Forward_Path'
 * '<S58>'  : 'DCMotorSpeedControl/PI_SpeedController/preInt Signal/Internal PreInt'
 * '<S59>'  : 'DCMotorSpeedControl/PI_SpeedController/preSat Signal/Forward_Path'
 * '<S60>'  : 'DCMotorSpeedControl/SpeedReference/LimitedCounter'
 * '<S61>'  : 'DCMotorSpeedControl/SpeedReference/LimitedCounter/Increment Real World'
 * '<S62>'  : 'DCMotorSpeedControl/SpeedReference/LimitedCounter/Wrap To Zero'
 */
#endif                                 /* DCMotorSpeedControl_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
