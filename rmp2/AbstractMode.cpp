/**
*  @file    AbstractMode.cpp
*  @author  FlightSimPCB (Volker Richter)
*  @date    2017-10-31
*  @version 1.0
*
*
*  @section DESCRIPTION
*
*  Implementation of AbstractMode (base of all RMP modes)
*
*  This file is part of the fspcb rmp firmware.
*/

#include "AbstractMode.h"
#include <Arduino.h>

AbstractMode::AbstractMode(ClickEncoder *encoder)
{
	enc = encoder;
	//activeCharValue = static_cast<char *>(malloc(sizeof(char) * 8));
	//stbyCharValue = static_cast<char *>(malloc(sizeof(char) * 8));
}
void AbstractMode::initLeftRightValues()
{
	lValue = activelValue = MIN_LEFT_VALUE * LEFT_SPACING;
	rValue = activeRValue = MIN_RIGHT_VALUE * RIGHT_SPACING;
}
void AbstractMode::SetValue(int32_t value)
{
	
	if (currentMode == DMODE::LEFT)
	{
		lValue = MIN_LEFT_VALUE + (value * LEFT_SPACING);

		if(lValue > MAX_LEFT_VALUE)
		{
			enc->write(0);
			lValue = MIN_LEFT_VALUE;
		} 
		else if(lValue < MIN_LEFT_VALUE)
		{											
			enc->write(static_cast<int32_t>((MAX_LEFT_VALUE - MIN_LEFT_VALUE)/ LEFT_SPACING));
			lValue = MAX_LEFT_VALUE;
		}
		
		if (lValue != prevtlValue)
		{
			UpdateStbyValue();
			prevtlValue = lValue;
		}
	} 
	else if ( currentMode == DMODE::RIGHT)
	{
		rValue = MIN_RIGHT_VALUE + (value * RIGHT_SPACING);
	
		if (rValue > MAX_RIGHT_VALUE)
		{
			enc->write(0);
			rValue = MIN_RIGHT_VALUE;
		}
		else if (rValue < MIN_RIGHT_VALUE)
		{
			enc->write(static_cast<int32_t>((MAX_RIGHT_VALUE - MIN_RIGHT_VALUE) / RIGHT_SPACING));
			rValue = MAX_RIGHT_VALUE;
		}

		if (rValue != prevtrValue)
		{
			UpdateStbyValue();
			prevtrValue = rValue;
		}
	}


	if (ActiveValue > 100000)
	{
		transmitValue = static_cast<uint16_t>(((ActiveValue - 100000) / 10));
		ActBCDValue = ToBcd(transmitValue);
		
		transmitValue = static_cast<uint16_t>(((StbyValue - 100000) / 10));
		StbyBCDValue = ToBcd(transmitValue);
	}
}

void AbstractMode::ToggleMode()
{
	currentMode = (currentMode == DMODE::LEFT) ? DMODE::RIGHT : DMODE::LEFT;
}

int32_t AbstractMode::GetActiveValue()
{
	return ActiveValue;
}

int32_t AbstractMode::GetStbyValue()
{
	return StbyValue;
}
String AbstractMode::GetActiveCharValue()
{
	return activeCharValue;
}

String AbstractMode::GetStbyCharValue()
{
	return stbyCharValue;
}

void AbstractMode::ToggleActiveStandby()
{
	Inverted = !Inverted;
	auto t = ActiveValue;
	auto tl = lValue;
	auto tr = rValue;

	auto bcd = ActBCDValue;

	ActiveValue = StbyValue;
	StbyValue = t;

	lValue = activelValue;
	rValue = activeRValue;

	activelValue = tl;
	activeRValue = tr;
	
	ActBCDValue = StbyBCDValue;
	StbyBCDValue = bcd;

	if (currentMode == DMODE::LEFT)
	{
		enc->write(static_cast<int32_t>((lValue - MIN_LEFT_VALUE) / LEFT_SPACING));
	} else
	{
		enc->write(static_cast<int32_t>((rValue - MIN_RIGHT_VALUE) / RIGHT_SPACING));
	}
}

void AbstractMode::UpdateStbyValue()
{
	StbyValue = (int32_t)(lValue * LEFT_FACTOR + rValue);
}
void AbstractMode::SetEncoder(ClickEncoder *encoder)
{
	enc = encoder;
}
uint16_t AbstractMode::GetActiveBCDValue()
{
	
	return ActBCDValue;
}

uint16_t AbstractMode::GetStbyBCDValue()
{
	return StbyBCDValue;
}

uint16_t AbstractMode::ToBcd(uint16_t value)
{
	if (value < 0 || value > 99999999)
		return 0;
	byte ret[2];
	for (uint8_t i = 0; i < 2; i++)
	{
		ret[i] = (uint8_t)(value % 10);
		value /= 10;
		ret[i] |= (uint8_t)((value % 10) << 4);
		value /= 10;
	}
	return static_cast<uint16_t>(ret[1] << 8 | ret[0]);
}
byte AbstractMode::bcdToDec(byte val)
{
	return (val / 16) * 10 + val % 16;
}

byte AbstractMode::decToBcd(byte val)
{
	return val + 6 * (val / 10);
}