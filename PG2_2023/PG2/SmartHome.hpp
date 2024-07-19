#pragma once
#include <fstream>
#include "Device.hpp"
#include "json.hpp"

class SmartHome {
public:
    SmartHome();

    void registerDevice(Device* device);

    void unregisterDevice(const std::string& name);

    void listDevices();

    void on();

    void off();

    void readFromFile(const std::string& filename);

    void writeToFile(const std::string& filename);

private:
    std::vector<Device*> m_devices;
};
