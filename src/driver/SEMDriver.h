/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SEMDriver.h
 * Author: rappic
 *
 * Created on 29. Dezember 2017, 08:21
 */

#ifndef SEMDRIVER_H
#define SEMDRIVER_H

#include <thread>

#include "gattlib.h"
#include "SEMBluetoothDriver.h"

class SEMDriver : SEMBluetoothDriver {

private:

        const char* _addr;
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
	SEMDriver(const char *addr);
	virtual ~SEMDriver();
        
        void worker();
        
        bool connect();
        void disconnect();

};

#endif /* SEMDRIVER_H */

