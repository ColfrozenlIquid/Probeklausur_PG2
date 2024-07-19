#pragma once
#include "Device.hpp"

class Thermostat : public Device {
public:
    Thermostat();

    int currentPowerUsage();
};
