/**
*  @file    display.cpp
*  @author  FlightSimPCB (Volker Richter)
*  @date    2017-10-31
*  @version 1.0
*
*
*  @section DESCRIPTION
*
*  Implementation of 7-seg Display
*
*  This file is part of the fspcb rmp firmware.
*/
#include "display.h"

Display::Display()
{
	TempValue = String("      ");
	Value = String("      ");
	PreviousValue = String("      ");
	
}
Display::Display(LedControl *led, uint8_t addr)
{
	Display();
	this->led = led;
	LedAddress = addr;
	
	
}

void Display::SetValue(unsigned long value)
{

	TempValue = String(value);
	SetValue(TempValue);
}
void Display::SetValue(unsigned int value) 
{

	TempValue = String(value);
	SetValue(TempValue);
}
void Display::SetValue(int32_t value)
{

	SetValue(String(static_cast<uint32_t>(value)));
}

void Display::SetValue(String value)
{
	
	if(value != Value)
	{
		Value = value;
		needsUpdate = true;
	}
    
}
String Display::GetValue()
{
	return Value;
}
void Display::resetValue()
{
	//Value = "      ";

}
void Display::update()
{
	
	
	if (needsUpdate == false)
    {
        return;
    }
	Value = padString(Value, (ZeroPrefix ? '0' : ' '));

	needsUpdate = false;
	uint8_t pos = 0;
	for(uint8_t i = 0; i < MAX_SCANLIMIT; i++)
	{
		this->led->setChar(LedAddress, i, Value[pos++], (i == DotPosition));
	}
	
	needsUpdate = false;
}

void Display::SetDotPosition(uint8_t dp)
{
	DotPosition = dp;
}

String Display::padString(String val, char padChar)
{
	while(val.length() < MAX_SCANLIMIT)
	{
		val = String(padChar + val);
	}
	return val;
}

