/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: DCMotorOpenLoop.h
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

#ifndef DCMotorOpenLoop_h_
#define DCMotorOpenLoop_h_
#ifndef DCMotorOpenLoop_COMMON_INCLUDES_
#define DCMotorOpenLoop_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* DCMotorOpenLoop_COMMON_INCLUDES_ */

#include "DCMotorOpenLoop_types.h"
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
  real_T Duty_pct;                     /* '<Root>/DutyLimit' */
  real_T Speed_rpm;                    /* '<S4>/CalDivide' */
  real_T Sensor_V;                     /* '<S2>/AdcToVolt' */
  real_T Current_A;                    /* '<S2>/LowPass' */
  int32_T EncCounts;                   /* '<S4>/Encoder' */
} B_DCMotorOpenLoop_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  codertarget_arduinobase_block_T obj; /* '<S1>/Digital Output1' */
  codertarget_arduinobase_block_T obj_o;/* '<S1>/Digital Output' */
  codertarget_arduinobase_inter_T obj_f;/* '<S1>/PWM1' */
  codertarget_arduinobase_inter_T obj_a;/* '<S1>/PWM' */
  codertarget_arduinobase_int_e_T obj_j;/* '<S2>/AnalogInput_A3' */
  codertarget_arduinobase_in_et_T obj_ox;/* '<S4>/Encoder' */
  real_T LowPass_states;               /* '<S2>/LowPass' */
  int32_T CountWindowDelay_DSTATE[5];  /* '<S4>/CountWindowDelay' */
  uint16_T Output_DSTATE;              /* '<S5>/Output' */
} DW_DCMotorOpenLoop_T;

/* Parameters (default storage) */
struct P_DCMotorOpenLoop_T_ {
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
                                        * Referenced by: '<S4>/CountsToRpm'
                                        */
  real_T OL_DutyGain;                  /* Variable: OL_DutyGain
                                        * Referenced by: '<Root>/DutyEnable'
                                        */
  real_T Spd_CalDivisor;               /* Variable: Spd_CalDivisor
                                        * Referenced by: '<S4>/CalDivide'
                                        */
  real_T Spd_RpmPerCount;              /* Variable: Spd_RpmPerCount
                                        * Referenced by: '<S4>/CountsToRpm'
                                        */
  real_T DutyTestSequence_OutValues[12];
                                   /* Mask Parameter: DutyTestSequence_OutValues
                                    * Referenced by: '<S3>/Lookup'
                                    */
  real_T DutyTestSequence_TimeValues[12];
                                  /* Mask Parameter: DutyTestSequence_TimeValues
                                   * Referenced by: '<S3>/Lookup'
                                   */
  uint16_T LimitedCounter_uplimit;     /* Mask Parameter: LimitedCounter_uplimit
                                        * Referenced by: '<S7>/FixPt Switch'
                                        */
  real_T Gain_Gain;                    /* Expression: 255/100
                                        * Referenced by: '<S1>/Gain'
                                        */
  real_T Gain1_Gain;                   /* Expression: -255/100
                                        * Referenced by: '<S1>/Gain1'
                                        */
  real_T SampleTimeMath_WtEt;         /* Computed Parameter: SampleTimeMath_WtEt
                                       * Referenced by: '<S3>/Sample Time Math'
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
  int32_T CountWindowDelay_InitialConditi;
                          /* Computed Parameter: CountWindowDelay_InitialConditi
                           * Referenced by: '<S4>/CountWindowDelay'
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
                                        * Referenced by: '<S7>/Constant'
                                        */
  uint16_T Output_InitialCondition;
                                  /* Computed Parameter: Output_InitialCondition
                                   * Referenced by: '<S5>/Output'
                                   */
  uint16_T FixPtConstant_Value;       /* Computed Parameter: FixPtConstant_Value
                                       * Referenced by: '<S6>/FixPt Constant'
                                       */
};

/* Real-time Model Data Structure */
struct tag_RTM_DCMotorOpenLoop_T {
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
extern P_DCMotorOpenLoop_T DCMotorOpenLoop_P;

/* Block signals (default storage) */
extern B_DCMotorOpenLoop_T DCMotorOpenLoop_B;

/* Block states (default storage) */
extern DW_DCMotorOpenLoop_T DCMotorOpenLoop_DW;

/* Model entry point functions */
extern void DCMotorOpenLoop_initialize(void);
extern void DCMotorOpenLoop_step(void);
extern void DCMotorOpenLoop_terminate(void);

/* Real-time Model object */
extern RT_MODEL_DCMotorOpenLoop_T *const DCMotorOpenLoop_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S3>/Data Type Propagation' : Unused code path elimination
 * Block '<S5>/Data Type Propagation' : Unused code path elimination
 * Block '<S6>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S7>/FixPt Data Type Duplicate1' : Unused code path elimination
 * Block '<S3>/Output' : Eliminate redundant signal conversion block
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
 * '<Root>' : 'DCMotorOpenLoop'
 * '<S1>'   : 'DCMotorOpenLoop/BTS7960_Driver'
 * '<S2>'   : 'DCMotorOpenLoop/CurrentSense'
 * '<S3>'   : 'DCMotorOpenLoop/DutyTestSequence'
 * '<S4>'   : 'DCMotorOpenLoop/EncoderSpeed'
 * '<S5>'   : 'DCMotorOpenLoop/DutyTestSequence/LimitedCounter'
 * '<S6>'   : 'DCMotorOpenLoop/DutyTestSequence/LimitedCounter/Increment Real World'
 * '<S7>'   : 'DCMotorOpenLoop/DutyTestSequence/LimitedCounter/Wrap To Zero'
 */
#endif                                 /* DCMotorOpenLoop_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
