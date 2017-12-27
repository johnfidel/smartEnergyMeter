cmake_minimum_required(VERSION 3.9)

include_directories(.)

include(ExternalProject)

ExternalProject_Add(gattlib
  GIT_REPOSITORY https://github.com/labapart/gattlib
  GIT_TAG dev
  PREFIX "gattlib-src"
  CONFIGURE_COMMAND cmake ../gattlib/
  BUILD_COMMAND make  
  INSTALL_COMMAND cmake -E echo "Skipping install step."
)

set (CMAKE_CXX_FLAGS "-fpermissive")

add_dependencies(gattlib gattlib)

include_directories(build/gattlib-src/gattlib/include)

project (smartEnergyMeter)

add_executable (
    smartEnergyMeter 
    
    src/main.cpp
    src/app/bt_scan.cpp
    src/driver/smartEnergyMeter.cpp    
)
