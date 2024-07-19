#include "FitnessCenter.hpp"


FitnessCenter::FitnessCenter() {
    m_person_list.push_back(new Employee(Employee::Category::MANAGER));

    m_person_list.push_back(new Employee(Employee::Category::PERSONAL_TRAINER));
    m_person_list.push_back(new Employee(Employee::Category::PERSONAL_TRAINER));

    m_person_list.push_back(new Employee(Employee::Category::TRAINEE));
    m_person_list.push_back(new Employee(Employee::Category::TRAINEE));
    m_person_list.push_back(new Employee(Employee::Category::TRAINEE));

    for (int i = 0; i < 100; i++) {
        m_person_list.push_back(new Customer());
    }
}

void FitnessCenter::printDatabase() {
    for (auto& person : m_person_list) {
        std::cout << person->data();
    }
    std::cout << std::endl;
}

signed int FitnessCenter::income() {
    signed int income = 0;
    signed int expenses = 0;
    for (auto& person : m_person_list) {
        if (Customer* customer = dynamic_cast<Customer*>(person)) {
            income += customer->membershipFee();
        }
        if (Employee* employee = dynamic_cast<Employee*>(person)) {
            expenses += employee->salary();
        }
    }
    return income - expenses;
}

void FitnessCenter::addCustomer(Customer* customer) {
    bool found = false;
    std::string current_uid = customer->getUID();
    for (auto& person : m_person_list) {
        if (person->getUID() == current_uid) {
            found = true;
            break;
        }
    }
    if (!found) {
        m_person_list.push_back(customer);
    }
}

void FitnessCenter::addEmployee(Employee* employee) {
    bool found = false;
    std::string current_uid = employee->getUID();
    for (auto& person : m_person_list) {
        if (person->getUID() == current_uid) {
            found = true;
            break;
        }
    }
    if (!found) {
        if ((this->income() - employee->salary()) >= 0) {
            m_person_list.push_back(employee);
        }
    }
}

void FitnessCenter::userInterface() {
    bool exit = false;
    while (!exit) {
        displayMenu();
        std::string user_input = getValidatedUserInput();

        switch (std::tolower(user_input[0])) {
        case 'p':
            printDatabase();
            break;
        case 'i':
            displayIncome();
            break;
        case 'c':
            generateNewCustomer();
            break;
        case 'e':
            generateNewEmployee();
            break;
        case 's':
            findPersonByID();
            break;
        case 'r':
            deletePersonByID();
            break;
        case 'd':
            sortDatabase();
            break;
        case 'j':
            saveDatabaseToJSON();
            break;
        case 'x':
            exit = true;
            break;
        default:
            std::cout << "Bitte eine valide Eingabe treffen" << std::endl;
            break;
        }
    }
}

