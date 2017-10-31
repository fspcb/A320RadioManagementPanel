/**
*  @file    IEventHandler.cpp
*  @author  FlightSimPCB (Volker Richter)
*  @date    2017-10-31
*  @version 1.0
*
*
*  @section DESCRIPTION
*
*  Implementation of IEventHandler (deprecated)
*
*  This file is part of the fspcb rmp firmware.
*/
#include "IEventHandler.h"


IEventHandler::IEventHandler()
{
}

void IEventHandler::SetRMPNumber(uint8_t num)
{
	RMPNum = num;
}
