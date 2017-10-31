#pragma once
/**
*  @file    ModeInterface.h
*  @author  FlightSimPCB (Volker Richter)
*  @date    2017-10-31
*  @version 1.0
*
*
*  @section DESCRIPTION
*
*  Interface for RMP modes
*
*  This file is part of the fspcb rmp firmware.
*/
#include "pinout.h"
#include "lib/ClickEncoder.h"
#include <WString.h>
class ModeInterface
{
public:
	enum DMODE { LEFT, RIGHT };
	enum GROUP { NONE, VHF, HF, NAV};

	bool NavLedEnabled = false;
	uint8_t DotPosition = 0;
	DMODE currentMode = DMODE::RIGHT;
	RLED StatusLED ;
	ClickEncoder *enc = nullptr;
	bool Inverted = false;
	bool PrefixWithZero = false;
	
	GROUP Group = GROUP::NONE;

	virtual void SetValue(int32_t value);
	virtual int32_t GetActiveValue();
	virtual int32_t GetStbyValue();
	virtual String GetActiveCharValue();
	virtual String GetStbyCharValue();
	virtual uint16_t GetActiveBCDValue();
	virtual uint16_t GetStbyBCDValue();

	virtual void ToggleMode();
	virtual void ToggleActiveStandby();
};
