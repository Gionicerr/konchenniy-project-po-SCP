#ifndef ALL_CLASSES_HPP
#define ALL_CLASSES_HPP

#include <iostream>
#include <string>
#include <vector>
#include <random>

class Human;
class SCPentity;
class StaffFoundation;
class ContainmentUnit;

// ==================== ThreatClass ====================
class ThreatClass {
private:
    std::string name;
    std::string description;
    int dangerlvl;

public:
    ThreatClass(std::string name, std::string desc, int lvl) :
        name(name), description(desc), dangerlvl(lvl) {}

    std::string getHumanName() const { return name; }
    std::string getDescription() const { return description; }
    int getDangerLevel() const { return dangerlvl; }
    void escalateThreat() { if (dangerlvl < 5) dangerlvl++; }
};

// ==================== Human ====================
class Human {
protected:
    static std::mt19937& getRNG() {
        static std::mt19937 rng{std::random_device{}()};
        return rng;
    }

    static const std::vector<std::string>& getPossibleMentalStates() {
        static const std::vector<std::string> states = {
            "Anxiety", "Depression", "Apathy", "Default", "Normal", "[DATA EXPUNGED]"
        };
        return states;
    }

    std::string name;
    std::string age;
    std::string description;
    std::string mentalState;
    std::string bodyChanges;

    static std::string randomFrom(const std::vector<std::string>& source) {
        if (source.empty()) return "";
        std::uniform_int_distribution<size_t> dist(0, source.size() - 1);
        return source[dist(getRNG())];
    }

    static int randomInt(int min, int maxInclusive) {
        std::uniform_int_distribution<int> dist(min, maxInclusive);
        return dist(getRNG());
    }

public:
    Human(std::string desc)
        : name("D-" + std::to_string(randomInt(1, 9999))),
          age(std::to_string(randomInt(20, 60))),
          description(std::move(desc)),
          mentalState(randomFrom(getPossibleMentalStates())),
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

// ==================== D_class ====================
class D_class : public Human {
public:
    D_class() : Human("Consumable material") {}

    std::string getHumanType() const override {
        return "D-class";
    }

    void triggerHuman() override {
        std::cout << name << " haven't recovered from the experiment and didn't react" << std::endl;
    }
};

// ==================== StaffFoundation ====================
class StaffFoundation {
private:
    std::vector<Human*> personal;

public:
    void addPerson(Human* person) {
        personal.push_back(person);
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
            std::cout << counter << ". Type: " << person->getHumanType() << std::endl
                      << " | Name: " << person->getHumanName() << std::endl
                      << " | Age: " << person->getHumanAge() << std::endl
                      << " | Description: " << person->getDescription() << std::endl
                      << " | Mental state: " << person->getMentalState() << std::endl
                      << " | Body changes: " << person->getNewBodyParts() << std::endl
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
        return personal[index];
    }

    bool releasePersonByIndex(std::size_t index) {
        if (index >= personal.size()) {
            return false;
        }
        delete personal[index];
        personal.erase(personal.begin() + index);
        return true;
    }

    bool deletePerson(Human* person) {
        for (auto it = personal.begin(); it != personal.end(); ++it) {
            if (*it == person) {
                delete *it;
                personal.erase(it);
                return true;
            }
        }
        return false;
    }
};

// ==================== SCPentity ====================
class SCPentity {
protected:
    ThreatClass threatClass;
    std::string description;
    int containmentDifficulty;

public:
    SCPentity(ThreatClass threat, std::string desc, int diff)
        : threatClass(std::move(threat)), description(std::move(desc)), containmentDifficulty(diff) {}

    virtual ~SCPentity() = default;

    virtual void triggerAnomaly() = 0;
    virtual std::string getContainmentProcedure() = 0;
    virtual void interact(SCPentity* other) = 0;
    virtual void interact(Human* other) = 0;
    virtual std::string getAnomalyType() = 0;
    virtual std::string getAnomalyName() = 0;

    const ThreatClass& getThreatClass() const { return threatClass; }
    void escalateThreat() { threatClass.escalateThreat(); }
};

// ==================== ContainmentUnit ====================
class ContainmentUnit {
private:
    std::vector<SCPentity*> anomalies;
    StaffFoundation* staff;

public:
    ContainmentUnit(StaffFoundation* staff) : staff(staff) {}

    void addAnomaly(SCPentity* anomaly) {
        anomalies.push_back(anomaly);
    }

    std::size_t getAnomalyCount() const { return anomalies.size(); }

    void simulateMassBreach() {
        if (anomalies.empty()) {
            std::cout << "Containment unit is empty\n";
            return;
        }

        for (auto& anomaly : anomalies) {
            anomaly->triggerAnomaly();
        }
    }

