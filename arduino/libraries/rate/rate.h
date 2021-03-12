#ifndef RATE_H
#define RATE_H

#include "Arduino.h"

class Rate
{
public:
	Rate(double rate)
	{
		_t = 0;
		_period = 1000000.0 / rate;
	}
	
	bool ready()
	{
		if(micros() > _t)
		{
			_t += _period;
			
			return true;
		}
		
		return false;
	}
	
	double _t;
	double _period;
};

#endif