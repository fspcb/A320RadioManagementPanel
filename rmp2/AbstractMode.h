#pragma once
/**
*  @file    AbstractMode.h
*  @author  FlightSimPCB (Volker Richter)
*  @date    2017-10-31
*  @version 1.0
*
*
*  @section DESCRIPTION
*
*  Interface for all RMP modes
*
*  This file is part of the fspcb rmp firmware.
*/
#include <stdint.h>
#include "ModeInterface.h"

#define SEND_CHAR_VALUE -99999

class AbstractMode : public ModeInterface
{
public:

	int32_t LEFT_SPACING = 0;
	int32_t MIN_LEFT_VALUE = 0;
	int32_t MAX_LEFT_VALUE = 0;
	int32_t LEFT_FACTOR = 0;


	int32_t RIGHT_SPACING = 0;
	int32_t MIN_RIGHT_VALUE = 0;
	int32_t MAX_RIGHT_VALUE = 0;

	bool Inverted = false;
	bool PrefixWithZero = false;

	AbstractMode(ClickEncoder * encoder);
	void initLeftRightValues();

	virtual void SetValue(int32_t value) override;
	void ToggleMode() override;
	void ToggleActiveStandby() override;
	int32_t GetActiveValue() override;
	int32_t GetStbyValue() override;
	String GetActiveCharValue() override;
	String GetStbyCharValue() override;
	uint16_t GetActiveBCDValue() override;
	uint16_t GetStbyBCDValue() override;
	
	static uint16_t ToBcd(uint16_t value);
	static byte bcdToDec(byte val);
	static byte decToBcd(byte val);

protected:
	int32_t lValue = 0;
	int32_t rValue = 0;

	int32_t prevtlValue = 0;
	int32_t prevtrValue = 0;

	int32_t activelValue = 0;
	int32_t activeRValue = 0;

	String activeCharValue;
	String stbyCharValue;

	void UpdateStbyValue();
	void SetEncoder(ClickEncoder * encoder);
	int32_t ActiveValue = 0;
	int32_t StbyValue = 0;
	int16_t transmitValue = 0;
	int16_t ActBCDValue = 0;
	int16_t StbyBCDValue = 0;
};
