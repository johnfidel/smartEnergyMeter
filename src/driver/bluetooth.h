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

#include <iostream>

#include "gattlib.h"
    
class bluetooth {
    
public:       
    
    static bool openAdapter(void *adapter);       
    static bool closeAdapter(void *adapter);       
            
    static gatt_connection_t *connectDevice(const char *addr);
    static void disconnectDevice(gatt_connection_t *connection);   
 
};

#endif /* BLUETOOTH_H */

