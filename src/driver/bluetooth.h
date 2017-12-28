/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   bluetooth.h
 * Author: rappic
 *
 * Created on 27. Dezember 2017, 16:46
 */
#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <pthread.h>
#include <list>
#include <iostream>

#include "gattlib.h"

#define BLE_SCAN_TIMEOUT   4

typedef void (*ble_discovered_device_t)(const char* addr, const char* name);

struct connection_t {
	pthread_t thread;
	char* addr;
};
    
class bluetooth {
    
public:
    static bool open_adapter(void *adapter);       
    
    static bool connect_device(void *arg);
    
    static bool scan();
    
private:       

    // We use a mutex to make the BLE connections synchronous
    static pthread_mutex_t g_mutex;

    static std::list<connection_t*> g_connections;
    
    static bool discovered_device(const char* addr, const char* name);

};

#endif /* BLUETOOTH_H */

