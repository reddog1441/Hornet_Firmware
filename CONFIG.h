#pragma once
//-----------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------ BASE TYPES ----------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#define ENABLE	1
#define DISABLE 2

//-----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- BUILD CONFIG ---------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#define DEBUG_BUILD ENABLE

//-----------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- BOARD FEATURES --------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#if DEBUG_BUILD == ENABLE
#define DEBUG_PRINT(message) Serial.println(message);
#define TP(message) Serial.println(message);
#else
#define DEBUG_PRINT(message)
#endif

//-----------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------- GENERAL SETTINGS -------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#define C_ERROR_BUFFER 10

//-----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- ERROR CODES ----------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#define E_NULL_PTR			0x01
#define E_TIMEOUT			0x05
#define E_HARDWARE_FAILURE	0x06
#define E_INDEX_OUT_BOUNDS	0x07

//-----------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------- SCHEDULER SETTINS ------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

// THe build depends on there being this many threads and them being from 0 to C_SCHEDULER_THREAD_NUM -1 with no repeats
#define C_SCHEDULER_THREAD_NUM 2

// must be in required start order
#define C_TEST1 0
#define C_TEST2 1

//-----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- STATE SETTINGS -------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#define ST_TO_CONNECT		Connect
#define ST_TO_IDLE			Idle
#define ST_TO_TAKEOFF		TakeOff
#define ST_TO_FLIGHT		Flight
#define ST_TO_LAND			Land
#define ST_TO_EMERGENCY		Emergency
#define ST_TO_CRACH			Crash