void FitnessCenter::saveDatabaseToJSON() {
    std::cout << "Database Saver:" << std::endl;
    std::cout << "Geben Sie den Dateiname fuer die Datenbankdatei an (speichert automatisch als .json)";
    std::cout << "\n > ";

    std::string user_input;
    std::getline(std::cin, user_input);
    user_input = "../../Datenbank/" + user_input + ".json";
    std::cout << "Sie haben den Pfad: " << user_input << " angegeben." << std::endl;

    try {
        saveFile(user_input);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void FitnessCenter::saveFile(const std::string& path) {
    std::ofstream output_filestream(path);

    if (!output_filestream.is_open()) {
        throw std::runtime_error("Der eingegebene Dateipfad konnte nicht geoeffnet werden.");
    }

    nlohmann::json json_object = generateJSONFromData();

    output_filestream << json_object.dump(2);

    output_filestream.close();

    std::cout << "Datenbank wurde erfolgreich gespeicher in: " << path << std::endl;
}

nlohmann::json FitnessCenter::generateJSONFromData() {
    nlohmann::json json_object;
    nlohmann::json person_array = nlohmann::json::array();

    for (auto& person : m_person_list) {
        person_array.push_back(person->generateJSON());
    }
    json_object["person"] = person_array;
    return json_object;
}

void FitnessCenter::generateNewCustomer() {
    std::cout << "Customer Creator:" << std::endl;
    std::string name = inputName();
    int age = inputAge(10, 120);
    m_person_list.push_back(new Customer(name, age));
}

std::string FitnessCenter::inputName() {
    std::string user_input;

    while (true) {
        std::cout << "Geben Sie einen Namen ein: ";
        std::getline(std::cin, user_input);

        if (isAlphabetic(user_input)) {
            std::cout << "Eingegebener Vorname ist: " << user_input << std::endl;
            return user_input;
        }
        else {
            std::cout << "Bitte einen validen Vornamen ohne Sonderzeichen und Nummern eingeben." << std::endl;
        }
    }
}

int FitnessCenter::inputAge(int min_age, int max_age) {
    int age;
    std::string user_input;

    while (true) {
        std::cout << "Geben Sie einen Alter ein: ";
        std::getline(std::cin, user_input);
        std::stringstream stringstream(user_input);

        if (stringstream >> age && stringstream.eof()) {
            if (isValidAge(age, min_age, max_age)) {
                std::cout << "Eingegebenes Alter ist: " << age << std::endl;
                return age;
            }
        }
        else {
            std::cout << "Bitte einen valides Alter eingeben." << std::endl;
        }
    }
}

Employee::Category FitnessCenter::inputCategory() {
    std::cout << "Geben sie eine Mitarbeiter Kategorie ein: " << std::endl;
    std::cout << "\tt/T: Trainee" << std::endl;
    std::cout << "\tp/P: Personal Trainer" << std::endl;
    std::cout << "\tm/M: Manager" << std::endl;

    while (true) {
        std::string user_input = getValidatedUserInput();

        switch (std::tolower(user_input[0])) {
        case 't':
            return Employee::Category::TRAINEE;
        case 'p':
            return Employee::Category::PERSONAL_TRAINER;
        case 'm':
            return Employee::Category::MANAGER;
        default:
            std::cout << "Bitte eine valide Eingabe treffen" << std::endl;
            break;
        }
    }
}

std::list<Person*>::iterator FitnessCenter::find(std::string ID) {
    for (auto it = m_person_list.begin(); it != m_person_list.end(); ++it) {
        if (dynamic_cast<Person*>(*it)->getUID() == ID) {
            std::cout << "Person mit ID: " << ID << " wurde in der Datenbank gefunden." << std::endl;
            return it;
        }
    }
    throw std::runtime_error("Person mit ID: " + ID + " konnte nicht gefunden werden");
}

void FitnessCenter::findPersonByID() {
    std::cout << "Person Finder:" << std::endl;
    std::cout << "Geben Sie die ID der zu suchenden Person an:";
    std::cout << "\n > ";

    std::string user_input;
    std::getline(std::cin, user_input);

    try {
        find(user_input);
    } catch (const std::exception& e) {
        std::cerr << e.what() <<std::endl;
    }
}

void FitnessCenter::deletePersonByID() {
    std::cout << "Person Remover:" << std::endl;
    std::cout << "Geben Sie die ID der zu entfernended Person an:";
    std::cout << "\n > ";

    std::string user_input;
    std::getline(std::cin, user_input);

    try {
        deletePerson(user_input);
    } catch (const std::exception& e) {
        std::cerr << e.what() <<std::endl;
    }
}

void FitnessCenter::deletePerson(std::string ID) {
    std::list<Person*>::iterator it = find(ID);
    delete *it;
    m_person_list.erase(it);
    std::cout << "Person mit ID: " << ID << " wurde aus der Datenbank entfernt." << std::endl;
}

bool FitnessCenter::isValidAge(int age, int min_age, int max_age) {
    if (age >= min_age && age <= max_age) {
        return true;
    }
    return false;
}

bool FitnessCenter::isAlphabetic(std::string string) {
    return std::all_of(string.begin(), string.end(),
        [] (char character) {
            return std::isalpha(character);
        }
    );
}

void FitnessCenter::sortDatabase() {
    m_person_list.sort(
        [](const Person* left, const Person* right) {
            if (left->getAge() == right->getAge()) {
                return left->getName() < right->getName();
            }
            return left->getAge() < right->getAge();
        }
    );
}

void FitnessCenter::generateNewEmployee() {
    std::cout << "Employee Creator:" << std::endl;
    std::string name = inputName();
    Employee::Category category = inputCategory();
    int age = inputAge(18, 65);
    Person* employee = new Employee(name, age, category);
    if (this->income() - dynamic_cast<Employee*>(employee)->salary() >= 0) {
        m_person_list.push_back(employee);
        std::cout << "Neuer Mitarbeiter hinzugefuegt" << std::endl;
    }
    else {
        std::cout << "Neuer Mitarbeiter konnte nicht hinzugefuegt werden" << std::endl;
        delete employee;
    }
}

void FitnessCenter::displayIncome() {
    std::cout << "Einkommen/ Bilanz: " << this->income() << std::endl;
}

void FitnessCenter::displayMenu() {
    std::cout << "\nBitte treffen Sie ihre Wahl:";
    std::cout << "\n\tp/P: Liste aller Personen";
    std::cout << "\n\ti/I: Einkommen/Bialanz des Centers berechnen";
    std::cout << "\n\tc/C: Customer hinzufuegen";
    std::cout << "\n\te/E: Employee hinzufuegen";
    std::cout << "\n\ts/S: Person nach ID suchen";
    std::cout << "\n\tr/R: Person nach ID entfernen";
    std::cout << "\n\td/D: Datenbank nach Alter sortieren";
    std::cout << "\n\tj/J: Datenbank in JSON speichern";
    std::cout << "\n\tx/X: Vorgang abbrechen";
}

std::string FitnessCenter::getValidatedUserInput() {
    std::string user_input;
    while (true) {
        std::cout << "\n > ";
        std::getline(std::cin, user_input);

        if (user_input.length() == 1 && std::isalpha(user_input[0])) {
            return user_input;
        }
        else {
            std::cout << "Bitte eine valide Eingabe treffen" << std::endl;
        }
    }
}
