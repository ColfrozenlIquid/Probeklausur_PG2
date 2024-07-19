#pragma once
#include "Device.hpp"

class SimpleLight : public Device {
public:
    SimpleLight();

    SimpleLight(const std::string name, std::vector<Channel*> channels);

    int currentPowerUsage();
};
