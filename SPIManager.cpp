#include "SPIManager.h"
#include <SPI.h>

SPIManager::SPIManager(volatile Error *theError) //:SharedBusManager(theError)
{
	//SPI.begin();
	//SPI.setClockDivider(SPI_CLOCK_DIV16); // 1MHZ SPI rate



	//@TODO remove this after the baromiter driver is added
	pinMode(40, OUTPUT);
	digitalWrite(40, HIGH);
}

//-----------------------------------------------------------------------------------------------------------------------------

void SPIManager::read(uint8_t address, uint8_t start, uint8_t *buffer, int size)
{
	digitalWrite(address, LOW);

	SPI.transfer(4,start);

	for (int i = 0; i < size; i++)
	{
		buffer[i] = SPI.transfer(4, 0);
	}

	digitalWrite(address, HIGH);
}

//-----------------------------------------------------------------------------------------------------------------------------

void SPIManager::write(uint8_t address, uint8_t start, uint8_t *buffer, int size)
{
	digitalWrite(address, LOW);

	SPI.transfer(4, start);

	for (int i = 0; i < size; i++)
	{
		SPI.transfer(4, buffer[i]);
	}

	digitalWrite(address, HIGH);
}

//-----------------------------------------------------------------------------------------------------------------------------

uint8_t SPIManager::transfer(uint8_t toSend)
{
	return SPI.transfer(4, toSend);
}