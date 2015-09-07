#pragma once

#include "Runnable.h"
#include "Coms.h"
#include "Error.h"
#include "MessageBuffer_Passer.h"
#include "CircularBuffer_Manager.h"

/**
* \brief	An object to buffer messages for sending
*/
class ComsEncoder:public Runnable
{
public:

	/**
	* \brief	Default constructor.
	*
	* \param	coms	The object to send messages
	* \param	e		The shared error object
	*
	* \author	Nicholas
	* \date	1/08/2015
	*/
	ComsEncoder(Coms* coms, Error *e);

	/**
	* \brief	Sends one of the waiting messages
	*/
	void run();

	/**
	* \brief	DO NOTHING
	*/
	bool start(){ return true; }

	/**
	* \brief	Add one message to the queue
	*
	* \param	data	The message to send
	*
	* \return	Was there enough room in the buffers to send the message
	*/
	bool sendData(MessageBuffer_Passer *data);

	/**
	* \brief	Add a single char to the queu (top priority)
	*
	* \param	message	The message to send
	*
	* \return	Was there enough room in the buffers to send the message
	*/
	bool sendChar(uint8_t message);

private:

	/** \brief	The object to send messages */
	Coms *_coms;

	/** \brief	The shared error object */
	Error *_e;

	/** \brief	The buffer of messages to send */
	MessageBuffer_Passer* _buffer[C_CL][C_COMENCODER_SIZE];

	/** \brief	The manger for the queue of messages */
	CircularBuffer_Manager<C_COMENCODER_SIZE> _buffer_man[C_CL];

	/** \brief	The buffer of bytes to send */
	uint8_t _messageBuffer[C_COMENCODER_M_SIZE];

	/** \brief	The manager for the byte buffer */
	CircularBuffer_Manager<C_COMENCODER_M_SIZE> _messageBuffer_man;
};
