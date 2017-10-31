#pragma once
/**
*  @file    IEventHandler.h
*  @author  FlightSimPCB (Volker Richter)
*  @date    2017-10-31
*  @version 1.0
*
*
*  @section DESCRIPTION
*
*  Interface for all sim plugins
*
*  This file is part of the fspcb rmp firmware.
*  @deprecated
*/
#include <WString.h>
#include "../pinout.h"


class IEventHandler
{
public:
	IEventHandler();

	void SetRMPNumber(uint8_t num = 1);
	virtual void OnButtonPressed(uint16_t buttonStates);
	virtual void OnNewDataValue(RMode mode, String active, String stby);

	virtual void OnDataReceived(char *serial_data);
protected:
	uint8_t RMPNum = 1;


};

