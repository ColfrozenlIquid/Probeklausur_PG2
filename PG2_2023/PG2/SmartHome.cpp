#include "SmartHome.hpp"

SmartHome::SmartHome() {}

void SmartHome::registerDevice(Device* device) {
    for (auto& registered_device : m_devices) {
        if (registered_device->getName() == device->getName()) {
            throw std::runtime_error("Device mit Namen: " + device->getName() + " ist bereits im SmartHome registriert.");
        }
    }
    m_devices.push_back(device);
}

void SmartHome::unregisterDevice(const std::string& name) {
    for (auto it = m_devices.begin(); it != m_devices.end(); ++it) {
        if ((*it)->getName() == name) {
            delete *it;
            m_devices.erase(it);
            return;
        }
    }
    throw std::runtime_error("Device mit Namen: " + name + " konnte nicht in den registrierten Devices gefunden werden.");
}

void SmartHome::listDevices() {
    for (auto& device : m_devices) {
        for (std::string& channel : device->getChannels()) {
            std::cout << channel << std::endl;
        }
    }
}

void SmartHome::on() {
    for (auto& device : m_devices) {
        device->on();
    }
}

void SmartHome::off() {
    for (auto& device : m_devices) {
        device->off();
    }
}

void SmartHome::readFromFile(const std::string &filename) {
    std::ifstream input_filestream(filename);

    if (!input_filestream.is_open()) {
        throw std::runtime_error("Die Datei mit Namen: " + filename + " konnte nicht geoeffnet werden.");
    }

    nlohmann::json json_object;

    input_filestream >> json_object;

    //Loop through devices
    std::vector<Device*> devices;

    for (auto& device_object : json_object.at("Devices")) {
        devices.push_back(Device::deviceBuilder(device_object));
    }

    for (auto& device : devices) {
        try {
            unregisterDevice(device->getName());
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }

        try {
            registerDevice(device);
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

void SmartHome::writeToFile(const std::string &filename) {
    std::ofstream output_filestream(filename);

    if (!output_filestream.is_open()) {
        throw std::runtime_error("Die Datei mit Namen: " + filename + " konnte nicht geoeffnet werden.");
    }

    nlohmann::json json_object;
    nlohmann::json json_array = nlohmann::json::array();

    for (auto& device : m_devices) {
        json_array.push_back(device->generateJSON());
    }

    json_object["Devices"] = json_array;

    output_filestream << json_object.dump(4);

    output_filestream.close();
}
