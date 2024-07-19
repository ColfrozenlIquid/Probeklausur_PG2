#include "Display.hpp"

Display::Display() : Device("Display", {new Channel("text", "", Channel::ChannelMode::WRITE)}) {}

Display::Display(std::string name, std::vector<Channel*> channels) : Device(name, channels) {}

Display* Display::DisplayBuilder(nlohmann::json json_object) {
    return new Display(json_object.at("Type").get<std::string>(), Channel::channelVectorBuilder(json_object.at("Channels")));
}

int Display::currentPowerUsage() {

}
