#pragma once

#include "Person.hpp"

class Customer : public Person {
public:
    Customer();

    Customer(std::string name, int age);

    std::string data() override;

    int membershipFee() const;

    nlohmann::json generateJSON() override;

private:
    std::string generateUID();
};
