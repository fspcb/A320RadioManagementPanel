/**
*  @file    rmp.cpp
*  @author  FlightSimPCB (Volker Richter)
*  @date    2017-10-31
*  @version 1.0
*
*
*  @section DESCRIPTION
*
*  Main implementation of the rmp
*
*  This file is part of the fspcb rmp firmware.
*/
#include "rmp.h"


/// <summary>
/// Initializes a new instance of the <see cref="RMP"/> class.
/// </summary>
RMP::RMP() {
	ActiveMode = Modes[static_cast<int>(RMode::VHF1)];
	RawHID.begin(&CHID_REPORT, sizeof(CHID_REPORT));

	for (uint8_t i = 0; i < NUM_MAX; i++)
	{
		led.shutdown(i, false);
		led.setIntensity(i, LED_INTENSITY);
		led.setScanLimit(i, MAX_SCANLIMIT);
	}
};



/// <summary>
/// Initializes the ic4051.
/// </summary>
void RMP::initialize_ic4051()
{	
	pinMode(PIN_CD4051_A, OUTPUT);
    pinMode(PIN_CD4051_B, OUTPUT);
    pinMode(PIN_CD4051_C, OUTPUT);
};

/// <summary>
/// Initializes the encoder.
/// </summary>
void RMP::initialize_encoder()
{
	pinMode(PIN_ENC_B, OUTPUT);
    digitalWrite(PIN_ENC_B, LOW);

	enc.setAccelerationEnabled(true);

};

/// <summary>
/// Initializes the 74HC595.
/// </summary>
void RMP::initialize74_hc595()
{
	FastGPIO::Pin<PIN_595_SCL>::setOutput(true);
	FastGPIO::Pin<PIN_595_RCK>::setOutput(false);
	FastGPIO::Pin<PIN_595_SCK>::setOutput(false);
	FastGPIO::Pin<PIN_595_SER>::setOutput(false);
}

/// <summary>
/// Executed if a button changes its state
/// </summary>
/// <param name="btn">RButton</param>
/// <param name="state">state</param>
void RMP::on_button_state_change(const RButton btn, const uint8_t state)
{
	if(state == 1)
	{
		on_button_pressed(btn);
	} 
	else
	{
		on_button_released(btn);
	}
};
/// <summary>
/// Executed on button down
/// </summary>
/// <param name="btn">Button</param>
void RMP::on_button_pressed(const RButton btn)
{
	switch(btn)
	{
		case RButton::SWONOFF:
			
			RadioOn = false;
			led.shutdown(ACTIVE, true);
			led.shutdown(STBY, true);
			update_hid_data();
			send_hid_status();
		break;
		case RButton::MODECHANGE:
			
		ActiveMode->ToggleMode();
			break;
		case RButton::ACTSTBY:
			ActiveMode->ToggleActiveStandby();
			break;
		case RButton::NAV:
			navMode = !navMode;
			if (!navMode && ActiveMode->Group == AbstractMode::GROUP::NAV) { 
				ActiveMode = Modes[static_cast<int>(RMode::VHF1)];
			}
			break;
		case RButton::VHF1:
			if (navMode) {
				navMode = false;
			}
			ActiveMode = Modes[static_cast<int>(RMode::VHF1)];
			break;
		case RButton::VHF2:
			if (navMode) {
				navMode = false;
			}
			ActiveMode = Modes[static_cast<int>(RMode::VHF2)];
			break;
		case RButton::VHF3:
			if (navMode) {
				navMode = false;
			}
			ActiveMode = Modes[static_cast<int>(RMode::VHF3)];
			break;
		case RButton::AM:
			
			if(ActiveMode->Group == ModeInterface::GROUP::HF)
			{
				
				AMEnabled = !AMEnabled;
			} 
			else
			{
				AMEnabled = false;
			}
			break;
		case RButton::HF1:
			if (navMode) {
				navMode = false;
			}
			ActiveMode = Modes[static_cast<int>(RMode::HF1)];
			break;
		case RButton::HF2:
			if (navMode) {
				navMode = false;
			}
			ActiveMode = Modes[static_cast<int>(RMode::HF2)];
			break;
		case RButton::VOR:
			if (navMode) {
				ActiveMode = Modes[static_cast<int>(RMode::VOR)];
			}
			break;
		case RButton::MLS:
			if (navMode) {
				ActiveMode = Modes[static_cast<int>(RMode::MLS)];
			}
			break;
		case RButton::ADF:
			if (navMode) {
				ActiveMode = Modes[static_cast<int>(RMode::ADF)];
			}
			break;
		case RButton::ILS:
			if (navMode) {
				ActiveMode = Modes[static_cast<int>(RMode::ILS)];
			}
		case RButton::BFO:
			if (ActiveMode == Modes[static_cast<int>(RMode::ADF)]) {
				BFOEnabled = !BFOEnabled;
			}
			break;
		case RButton::SEL: 
			all_on(); 

			break;

	}
	if (ActiveMode->Group != ModeInterface::GROUP::HF)
	{
		AMEnabled = false;
	}
	if (ActiveMode != Modes[static_cast<int>(RMode::ADF)]) {
		BFOEnabled = false;
	}
	
	needsTransmit = true;
	rmpDirty = true;

	send_hid_status();
	dump_hid_report();
	delay(20);

}
/// <summary>
/// Executed on button release
/// </summary>
/// <param name="btn">Button</param>
void RMP::on_button_released(const RButton btn)
{
	if (btn == RButton::SWONOFF) {
		RadioOn = true;
		led.shutdown(ACTIVE, false);
		led.shutdown(STBY, false);
	
	}
	needsTransmit = true;
	rmpDirty = true;
}


