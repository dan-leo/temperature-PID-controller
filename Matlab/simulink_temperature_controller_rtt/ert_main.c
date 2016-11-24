/*
 * File: ert_main.c
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
#include "Arduino.h"
#include "io_wrappers.h"
#define INIT_TIMER_VAL                 65411
#define SETUP_PRESCALER                TCCR1B |= ((1<<CS12)); TCCR1B &= ~((1<<CS11) | (1<<CS10))
#define INTERRUPT_VECTOR               TIMER1_OVF_vect
#define DISABLE_TIMER                  TIMSK1 &= ~(1<<TOIE1)
#define ENABLE_TIMER                   TIMSK1 |= (1<<TOIE1)
#define TIMER_NORMAL_MODE              TCCR1A &= ~((1<<WGM11) | (1<<WGM10)); TCCR1B &= ~((1<<WGM13) | (1<<WGM12))
#define RESET_TIMER                    TCNT1 = INIT_TIMER_VAL

volatile int IsrOverrun = 0;
boolean_T isRateRunning[3] = { 0, 0, 0 };

boolean_T need2runFlags[3] = { 0, 0, 0 };

/*
 * The timer interrupt handler (gets invoked on every counter overflow).
 */
ISR(INTERRUPT_VECTOR)
{
  RESET_TIMER;
  rt_OneStep();
}

/*
 * Configures the base rate interrupt timer
 */
static void arduino_Timer_Setup()
{
  // Sets up the timer overflow interrupt.
  RESET_TIMER;

  // Initially disable the overflow interrupt (before configuration).
  DISABLE_TIMER;

  // Set the timer to normal mode.
  TIMER_NORMAL_MODE;

  // Set the prescaler.
  SETUP_PRESCALER;

  // Everything configured, so enable the overflow interrupt.
  ENABLE_TIMER;
}

void rt_OneStep(void)
{
  boolean_T eventFlags[3];
  int_T i;

  /* Check base rate for overrun */
  if (isRateRunning[0]++) {
    IsrOverrun = 1;
    isRateRunning[0]--;                /* allow future iterations to succeed*/
    return;
  }

  sei();

  /*
   * For a bare-board target (i.e., no operating system), the
   * following code checks whether any subrate overruns,
   * and also sets the rates that need to run this time step.
   */
  for (i = 1; i < 3; i++) {
    eventFlags[i] = ((boolean_T)rtmStepTask(simulink_temperature_control_M, i));
  }

  simulink_temperature_controller_output0();

  /* Get model outputs here */
  simulink_temperature_controller_update0();
  cli();
  isRateRunning[0]--;
  for (i = 1; i < 3; i++) {
    if (eventFlags[i]) {
      if (need2runFlags[i]++) {
        IsrOverrun = 1;
        need2runFlags[i]--;            /* allow future iterations to succeed*/
        break;
      }
    }
  }

  for (i = 1; i < 3; i++) {
    if (isRateRunning[i]) {
      /* Yield to higher priority*/
      return;
    }

    if (need2runFlags[i]) {
      isRateRunning[i]++;
      sei();
      switch (i) {
       case 1:
        simulink_temperature_controller_output1();

        /* Get model outputs here */
        simulink_temperature_controller_update1();
        break;

       case 2:
        simulink_temperature_controller_output2();

        /* Get model outputs here */
        simulink_temperature_controller_update2();
        break;

       default:
        break;
      }

      cli();
      need2runFlags[i]--;
      isRateRunning[i]--;
    }
  }
}

int_T main(void)
{
  init();

#ifdef _RTT_USE_SERIAL0_

  Serial_begin(0, 9600);
  Serial_write(0, "***starting the model***", 26);

#endif

  simulink_temperature_controller_initialize();
  arduino_Timer_Setup();

  /* The main step loop */
  while (rtmGetErrorStatus(simulink_temperature_control_M) == (NULL)) {
  }

  simulink_temperature_controller_terminate();

  /* Disable Interrupts */
  cli();
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
