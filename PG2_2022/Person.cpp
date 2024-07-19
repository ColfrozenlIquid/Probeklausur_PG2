#include "Person.hpp"

Person::Person() {}

Person::~Person() {}

void Person::setAge(int age) {
    m_age = age;
}

void Person::setName(std::string name) {
    m_name = name;
}

void Person::setUID(std::string uid) {
    m_uid = uid;
}

int Person::getAge() const {
    return m_age;
}

std::string Person::getUID() {
    return m_uid;
}

int Person::generateUID() {
    return m_next_uid++;
}

std::string Person::getName() const {
    return m_name;
}

int Person::generateRandomAge(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

int Person::m_next_uid = 1;
