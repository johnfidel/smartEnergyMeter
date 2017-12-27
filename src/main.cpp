#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <algorithm>
#include <sys/queue.h>
#include <iostream>

#include "driver/smartEnergyMeter.h"
#include "app/bt_scan.h"
#include "gattlib.h"

int main(int argc, const char *argv[])
{         
    std::cout << "hallo" << std::endl;
    
    for (int i=0; i < argc; i++)
    {
            if (argv[i] == "--scan"){
                    bt_scan(argc, argv);
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

    return 0;
}
