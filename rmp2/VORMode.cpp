/**
*  @file    VORMode.cpp
*  @author  FlightSimPCB (Volker Richter)
*  @date    2017-10-31
*  @version 1.0
*
*
*  @section DESCRIPTION
*
*  Implementation of VORMode
*
*  This file is part of the fspcb rmp firmware.
*/
#include "VORMode.h"

#include "VHFMode.h"

VORMode::VORMode(ClickEncoder * encoder, RLED led) : AbstractMode(encoder)
{

	LEFT_SPACING = VOR_LRANGE_SPACING;
	MIN_LEFT_VALUE = VOR_LRANGE_MIN;
	MAX_LEFT_VALUE = VOR_LRANGE_MAX;
	LEFT_FACTOR = VOR_LRANGE_FACTOR;

	RIGHT_SPACING = VOR_RRANGE_SPACING;
	MIN_RIGHT_VALUE = VOR_RRANGE_MIN;
	MAX_RIGHT_VALUE = VOR_RRANGE_MAX;
	DotPosition = VOR_DECIMAL;

	StbyValue = MIN_LEFT_VALUE * LEFT_FACTOR + MIN_RIGHT_VALUE;
	ActiveValue = MIN_LEFT_VALUE * LEFT_FACTOR + MIN_RIGHT_VALUE;

	StatusLED = led;

	Group = GROUP::NAV;
	initLeftRightValues();
}
