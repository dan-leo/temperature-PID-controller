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
#define pin_pot_fan 1

void clear(String *str);ssss

void setup() {
	// set up the LCD's number of columns and rows:
	lcd.begin(16, 2);
	// Print a message to the LCD.
	// lcd.print("time,Traw,T,Fan%");
	Serial.begin(9600);
}

void loop() {

	// print the number of seconds since reset:
	int time_since_reset = millis() / 1000;

	int temp_raw = analogRead(pin_temp);
	// actual temp
	float temp = 0.489*temp_raw - 2;

	// potentiometer for manual fan control
	int pot_fan = analogRead(pin_pot_fan);

	// message buffers
	String msg_str = "";
	String msg_lcd = "";

	lcd.clear();

	// **************** LCD PRINTING ****************

	// set the cursor to column 0, line 1
	lcd.setCursor(0, 0);
	msg_lcd.concat(pot_fan);

	lcd.print(msg_lcd);

	// set the cursor to column 0, line 1
	lcd.setCursor(0, 1);

	msg_lcd = "";
	msg_lcd.concat(time_since_reset);
	msg_lcd.concat(' ');
	msg_lcd.concat(temp_raw);
	msg_lcd.concat(' ');
	msg_lcd.concat(temp);

	lcd.print(msg_lcd);

	// **********************************************

	// ***************** SERIAL PRINTING ************

	msg_str.concat(time_since_reset);
	msg_str.concat('\t');
	msg_str.concat(temp_raw);


	msg_str.concat('\t');
	msg_str.concat(temp);
	msg_str.concat('\t');
	msg_str.concat(pot_fan);
	msg_str.concat('\n');

	Serial.print(msg_str);

	// **********************************************

	delay(1000);
}

/*void clear(String *str){
	unsigned int i = 0;
	for (i = 0; i < str->length(); i++){
		str->setCharAt(i, ' ');
	}
}*/




