cmake_minimum_required(VERSION 3.9)

#-------------------------------------------------------------------------------
# get and build gattlib
#-------------------------------------------------------------------------------
include(ExternalProject)
ExternalProject_Add(gattlib_src
  GIT_REPOSITORY https://github.com/labapart/gattlib
  GIT_TAG dev
  PREFIX "gattlib-src"
  CONFIGURE_COMMAND cmake -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/lib ../gattlib_src/
  BUILD_COMMAND make    
  INSTALL_COMMAND make install
)
#-------------------------------------------------------------------------------

project (smartEnergyMeter)

add_library(gattlib SHARED IMPORTED)
set_target_properties(gattlib PROPERTIES IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/lib/lib/libgattlib.so )

include_directories(${CMAKE_BINARY_DIR}/lib/include/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fpermissive")

set(source_directories 
    . 
    src
    src/app
    src/driver
    src/device
)

include_directories(${source_directories})
link_directories(${source_directories})

add_executable (
    smartEnergyMeter 
    
    src/main.cpp    

    src/app/bt_scan.cpp
    src/app/bt_scan.h

    src/device/smartEnergyMeter.cpp    
    src/device/smartEnergyMeter.h
    
    src/driver/bluetooth.cpp
    src/driver/bluetooth.h
)

target_link_libraries(smartEnergyMeter gattlib)
target_link_libraries(smartEnergyMeter pthread)
