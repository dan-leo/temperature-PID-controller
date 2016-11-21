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
#include <time.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define pin_temp 0

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("time,Traw,T,Fan%");
  Serial.begin(9600);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  int time_since_reset = millis() / 1000;

  int temp_raw = analogRead(pin_temp);
  float temp = 0.489*temp_raw - 2;

  String msg_str = "";
  String msg_lcd = "";
  msg_str.concat(time_since_reset);
  msg_lcd.concat(time_since_reset);
  msg_str.concat('\t');
  msg_lcd.concat(' ');
  msg_str.concat(temp_raw);
  msg_lcd.concat(temp_raw);
  msg_str.concat('\t');
  msg_lcd.concat(' ');
  msg_str.concat(temp);
  msg_lcd.concat(temp);
  msg_str.concat('\n');

  lcd.print(msg_lcd);
  Serial.print(msg_str);

  delay(1000);
}




