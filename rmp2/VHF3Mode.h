#pragma once
/**
*  @file    VHF3Mode.h
*  @author  FlightSimPCB (Volker Richter)
*  @date    2017-10-31
*  @version 1.0
*
*
*  @section DESCRIPTION
*
*  VHF3Mode (acars) header file
*
*  This file is part of the fspcb rmp firmware.
*/
#include "AbstractMode.h"
#include "frequencies.h"
#include "pinout.h"

class VHF3Mode : public VHFMode
{
public:
	VHF3Mode(ClickEncoder *encoder, RLED led);

	int32_t GetActiveValue() override;
	int32_t GetStbyValue() override;
};
