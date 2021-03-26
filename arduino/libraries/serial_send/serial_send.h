#ifndef SERIAL_SEND_H
#define SERIAL_SEND_H

#include "Arduino.h"



template<typename T>
class SerialSend
{
	public:
		SerialSend(bool enable_header, unsigned long buffer_size):
			_enable_header(enable_header),
			_buffer(0),
			_buffer_size(buffer_size),
			_write_head(0),
			_i(0)
		{
			if(buffer_size > 0)
			{
				_buffer = new T[buffer_size];
				
				_header_size = sizeof(T) + sizeof(int);
				_header = new byte[_header_size];
				
				for(unsigned int i = 0; i < sizeof(T); ++i)
				{
					*((_header) + i) = 0x80;	
				}	
			}
		}
		void send(T const & t)
		{
			if((_buffer_size > 0) && _enable_header)
			{
				_buffer[_write_head] = t;
				
				_write_head += 1;
				
				if(_write_head == _buffer_size)
				{
					//Serial.write((byte*)_buffer, (_buffer_size + 1) * sizeof(T));
					
					*((int*)(_header + sizeof(T))) = _i;
					
					Serial.write(_header, _header_size);
					Serial.write((byte*)_buffer, _buffer_size * sizeof(T));
					
					_write_head = 0;
					_i += 1;
				}
			}
			else
			{
				Serial.write((byte*)&t, sizeof(T));
			}
		}
	private:
		bool _enable_header;
		T* _buffer;
		unsigned long _buffer_size;
		unsigned long _write_head;
		byte* _header;
		long _header_size;
		int _i;
};

#endif




