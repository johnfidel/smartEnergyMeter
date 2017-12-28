#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <algorithm>
#include <sys/queue.h>
#include <iostream>
#include <string>

#include "device/smartEnergyMeter.h"
#include "app/bt_scan.h"
#include "gattlib.h"
#include "driver/bluetooth.h"

#include "app/bt_scan.h"

int main(int argc, const char *argv[])
{         
    std::cout << "hallo " << argc << " ";    
    
    int count;
    for (count = 0; count < argc; count++)
    {
        std::cout << " " << argv[count];
        
        std::string scan("--scan");        
        if (scan.compare(argv[count]) == 0)
        {
                //bt_scan(1, argv);
                bluetooth::scan();
        }
        else
        {
                smartEnergyMeter *meter;
                gatt_connection_t *connection;

                meter = new smartEnergyMeter();

                //gattlib_adapter_open('hci0', );

                //meter->getCurrentValues();

                free(meter);
        }
    }

    std::cout << std::endl;
    
    return 0;
}
