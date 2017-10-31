/**
*  @file    VHF3Mode.cpp
*  @author  FlightSimPCB (Volker Richter)
*  @date    2017-10-31
*  @version 1.0
*
*
*  @section DESCRIPTION
*
*  Implementation of VHF3 Mode
*
*  This file is part of the fspcb rmp firmware.
*/
#include "VHFMode.h"
#include "VHF3Mode.h"

VHF3Mode::VHF3Mode(ClickEncoder * encoder, RLED led) : VHFMode(encoder, led)
{
	StbyValue = MIN_LEFT_VALUE * LEFT_FACTOR + MIN_RIGHT_VALUE;
	ActiveValue = SEND_CHAR_VALUE;

	this->activeCharValue = F("ACARS ");
	this->stbyCharValue = F("ACARS ");

	StatusLED = led;

	initLeftRightValues();
}

int32_t VHF3Mode::GetActiveValue()
{
	if(Inverted)
	{
		return ActiveValue;
	}
	return SEND_CHAR_VALUE;
}
int32_t VHF3Mode::GetStbyValue()
{
	if (!Inverted)
	{
		return StbyValue;
	}
	return SEND_CHAR_VALUE;
}

