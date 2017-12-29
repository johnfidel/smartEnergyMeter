/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tintyb_accessor.cpp
 * Author: rappic
 * 
 * Created on 29. Dezember 2017, 18:49
 */
#include <thread>
#include <iostream>
#include <list>
#include <vector>
#include <iterator>

#include "tinyb.hpp"
#include "TinyBDriver.h"

TinyBDriver::TinyBDriver() {
}

TinyBDriver::TinyBDriver(const TinyBDriver& orig) {
}

TinyBDriver::~TinyBDriver() {
}

bool TinyBDriver::connect()
{
    BluetoothManager *manager = nullptr;
    try {
        manager = BluetoothManager::get_bluetooth_manager();
    } catch(const std::runtime_error& e) {
        std::cerr << "Error while initializing libtinyb: " << e.what() << std::endl;
        exit(1);
    }

    /* Start the discovery of devices */
    bool ret = manager->start_discovery();
    std::cout << "Started = " << (ret ? "true" : "false") << std::endl;

    BluetoothDevice &device = NULL;    

    for (int i = 0; i < 15; ++i) {
        std::cout << "Discovered devices: " << std::endl;
        /* Get the list of devices */
        auto list = manager->get_devices();
        
        for (auto &dev : list)
        {
            device = &dev;            
            std::cout << "Class = " << dev->get_class_name() << " ";
            std::cout << "Path = " << dev->get_object_path() << " ";
            std::cout << "Name = " << dev->get_name() << " ";
            std::cout << "Connected = " << dev->get_connected() << " ";
            std::cout << "UUID: " << dev->get_uuid() << " ";
            std::cout << std::endl;            
            
            
        }       
        std::cout << std::endl;
    }

    /* Stop the discovery (the device was found or number of tries ran out */
    ret = manager->stop_discovery();
    std::cout << "Stopped = " << (ret ? "true" : "false") << std::endl;    
}

void TinyBDriver::disconnect()
{
    
}
