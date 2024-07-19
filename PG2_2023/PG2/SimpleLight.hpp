#pragma once
#include "Device.hpp"

class SimpleLight : public Device {
public:
    SimpleLight();

    SimpleLight(const std::string name, std::vector<Channel*> channels);

    static SimpleLight* SimpleLightBuilder(nlohmann::json json_object);

    int currentPowerUsage();

private:
    static constexpr int m_wattage = 30;   //30 Watt
};
