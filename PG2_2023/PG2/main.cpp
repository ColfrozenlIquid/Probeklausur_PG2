#include "DimmableLight.hpp"
#include "SmartHome.hpp"
#include "Thermostat.hpp"
#include "Display.hpp"

int main() {
    SmartHome smarthome;
    smarthome.registerDevice(new DimmableLight());
    smarthome.registerDevice(new SimpleLight());
    smarthome.registerDevice(new Thermostat());
    smarthome.registerDevice(new Display());

    smarthome.powerUsage();

    smarthome.writeToFile("../../smarthome.json");

    smarthome.readFromFile("../../smarthome.json");

    return 0;
}
