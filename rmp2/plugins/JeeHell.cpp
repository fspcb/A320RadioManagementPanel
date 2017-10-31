/**
*  @file    JeeHell.cpp
*  @author  FlightSimPCB (Volker Richter)
*  @date    2017-10-31
*  @version 1.0
*
*
*  @section DESCRIPTION
*
*  Implementation of JeeHell plugin via serial line (deprecated)
*
*  This file is part of the fspcb rmp firmware.
*/
#include "JeeHell.h"
#include <Arduino.h>

JeeHell::JeeHell()
{
	
}

void JeeHell::OnButtonPressed(uint16_t buttonStates)
{
	//if (Serial.availableForWrite()) {
	//	
	//	Serial.write(magic, sizeof(*magic)*sizeof(uint8_t));
	//	Serial.write(RMPNum);
	//	Serial.write((uint8_t)0);
	//		 
	//	uint8_t state[2] = { (uint8_t)buttonStates, (uint8_t)(buttonStates >> 8) };

	//	Serial.write(state, 2);
	//	
	//}
}

void JeeHell::OnNewDataValue(RMode mode, String active, String stby)
{
	/*Serial.write(magic, sizeof(*magic) * sizeof(uint8_t));
	Serial.write(RMPNum);
	Serial.write((uint8_t)0);*/
}

void JeeHell::OnDataReceived(char * serial_data)
{
}
