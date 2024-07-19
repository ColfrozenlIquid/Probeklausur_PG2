#include "DimmableLight.hpp"

DimmableLight::DimmableLight() : SimpleLight("DimmableLight", {new Channel("brightness", "100", Channel::ChannelMode::READWRITE)}) {}

DimmableLight::DimmableLight(std::string name, std::vector<Channel*> channels) : SimpleLight(name, channels) {}

DimmableLight* DimmableLight::DimmableLightBuilder(nlohmann::json json_object) {
    return new DimmableLight(json_object.at("Type").get<std::string>(), Channel::channelVectorBuilder(json_object.at("Channels")));
}

int DimmableLight::currentPowerUsage() {}
