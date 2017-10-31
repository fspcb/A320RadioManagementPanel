#pragma once
/**
*  @file    VHFMode.h
*  @author  FlightSimPCB (Volker Richter)
*  @date    2017-10-31
*  @version 1.0
*
*
*  @section DESCRIPTION
*
*  VHFMode header file
*
*  This file is part of the fspcb rmp firmware.
*/
#include "AbstractMode.h"
#include "frequencies.h"
#include "pinout.h"

class VHFMode : public AbstractMode
{
public:
	VHFMode(ClickEncoder *encoder, RLED led);
};
