#include "DimmableLight.hpp"

DimmableLight::DimmableLight() : SimpleLight("DimmableLight", {new Channel("brightness", "100", Channel::ChannelMode::READWRITE)}) {}

int DimmableLight::currentPowerUsage() {

}
