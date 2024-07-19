#pragma once

#include <string>
#include <random>
#include "json.hpp"
#include "names.hpp"

class Person {
public:
    Person();

    Person(std::string name, int age);

    virtual ~Person();

    virtual std::string data() = 0;

    virtual nlohmann::json generateJSON() = 0;

    static int m_next_uid;

    void setAge(int age);

    void setName(std::string name);

    void setUID(std::string uid);

    int getAge() const;

    std::string getUID();

    std::string getName() const;

    static int generateRandomAge(int min, int max);

    static int generateUID();

private:
    std::string m_name;
    int m_age;
    std::string m_uid;
};
