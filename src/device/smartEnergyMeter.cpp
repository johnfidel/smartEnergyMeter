/*
 * smartEnergyMeter.cpp
 *
 *  Created on: 12.11.2017
 *      Author: rappic
 */
#include <iostream>
#include <thread>

#include "gattlib.h"
#include "gattlib_access.h"
#include "smartEnergyMeter.h"
#include "gattlib.h"
#include "uuid.h"

/// 
/// \param addr
smartEnergyMeter::smartEnergyMeter(const char *addr) :
    _addr(addr), _usedAdapter(NULL), _connection(NULL)
{
    //_worker = new std::thread(worker);
}

///
smartEnergyMeter::~smartEnergyMeter() 
{        
    disconnect();
    gattlib_access::closeAdapter(_usedAdapter);    
}

///
void smartEnergyMeter::worker()
{   
    int ret;
    uuid_t uuid;
    void *buffer;
    size_t buffersize; 
    uuid.type = 25;
    uuid.value.uuid16 = 10790;
    
    int charCount;    
    gattlib_characteristic_t *chars;
    int descCount;
    gattlib_descriptor_t *desc;
    
//    ret = gattlib_discover_char(_connection, &chars, &charCount);
//    std::cout << ret << std::endl;
            
    uuid.value.uuid16 = GATT_CHARAC_DEVICE_NAME;
    ret = gattlib_read_char_by_uuid(_connection, &uuid, buffer, &buffersize);
    std::cout << ret << std::endl;    
    
    //for (int i = 0; i < charCount; i++)
    //{        
//    ret = gattlib_read_char_by_uuid(_connection, &chars[8].uuid, buffer, &buffersize);
//    std::cout << ret << std::endl;
//    ret = gattlib_read_char_by_uuid(_connection, &chars[9].uuid, buffer, &buffersize);
//    std::cout << ret << std::endl;
//    ret = gattlib_read_char_by_uuid(_connection, &chars[10].uuid, buffer, &buffersize);
//    std::cout << ret << std::endl;
        
    //}            
}

/// 
/// \return 
void smartEnergyMeter::disconnect()
{
    if (_connection != NULL)
    {        
        gattlib_access::disconnectDevice(_connection);               
    }
}

/// 
/// \return 
bool smartEnergyMeter::connect()
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
bool smartEnergyMeter::getCurrentValues()
{
	bool result = false;

	return result;
}
