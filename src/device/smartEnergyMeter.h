/*
 * smartEnergyMeter.h
 *
 *  Created on: 12.11.2017
 *      Author: rappic
 */

#ifndef DRIVER_SMARTENERGYMETER_H_
#define DRIVER_SMARTENERGYMETER_H_

#include "gattlib.h"

class smartEnergyMeter {

private:

        const char* _addr;
        
	double _voltage;
	double _current;
	double _power;
	double _cosphy;
	double _frequency;

	bool getCurrentValues();        
        
public:
	smartEnergyMeter(const char *addr);
	virtual ~smartEnergyMeter();               

};

#endif /* DRIVER_SMARTENERGYMETER_H_ */

