#pragma once
#include "Device.hpp"
#include "SimpleLight.hpp"

class DimmableLight : public SimpleLight {
public:
    DimmableLight();

    DimmableLight(std::string name, std::vector<Channel *> channels);

    static DimmableLight* DimmableLightBuilder(nlohmann::json json_object);

    int currentPowerUsage();

private:
    static constexpr int m_wattage = 40;   //40 Watt
};
