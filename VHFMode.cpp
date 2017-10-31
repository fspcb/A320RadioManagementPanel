/**
*  @file    VHFMode.cpp
*  @author  FlightSimPCB (Volker Richter)
*  @date    2017-10-31
*  @version 1.0
*
*
*  @section DESCRIPTION
*
*  Implementation of VHFMode
*
*  This file is part of the fspcb rmp firmware.
*/
#include "VHFMode.h"

VHFMode::VHFMode(ClickEncoder * encoder, RLED led) : AbstractMode(encoder)
{

	 LEFT_SPACING = VHF_LRANGE_SPACING;
	 MIN_LEFT_VALUE = VHF_LRANGE_MIN;
	 MAX_LEFT_VALUE = VHF_LRANGE_MAX;
	 LEFT_FACTOR = VHF_LRANGE_FACTOR;

	 RIGHT_SPACING = VHF_RRANGE_SPACING;
	 MIN_RIGHT_VALUE = VHF_RRANGE_MIN;
	 MAX_RIGHT_VALUE = VHF_RRANGE_MAX;
	 DotPosition = VHF_DECIMAL;

	 StbyValue = MIN_LEFT_VALUE * LEFT_FACTOR + MIN_RIGHT_VALUE;
	 ActiveValue = MIN_LEFT_VALUE * LEFT_FACTOR + MIN_RIGHT_VALUE;

	 StatusLED = led;

	 Group = GROUP::VHF;
	 initLeftRightValues();
}
