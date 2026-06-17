#ifndef CLASS_SCP_294_HPP
#define CLASS_SCP_294_HPP

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../SCPEntity.hpp"
#include "../class_staff.hpp"

class SCP294 : public SCPentity {
private:
    StaffFoundation* staff;
    std::vector<std::string> availableLiquids;
    int usageCount;
public:
    SCP294(StaffFoundation* staff) : SCPentity(ThreatClass("Euclid", "Anomalous liquid generation", 3),
            "Coffee machine producing any liquid", 3), staff(staff), usageCount(0) {
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
        }
        else 
            std::cout << "SCP-294 cant interact with " << other->getAnomalyName() << std::endl;
    }
    void interact(Human* other) override {
        std::cout << other->getHumanName() << " ordered a [DATA EXPUNGED], his mind is gone" << std::endl;
        staff->deletePerson(other);
    }
    void resetUsage() {
        usageCount = 0;
        std::cout << "Wait for 90 minutes to stavle operation vending machine" << std::endl;
    }
};

#endif