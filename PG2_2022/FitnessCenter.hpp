#pragma once

#include "names.hpp"
#include "Person.hpp"
#include "Customer.hpp"
#include "Employee.hpp"
#include "json.hpp""

#include <list>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>

// class Person;

class FitnessCenter {
public:
    FitnessCenter();

    void userInterface();

private:
    std::list<Person*> m_person_list;

    int getRandomAge(int min, int max) const;

    std::string getValidatedUserInput();

    void displayMenu();

    signed int income();

    void printDatabase();

    void addCustomer(Customer* customer);

    void addEmployee(Employee* employee);

    void displayIncome();

    void generateNewCustomer();

    void generateNewEmployee();

    std::string checkValidName();

    std::string inputName();

    bool isAlphabetic(std::string string);

    bool isValidAge(int age, int min_age, int max_age);

    int inputAge(int min_age, int max_age);

    Employee::Category inputCategory();

    std::list<Person*>::iterator find(std::string ID);

    void findPersonByID();

    void deletePerson(std::string ID);

    void deletePersonByID();

    void sortDatabase();

    void saveDatabaseToJSON();

    void saveFile(const std::string &path);

    nlohmann::json generateJSONFromData();
};
