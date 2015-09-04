#include "HornetManager.h"


//-----------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- CONSTRUCTION ----------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

HornetManager::HornetManager(Error *theError) :_scheduler(theError)
{
	_e = theError;
	_state = Init;
}
//-----------------------------------------------------------------------------------------------------------------------------

void HornetManager::start()
{
	if (!_scheduler.finish())
	{
		while (true)
		{
			TP("Not all objects attached");//@TODO add build exeption here
			delay(500);
		}
	}
	if (!_scheduler.startAll())
	{
		while (true)
		{
			TP("Failed to start");//@TODO add build exeption here
			delay(500);
		}
	}

	changeState(ST_TO_CONNECT);
}


//-----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- MAIN LOOP ------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

void HornetManager::run()
{	
	// exicute the threads
	_scheduler.run(); 

	// catch exeption
	if (_e->isError())
	{
		TP("ERROR");
		delay(500);
	}
}

void HornetManager::changeState(State newState)
{
	_state = newState;
}
