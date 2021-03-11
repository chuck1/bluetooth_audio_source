#ifndef SERIAL_SEND_H
#define SERIAL_SEND_H

#include "Arduino.h"

template<typename T>
class SerialSend
{
	public:
		SerialSend(unsigned long buffer_size):
			_buffer(0),
			_buffer_size(buffer_size),
			_write_head(0)
		{
			if(buffer_size > 0)
			{
				_buffer = new T[buffer_size];
			}
		}
		void send(T const & t)
		{
			if(_buffer_size > 0)
			{
				_buffer[_write_head] = t;
				
				_write_head += 1;
				
				if(_write_head == _buffer_size)
				{
					Serial.write((byte*)_buffer, _buffer_size * sizeof(T));
					
					_write_head = 0;
				}
			}
			else
			{
				Serial.write((byte*)&t, sizeof(T));
			}
		}
	private:
		T* _buffer;
		unsigned long _buffer_size;
		unsigned long _write_head;
};

#endif




