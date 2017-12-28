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

#include "bluetooth.h"

// We use a mutex to make the BLE connections synchronous
pthread_mutex_t bluetooth::g_mutex = PTHREAD_MUTEX_INITIALIZER;
std::list<connection_t*> bluetooth::g_connections;
    
/// 
/// \return 
bool bluetooth::open_adapter(void *adapter)
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
/// \return 
bool bluetooth::discovered_device(const char* addr, const char* name)
{
    struct connection_t *connection;
    int ret;

    if (name) {
            printf("Discovered %s - '%s'\n", addr, name);
    } else {
            printf("Discovered %s\n", addr);
    }

    connection = malloc(sizeof(struct connection_t));
    if (connection == NULL) {
            fprintf(stderr, "Failt to allocate connection.\n");
            return;
    }
    connection->addr = strdup(addr);

    ret = pthread_create(&connection->thread, NULL, connect_device, connection);
    if (ret != 0) {
            fprintf(stderr, "Failt to create BLE connection thread.\n");
            free(connection);
            return;
    }
    g_connections.push_front(connection);    
}

/// 
/// \return 
bool bluetooth::connect_device(void *arg)
{
    struct connection_t *connection = arg;
    char* addr = connection->addr;
    gatt_connection_t* gatt_connection;
    gattlib_primary_service_t* services;
    gattlib_characteristic_t* characteristics;
    int services_count, characteristics_count;
    char uuid_str[MAX_LEN_UUID_STR + 1];
    int ret, i;

    pthread_mutex_lock(&g_mutex);

    printf("------------START %s ---------------\n", addr);

    gatt_connection = gattlib_connect(NULL, addr, BDADDR_LE_PUBLIC, BT_SEC_LOW, 0, 0);
    if (gatt_connection == NULL) {
            gatt_connection = gattlib_connect(NULL, addr, BDADDR_LE_RANDOM, BT_SEC_LOW, 0, 0);
            if (gatt_connection == NULL) {
                    fprintf(stderr, "Fail to connect to the bluetooth device.\n");
                    goto connection_exit;
            } else {
                    puts("Succeeded to connect to the bluetooth device with random address.");
            }
    } else {
            puts("Succeeded to connect to the bluetooth device.");
    }

    ret = gattlib_discover_primary(gatt_connection, &services, &services_count);
    if (ret != 0) {
            fprintf(stderr, "Fail to discover primary services.\n");
            goto disconnect_exit;
    }

    for (i = 0; i < services_count; i++) {
            gattlib_uuid_to_string(&services[i].uuid, uuid_str, sizeof(uuid_str));

            printf("service[%d] start_handle:%02x end_handle:%02x uuid:%s\n", i,
                            services[i].attr_handle_start, services[i].attr_handle_end,
                            uuid_str);
    }
    free(services);

    ret = gattlib_discover_char(gatt_connection, &characteristics, &characteristics_count);
    if (ret != 0) {
            fprintf(stderr, "Fail to discover characteristics.\n");
            goto disconnect_exit;
    }
    for (i = 0; i < characteristics_count; i++) {
            gattlib_uuid_to_string(&characteristics[i].uuid, uuid_str, sizeof(uuid_str));

            printf("characteristic[%d] properties:%02x value_handle:%04x uuid:%s\n", i,
                            characteristics[i].properties, characteristics[i].value_handle,
                            uuid_str);
    }
    free(characteristics);

disconnect_exit:
    gattlib_disconnect(gatt_connection);

connection_exit:
    printf("------------DONE %s ---------------\n", addr);
    pthread_mutex_unlock(&g_mutex);
    return NULL;    
}

/// 
/// \return 
bool bluetooth::scan()
{
    void *adapter;
    int ret;
    
    if (open_adapter(adapter)) 
    {
        pthread_mutex_lock(&g_mutex);
        ret = gattlib_adapter_scan_enable(adapter, discovered_device, BLE_SCAN_TIMEOUT);
        if (ret) {
                fprintf(stderr, "ERROR: Failed to scan.\n");
                return 1;
        }

        gattlib_adapter_scan_disable(adapter);

        puts("Scan completed");
        pthread_mutex_unlock(&g_mutex);

        // Wait for the thread to complete
        for (connection_t* actConn : g_connections)
        {
            if (actConn != NULL) 
            {
                pthread_join(actConn->thread, NULL);            
                free(actConn->addr);            
                free(actConn);
            }            
        }       

        gattlib_adapter_close(adapter);
        return 0;
    }
    return true;    
}

