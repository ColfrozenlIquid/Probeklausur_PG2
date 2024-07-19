#pragma once
#include "Device.hpp"

class Display : public Device {
public:
    Display();

    Display(std::string name, std::vector<Channel *> channels);

    static Display* DisplayBuilder(nlohmann::json json_object);

    int currentPowerUsage();

private:
    static constexpr int m_wattage = 200;   //200 Watt
};
