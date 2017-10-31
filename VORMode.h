#pragma once
/**
*  @file    VorMode.h
*  @author  FlightSimPCB (Volker Richter)
*  @date    2017-10-31
*  @version 1.0
*
*
*  @section DESCRIPTION
*
*  VORMode header file
*
*  This file is part of the fspcb rmp firmware.
*/
#include "AbstractMode.h"
#include "frequencies.h"
#include "pinout.h"

class VORMode :	public AbstractMode
{
public:
	VORMode(ClickEncoder *encoder, RLED led);
};

