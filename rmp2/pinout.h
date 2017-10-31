#pragma once
/**
*  @file    pinout.h
*  @author  FlightSimPCB (Volker Richter)
*  @date    2017-10-31
*  @version 1.0
*
*
*  @section DESCRIPTION
*
*  Arduino pin configuration
*
*  This file is part of the fspcb rmp firmware.
*/

#define PIN_CD4051_A 4
#define PIN_CD4051_B 2
#define PIN_CD4051_C 3
#define PIN_CD4051_INH1 14
#define PIN_CD4051_INH2 A0

#define PIN_595_RCK 5
#define PIN_595_SCL 7
#define PIN_595_SCK 9
#define PIN_595_SER 16
#define NUM_595 2

#define PIN_MAX_LOAD 6
#define PIN_MAX_CLK 8
#define PIN_MAX_DIN 10
#define NUM_MAX 2

#define PIN_ENC_A A1
#define PIN_ENC_B 20
#define PIN_ENC_C A3


enum class RLED : uint8_t { NIL1, BFO, ADF, MLS, ILS, NIL3 , NILX, NILX2, HF1, VHF3, VHF2, VHF1, VOR, NAV, AM, HF2 };
enum class RButton : uint8_t { VHF2, VHF1, SEL, SWONOFF, HF2, NAV, AM, VHF3, MODECHANGE, ACTSTBY, BFO, ILS, MLS, ADF, VOR, HF1 };
enum class RMode : uint8_t { VHF1, VHF2, VHF3, HF1, HF2, VOR, ILS, MLS, ADF, BFO };