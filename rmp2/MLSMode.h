#pragma once
/**
*  @file    MLSMode.h
*  @author  FlightSimPCB (Volker Richter)
*  @date    2017-10-31
*  @version 1.0
*
*
*  @section DESCRIPTION
*
*  MLSMode Header file
*
*  This file is part of the fspcb rmp firmware.
*/
#include "AbstractMode.h"
#include "frequencies.h"
class MLSMode :
	public AbstractMode
{
public:
	MLSMode(ClickEncoder *encoder, RLED led);
};

