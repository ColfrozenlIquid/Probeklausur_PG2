#pragma once
#include <string>
#include <vector>
#include "json.hpp"

class Channel {
public:
    enum ChannelMode {
        READ,
        WRITE,
        READWRITE,
    };

public:
    Channel() = delete;

    Channel(const std::string& name, const std::string& value, ChannelMode mode);

    std::string getName() const;

    std::string getValue() const;

    ChannelMode getMode() const;

    void setValue(const std::string& value);

    nlohmann::json generateJSON();

    std::string ChannelModeToString(ChannelMode channel_mode);

    static Channel* channelBuilder(nlohmann::json json_object);
private:
    const std::string m_name;
    std::string m_value;
    ChannelMode m_mode;

    static ChannelMode stringToChannelMode(const std::string& channel_mode);
};
