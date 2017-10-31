#pragma once
/**
*  @file    ILSMode.h
*  @author  FlightSimPCB (Volker Richter)
*  @date    2017-10-31
*  @version 1.0
*
*
*  @section DESCRIPTION
*
*  ILSMode Header file
*
*  This file is part of the fspcb rmp firmware.
*/
#include "AbstractMode.h"
#include "frequencies.h"

class ILSMode :
	public AbstractMode
{
public:
	ILSMode(ClickEncoder *encoder, RLED led);
	char CourseTmp[7];

	int32_t GetStbyValue() override;
	String GetStbyCharValue() override;
	void SetValue(int32_t value) override;
	void ToggleActiveStandby() override;
private: 
	uint16_t course = 0;
};

