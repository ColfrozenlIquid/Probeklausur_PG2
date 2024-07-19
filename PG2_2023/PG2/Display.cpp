#include "Display.hpp"

Display::Display() : Device("Display", {new Channel("text", "", Channel::ChannelMode::WRITE)}) {}

int Display::currentPowerUsage() {

}
