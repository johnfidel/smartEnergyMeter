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
    _addr(addr)
{}

///
smartEnergyMeter::~smartEnergyMeter() 
{ }

/// 
/// \return 
bool smartEnergyMeter::getCurrentValues()
{
	bool result = false;

	return result;
}
