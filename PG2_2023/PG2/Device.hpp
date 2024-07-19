#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Channel.hpp"
#include "json.hpp"

class Device {
public:
    Device() = delete;

    Device(const std::string& name, std::vector<Channel*> channels);

    virtual ~Device() = default;

    void on();

    void off();

    void toggle();

    std::vector<std::string> getChannels();

    std::string getName() const;

    std::string getValue(const std::string& name);

    void setValue(const std::string& name, const std::string& value);

    nlohmann::json generateJSON();

    static Device* deviceBuilder(nlohmann::json json_object);

    void addChannels(Channel* channel);

    virtual int currentPowerUsage() = 0;

private:
    bool m_active;
    const std::string m_name;
    std::vector<Channel*> m_channels;
    int m_max_power_usage;

    static Device *deviceTypeFromJSON(nlohmann::json json_object);
};
