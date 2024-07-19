#include "Channel.hpp"
#include <iostream>

Channel::Channel(const std::string &name, const std::string &value, ChannelMode mode) : m_name(name), m_value(value), m_mode(mode) {}

std::string Channel::getName() const {
    return m_name;
}

std::string Channel::getValue() const {
    return m_value;
}

Channel::ChannelMode Channel::getMode() const {
    return m_mode;
}

void Channel::setValue(const std::string& value) {
    this->m_value = value;
}

nlohmann::json Channel::generateJSON() {
    return nlohmann::json {
        {"Name", m_name},
        {"Value", m_value},
        {"Mode", ChannelModeToString(m_mode)}
    };
}

std::string Channel::ChannelModeToString(ChannelMode channel_mode) {
    switch (channel_mode) {
        case READ:
            return "READ";
        case WRITE:
            return "WRITE";
        case READWRITE:
            return "READWRITE";
    }
}

std::vector<Channel*> Channel::channelVectorBuilder(nlohmann::json json_object) {
    std::vector<Channel*> channels;
    for (auto& channel : json_object) {
        channels.push_back(new Channel(
            channel.at("Name").get<std::string>(),
            channel.at("Value").get<std::string>(),
            Channel::stringToChannelMode(channel.at("Mode").get<std::string>())
        ));
    }
    return channels;
}

Channel::ChannelMode Channel::stringToChannelMode(const std::string& channel_mode) {
    if (channel_mode == "READ") {
        return Channel::ChannelMode::READ;
    }
    else if (channel_mode == "WRITE") {
        return Channel::ChannelMode::WRITE;
    }
    else if (channel_mode == "READWRITE") {
        return Channel::ChannelMode::READWRITE;
    }
    return Channel::ChannelMode::READ;
}
