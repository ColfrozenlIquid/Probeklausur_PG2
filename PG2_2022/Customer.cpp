#include "Customer.hpp"
#include <sstream>

Customer::Customer() : Person() {
    this->setUID(generateUID());
    this->setAge(Person::generateRandomAge(10, 80));
    this->setName(RandomNameGenerator::getRandomName());
}

Customer::Customer(std::string name, int age) : Person() {
    this->setUID(generateUID());
    this->setName(name);
    this->setAge(age);
}

std::string Customer::generateUID() {
    int uid = Person::generateUID();
    return std::string("c_" + std::to_string(uid));
}

std::string Customer::data() {
    std::stringstream stringstream;
    stringstream << "\n\nType: Customer";
    stringstream << "\nUID: " << this->getUID();
    stringstream << "\nName: " << this->getName();
    stringstream << "\nAlter: " << this->getAge();
    stringstream << "\nMitgliedsbeitrag: " << this->membershipFee();
    return stringstream.str();
}

int Customer::membershipFee() const {
    if (this->getAge() >= 65 || this->getAge() < 18) {
        return 40;
    }
    return 60;
}

nlohmann::json Customer::generateJSON() {
    return nlohmann::json {
        {"Type", "Customer"},
        {"UID", this->getUID()},
        {"Name", this->getName()},
        {"Alter", this->getAge()},
        {"Mitgliedsbeitrag", this->membershipFee()},
    };
}
