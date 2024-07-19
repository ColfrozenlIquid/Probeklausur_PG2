#pragma once
#include "Device.hpp"

class Display : public Device {
public:
    Display();

    int currentPowerUsage();
};
