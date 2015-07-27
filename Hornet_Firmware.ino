#include "Coms.h"

Coms com(Serial3);

String toHex2(uint8_t b)
{
	String hex[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F" };
	uint8_t hi;
	uint8_t lo;
	hi = (b >> 4);
	lo = (b & 0b00001111);
	return hex[hi] + hex[lo];
}

uint8_t payload[] = { 1, 2 };

void setup()
{
	Serial3.begin(9600);
  /* add setup code here */
	Serial.begin(9600);
	delay(1000);
	com.send(payload, sizeof(payload));
}


void loop()
{
	com.run();
	/*if (Serial3.available())
	{
		Serial.println(toHex2(Serial3.read()));
	}*/

	uint8_t payload[] = { 'h','e','l'};
	if (com.canSend())
	{
		com.send(payload, sizeof(payload));
		payload[0] = payload[0]++;
	}
	
  /* add main program code here */

}