    void printThreatReport() const {
        if (anomalies.empty()) {
            std::cout << "No anomalies registered\n";
            return;
        }

        int counter = 0;
        for (const auto& anomaly : anomalies) {
            ++counter;
            std::cout << counter << ". " << anomaly->getAnomalyName()
                      << " | Threat: " << anomaly->getThreatClass().getHumanName()
                      << " | Danger lvl: " << anomaly->getThreatClass().getDangerLevel()
                      << " | Type: " << anomaly->getAnomalyType() << std::endl;
        }
    }

    SCPentity* returnAnomalyByIndex(std::size_t index) {
        if (index >= anomalies.size()) {
            std::cout << "No SCP with this number\n";
            return nullptr;
        }
        return anomalies[index];
    }

    bool releaseAnomalyByIndex(std::size_t index) {
        if (index >= anomalies.size()) {
            return false;
        }
        delete anomalies[index];
        anomalies.erase(anomalies.begin() + index);
        return true;
    }

    bool deleteAnomaly(SCPentity* anomaly) {
        for (auto it = anomalies.begin(); it != anomalies.end(); ++it) {
            if (*it == anomaly) {
                delete *it;
                anomalies.erase(it);
                return true;
            }
        }
        return false;
    }
};

// ==================== SCPs ====================

class SCP040 : public SCPentity {
private:
    StaffFoundation* staff;
    std::vector<std::string> rand_phrases;
    std::vector<std::string> body_parts;
    std::string body_part;
    int usageCount;

public:
    SCP040(StaffFoundation* staff) 
        : SCPentity(ThreatClass("Euclid", "has the ability to physically change subjects", 3),
                    "A little 8 years old girl with bright pink hair", 3), 
          staff(staff), usageCount(0) {
        rand_phrases = {
            "SCP-040 doesn't want to play now. Better not to bother her.",
            "SCP-040 is in a bad mood right now. You'd better leave, or you'll get a new body part.",
            "You woke SCP-040 up and it's created a new "
        };
        body_parts = {
            "claws", "feathers", "scales", "horns", "tails", "fins", "tentacles", "eyes",
            "wings", "fangs", "antennae", "spines", "fur", "beaks", "gills", "paws", 
            "mandibles", "carapace", "hooves", "skin patches"
        };
        body_part = body_parts[rand() % body_parts.size()];
    }

    std::string getAnomalyType() override {
        return "Humanoid entity";
    }

    void triggerAnomaly() override {
        std::string rand_phrase = rand_phrases[rand() % rand_phrases.size()];
        if (rand_phrase == rand_phrases[2]) {
            std::cout << rand_phrase << body_part << " for you" << std::endl;
        } else {
            std::cout << rand_phrase << std::endl;
        }
    }

    std::string getAnomalyName() override {
        return "SCP-040";
    }

    std::string getContainmentProcedure() override {
        return "SCP-040 is being held in a residential module for two people (with no restrictions on amenities)";
    }

    void interact(SCPentity* other) override {
        std::cout << "No documented instances of direct contact between SCP-040 and other SCP objects exist within Foundation records." << std::endl;
    }

    void interact(Human* other) override {
        std::cout << other->getHumanName() << " was body changed by SCP-040 and now D-class has a new " << body_part << std::endl;
        other->setBodyChanges(body_part);
    }

    void resetUsage() {
        usageCount = 0;
        std::cout << "SCP-040 was startled by the sudden appearance of the D-class and fell, "
                  << "hitting her head, which caused her to forget everything that had happened that day." << std::endl;
    }
};

class SCP106 : public SCPentity {
private:
    StaffFoundation* staff;
    std::vector<std::string> pocketDimensionRooms = {
        "rusted boiler room", "abandoned hallway", "pitch black bunker", "collapsed tunnel"
    };

public:
    SCP106(StaffFoundation* staff)
        : SCPentity(ThreatClass("Keter", "A corrosive humanoid able to phase through matter", 5),
                    "An elderly humanoid entity that dissolves everything it touches", 4),
          staff(staff) {}

    std::string getAnomalyType() override { return "Humanoid entity"; }
    std::string getAnomalyName() override { return "SCP-106"; }

    void triggerAnomaly() override {
        std::cout << "SCP-106 slips through a wall and drags a piece of metal into its pocket dimension.\n";
    }

    std::string getContainmentProcedure() override {
        return "Keep SCP-106 inside a reinforced container suspended by electromagnets. "
               "Damage triggers immediate sealed chamber protocol.";
    }

    void interact(SCPentity* other) override {
        if (other->getAnomalyType() == "Humanoid entity") {
            std::cout << other->getAnomalyName()
                      << " refuses to approach SCP-106 after witnessing its corrosive slime.\n";
        } else {
            std::cout << "SCP-106 ignores " << other->getAnomalyName() << " and vanishes into the floor.\n";
        }
    }

