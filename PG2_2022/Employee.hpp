#pragma once

#include "Person.hpp"

class Employee : public Person {
public:

    enum Category {
        TRAINEE,
        PERSONAL_TRAINER,
        MANAGER,
    };

    Employee(Category category);

    Employee(std::string name, int age, Category category);

    std::string data() override;

    int salary() const;

    nlohmann::json generateJSON() override;

private:
    Category m_category;

    std::string getCategoryString(Category category);
    std::string generateUID();
};