/// <summary>
/// Initializes the RMP
/// </summary>
void RMP::initialize()
{
	initialize74_hc595();
    initialize_encoder();
	initialize_ic4051();
	
	all_on();
	delay(1000);
	
}

/// <summary>
/// Reads the button states via the CD4051 demultiplexer
/// </summary>
void RMP::read_button_states()
{
  for(uint8_t i=0;i<8;i++)
  {
    const bool c1 = bitRead(i,0);
    const bool c2 = bitRead(i,1);
    const bool c3 = bitRead(i,2);

    digitalWrite(PIN_CD4051_A, c1);
    digitalWrite(PIN_CD4051_B, c2);
    digitalWrite(PIN_CD4051_C, c3);


	bitWrite(ButtonStates, i, digitalRead(PIN_CD4051_INH1));
	bitWrite(ButtonStates, 8+i, digitalRead(PIN_CD4051_INH2));

	if (bitRead(PrevButtonStates, i) != bitRead(ButtonStates,i))
	{	
		on_button_state_change(static_cast<RButton>(i), bitRead(ButtonStates, i));
		PrevButtonStates = ButtonStates;
	}
	if (bitRead(PrevButtonStates, 8 + i) != bitRead(ButtonStates, 8 + i))
	{
		on_button_state_change(static_cast<RButton>(8 + i), bitRead(ButtonStates, 8 + i));
		PrevButtonStates = ButtonStates;
	}
  	
	
	
  }
  

}

/// <summary>
/// Executed by interrupt timer. Updates the encoder
/// </summary>
void RMP::timer_isr()
{
	enc.service();
}


/// <summary>
/// Arduino Loop()
/// </summary>
void RMP::loop()
{
	read_button_states();

	if (RadioOn) {
		update_encoder();
		update_display();
		update_hid_data();
	}
	else {
		all_off();
	}
}

/// <summary>
/// Sets all LEDS/Displays to on
/// </summary>
void RMP::all_on()
{
   set_all_leds(true);
   rmpDirty = true;
    
}


