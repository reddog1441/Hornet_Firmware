#pragma once
#include "Error.h"
#include "Arduino.h"

template<class T, int Size>
class CircularBuffer
{
public:

	/**
	* \fn	CircularBuffer_Manager::CircularBuffer()
	*
	* \brief	Default constructor.
	*
	* \author	Nicholas
	* \date	1/08/2015
	*/
	CircularBuffer(Error *e)
	{
		_e = e;
		_start = 0;
		_end = 0;
	}

	/**
	* \fn	bool CircularBuffer::isEmpty()
	*
	* \brief	Query if this object is empty.
	*
	* \author	Nicholas
	* \date	1/08/2015
	*
	* \return	true if empty, false if not.
	*/
	bool isEmpty()
	{
		return _start == _end;
	}

	/**
	* \fn	bool CircularBuffer::isFull()
	*
	* \brief	Query if this object is full.
	*
	* \author	Nicholas
	* \date	1/08/2015
	*
	* \return	true if full, false if not.
	*/
	bool isFull()
	{
		if (_end == 0 && (_start - 1) == Size)
		{
			return true;
		}

		if (_start == (_end - 1))
		{
			return true;
		}

		return false;
	}

	int size()
	{
		if (_start >= _end)
		{
			return (_start - _end);
		}

		return _start + (Size - _end);
	}

	void add(T toAdd)
	{
		if (isFull())
		{
			_e->add(E_ILLEGAL_ACCESS, "Attempting to add to a full buffer");
			return;
		}

		int toRemove = _start;

		_start++;
		if (_start >= Size)
		{
			_start = 0;
		}

		_buffer[toRemove] = toAdd;
	}

	/**
	* \fn	int CircularBuffer_Manager::remove(Error *e)
	*
	* \brief	Removes an object from the buffer
	*
	* \author	Nicholas
	* \date	1/08/2015
	*
	* \throw	E_ILLEGAL_ACCESS	If full
	*
	* \return	The index of the object to remove
	*/
	T remove()
	{
		if (isEmpty())
		{
			_e->add(E_ILLEGAL_ACCESS, "Attempting to remove from an empty buffer");
			return 0;
		}

		int toRemove = _end;

		_end++;
		if (_end >= Size)
		{
			_end = 0;
		}

		return _buffer[toRemove];
	}


private:

	/** \brief	The index to add to. */
	int _start;

	/** \brief	The index to remove from. */
	int _end;

	/** \brief	The systems error object */
	Error *_e;

	T _buffer[Size];
};
