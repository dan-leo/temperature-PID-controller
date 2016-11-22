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

#include <time.h>
#include "libraries/PID/PID_v1.h"
//#include "libraries/Timer/Timer.h"
#include "libraries/SimpleTimer/SimpleTimer.h"
#include "libraries/TimerOne/TimerOne.h"

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define pin_temp 0
#define pin_pot_fan 1
#define pin_fan 6

SimpleTimer timer;

unsigned int counter_timer1 = 0;
int pot_fan;
int time_since_reset;
int temp_raw;
float temp;

//void clear(String *str);
void print_lcd();

void setup() {
	// set up the LCD's number of columns and rows:
	lcd.begin(16, 2);
	// Print a message to the LCD.
	// lcd.print("time,Traw,T,Fan%");
	Serial.begin(9600);

	//	timer.setInterval(1, slow_loop);

	pinMode(13, OUTPUT);

	Timer1.initialize(100000); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
	Timer1.attachInterrupt( timerISR ); // attach the service routine here
}

void loop() {

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

	// potentiometer for manual fan control
	pot_fan = analogRead(pin_pot_fan);
	pot_fan>>=2;
	analogWrite(pin_fan, pot_fan);

	// doesn't works
//	if (pot_fan - prev_pot_fan > -5){
//		if (pot_fan - prev_pot_fan < 5){
//			counter_timer1=1;
//			print_lcd();
//		}
//	}

	prev_pot_fan = pot_fan;

	if (!counter_timer1)
	{
		// print the number of seconds since reset:
		time_since_reset = millis() / 1000;

		temp_raw = analogRead(pin_temp);

		// actual temp

		// ** LM35 **
		// temp = 0.489*temp_raw - 2;

		// ** MSC9700 **
		temp = 0.489*(temp_raw - 103);

		// ** Print to LCD **
		print_lcd();

		// message buffers
		String msg_str = "";

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
	msg_lcd.concat(pot_fan);
	msg_lcd.concat(' ');
	msg_lcd.concat(pot_fan*0.392157);
	msg_lcd.concat('%');

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

}

