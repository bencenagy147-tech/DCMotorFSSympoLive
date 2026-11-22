/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: DCMotorSpeedControl_private.h
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

#ifndef DCMotorSpeedControl_private_h_
#define DCMotorSpeedControl_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "DCMotorSpeedControl_types.h"
#include "DCMotorSpeedControl.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmSetTFinal
#define rtmSetTFinal(rtm, val)         ((rtm)->Timing.tFinal = (val))
#endif

extern real32_T rt_roundf_snf(real32_T u);
extern uint32_T plook_u32d_bincka(real_T u, const real_T bp[], uint32_T maxIndex);
extern uint32_T binsearch_u32d(real_T u, const real_T bp[], uint32_T startIndex,
  uint32_T maxIndex);

#endif                                 /* DCMotorSpeedControl_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
