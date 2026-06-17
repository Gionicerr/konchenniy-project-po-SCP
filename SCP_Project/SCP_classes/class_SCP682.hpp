#ifndef CLASS_SCP_682_HPP
#define CLASS_SCP_682_HPP

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../SCPEntity.hpp"
#include "../class_staff.hpp"

class SCP682 : public SCPentity{
private:
    StaffFoundation* staff;
public:
    SCP682(StaffFoundation* staff) : SCPentity(ThreatClass("Keter", "Abnormal strength and regeneration", 5), 
        "An invulnerable, highly adaptive and aggressive reptile", 3), staff(staff) {}
        
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
        std::cout << "Contact of other SCPs with SCP-682 is prohibited due to undefined behavior " <<
            "and multiple escape attempts" << std::endl;
    }
    void interact(Human* other) override {
        std::cout << other->getHumanName() << " was brutally bitten by SCP-682" << std::endl;
        staff->deletePerson(other);
    }
};

#endif