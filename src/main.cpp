#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <algorithm>
#include <sys/queue.h>
#include <iostream>
#include <string>

#include "SEMDriver.h"
#include "gattlib.h"
#include "bluetooth.h"
#include "bt_scan.h"

#include "TinyBDriver.h"

void doScan(int argc, const char *argv[])
{
    bt_scan(1, argv);    
}

void handleSmartEnergyMeter()
{
//    SEMDriver *driver = new SEMDriver("B4:99:4C:52:D1:11");
//    if (driver->connect())
//    {
//        driver->worker();
//        driver->disconnect();
//    }      
//    free(driver);      
    
    TinyBDriver *driver = new TinyBDriver();
    driver->connect();    
}

int main(int argc, const char *argv[])
{             
    int count;
   
    if (argc > 1) 
    {
        for (count = 1; count < argc; count++)
        {                        
            std::string scan("--scan");                    
            if (scan.compare(argv[count]) == 0)
            {
                doScan(argc, argv);
            }            
        }            
    }
    else
    {
        handleSmartEnergyMeter();    
    }     
    
    return 0;
}

