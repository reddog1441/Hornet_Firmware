#pragma once
#include "CONFIG.h"
#include "Runnable.h"

#if ENABLE_ACC == ENABLED

#include "HornetManager.h"
#include "Error.h"
#include "SPIManager.h"
#include "I2CManager.h"
#include <stdint.h>

#include "AP_InertialSensor_MPU600xx.h"
#include "MovingAverage.h"
#include "MessageBuffer_Manager.h"

class AccGyro :public Runnable
{
public:
	AccGyro(HornetManager* theManager, Error* e, I2CManager *theI2CManager, uint8_t interruptPin);

	AccGyro(HornetManager* theManager, Error* e, SPIManager *theSPIManager, uint8_t cs_pin, uint8_t interruptPin);

	bool start();

	void run();

private:

	HornetManager* _hornetManager;
	Error* _e;


	MovingAverage<float, C_PITCH_ROLL_WINDOW_AVE_WIDTH> _pitchBuffer;
	MovingAverage<float, C_PITCH_ROLL_WINDOW_AVE_WIDTH> _rollBuffer;

	/** \brief	The message buffers for Yaw data */
	MessageBuffer_Manager<MB_ROLL_PITCH_SETTINGS> _rollPitchSender;

	/** \brief	The message buffers for raw mag data */
	MessageBuffer_Manager<MB_RAW_ACC_SETTINGS> _rawSender;


	AP_InertialSensor_MPU600xx _ins;
};
#else

class AccGyro:public Runnable
{
public:
	AccGyro(){}
	void start(){}
	void run(){}
};

#endif
