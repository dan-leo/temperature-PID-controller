/*
 * File: simulink_temperature_controller_data.c
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

#include "simulink_temperature_controller.h"
#include "simulink_temperature_controller_private.h"

/* Block parameters (auto storage) */
P_simulink_temperature_contro_T simulink_temperature_controll_P = {
  13U,                                 /* Mask Parameter: DigitalOutput_pinNumber
                                        * Referenced by: '<S1>/Digital Output'
                                        */
  0U,                                  /* Mask Parameter: SerialTransmit_portNumber
                                        * Referenced by: '<Root>/Serial Transmit'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<Root>/Pulse Generator'
                                        */
  10.0,                                /* Expression: 10
                                        * Referenced by: '<Root>/Pulse Generator'
                                        */
  5.0,                                 /* Expression: 5
                                        * Referenced by: '<Root>/Pulse Generator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Pulse Generator'
                                        */
  0U,                                  /* Computed Parameter: AnalogInput_p1
                                        * Referenced by: '<Root>/Analog Input'
                                        */
  0U,                                  /* Computed Parameter: SerialReceive_p1
                                        * Referenced by: '<Root>/Serial Receive'
                                        */
  1                                    /* Computed Parameter: SerialReceive_p2
                                        * Referenced by: '<Root>/Serial Receive'
                                        */
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
