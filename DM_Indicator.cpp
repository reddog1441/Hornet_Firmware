#include "DM_Indicator.h"

// rows on = HIGH
//comul on = LOW

#ifdef USE_DM_INDICATOR
#include "arduino.h"



//-----------------------------------------------------------------------------------------------------------------------------

Indicator::Indicator(Error *e)
{
	_e = e;

}

bool Indicator::start()
{
	for (int i = 0; i < (NUM_ROWS); i++)
	{
		pinMode(ROWS[i], OUTPUT);
		digitalWrite(ROWS[i], ROW_OFF);
	}

	for (int i = 0; i < (NUM_COLLUNS); i++)
	{
		pinMode(COLUMNS[i], OUTPUT);
		digitalWrite(COLUMNS[i], COLUMNS_OFF);
	}

	pinMode(CANODE_4, OUTPUT);
	pinMode(CANODE_5, OUTPUT);

	_setting_1 = 0;
	_setting_2 = 0;
	_blinks = 0;
	_rate = 500;

	//safeOff();
	_sequenceGenerator.set(500, 0, 0);	//default is solid on
	return true;
}

//-----------------------------------------------------------------------------------------------------------------------------

void Indicator::reset()
{
	/*for (int i = 0; i < (NUM_ROWS-1); i++)
	{
		digitalWrite(ROWS[i], ROW_OFF);
	}

	for (int i = 0; i < (NUM_COLLUNS - 1); i++)
	{
		digitalWrite(COLUMNS[i], COLUMNS_OFF);
	}

	_isOn = false;

	_blinks = 1;
	_rate = 1000;
	_setting_1 = 0;
	_setting_2 = 0;

	_isBreak = false;
	_pinIsOn = false;*/
}

//-----------------------------------------------------------------------------------------------------------------------------

void Indicator::on()
{
	_sequenceGenerator.set(_rate, _blinks, 3);	//reset
	_isOn = true;
	if (_sequenceGenerator.isHigh())
	{
		lightOn(_setting_1, _setting_2);
	}
	else
	{
		lightOff(_setting_1, _setting_2);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

void Indicator::off()
{
	_isOn = false;
	lightOff(_setting_1, _setting_2);
}

//-----------------------------------------------------------------------------------------------------------------------------

void Indicator::setDisplay(int setting_1, int setting_2, int blinks, int rate)
{
	if (setting_1 < 0 || setting_1 >= MATRIX_SIZE || setting_2 < 0 || setting_2 >= MATRIX_SIZE)
	{
		_e->add(E_INDEX_OUT_BOUNDS, __LINE__);
		return;
	}

	// reset
	lightOff(_setting_1, _setting_2);
	_sequenceGenerator.set(rate, blinks, 3);

	_setting_1 = setting_1;
	_setting_2 = setting_2;
	_blinks = blinks;
	_rate = rate;

	if (_isOn)
	{
		if (_sequenceGenerator.isHigh())
		{
			lightOn(_setting_1, _setting_2);
		}
		else
		{
			lightOff(_setting_1, _setting_2);
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

void Indicator::run()
{
	if (_isOn)
	{
		if (_sequenceGenerator.run())
		{
			if (_sequenceGenerator.isHigh())
			{
				lightOn(_setting_1, _setting_2);
			}
			else
			{
				lightOff(_setting_1, _setting_2);
			}
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

void Indicator::safeOn()
{
	digitalWrite(ROWS[4], ROW_ON);
	digitalWrite(COLUMNS[6], COLUMNS_ON);
}

//-----------------------------------------------------------------------------------------------------------------------------

void Indicator::safeOff()
{
	digitalWrite(ROWS[4], ROW_OFF);
	digitalWrite(COLUMNS[6], COLUMNS_OFF);
}

//-----------------------------------------------------------------------------------------------------------------------------

void Indicator::lightOn(int setting_1, int setting_2)
{
	// asume that settings are valid as they are gate checked by setParam

	digitalWrite(ROWS[setting_1%(NUM_ROWS-1)], ROW_ON);
	digitalWrite(COLUMNS[setting_1 / (NUM_ROWS - 1)], COLUMNS_ON);
	digitalWrite(ROWS[setting_2 % (NUM_ROWS - 1)], ROW_ON);
	digitalWrite(COLUMNS[setting_2 / (NUM_ROWS - 1)], COLUMNS_ON);
}

//-----------------------------------------------------------------------------------------------------------------------------

void Indicator::lightOff(int setting_1, int setting_2)
{
	digitalWrite(ROWS[setting_1 % (NUM_ROWS - 1)], ROW_OFF);
	digitalWrite(COLUMNS[setting_1 / (NUM_ROWS - 1)], COLUMNS_OFF);
	digitalWrite(ROWS[setting_2 % (NUM_ROWS - 1)], ROW_OFF);
	digitalWrite(COLUMNS[setting_2 / (NUM_ROWS - 1)], COLUMNS_OFF);
}

#endif


// row col
/*
const int SETTING_MAP[][4] = {
{ 0, 0, 0, 0 },
{ 1, 0, 1, 0 },
{ 2, 0, 2, 0 },
{ 3, 0, 3, 0 },
{ 0, 1, 0, 1 },
{ 1, 1, 1, 1 },
{ 2, 1, 2, 1 },
{ 3, 1, 3, 1 },
{ 0, 2, 0, 2 },
{ 1, 2, 1, 2 },
{ 2, 2, 2, 2 },
{ 3, 2, 3, 2 },
{ 0, 3, 0, 3 },
{ 1, 3, 1, 3 },
{ 2, 3, 2, 3 },
{ 3, 3, 3, 3 },
{ 0, 4, 0, 4 },
{ 1, 4, 1, 4 },
{ 2, 4, 2, 4 },
{ 3, 4, 3, 4 },
{ 0, 0, 0, 0 },
{ 1, 0, 1, 0 },
{ 2, 0, 2, 0 },
{ 3, 0, 3, 0 },
{ 0, 0, 0, 0 },
{ 0, 0, 1, 1 } ,
{ 0, 0, 2, 2 } ,
{ 0, 0, 3, 3 } };*/