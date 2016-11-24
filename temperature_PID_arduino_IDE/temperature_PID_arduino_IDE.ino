/*
 * temperature_PID.ino
 *
 *  Created on: 21 Nov 2016
 *      Author: d7rob
 */

// @author: Daniel Robinson

// include the library code:
#include "Arduino.h"
#include <LiquidCrystal.h>

//uncomment this to use LiquidCrystal library
//#include "libraries/LCD/LiquidCrystal.h"

#include "libraries/PID/PID_v1.h"
#include "libraries/TimerOne/TimerOne.h"

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define pin_temp 0
#define pin_pot_fan 1
#define pin_fan 6

unsigned int counter_timer1 = 0;
int pot_fan;
int time_since_reset;
int temp_raw;
float temp;
float pot_100;

double PID_Setpoint, PID_Input, PID_Output;

//Specify the links and initial tuning parameters
double Kp=50, Ki=75, Kd=1;

PID myPID(&PID_Input, &PID_Output, &PID_Setpoint, Kp, Ki, Kd, REVERSE);

//void clear(String *str);
void print_lcd();

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  // lcd.print("time,Traw,T,Fan%");
  Serial.begin(9600);

  //  timer.setInterval(1, slow_loop);

  pinMode(13, OUTPUT);

  temp_raw = analogRead(pin_temp);
  PID_Input = get_temp(temp_raw);
  PID_Setpoint = 30;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);

  Timer1.initialize(100000); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  Timer1.attachInterrupt( timerISR ); // attach the service routine here
}

void loop() {

  if (Serial.available()){
    String rx_msg = Serial.readString();
    Serial.println(rx_msg);
    String prefix = rx_msg.substring(0, 2);
    if (prefix.equals("P=")){
      Serial.println(rx_msg);
    }
//    if (rx_msg.substring(0, 2))
  }
  // delay(1000);
}

/*void clear(String *str){
  unsigned int i = 0;
  for (i = 0; i < str->length(); i++){
    str->setCharAt(i, ' ');
  }
}*/

// 1 second loop
void slow_loop(){
  lcd.clear();
  lcd.setCursor(8, 0);
  lcd.println("hello");
}

void timerISR()
{
  static int prev_pot_fan;

  // Toggle LED
  digitalWrite( 13, digitalRead( 13 ) ^ 1 );

  // doesn't works
  //  if (pot_fan - prev_pot_fan > -5){
  //    if (pot_fan - prev_pot_fan < 5){
  //      counter_timer1=1;
  //      print_lcd();
  //    }
  //  }

  prev_pot_fan = pot_fan;

  if (!counter_timer1) // basically happens every 10th count i.e. effectively 1Hz
  {
    // print the number of seconds since reset:
    time_since_reset = millis() / 1000;

    // potentiometer for manual fan control
    pot_fan = analogRead(pin_pot_fan);
    pot_fan >>= 2;
    pot_100 = pot_fan*0.392157;
    PID_Setpoint = pot_100;
    // analogWrite(pin_fan, pot_fan);



    temp_raw = analogRead(pin_temp);
    temp = get_temp(temp_raw);

    PID_Input = temp;

    myPID.Compute();

    analogWrite(pin_fan, PID_Output);


    // ** Print to LCD **
    print_lcd();

    // message buffers
    String msg_str = "";

    // ***************** SERIAL PRINTING ************

    msg_str.concat(time_since_reset);
    msg_str.concat('\t');

    //    msg_str.concat(temp_raw);
    //    msg_str.concat('\t');
    //    msg_str.concat(temp);
    //    msg_str.concat('\t');
    //    msg_str.concat(pot_fan);

    msg_str.concat(PID_Setpoint);
    msg_str.concat('\t');
    msg_str.concat(PID_Input);
    msg_str.concat('\t');
    msg_str.concat(PID_Output);
    msg_str.concat('\t');
    msg_str.concat('\n');


    Serial.print(msg_str);

    // **********************************************
  }

  counter_timer1++;
  counter_timer1 %= 10;
}

void print_lcd(){

  String msg_lcd = "";

  lcd.clear();

  // **************** LCD PRINTING ****************

  // set the cursor to column 0, line 1
  lcd.setCursor(0, 0);
  msg_lcd.concat(temp_raw);
  msg_lcd.concat(' ');
  msg_lcd.concat(PID_Setpoint);
  msg_lcd.concat(' ');
  msg_lcd.concat(PID_Output);

  lcd.print(msg_lcd);

  // set the cursor to column 0, line 1
  lcd.setCursor(0, 1);

  msg_lcd = "";
  msg_lcd.concat(time_since_reset);
  //  msg_lcd.concat(' ');
  //  msg_lcd.concat(temp_raw);
  msg_lcd.concat(' ');
  msg_lcd.concat(temp);
  msg_lcd.concat(' ');
  msg_lcd.concat(PID_Input*100/PID_Setpoint - 100);

  lcd.print(msg_lcd);

  // **********************************************
}

void step_fan(){

}

float get_temp(float temp_raw){
  // actual temp
  // ** LM35 **
//   return 0.489*temp_raw - 2;

  // ** MSC9700 **
  return 0.489*(temp_raw - 103);
}


