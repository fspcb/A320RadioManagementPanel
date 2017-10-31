#pragma once
/**
*  @file    JeeHell.h
*  @author  FlightSimPCB (Volker Richter)
*  @date    2017-10-31
*  @version 1.0
*
*
*  @section DESCRIPTION
*
*  JeeHell plugin header file
*  @deprecated
*  This file is part of the fspcb rmp firmware.
*/
#include "IEventHandler.h"

class JeeHell : public IEventHandler
{	
	uint8_t magic[3] = { 0xff, 0xfa, 0x02 };
	
public:
	JeeHell();
	void OnButtonPressed(uint16_t buttonStates);
	void OnNewDataValue(RMode mode, String active, String stby);

	void OnDataReceived(char *serial_data);
};