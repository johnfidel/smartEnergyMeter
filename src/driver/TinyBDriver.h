/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tintyb_accessor.h
 * Author: rappic
 *
 * Created on 29. Dezember 2017, 18:49
 */

#ifndef TINYBDRIVER_H
#define TINYBDRIVER_H

#include "SEMBluetoothDriver.h"

class TinyBDriver : SEMBluetoothDriver {
public:
    TinyBDriver();
    TinyBDriver(const TinyBDriver& orig);
    virtual ~TinyBDriver();
    
    bool connect();
    void disconnect();
    
private:

};

#endif /* TINYBDRIVER_H */

