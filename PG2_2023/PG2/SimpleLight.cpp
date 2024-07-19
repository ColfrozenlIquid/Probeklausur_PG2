#include "SimpleLight.hpp"

SimpleLight::SimpleLight() : Device("SimpleLight", {new Channel("color", "white", Channel::ChannelMode::READWRITE)}) {}

SimpleLight::SimpleLight(const std::string name, std::vector<Channel*> channels)
    : Device(name, {new Channel("color", "white", Channel::ChannelMode::READWRITE)})
{
    for (auto& channel : channels) {
        this->addChannels(channel);
    }
}

int SimpleLight::currentPowerUsage() {

}

