#pragma once
#include <Arduino.h>

//-----------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------ BASE TYPES ----------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#define ENABLE	1
#define DISABLE 2

#define XBEE	1
#define SERIAL	2

//-----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- BUILD CONFIG ---------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#define DEBUG_BUILD			ENABLE

#define ENABLE_INDICATOR	ENABLE
#define ENABLE_GYRO			ENABLE
#define	ENABLE_LIDAR		ENABLE

#define COM_MODE			SERIAL

//-----------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- BOARD FEATURES --------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#if DEBUG_BUILD == ENABLE

#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINTLN(x) Serial.println(x)
#define TP(message) Serial.println(message);

#else

#define DEBUG_PRINT(x)
#define DEBUG_PRINTLN(x)

#endif

//-----------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------ COMPONENTS ----------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

#if ENABLE_INDICATOR == ENABLE
	//#define USE_DM_INDICATOR
	#define USE_RBG_INDICATOR
#endif

#if ENABLE_GYRO == ENABLE
	#define USE_GYRO
	#define USE_MPU6050
#endif

#if ENABLE_LIDAR == ENABLE
	#define  USE_LIDAR
#endif

#if COM_MODE == XBEE
	#define COM_SERIAL		XBEE_SERIAL
#endif
#if COM_MODE == SERIAL
	#define COM_SERIAL		Serial
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
#define E_BUFFER_OVERFLOW   0x08
#define E_BUS_FAIL			0x09
#define E_PACKET_CORRUPTION	0x0A

//-----------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------- SCHEDULER SETTINS ------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

// The build depends on there being this many threads and them being from 0 to C_SCHEDULER_THREAD_NUM -1 with no repeats
#define C_SCHEDULER_THREAD_NUM 5

// must be in required start order
#define C_SCHEDULER_INDICATOR_THREAD 0
#define C_SCHEDULER_COMENCODER_THREAD 1
#define C_SCHEDULER_GYRO_THREAD 2
#define C_SCHEDULER_FLIGHT_THREAD 3
#define C_SCHEDULER_LIDAR_THREAD 4

//-----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- STATE SETTINGS -------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------


//							____________|			  Thread Priority						|_______________________
//							| State		| INDICATOR		| COM EN	|GYRO	|FLIGHT	|LIDAR	| LIGHT	|BLINKS| RATE
//							-----------------------------------------------------------------
#define ST_TO_CONNECT		Connect,	10,				1,			0,		5,		1,		0,		1,		1000
#define ST_TO_IDLE			Idle,		10,				1,			5,		5,		1,		1,		2,		250
#define ST_TO_TAKEOFF		TakeOff,	10,				1,			5,		5,		1,		3,		3,		100
#define ST_TO_FLIGHT		Flight,		10,				1,			5,		5,		1,		2,		1,		1000
#define ST_TO_LAND			Land,		10,				1,			5,		5,		1,		3,		4,		100
#define ST_TO_EMERGENCY		Emergency,	10,				1,			5,		5,		1,		3,		1,		1000
#define ST_TO_CRACH			Crash,		10,				1,			5,		5,		1,		3,		1,		1000

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

// RBG indicator
#define RBG_GREEN 53
#define RBG_RED 51
#define RBG_BLUE 49

// APM conections
#define C_APM_ROLL		10
#define C_APM_PITCH		11
#define C_APM_THROTTLE	12
#define C_APM_YAW		13

// Coms
#define XBEE_SERIAL		Serial1

// LIDAR
#define C_LIDAR_SERIAL	Serial2


//-----------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------- MESSAGE SETTINGS -------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

// inbound
#define MB_INBOUND_COUNT	4		// must match the numebr of packets!!
#define MB_INBOUND_OFFSET	100		// must match the lowest ID

#define MB_JOY_XY			100
#define MB_JOY_THROTTLE		101
#define MB_JOY_Z			102
#define MB_ARM_DISARM		103

// outbound
#define MB_OUTBOUND_COUTN	3		// must match the numebr of packets!!
#define MB_OUTBOUND_OFFSET	1		// must match the lowest ID

#define MB_ROLL_PITCH_YAW	1
#define MB_STATUS			2
#define MB_LAST_LIDAR		3

