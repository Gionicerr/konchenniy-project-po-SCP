#ifndef CLASS_SCP106_HPP
#define CLASS_SCP106_HPP

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "../SCPEntity.hpp"
#include "../class_staff.hpp"

class SCP106 : public SCPentity {
private:
    StaffFoundation* staff;
    std::vector<std::string> pocketDimensionRooms = {
        "rusted boiler room", "abandoned hallway", "pitch black bunker", "collapsed tunnel"
    };

public:
    SCP106(StaffFoundation* staff) : SCPentity(ThreatClass("Keter", "A corrosive humanoid able to phase through matter", 5),
                    "An elderly humanoid entity that dissolves everything it touches", 4), staff(staff) {}

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

#endif