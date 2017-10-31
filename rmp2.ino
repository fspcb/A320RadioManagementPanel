/**
*  @file    rmp2.ino
*  @author  FlightSimPCB (Volker Richter)
*  @date    2017-10-31
*  @version 1.0
*
*
*  @section DESCRIPTION
*
*  Arduino file for firmware upload
*
*  This file is part of the fspcb rmp firmware.
*/

#include "rmp.h"

RMP *rmp = nullptr;
void timerISR();

void setup() 
{
	rmp = new RMP();
	rmp->initialize();

	Timer1.initialize(1000);
	Timer1.attachInterrupt(timerISR);
}

void loop() 
{
	rmp->loop();
}

void timerISR()
{	
	rmp->timer_isr();	
}