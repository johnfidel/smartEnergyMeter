/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SEMDriver.cpp
 * Author: rappic
 * 
 * Created on 29. Dezember 2017, 08:21
 * 
 * SEM is a shortcut for SmartEnergyMeter
 */

#include <iostream>
#include <thread>
#include <iomanip>

#include "gattlib.h"
#include "gattlib_access.h"
#include "SEMDriver.h"
#include "gattlib.h"
#include "uuid.h"

/// 
/// \param addr
SEMDriver::SEMDriver(const char *addr) :
    _addr(addr), _usedAdapter(NULL), _connection(NULL)
{
    //_worker = new std::thread(worker);
}

///
SEMDriver::~SEMDriver() 
{        
    disconnect();
    gattlib_access::closeAdapter(_usedAdapter);    
}

///
void SEMDriver::worker()
{   
    int ret;
    uuid_t uuid;
    uint8_t buffer[100];
    size_t buffersize; 
    uuid.type = 25;
    uuid.value.uuid16 = 10790;
    
    int charCount;    
    gattlib_characteristic_t *chars;          
            
    ret = gattlib_discover_char(_connection, &chars, &charCount);
    std::cout << ret << std::endl;        
    
    for (int i = 8; i <= 10; i++)
    {        
        buffersize = sizeof(buffer);
        ret = gattlib_read_char_by_uuid(_connection, &chars[i].uuid, buffer, &buffersize);
        if (ret == 0)
        {
//            std::cout << "read: " << chars[i].handle << " " 
//                    << chars[i].properties << " "
//                    << chars[i].uuid.type << " "
//                    << chars[i].uuid.value.uuid128.data << " "
//                    << chars[i].value_handle << std::endl;                            
            
            for (int j = 0; j < buffersize; j++)
            {
                //std::cout << std::hex << std::setw(2) << buffer[j];                
                std::cout << char(buffer[j] + '0');                
            }
            std::cout << std::endl;                            
        }            
        else
        {
            std::cout << "Error reading characteristic #" << i << std::endl;        
        }
    }            
}

/// 
/// \return 
void SEMDriver::disconnect()
{
    if (_connection != NULL)
    {        
        gattlib_access::disconnectDevice(_connection);               
    }
}

/// 
/// \return 
bool SEMDriver::connect()
{
    if (_usedAdapter == NULL)
    {
        if (gattlib_access::openAdapter(_usedAdapter))
        {
            _connection = gattlib_access::connectDevice(_addr);
            return true;
        }
    }
    else
    {
        _connection = gattlib_access::connectDevice(_addr);
        return true;
    }
    return false;
}

/// 
/// \return 
bool SEMDriver::getCurrentValues()
{
	bool result = false;

	return result;
}
