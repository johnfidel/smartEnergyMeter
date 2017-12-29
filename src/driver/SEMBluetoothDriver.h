/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SEMBluetoothDriver.h
 * Author: rappic
 *
 * Created on 29. Dezember 2017, 17:55
 * 
 * SEM is standing for Smart Energy Meter
 */

#ifndef SEMBLUETOOTHDRIVER_H
#define SEMBLUETOOTHDRIVER_H

class SEMBluetoothDriver
{
public:
    virtual bool connect() = 0;
    virtual void disconnect() = 0;
    
};


#endif /* SEMBLUETOOTHDRIVER_H */

