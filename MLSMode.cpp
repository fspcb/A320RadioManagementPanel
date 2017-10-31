/**
*  @file    MLSMode.cpp
*  @author  FlightSimPCB (Volker Richter)
*  @date    2017-10-31
*  @version 1.0
*
*
*  @section DESCRIPTION
*
*  Implementation of MLSMode
*
*  This file is part of the fspcb rmp firmware.
*/
#include "MLSMode.h"

MLSMode::MLSMode(ClickEncoder * encoder, RLED led) : AbstractMode(encoder)
{

	LEFT_SPACING = MLS_LRANGE_SPACING;
	MIN_LEFT_VALUE = MLS_LRANGE_MIN;
	MAX_LEFT_VALUE = MLS_LRANGE_MAX;
	LEFT_FACTOR = MLS_LRANGE_FACTOR;

	RIGHT_SPACING = MLS_RRANGE_SPACING;
	MIN_RIGHT_VALUE = MLS_RRANGE_MIN;
	MAX_RIGHT_VALUE = MLS_RRANGE_MAX;
	DotPosition = MLS_DECIMAL;

	StbyValue = MIN_LEFT_VALUE * LEFT_FACTOR + MIN_RIGHT_VALUE;
	ActiveValue = MIN_LEFT_VALUE * LEFT_FACTOR + MIN_RIGHT_VALUE;

	StatusLED = led;

	Group = GROUP::NAV;
	initLeftRightValues();
}