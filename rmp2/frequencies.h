#pragma once
/**
*  @file    frequencies.h
*  @author  FlightSimPCB (Volker Richter)
*  @date    2017-10-31
*  @version 1.0
*
*
*  @section DESCRIPTION
*
*  Frequency ranges for all modes
*
*  This file is part of the fspcb rmp firmware.
*/


// VHF

#define VHF_LRANGE_MIN 118
#define VHF_LRANGE_MAX 136
#define VHF_LRANGE_SPACING 1
#define VHF_LRANGE_FACTOR 1000

#define VHF_RRANGE_MIN 0
#define VHF_RRANGE_MAX 975
#define VHF_RRANGE_SPACING 25

#define VHF_SPACING 25
#define VHF_DECIMAL 2

// HF

#define HF_LRANGE_MIN 2
#define HF_LRANGE_MAX 24
#define HF_LRANGE_SPACING 1
#define HF_LRANGE_FACTOR 1000

#define HF_RRANGE_MIN 0
#define HF_RRANGE_MAX 999
#define HF_RRANGE_SPACING 1

#define HF_DECIMAL 2

// VOR

#define VOR_LRANGE_MIN 108
#define VOR_LRANGE_MAX 117
#define VOR_LRANGE_SPACING 1
#define VOR_LRANGE_FACTOR 1000

#define VOR_RRANGE_MIN 0
#define VOR_RRANGE_MAX 999
#define VOR_RRANGE_SPACING 50
#define VOR_DECIMAL 2

// ILS 

#define ILS_LRANGE_MIN 108
#define ILS_LRANGE_MAX 111
#define ILS_LRANGE_SPACING 1
#define ILS_LRANGE_FACTOR 1000

#define ILS_RRANGE_MIN 0
#define ILS_RRANGE_MAX 950
#define ILS_RRANGE_SPACING 50
#define ILS_DECIMAL 2

#define ILS_CRS_MIN 0
#define ILS_CRS_MAX 359

// MLS

#define MLS_LRANGE_MIN 5
#define MLS_LRANGE_MAX 5
#define MLS_LRANGE_SPACING 1
#define MLS_LRANGE_FACTOR 1000

#define MLS_RRANGE_MIN 310
#define MLS_RRANGE_MAX 907
#define MLS_RRANGE_SPACING 1
#define MLS_DECIMAL 2

// ADF

#define ADF_LRANGE_MIN 190
#define ADF_LRANGE_MAX 1750
#define ADF_LRANGE_SPACING 1
#define ADF_LRANGE_FACTOR 100

#define ADF_RRANGE_MIN 0
#define ADF_RRANGE_MAX 0
#define ADF_RRANGE_SPACING 0
#define ADF_DECIMAL 3
#define ADF_ZERO_PREFIX 1






