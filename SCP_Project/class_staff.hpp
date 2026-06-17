#ifndef CLASS_STAFF_HPP
#define CLASS_STAFF_HPP

#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>

class Human {
protected:
    inline static std::mt19937 rng{std::random_device{}()};
    
    inline static std::vector<std::string> possibleMentalStates = {
        "Anxiety", "Depression", "Apathy", "Default", "Normal", "[DATA EXPUNGED]"
    };

    std::string name;
    std::string age;
    std::string description;
    std::string mentalState;
    std::string bodyChanges;

    static std::string randomFrom(const std::vector<std::string>& source) {
        std::uniform_int_distribution<std::size_t> dist(0, source.size() - 1);
        return source[dist(rng)];
    }

    static int randomInt(int min, int maxInclusive) {
        std::uniform_int_distribution<int> dist(min, maxInclusive);
        return dist(rng);
    }

public:
    Human(std::string desc)
        : name("D-" + std::to_string(randomInt(1, 9999))),
          age(std::to_string(randomInt(20, 60))),
          description(std::move(desc)),
          mentalState(randomFrom(possibleMentalStates)),
          bodyChanges("None") {}

    virtual ~Human() = default;

    const std::string& getHumanName() const { return name; }
    const std::string& getHumanAge() const { return age; }
    const std::string& getDescription() const { return description; }
    const std::string& getMentalState() const { return mentalState; }
    const std::string& getNewBodyParts() const { return bodyChanges; }

    void setHumanName(const std::string& newName) { name = newName; }
    void setHumanAge(const std::string& newAge) { age = newAge; }
    void setBodyChanges(const std::string& newBody) { bodyChanges = newBody; }
    void setMentalState(const std::string& newState) { mentalState = newState; }

    virtual std::string getHumanType() const = 0;
    virtual void triggerHuman() = 0;
};

class D_class;

class StaffFoundation {
private:
    std::vector<std::unique_ptr<Human>> personal;

public:
    void addPerson(std::unique_ptr<Human> person) {
        personal.push_back(std::move(person));
    }

    std::size_t getPersonnelCount() const { return personal.size(); }

    void printPersonalInformation() const {
        if (personal.empty()) {
            std::cout << "No personnel registered\n";
            return;
        }

        int counter = 0;
        for (const auto& person : personal) {
            ++counter;
            std::cout << counter << ". Type: " << person->getHumanType()
                      << " | Name: " << person->getHumanName()
                      << " | Age: " << person->getHumanAge()
                      << " | Description: " << person->getDescription()
                      << " | Mental state: " << person->getMentalState()
                      << " | Body changes: " << person->getNewBodyParts()
                      << std::endl;
        }
    }

    void triggerEveryPerson() {
        for (auto& person : personal) {
            person->triggerHuman();
        }
    }

    Human* returnHumanByIndex(std::size_t index) {
        if (index >= personal.size()) {
            std::cout << "No employee with this number\n";
            return nullptr;
        }
        return personal[index].get();
    }

    std::unique_ptr<Human> releasePersonByIndex(std::size_t index) {
        if (index >= personal.size()) {
            return nullptr;
        }
        auto it = personal.begin() + static_cast<long>(index);
        std::unique_ptr<Human> person = std::move(*it);
        personal.erase(it);
        return person;
    }

    bool deletePerson(Human* person) {
        for (auto it = personal.begin(); it != personal.end(); ++it) {
            if (it->get() == person) {
                personal.erase(it);
                return true;
            }
        }
        return false;
    }
};

#endif