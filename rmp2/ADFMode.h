#pragma once
/**
*  @file    AFDMode.h
*  @author  FlightSimPCB (Volker Richter)
*  @date    2017-10-31
*  @version 1.0
*
*
*  @section DESCRIPTION
*
*  ADFMode Header File
*
*  This file is part of the fspcb rmp firmware.
*/

#include "AbstractMode.h"
#include "frequencies.h"
class ADFMode :
	public AbstractMode
{
public:
	
	ADFMode(ClickEncoder *encoder, RLED led);
};

