#pragma once
/**
*  @file    rmp.h
*  @author  FlightSimPCB (Volker Richter)
*  @date    2017-10-31
*  @version 1.0
*
*
*  @section DESCRIPTION
*
*  RMP main header file
*
*  This file is part of the fspcb rmp firmware.
*/
#include "lib/HID.h"
#include "lib/HID-Settings.h"
#include "lib/RawHID.h"

#include <stdint.h>

#include "lib/ClickEncoder.h"
#include "lib/TimerOne.h"
#include "lib/Shifty.h"
#include "lib/LedControl.h"
#include "pinout.h"
#include "frequencies.h"
#include "config.h"
#include "display.h"
#include "ModeInterface.h"
#include "FastGPIO.h"

#include "VHFMode.h"
#include "HFMode.h"
#include "VHF3Mode.h"
#include "VORMode.h"
#include "ILSMode.h"
#include "MLSMode.h"
#include "ADFMode.h"	

#include "plugins/IEventHandler.h"
#define ON true
#define OFF false


struct hidreport_t
{
	bool RadioEnabled : 1;
	bool VHF1 : 1;
	bool VHF2 : 1;
	bool VHF3 : 1;
	bool HF1 : 1;
	bool HF2 : 1;
	bool AM : 1;
	bool NAV : 1;

	bool VOR : 1;
	bool ILS : 1;
	bool MLS : 1;
	bool ADF : 1;
	bool BFO : 1;
	bool : 0;
	uint8_t data[10];
};


class RMP
{
  public:
    RMP();
 
	
    /**
    * should be called in setup() of the .ino script
    **/
    void initialize();

    /** 
    * should be called in loop() of the .ino script
    **/
    void loop();

    /** 
    * Sets all LEDs on and 7-seg to '888888' (testing)
    **/
    void all_on();

    /** 
    * switches all LEDs off and clears the 7-seg display (testing)
    **/
    void all_off();


    /**
    * Set the value of a display to the contents of value - limited by MAX_SCANLIMIT
    * display can be either ACTIVE or STBY
    **/    
	void set_led(RLED led, bool enable);

	/* should be called by the timer*/
	void timer_isr();

	
	

  private:
	/// INIT
    void initialize_encoder();
    static void initialize_ic4051();
	static void initialize74_hc595();
    
	// Button Handler
	void on_button_state_change(RButton btn, uint8_t state);
	void on_button_pressed(RButton btn);
	void on_button_released(RButton btn);
	void read_button_states();

	// LED
    void set_all_leds(bool enabled);
	void clear_leds();

	// UPDATE
    void update_display();
	void update_hid_data();
	void update_encoder();
	
	// HID
	void send_hid_status();
	static void dump_hid_report();


	// Variables
	
	/**
	 * 7-segment displays
	 */
	LedControl led = LedControl(PIN_MAX_DIN, PIN_MAX_CLK, PIN_MAX_LOAD, NUM_MAX);
  	
	/**
	 * Encoder Control
	 */
	ClickEncoder enc = ClickEncoder(PIN_ENC_A, PIN_ENC_C, 999, 4);
    

	/**
	 * the active Radio Mode
	 */
    RMode currentMode = RMode::VHF1;
    
	/**
	 * Container for ACT/STBY Displays
	 */
	Display FrequencyDisplay[2] = { {&led, ACTIVE}, {&led, STBY} };
    
	/**
	 * BitArray of the buttons
	 */
	uint16_t ButtonStates = 0;
	uint16_t PrevButtonStates = 0;

	/**
	 * Values of the Encoder
	 */
	int32_t EncoderState = 0;
	int32_t LastEncoderState = -1;


	/**
	 * Currently supported modes
	 */
	ModeInterface* Modes[9] = {
									new VHFMode(&enc, RLED::VHF1),
									new VHFMode(&enc, RLED::VHF2),
									
									new VHF3Mode(&enc,RLED::VHF3),
									new HFMode(&enc,RLED::HF1),
									new HFMode(&enc, RLED::HF2),
									new VORMode(&enc, RLED::VOR),
									new ILSMode(&enc, RLED::ILS),
									new MLSMode(&enc, RLED::MLS),
									new ADFMode(&enc, RLED::ADF)
	
	};
	
	/*
	 * Pointer to the currently selected mode
	 */
	ModeInterface *ActiveMode = nullptr;
	
	/**
	 * additional state variables for LEDs
	 */
	bool navMode = false;
	bool AMEnabled = false;
	bool BFOEnabled = false;
	bool RadioOn = true;

	/**
	 * container for HID data
	 */
	hidreport_t CHID_REPORT;

	/**
	 * Flag: HID data should be transferred
	 */
	bool needsTransmit = false;
	
	/**
	 * Flag: Something changed and the displays need to be updated
	 */
	bool rmpDirty = false;

	/**
	 * State LEDs as Bitarray
	 */
	uint16_t StateLeds = 0;
	
};

