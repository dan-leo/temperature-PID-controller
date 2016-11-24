/*
 * functions.c
 *
 *  Created on: 23 Nov 2016
 *      Author: d7rob
 */

#include "functions.h"


float get_temp(float temp_raw){
	// actual temp
	// ** LM35 **
//	 return 0.489*temp_raw - 2;

	// ** MSC9700 **
	return 0.489*(temp_raw - 103);
}
