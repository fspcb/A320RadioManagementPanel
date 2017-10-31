#pragma once
/**
*  @file    HFMode.h
*  @author  FlightSimPCB (Volker Richter)
*  @date    2017-10-31
*  @version 1.0
*
*
*  @section DESCRIPTION
*
*  HFMode Header file
*
*  This file is part of the fspcb rmp firmware.
*/
#include "AbstractMode.h"
#include "frequencies.h"
#include "pinout.h"

class HFMode : public AbstractMode
{
public:
	HFMode(ClickEncoder *encoder, RLED led);
};
