#pragma once
#include "Device.hpp"

class Thermostat : public Device {
public:
    Thermostat();

    Thermostat(std::string name, std::vector<Channel*> channels);

    static Thermostat *ThermostatBuilder(nlohmann::json json_object);

    int currentPowerUsage();
};
