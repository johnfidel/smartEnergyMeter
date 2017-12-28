/*
 * smartEnergyMeter.cpp
 *
 *  Created on: 12.11.2017
 *      Author: rappic
 */
#include <thread>

#include "gattlib.h"
#include "bluetooth.h"
#include "smartEnergyMeter.h"

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
    bluetooth::closeAdapter(_usedAdapter);    
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
    
    int charsCount;    
    gattlib_characteristic_t *chars;
    
    ret = gattlib_discover_char(_connection, &chars, &charsCount);
          
    buffersize = 6;
    gattlib_string_to_uuid("0x2a05", buffersize, &uuid);
            
    ret = gattlib_read_char_by_uuid(_connection, &uuid, buffer, &buffersize);
    
    std::cout << ret << std::endl;
}

/// 
/// \return 
void smartEnergyMeter::disconnect()
{
    if (_connection != NULL)
    {        
        bluetooth::disconnectDevice(_connection);               
    }
}

/// 
/// \return 
bool smartEnergyMeter::connect()
{
    if (_usedAdapter == NULL)
    {
        if (bluetooth::openAdapter(_usedAdapter))
        {
            _connection = bluetooth::connectDevice(_addr);
            return true;
        }
    }
    else
    {
        _connection = bluetooth::connectDevice(_addr);
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
