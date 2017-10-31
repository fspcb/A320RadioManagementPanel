#pragma once
/**
*  @file    display.h
*  @author  FlightSimPCB (Volker Richter)
*  @date    2017-10-31
*  @version 1.0
*
*
*  @section DESCRIPTION
*
*  Display class for 7-seg display
*
*  This file is part of the fspcb rmp firmware.
*/
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "lib/LedControl.h"
#include "config.h"

#define MAX_SCANLIMIT 6

#define ACTIVE 0
#define STBY 1



class Display
{
	private:
		String Value;
		String PreviousValue;
		String TempValue;

		
		uint8_t DotPosition = 99;
		bool needsUpdate = false;
		LedControl *led;
		uint8_t LedAddress = 0;
	
		void resetValue();

    public: 
		bool ZeroPrefix = false;
		Display();
		Display(LedControl *led, uint8_t addr);
		void SetValue(String value);
		void SetValue(unsigned long value);
		void SetValue(unsigned int value);
		void SetValue(int32_t value);
        
		String GetValue();
		
        void update();
		void SetDotPosition(uint8_t dp);
		static String padString(String val, char padChar);
};