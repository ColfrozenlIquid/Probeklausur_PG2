#include "Display.hpp"

Display::Display() : Device("Display", {new Channel("text", "", Channel::ChannelMode::WRITE)}, m_wattage) {}

Display::Display(std::string name, std::vector<Channel*> channels) : Device(name, channels, m_wattage) {}

Display* Display::DisplayBuilder(nlohmann::json json_object) {
    return new Display(json_object.at("Type").get<std::string>(), Channel::channelVectorBuilder(json_object.at("Channels")));
}

int Display::currentPowerUsage() {
    if (this->getActive()) {
        return m_wattage;
    }
    return 0;
}
