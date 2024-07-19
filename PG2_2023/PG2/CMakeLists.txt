cmake_minimum_required(VERSION 3.5)

project(PG2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(PG2 main.cpp
    Channel.hpp Channel.cpp
    Device.hpp Device.cpp
    SimpleLight.hpp SimpleLight.cpp
    DimmableLight.hpp DimmableLight.cpp
    Thermostat.hpp Thermostat.cpp
    Display.hpp Display.cpp
    SmartHome.hpp SmartHome.cpp
    json.hpp)

include(GNUInstallDirs)
install(TARGETS PG2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