/// <summary>
/// Sets all LEDs/Displays to off
/// </summary>
void RMP::all_off()
{
   set_all_leds(false);
   rmpDirty = true;
}


/// <summary>
/// Sets all leds.
/// </summary>
/// <param name="enabled">on(true) or off(false)</param>
void RMP::set_all_leds(const bool enabled) {
	uint8_t i, j;

	StateLeds = (enabled) ? 0xffff : 0;
    
	for (i = 0;i < NUM_MAX; i++ ){
        if(enabled == true) {
            for(j = 0; j < 8; j++ ) {
                led.setDigit(i, j, 8, true);
            }
        } else {
            led.clearDisplay(i);
        }
    }    
}

/// <summary>
/// Clears the leds.
/// </summary>
void RMP::clear_leds()
{
	StateLeds = 0;
}

/// <summary>
/// Sets a single led on or off
/// </summary>
/// <param name="led">the led</param>
/// <param name="enable">if set to <c>true</c> [enable].</param>
void RMP::set_led(RLED led, bool enable)
{
	bitWrite(StateLeds, (uint8_t)led, enable);
}

/// <summary>
/// Updates the display.
/// </summary>
void RMP::update_display()
{
	if(!rmpDirty)
	{
		return;
	}

    for (uint8_t i = 0;i < NUM_MAX; i++ ){
        FrequencyDisplay[i].update();
    }

	clear_leds();

	set_led(RLED::NAV, navMode);
	set_led(ActiveMode->StatusLED, ON);
	set_led(RLED::AM, AMEnabled);
	set_led(RLED::BFO, BFOEnabled);
	
	FastGPIO::Pin<PIN_595_RCK>::setOutputValueLow();
	shiftOut(PIN_595_SER, PIN_595_SCK, MSBFIRST, StateLeds );
	shiftOut(PIN_595_SER, PIN_595_SCK, MSBFIRST, StateLeds >> 8);
	FastGPIO::Pin<PIN_595_RCK>::setOutputValueHigh();
	
	rmpDirty = false;

}
/// <summary>
/// Updates the hid data.
/// </summary>
void RMP::update_hid_data()
{
	CHID_REPORT.RadioEnabled = RadioOn;
	CHID_REPORT.VHF1 = (ActiveMode == Modes[static_cast<int>(RMode::VHF1)]);
	CHID_REPORT.VHF2 = (ActiveMode == Modes[static_cast<int>(RMode::VHF2)]);
	CHID_REPORT.VHF3 = (ActiveMode == Modes[static_cast<int>(RMode::VHF3)]);
	CHID_REPORT.HF1 = (ActiveMode == Modes[static_cast<int>(RMode::HF1)]);
	CHID_REPORT.HF2 = (ActiveMode == Modes[static_cast<int>(RMode::HF2)]);
	
	CHID_REPORT.VOR = (ActiveMode == Modes[static_cast<int>(RMode::VOR)]);
	CHID_REPORT.ILS = (ActiveMode == Modes[static_cast<int>(RMode::ILS)]);
	CHID_REPORT.MLS = (ActiveMode == Modes[static_cast<int>(RMode::MLS)]);
	CHID_REPORT.ADF = (ActiveMode == Modes[static_cast<int>(RMode::ADF)]);
	CHID_REPORT.BFO = BFOEnabled;
	CHID_REPORT.AM = AMEnabled;
	CHID_REPORT.NAV = navMode;

	CHID_REPORT.data[0] = lowByte(Modes[static_cast<int>(RMode::VHF1)]->GetActiveBCDValue());
	CHID_REPORT.data[1] = highByte(Modes[static_cast<int>(RMode::VHF1)]->GetActiveBCDValue());

	CHID_REPORT.data[2] = lowByte(Modes[static_cast<int>(RMode::VHF1)]->GetStbyBCDValue());
	CHID_REPORT.data[3] = highByte(Modes[static_cast<int>(RMode::VHF1)]->GetStbyBCDValue());

	CHID_REPORT.data[4] = lowByte(Modes[static_cast<int>(RMode::VHF2)]->GetActiveBCDValue());
	CHID_REPORT.data[5] = highByte(Modes[static_cast<int>(RMode::VHF2)]->GetActiveBCDValue());

	CHID_REPORT.data[6] = lowByte(Modes[static_cast<int>(RMode::VHF2)]->GetStbyBCDValue());
	CHID_REPORT.data[7] = highByte(Modes[static_cast<int>(RMode::VHF2)]->GetStbyBCDValue());

	CHID_REPORT.data[8] = lowByte(Modes[static_cast<int>(RMode::VOR)]->GetActiveBCDValue());
	CHID_REPORT.data[9] = highByte(Modes[static_cast<int>(RMode::VOR)]->GetActiveBCDValue());

	if(needsTransmit)
	{
		needsTransmit = false;
		send_hid_status();
		dump_hid_report();
	}

}
/// <summary>
/// Updates the encoder.
/// </summary>
void RMP::update_encoder()
{
	
	if((EncoderState = enc.read()) != LastEncoderState)
	{
		
		ActiveMode->SetValue(EncoderState);
		FrequencyDisplay[STBY].SetValue(ActiveMode->GetStbyValue());
		FrequencyDisplay[STBY].SetDotPosition(ActiveMode->DotPosition);
		LastEncoderState = EncoderState;	
		needsTransmit = true;
		rmpDirty = true;
	}
	
	if (needsTransmit == true) {

		if (ActiveMode->GetActiveValue() == SEND_CHAR_VALUE)
		{
			FrequencyDisplay[ACTIVE].SetValue(ActiveMode->GetActiveCharValue());
			FrequencyDisplay[ACTIVE].SetDotPosition(9);
		}
		else
		{
			FrequencyDisplay[ACTIVE].SetValue(ActiveMode->GetActiveValue());
			FrequencyDisplay[ACTIVE].SetDotPosition(ActiveMode->DotPosition);
			FrequencyDisplay[ACTIVE].ZeroPrefix = ActiveMode->PrefixWithZero;
		}

		if (ActiveMode->GetStbyValue() == SEND_CHAR_VALUE)
		{
			FrequencyDisplay[STBY].SetValue(ActiveMode->GetStbyCharValue());
			FrequencyDisplay[STBY].SetDotPosition(9);
		}
		else
		{
			FrequencyDisplay[STBY].SetValue(ActiveMode->GetStbyValue());
			FrequencyDisplay[STBY].SetDotPosition(ActiveMode->DotPosition);
			FrequencyDisplay[STBY].ZeroPrefix = ActiveMode->PrefixWithZero;
		}
	}
	
	
}


/// <summary>
/// Sends the hid status.
/// </summary>
void RMP::send_hid_status()
{
	RawHID.write((uint8_t *)&CHID_REPORT, sizeof(CHID_REPORT));
}

/// <summary>
/// Dumps the hid report.
/// </summary>
void RMP::dump_hid_report()
{
	/*Serial.print("HID REPORT (SIZE ");
	Serial.print(sizeof(CHID_REPORT));
	Serial.println(")");
	Serial.print(((uint8_t *)&CHID_REPORT)[0], 2);
	Serial.print(" | ");
	Serial.print(((uint8_t *)&CHID_REPORT)[1], 2);
	Serial.print(" ");

	for (uint8_t i = 2; i < sizeof(CHID_REPORT); i++)
	{
		Serial.print("0x");
		Serial.print(((uint8_t *)&CHID_REPORT)[i], 16);
		Serial.print(" ");
	}
	Serial.println();
	Serial.print("DISPLAY Active: ");
	Serial.print(FrequencyDisplay[ACTIVE].GetValue());
	Serial.print(" STBY: ");
	Serial.println(FrequencyDisplay[STBY].GetValue());
	*/
}
