#include "HFMode.h"
/**
*  @file    HFMode.cpp
*  @author  FlightSimPCB (Volker Richter)
*  @date    2017-10-31
*  @version 1.0
*
*
*  @section DESCRIPTION
*
*  Implementation of HFMode
*
*  This file is part of the fspcb rmp firmware.
*/
HFMode::HFMode(ClickEncoder * encoder, RLED led) : AbstractMode(encoder)
{

	 LEFT_SPACING = HF_LRANGE_SPACING;
	 MIN_LEFT_VALUE = HF_LRANGE_MIN;
	 MAX_LEFT_VALUE = HF_LRANGE_MAX;
	 LEFT_FACTOR = HF_LRANGE_FACTOR;

	 RIGHT_SPACING = HF_RRANGE_SPACING;
	 MIN_RIGHT_VALUE = HF_RRANGE_MIN;
	 MAX_RIGHT_VALUE = HF_RRANGE_MAX;
	 DotPosition = HF_DECIMAL;

	 lValue = MIN_LEFT_VALUE;
	 rValue = MIN_RIGHT_VALUE;

	 StbyValue = MIN_LEFT_VALUE * LEFT_FACTOR + MIN_RIGHT_VALUE;
	 ActiveValue = MIN_LEFT_VALUE * LEFT_FACTOR + MIN_RIGHT_VALUE;

	 StatusLED = led;
	 Group = GROUP::HF;

	 initLeftRightValues();
}
