/*
 * File: simulink_temperature_controller.c
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

/* Block states (auto storage) */
DW_simulink_temperature_contr_T simulink_temperature_control_DW;

/* Real-time model */
RT_MODEL_simulink_temperature_T simulink_temperature_control_M_;
RT_MODEL_simulink_temperature_T *const simulink_temperature_control_M =
  &simulink_temperature_control_M_;
static void rate_monotonic_scheduler(void);

/*
 *   This function updates active task flag for each subrate
 * and rate transition flags for tasks that exchange data.
 * The function assumes rate-monotonic multitasking scheduler.
 * The function must be called at model base rate so that
 * the generated code self-manages all its subrates and rate
 * transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (simulink_temperature_control_M->Timing.TaskCounters.TID[1])++;
  if ((simulink_temperature_control_M->Timing.TaskCounters.TID[1]) > 49) {/* Sample time: [0.1s, 0.0s] */
    simulink_temperature_control_M->Timing.TaskCounters.TID[1] = 0;
  }

  (simulink_temperature_control_M->Timing.TaskCounters.TID[2])++;
  if ((simulink_temperature_control_M->Timing.TaskCounters.TID[2]) > 499) {/* Sample time: [1.0s, 0.0s] */
    simulink_temperature_control_M->Timing.TaskCounters.TID[2] = 0;
  }
}

/* Model output function for TID0 */
void simulink_temperature_controller_output0(void) /* Sample time: [0.002s, 0.0s] */
{
  uint8_T rtb_SerialReceive_o1;
  int16_T rtb_SerialReceive_o2;

  {                                    /* Sample time: [0.002s, 0.0s] */
    rate_monotonic_scheduler();
  }

  /* S-Function (arduinoserialread_sfcn): '<Root>/Serial Receive' */
  Serial_read(simulink_temperature_controll_P.SerialReceive_p1,
              simulink_temperature_controll_P.SerialReceive_p2,
              &rtb_SerialReceive_o1, &rtb_SerialReceive_o2);
}

/* Model update function for TID0 */
void simulink_temperature_controller_update0(void) /* Sample time: [0.002s, 0.0s] */
{
  /* (no update code required) */
}

/* Model output function for TID1 */
void simulink_temperature_controller_output1(void) /* Sample time: [0.1s, 0.0s] */
{
  real_T rtb_PulseGenerator;
  uint8_T rtb_PulseGenerator_0;

  /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
  rtb_PulseGenerator = (simulink_temperature_control_DW.clockTickCounter <
                        simulink_temperature_controll_P.PulseGenerator_Duty) &&
    (simulink_temperature_control_DW.clockTickCounter >= 0L) ?
    simulink_temperature_controll_P.PulseGenerator_Amp : 0.0;
  if (simulink_temperature_control_DW.clockTickCounter >=
      simulink_temperature_controll_P.PulseGenerator_Period - 1.0) {
    simulink_temperature_control_DW.clockTickCounter = 0L;
  } else {
    simulink_temperature_control_DW.clockTickCounter++;
  }

  /* End of DiscretePulseGenerator: '<Root>/Pulse Generator' */

  /* DataTypeConversion: '<S1>/Data Type Conversion' */
  if (rtb_PulseGenerator < 256.0) {
    if (rtb_PulseGenerator >= 0.0) {
      rtb_PulseGenerator_0 = (uint8_T)rtb_PulseGenerator;
    } else {
      rtb_PulseGenerator_0 = 0U;
    }
  } else {
    rtb_PulseGenerator_0 = MAX_uint8_T;
  }

  /* End of DataTypeConversion: '<S1>/Data Type Conversion' */

  /* S-Function (arduinodigitaloutput_sfcn): '<S1>/Digital Output' */
  MW_digitalWrite(simulink_temperature_controll_P.DigitalOutput_pinNumber,
                  rtb_PulseGenerator_0);
}

/* Model update function for TID1 */
void simulink_temperature_controller_update1(void) /* Sample time: [0.1s, 0.0s] */
{
  /* (no update code required) */
}

/* Model output function for TID2 */
void simulink_temperature_controller_output2(void) /* Sample time: [1.0s, 0.0s] */
{
  uint16_T rtb_AnalogInput_0;
  uint8_T rtb_DataTypeConversion_0;

  /* S-Function (arduinoanaloginput_sfcn): '<Root>/Analog Input' */
  rtb_AnalogInput_0 = MW_analogRead
    (simulink_temperature_controll_P.AnalogInput_p1);

  /* S-Function (arduinoserialwrite_sfcn): '<Root>/Serial Transmit' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion'
   *  S-Function (arduinoanaloginput_sfcn): '<Root>/Analog Input'
   */
  rtb_DataTypeConversion_0 = (uint8_T)rtb_AnalogInput_0;
  Serial_write(simulink_temperature_controll_P.SerialTransmit_portNumber,
               &rtb_DataTypeConversion_0, 1UL);
}

/* Model update function for TID2 */
void simulink_temperature_controller_update2(void) /* Sample time: [1.0s, 0.0s] */
{
  /* (no update code required) */
}

/* Model initialize function */
void simulink_temperature_controller_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)simulink_temperature_control_M, 0,
                sizeof(RT_MODEL_simulink_temperature_T));

  /* states (dwork) */
  (void) memset((void *)&simulink_temperature_control_DW, 0,
                sizeof(DW_simulink_temperature_contr_T));

  /* Start for S-Function (arduinoanaloginput_sfcn): '<Root>/Analog Input' */
  MW_pinModeAnalogInput(simulink_temperature_controll_P.AnalogInput_p1);

  /* Start for S-Function (arduinodigitaloutput_sfcn): '<S1>/Digital Output' */
  MW_pinModeOutput(simulink_temperature_controll_P.DigitalOutput_pinNumber);

  /* InitializeConditions for DiscretePulseGenerator: '<Root>/Pulse Generator' */
  simulink_temperature_control_DW.clockTickCounter = 0L;
}

/* Model terminate function */
void simulink_temperature_controller_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
