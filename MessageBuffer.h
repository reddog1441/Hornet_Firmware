#pragma once

#include "MessageBuffer_Passer.h"

template<int Size,int ID>
class MessageBuffer : public MessageBuffer_Passer
{
public:

	typedef union MemoryMap
	{
		struct
		{
			uint8_t comID;
			float data[Size];
		}value;
		struct
		{
			uint8_t comID;
			uint8_t data[Size * sizeof(float)];
		}raw;
		struct
		{
			uint8_t data[Size * sizeof(float)+1];
		}packet;
	};

	//-----------------------------------------------------------------------------------------------------------------------------

	MessageBuffer()
	{
		_message.value.comID = ID;
		_isLocked = false;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	float* getData()
	{
		return _message.value.data;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	void setData(float* data)
	{
		for (int i = 0; i < Size; i++)
		{
			_message.value.data[i] = data[i];
		}
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	uint8_t* getBytes()
	{
		return _message.raw.data;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	void setBytes(uint8_t* data)
	{
		for (int i = 0; i < (Size *sizeof(double)); i++)
		{
			_message.raw.data[i] = data[i];
		}
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	int getSize()
	{
		return Size;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	uint8_t* getPacket()
	{
		return _message.packet.data;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	bool isLocked()
	{
		return _isLocked;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	void lock()
	{
		_isLocked = true;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	void unlock()
	{
		_isLocked = false;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	uint8_t getID()
	{
		return _message.value.comID;
	}
private:
	MemoryMap _message;
	bool _isLocked;
};