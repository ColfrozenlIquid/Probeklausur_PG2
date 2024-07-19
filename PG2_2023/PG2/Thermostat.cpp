#include "Thermostat.hpp"

Thermostat::Thermostat() : Device("Thermostat",
    {
        new Channel("temperature", "19", Channel::ChannelMode::READ),
        new Channel("targetTemperature", "22", Channel::ChannelMode::READWRITE)
    }
){}

int Thermostat::currentPowerUsage() {

}
