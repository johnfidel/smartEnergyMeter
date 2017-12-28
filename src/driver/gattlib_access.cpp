/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   bluetooth.cpp
 * Author: rappic
 * 
 * Created on 27. Dezember 2017, 16:46
 */

#include <iterator>
#include <list>

#include "gattlib_access.h"
    
/// 
/// \return 
bool gattlib_access::openAdapter(void *adapter)
{
    const char* adapter_name;    
    int ret;
    adapter_name = NULL;       

    ret = gattlib_adapter_open(adapter_name, &adapter);
    if (ret) {
            fprintf(stderr, "ERROR: Failed to open adapter.\n");
            return false;
    }    
    return true;
}

/// 
/// \param connection
void gattlib_access::disconnectDevice(gatt_connection_t* connection)
{
    gattlib_disconnect(connection); 
}

/// 
/// \param addr
/// \return 
gatt_connection_t *gattlib_access::connectDevice(const char *addr)
{    
    gatt_connection_t* gatt_connection;    
    int ret;   
    void *adapter;
       
    if (openAdapter(adapter))
    {
        gatt_connection = gattlib_connect(NULL, addr, BDADDR_LE_PUBLIC, BT_SEC_LOW, 0, 0);
        if (gatt_connection == NULL) {
                gatt_connection = gattlib_connect(NULL, addr, BDADDR_LE_RANDOM, BT_SEC_LOW, 0, 0);
                if (gatt_connection == NULL) {
                        fprintf(stderr, "Fail to connect to the bluetooth device.\n");
                        return NULL;
                } else {
                        puts("Succeeded to connect to the bluetooth device with random address.");
                }
        } else {
                puts("Succeeded to connect to the bluetooth device.");
        }  
        return gatt_connection;        
    }
    return NULL;
}

/// 
/// \param adapter
/// \return 
bool gattlib_access::closeAdapter(void* adapter)
{
    gattlib_adapter_close(adapter);    
}
