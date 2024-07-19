#include "Thermostat.hpp"

Thermostat::Thermostat() : Device("Thermostat",
    {
        new Channel("temperature", "19", Channel::ChannelMode::READ),
        new Channel("targetTemperature", "22", Channel::ChannelMode::READWRITE)
    }
){}

Thermostat::Thermostat(std::string name, std::vector<Channel *> channels) : Device(name, channels) {}

Thermostat* Thermostat::ThermostatBuilder(nlohmann::json json_object) {
    return new Thermostat(json_object.at("Type").get<std::string>(), Channel::channelVectorBuilder(json_object.at("Channels")));
}

int Thermostat::currentPowerUsage() {

}
