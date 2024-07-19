#include "Device.hpp"

#include "DimmableLight.hpp"

Device::Device(const std::string& name, std::vector<Channel*> channels) : m_name(name) {
    m_channels.insert(m_channels.end(), channels.begin(), channels.end());
}

void Device::on() {
    m_active = true;
}

void Device::off() {
    m_active = false;
}

void Device::toggle() {
    m_active = !m_active;
}

std::vector<std::string> Device::getChannels() {
    std::vector<std::string> channel_names;
    for (auto& channel : m_channels) {
        channel_names.push_back(channel->getName());
    }
    return channel_names;
}

std::string Device::getName() const {
    return m_name;
}

std::string Device::getValue(const std::string& name) {
    for (auto& channel : m_channels) {
        if (channel->getName() == name) {
            if (channel->getMode() == Channel::ChannelMode::WRITE) {
                throw std::logic_error("Channel mit dem Namen: " + name + " ist WRITE-only und kann nicht gelesen werden.");
            }
            return channel->getValue();
        }
    }
    throw std::invalid_argument("Channel mit dem Namen: " + name + " konnte nicht gefunden werden.");
}

void Device::setValue(const std::string& name, const std::string& value) {
    for (auto& channel : m_channels) {
        if (channel->getName() == name) {
            if (channel->getMode() == Channel::ChannelMode::READ) {
                throw std::logic_error("Channel mit dem Namen: " + name + " ist READ-only und kann nicht beschrieben werden.");
            }
            channel->setValue(value);
            if (name == "text") {
                std::cout << value << std::endl;
            }
            return;
        }
    }
    throw std::invalid_argument("Channel mit dem Namen: " + name + " konnte nicht gefunden werden.");
}

nlohmann::json Device::generateJSON() {
    nlohmann::json json_object;
    json_object["Type"] = m_name;
    json_object["Active"] = m_active;
    nlohmann::json json_array = nlohmann::json::array();
    for (auto& channel : m_channels) {
        json_array.push_back(channel->generateJSON());
    }
    json_object["Channels"] = json_array;
    return json_object;
}

Device* Device::deviceBuilder(nlohmann::json json_object) {
    std::vector<Channel*> channels;
    for (auto& channel : json_object.at("Channels")) {
        channels.push_back(Channel::channelBuilder(channel));
    }

    Device* device = new Device(
        json_object.at("Type").get<std::string>(),
        channels
    );
    device->m_active = json_object.at("Active").get<bool>();
    return device;
}

Device* Device::deviceTypeFromJSON(const std::string& device_type){
    if (device_type == "DimmableLight") {
        return new DimmableLight();
    }
}

void Device::addChannels(Channel* channel) {
    m_channels.push_back(channel);
}
