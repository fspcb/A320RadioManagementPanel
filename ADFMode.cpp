/**
*  @file    ADFMode.cpp
*  @author  FlightSimPCB (Volker Richter)
*  @date    2017-10-31
*  @version 1.0
*
*
*  @section DESCRIPTION
*
*  Implementation of ADFMode
*
*  This file is part of the fspcb rmp firmware.
*/
#include "ADFMode.h"

ADFMode::ADFMode(ClickEncoder * encoder, RLED led) : AbstractMode(encoder)
{

	LEFT_SPACING = ADF_LRANGE_SPACING;
	MIN_LEFT_VALUE = ADF_LRANGE_MIN;
	MAX_LEFT_VALUE = ADF_LRANGE_MAX;
	LEFT_FACTOR = ADF_LRANGE_FACTOR;

	RIGHT_SPACING = ADF_RRANGE_SPACING;
	MIN_RIGHT_VALUE = ADF_RRANGE_MIN;
	MAX_RIGHT_VALUE = ADF_RRANGE_MAX;
	DotPosition = ADF_DECIMAL;
	PrefixWithZero = ADF_ZERO_PREFIX;


	StbyValue = MIN_LEFT_VALUE * LEFT_FACTOR + MIN_RIGHT_VALUE;
	ActiveValue = MIN_LEFT_VALUE * LEFT_FACTOR + MIN_RIGHT_VALUE;

	StatusLED = led;

	Group = GROUP::NAV;
	initLeftRightValues();
}
