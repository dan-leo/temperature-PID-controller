/*
 * File: simulink_temperature_controller.h
 *
 * Code generated for Simulink model 'simulink_temperature_controller'.
 *
 * Model version                  : 1.2
 * Simulink Coder version         : 8.8 (R2015a) 09-Feb-2015
 * TLC version                    : 8.8 (Jan 20 2015)
 * C/C++ source code generated on : Thu Nov 24 16:20:07 2016
 *
 * Target selection: realtime.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_simulink_temperature_controller_h_
#define RTW_HEADER_simulink_temperature_controller_h_
#include <string.h>
#include <stddef.h>
#ifndef simulink_temperature_controller_COMMON_INCLUDES_
# define simulink_temperature_controller_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "arduino_analoginput_lct.h"
#include "arduino_serialwrite_lct.h"
#include "arduino_digitaloutput_lct.h"
#include "arduino_serialread_lct.h"
#endif                                 /* simulink_temperature_controller_COMMON_INCLUDES_ */

#include "simulink_temperature_controller_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmStepTask
# define rtmStepTask(rtm, idx)         ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

#ifndef rtmTaskCounter
# define rtmTaskCounter(rtm, idx)      ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  int32_T clockTickCounter;            /* '<Root>/Pulse Generator' */
} DW_simulink_temperature_contr_T;

/* Parameters (auto storage) */
struct P_simulink_temperature_contro_T_ {
  uint32_T DigitalOutput_pinNumber;    /* Mask Parameter: DigitalOutput_pinNumber
                                        * Referenced by: '<S1>/Digital Output'
                                        */
  uint32_T SerialTransmit_portNumber;  /* Mask Parameter: SerialTransmit_portNumber
                                        * Referenced by: '<Root>/Serial Transmit'
                                        */
  real_T PulseGenerator_Amp;           /* Expression: 1
                                        * Referenced by: '<Root>/Pulse Generator'
                                        */
  real_T PulseGenerator_Period;        /* Expression: 10
                                        * Referenced by: '<Root>/Pulse Generator'
                                        */
  real_T PulseGenerator_Duty;          /* Expression: 5
                                        * Referenced by: '<Root>/Pulse Generator'
                                        */
  real_T PulseGenerator_PhaseDelay;    /* Expression: 0
                                        * Referenced by: '<Root>/Pulse Generator'
                                        */
  uint32_T AnalogInput_p1;             /* Computed Parameter: AnalogInput_p1
                                        * Referenced by: '<Root>/Analog Input'
                                        */
  uint32_T SerialReceive_p1;           /* Computed Parameter: SerialReceive_p1
                                        * Referenced by: '<Root>/Serial Receive'
                                        */
  boolean_T SerialReceive_p2;          /* Computed Parameter: SerialReceive_p2
                                        * Referenced by: '<Root>/Serial Receive'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_simulink_temperature__T {
  const char_T * volatile errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    struct {
      uint16_T TID[3];
    } TaskCounters;
  } Timing;
};

/* Block parameters (auto storage) */
extern P_simulink_temperature_contro_T simulink_temperature_controll_P;

/* Block states (auto storage) */
extern DW_simulink_temperature_contr_T simulink_temperature_control_DW;

/* Model entry point functions */
extern void simulink_temperature_controller_initialize(void);
extern void simulink_temperature_controller_output0(void);
extern void simulink_temperature_controller_update0(void);
extern void simulink_temperature_controller_output1(void);
extern void simulink_temperature_controller_update1(void);
extern void simulink_temperature_controller_output2(void);
extern void simulink_temperature_controller_update2(void);
extern void simulink_temperature_controller_terminate(void);

/* Real-time Model object */
extern RT_MODEL_simulink_temperature_T *const simulink_temperature_control_M;

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
 * '<Root>' : 'simulink_temperature_controller'
 * '<S1>'   : 'simulink_temperature_controller/Digital Output'
 */
#endif                                 /* RTW_HEADER_simulink_temperature_controller_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
