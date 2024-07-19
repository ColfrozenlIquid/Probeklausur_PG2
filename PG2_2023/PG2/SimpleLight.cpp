#include "SimpleLight.hpp"

SimpleLight::SimpleLight() : Device("SimpleLight", {new Channel("color", "white", Channel::ChannelMode::READWRITE)}, m_wattage) {}

SimpleLight::SimpleLight(const std::string name, std::vector<Channel*> channels) : Device(name, channels, m_wattage) {}

SimpleLight* SimpleLight::SimpleLightBuilder(nlohmann::json json_object) {
    return new SimpleLight(json_object.at("Type").get<std::string>(), Channel::channelVectorBuilder(json_object.at("Channels")));
}

int SimpleLight::currentPowerUsage() {
    if (this->getActive()) {
        return m_wattage;
    }
    return 0;
}
