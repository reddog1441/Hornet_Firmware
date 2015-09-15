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


#define ENABLE_INDICATOR	ENABLE
#define ENABLE_ACC			ENABLE
#define ENABLE_MAG			ENABLE

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
// ------------------------------------------------------ COMPONENTS ----------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#if ENABLE_INDICATOR == ENABLE
#define USE_DM_INDICATOR
#endif

#if ENABLE_ACC == ENABLE
#define USE_ACC
#define USE_MPU6050
#endif

#if ENABLE_MAG == ENABLE
#define USE_MAG
#define USE_MICROMAG3
#endif

#define USER_SERIAL_COMS

//-----------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------- GENERAL SETTINGS -------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#define C_ERROR_BUFFER 10
#define C_COMS_BUFFER 10
#define C_COMS_PORT Serial
#define C_COMENCODER_SIZE 10
#define C_COMENCODER_M_SIZE 20
#define C_CONNECT_PULSE_TIME 1000
#define C_I2C_READ_WAIT 100
#define C_PITCH_ROLL_WINDOW_AVE_WIDTH 10
#define C_YAW_WINDOW_AVE_WIDTH 10
#define C_MAG_MAX_READ_TIME 150

//-----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- ERROR CODES ----------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#define E_NULL_PTR			0x01
#define E_TIMEOUT			0x05
#define E_HARDWARE_FAILURE	0x06
#define E_INDEX_OUT_BOUNDS	0x07
#define E_BUFFER_OVERFLOW   0x08
#define E_BUS_FAIL			0x09

//-----------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------- SCHEDULER SETTINS ------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

// THe build depends on there being this many threads and them being from 0 to C_SCHEDULER_THREAD_NUM -1 with no repeats
#define C_SCHEDULER_THREAD_NUM 4

// must be in required start order
#define C_SCHEDULER_INDICATOR_THREAD 0
#define C_SCHEDULER_COMENCODER_THREAD 1
#define C_SCHEDULER_ACCGYRO_THREAD 2
#define C_SCHEDULER_MAG_THREAD 3

//-----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- STATE SETTINGS -------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------


//							____________|			  Thread Priority				|_______________________
//							| State		| INDICATOR		| COM EN	|ACC	|Mag	| LIGHT	|BLINKS| RATE
//							-----------------------------------------------------------------
#define ST_TO_CONNECT		Connect,	10,				1,			0,		0,		0,		1,		1000
#define ST_TO_IDLE			Idle,		10,				1,			5,		5,		5,		2,		250
#define ST_TO_TAKEOFF		TakeOff,	10,				1,			5,		5,		10,		3,		500
#define ST_TO_FLIGHT		Flight,		10,				1,			5,		5,		15,		1,		1000
#define ST_TO_LAND			Land,		10,				1,			5,		5,		20,		1,		1000
#define ST_TO_EMERGENCY		Emergency,	10,				1,			5,		5,		21,		1,		1000
#define ST_TO_CRACH			Crash,		10,				1,			5,		5,		22,		1,		1000

//-----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- PIN SETTINGS ---------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

// dot matrix
#define CANODE_1 A6
#define CANODE_2 A5
#define CANODE_3 A4
#define CANODE_4 A3
#define CANODE_5 A2
#define CANODE_6 A1
#define CANODE_7 A0
#define CANODE_8 9
#define CANODE_9 8
#define CANODE_10 7
#define CANODE_11 6
#define CANODE_12 5
#define CANODE_13 49
#define CANODE_14 47

// mag
#define C_MAG_SSNOT 10
#define C_MAG_DRDY 11
#define C_MAG_RESET 12

//-----------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------- MESSAGE SETTINGS -------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

// outbound	 com IDS
#define MB_RAW_MAG		1
#define MB_YAW			2
#define MB_ROLL_PITCH	'p'
#define MB_RAW_ACC		'g'

// com priorities
#define C_CL			6
#define C_CL_COMS		0
#define C_CL_SYSTEM_CMD 1
#define C_CL_NAV_CMD	2
#define C_CL_NAV_INFO	3
#define C_CL_NAV_USE	4
#define C_CL_DEBUG		5

#define C_COMS_CODE_CONNECT_REQUEST 'a'
#define C_COMS_CODE_CONNECT_CONFIRM 'b'



//									_________________________________________________________________
//									| ID			| SIZE	| MONITOR	| COM PRI		| BUFFER SIZE
//									-----------------------------------------------------------------
#define MB_RAW_MAG_SETTING			MB_RAW_MAG,		3,		100,		C_CL_DEBUG,		10
#define MB_YAW_SETTINGS				MB_YAW,			1,		10,			C_CL_NAV_INFO,	10
#define MB_ROLL_PITCH_SETTINGS		MB_ROLL_PITCH,	2,		10,			C_CL_NAV_INFO,	10
#define MB_RAW_ACC_SETTINGS			MB_RAW_ACC,		6,		100,		C_CL_DEBUG,		10