    void interact(Human* other) override {
        std::string room = pocketDimensionRooms[std::rand() % pocketDimensionRooms.size()];
        std::cout << other->getHumanName() << " was dragged into a " << room
                  << " inside the pocket dimension. Personnel lost.\n";
        staff->deletePerson(other);
    }
};

class SCP294 : public SCPentity {
private:
    StaffFoundation* staff;
    std::vector<std::string> availableLiquids;
    int usageCount;

public:
    SCP294(StaffFoundation* staff) 
        : SCPentity(ThreatClass("Euclid", "Anomalous liquid generation", 3),
                    "Coffee machine producing any liquid", 3), 
          staff(staff), usageCount(0) {
        availableLiquids = {"a coffee", "water", "[DATA EXPUNGED]"};
    }

    std::string getAnomalyType() override {
        return "Anomalous Device";
    }

    std::string getAnomalyName() override {
        return "SCP-294";
    }

    void triggerAnomaly() override {
        std::string liquid = availableLiquids[rand() % availableLiquids.size()];
        std::cout << "SCP-294 produced " << liquid << " for you" << std::endl;
        usageCount++;
    }

    std::string getContainmentProcedure() override {
        return "Store in secured area. Prohibited to request [DATA EXPUNGED] liquids.";
    }

    void interact(SCPentity* other) override {
        if (other->getAnomalyType() == "Humanoid entity") {
            std::string liquid = availableLiquids[rand() % availableLiquids.size()];
            std::cout << "SCP-294 offers " << liquid << " to " << other->getAnomalyName() << std::endl;
        } else {
            std::cout << "SCP-294 cant interact with " << other->getAnomalyName() << std::endl;
        }
    }

    void interact(Human* other) override {
        std::cout << other->getHumanName() << " ordered a [DATA EXPUNGED], his mind is gone" << std::endl;
        staff->deletePerson(other);
    }

    void resetUsage() {
        usageCount = 0;
        std::cout << "Wait for 90 minutes to stable operation vending machine" << std::endl;
    }
};

class SCP682 : public SCPentity {
private:
    StaffFoundation* staff;

public:
    SCP682(StaffFoundation* staff) 
        : SCPentity(ThreatClass("Keter", "Abnormal strength and regeneration", 5),
                    "An invulnerable, highly adaptive and aggressive reptile", 3), 
          staff(staff) {}

    std::string getAnomalyType() override {
        return "Reptilian entity";
    }

    void triggerAnomaly() override {
        std::cout << "SCP-682 is too dangerous. Its better not to disturb it" << std::endl;
    }

    std::string getAnomalyName() override {
        return "SCP-682";
    }

    std::string getContainmentProcedure() override {
        return "SCP-682 is being held in a specially equipped chamber partially "
               "filled with acid. Interaction with entity is prohibited";
    }

    void interact(SCPentity* other) override {
        std::cout << "Contact of other SCPs with SCP-682 is prohibited due to undefined behavior "
                  << "and multiple escape attempts" << std::endl;
    }

    void interact(Human* other) override {
        std::cout << other->getHumanName() << " was brutally bitten by SCP-682" << std::endl;
        staff->deletePerson(other);
    }
};

class SCP999 : public SCPentity {
private:
    std::vector<std::string> possibleodors;
    std::vector<std::string> possibleforms;

public:
    SCP999() 
        : SCPentity(ThreatClass("Safe", "Causes euphoria", 1), 
                    "A tickly orange gelatinous monster", 1) {
        possibleodors = {"chocolate", "fresh laundry", "bacon", "roses", "Play-Doh", "[DATA EXPUNGED]"};
        possibleforms = {"oblate spheroid", "humanoid", "[DATA EXPUNGED]"};
    }

    std::string getAnomalyName() override {
        return "SCP-999";
    }

    std::string getAnomalyType() override {
        return "Biological anomaly";
    }

    void triggerAnomaly() override {
        std::string odor = possibleodors[rand() % possibleodors.size()];
        std::string form = possibleforms[rand() % possibleforms.size()];
        std::cout << "SCP-999 in " << form << " form and with " << odor << " odor tickles you" << std::endl;
    }

    std::string getContainmentProcedure() override {
        return "SCP-999 is walking around the security office. Staff interaction with facility is allowed";
    }

    void interact(SCPentity* other) override {
        if (other->getAnomalyType() == "Reptilian entity" || other->getAnomalyType() == "Humanoid entity") {
            if (other->getThreatClass().getDangerLevel() > 3) {
                std::cout << "SCP-999 calmed the " << other->getAnomalyName() << std::endl;
            } else {
                std::cout << "SCP-999 amused the " << other->getAnomalyName() << std::endl;
            }
        } else {
            std::cout << "SCP-999 cant interact with this object" << std::endl;
        }
    }

    void interact(Human* other) override {
        std::cout << other->getHumanName() << " is got euphoria" << std::endl;
        other->setMentalState("Euphoria");
    }
};

#endif