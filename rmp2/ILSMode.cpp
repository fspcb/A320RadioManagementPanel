/**
*  @file    ILSMode.cpp
*  @author  FlightSimPCB (Volker Richter)
*  @date    2017-10-31
*  @version 1.0
*
*
*  @section DESCRIPTION
*
*  Implementation of ILSMode with course selector
*
*  This file is part of the fspcb rmp firmware.
*/
#include "ILSMode.h"

ILSMode::ILSMode(ClickEncoder * encoder, RLED led) : AbstractMode(encoder)
{

	LEFT_SPACING = ILS_LRANGE_SPACING;
	MIN_LEFT_VALUE = ILS_LRANGE_MIN;
	MAX_LEFT_VALUE = ILS_LRANGE_MAX;
	LEFT_FACTOR = ILS_LRANGE_FACTOR;

	RIGHT_SPACING = ILS_RRANGE_SPACING;
	MIN_RIGHT_VALUE = ILS_RRANGE_MIN;
	MAX_RIGHT_VALUE = ILS_RRANGE_MAX;
	DotPosition = ILS_DECIMAL;

	StbyValue = MIN_LEFT_VALUE * LEFT_FACTOR + MIN_RIGHT_VALUE;
	ActiveValue = MIN_LEFT_VALUE * LEFT_FACTOR + MIN_RIGHT_VALUE;

	StatusLED = led;
	enc->write(course);
	Group = GROUP::NAV;
	initLeftRightValues();
}

int32_t ILSMode::GetStbyValue()
{
	if (Inverted)
		return StbyValue;
	return SEND_CHAR_VALUE;
}

String ILSMode::GetStbyCharValue()
{
	sprintf(CourseTmp, "C-%03i", course);
	return String(CourseTmp);
}

void ILSMode::SetValue(int32_t value)
{
	if (Inverted) {
		AbstractMode::SetValue(value);
	}
	else {
		if (value > ILS_CRS_MAX) {
			value = ILS_CRS_MIN;
			enc->write(ILS_CRS_MIN);
		} 
		else if (value < ILS_CRS_MIN) {
			value = ILS_CRS_MAX;
			enc->write(ILS_CRS_MAX);
		}
		course = value;
	}
	
}
void ILSMode::ToggleActiveStandby()
{
	Inverted = !Inverted;
	auto t = ActiveValue;
	auto tl = lValue;
	auto tr = rValue;

	ActiveValue = StbyValue;
	StbyValue = t;

	lValue = activelValue;
	rValue = activeRValue;

	activelValue = tl;
	activeRValue = tr;

	if (Inverted) {
		
		if (currentMode == DMODE::LEFT)
		{
			enc->write(static_cast<int32_t>((lValue - MIN_LEFT_VALUE) / LEFT_SPACING));
		}
		else
		{
			enc->write(static_cast<int32_t>((rValue - MIN_RIGHT_VALUE) / RIGHT_SPACING));
		}
	}
	else {
		StbyValue = ActiveValue;
		lValue = tl;
		rValue = tr;
		enc->write(course);
	}
}
