/*
 * smartEnergyMeter.h
 *
 *  Created on: 12.11.2017
 *      Author: rappic
 */

#ifndef DRIVER_SMARTENERGYMETER_H_
#define DRIVER_SMARTENERGYMETER_H_

#include <thread>

#include "gattlib.h"

class smartEnergyMeter {

private:

        char* _addr;
        void *_usedAdapter;
        gatt_connection_t *_connection;
        std::thread *_worker;
        
	double _voltage;
	double _current;
	double _power;
	double _cosphy;
	double _frequency;

	bool getCurrentValues();        
        
public:
	smartEnergyMeter(const char *addr);
	virtual ~smartEnergyMeter();
        
        void worker();
        
        bool connect();
        void disconnect();

};

#endif /* DRIVER_SMARTENERGYMETER_H_ */

