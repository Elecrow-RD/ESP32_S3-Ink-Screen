/*****************************************************************************
* | File      	:	Debug.h
* | Author      :   Waveshare team
* | Function    :	debug with printf
* | Info        :
*   Image scanning
*      Please use progressive scanning to generate images or fonts
*----------------
* |	This version:   V1.0
* | Date        :   2018-01-11
* | Info        :   Basic version
*
******************************************************************************/
#ifndef __DEBUG_H
#define __DEBUG_H

#include <arduino.h>
#include <Wire.h>


#define USE_DEBUG 1
#if USE_DEBUG
	#define DEBUG(__info) Serial.print(__info)
#else
	#define DEBUG(__info)  
#endif

#endif

