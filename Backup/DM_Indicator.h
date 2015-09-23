#pragma once
#include "CONFIG.h"

#ifdef USE_DM_INDICATOR
#include "Indicator.h"

class DM_Indicator:public Indicator
{
public:
	DM_Indicator();
	void safeOn();
	void safeOff();
private:
	void lightOn(int setting);
	void lightOff();
	int _lastSetting;
};

#endif