#pragma once
#include "Device.hpp"
#include "SimpleLight.hpp"

class DimmableLight : public SimpleLight {
public:
    DimmableLight();

    int currentPowerUsage();
};
