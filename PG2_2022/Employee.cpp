#include "Employee.hpp"
#include <sstream>

Employee::Employee(Category category) : Person(), m_category(category) {
    this->setUID(generateUID());
    this->setAge(Person::generateRandomAge(18, 65));
    this->setName(RandomNameGenerator::getRandomName());
}

Employee::Employee(std::string name, int age, Category category) : Person() {
    this->setUID(generateUID());
    this->setName(name);
    this->setAge(age);
}

std::string Employee::generateUID() {
    int uid = Person::generateUID();
    return std::string("e_" + std::to_string(uid));
}

std::string Employee::data() {
    std::stringstream stringstream;
    stringstream << "\n\nType: Employee";
    stringstream << "\nUID: " << this->getUID();
    stringstream << "\nTitle: " << this->getCategoryString(m_category);
    stringstream << "\nName: " << this->getName();
    stringstream << "\nAlter: " << this->getAge();
    stringstream << "\nGehalt: " << this->salary();
    return stringstream.str();
}

int Employee::salary() const {
    switch (m_category) {
        case MANAGER:
            return 1500;
            break;
        case TRAINEE:
            return 450;
            break;
        case PERSONAL_TRAINER:
            return 1000;
            break;
    }
}

nlohmann::json Employee::generateJSON() {
    return nlohmann::json {
        {"Type", "Employee"},
        {"UID", this->getUID()},
        {"Title", this->getCategoryString(m_category)},
        {"Name", this->getName()},
        {"Alter", this->getAge()},
        {"Gehalt", this->salary()},
    };
}

std::string Employee::getCategoryString(Category category) {
    switch (category) {
    case MANAGER :
        return "Manager";
    case TRAINEE :
        return "Trainee";
    case PERSONAL_TRAINER :
        return "Personal Trainer";
    }
}
