#ifndef CLASS_SCP040_HPP
#define CLASS_SCP040_HPP

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../SCPEntity.hpp"
#include "../class_staff.hpp"

class SCP040 : public SCPentity{
private:
    StaffFoundation* staff;
    std::vector<std::string> rand_phrases;
    std::vector<std::string> body_parts;
    int usageCount;
public:
    SCP040(StaffFoundation* staff) : SCPentity(ThreatClass("Euclid", "has the ability to physically change subjects", 3), 
        "A little 8 years old girl with bright pink hair", 3), staff(staff), usageCount(0) {
            rand_phrases = {"SCP-040 doesn't want to play now. Better not to bother her.", 
                "SCP-040 is in a bad mood right now. You'd better leave, or you'll get a new body part.",
                "You woke SCP-040 up and it's created a new"},
            body_parts = {"claws", "feathers", "scales", "horns", "tails", "fins", "tentacles", "eyes",
                "wings", "fangs", "antennae", "spines", "fur", "beaks", "gills", "paws", "mandibles", "carapace", "hooves", "skin patches"};
        }
    std::string body_part = body_parts[rand() % body_parts.size()];
    std::string getAnomalyType() override {
        return "Humanoid entity";
    }
    void triggerAnomaly() override {
        std::string rand_phrase = rand_phrases[rand() % rand_phrases.size()];
        if (rand_phrase == rand_phrases[2]){
            std::cout << rand_phrase << body_part << "for you" << std::endl;
        }
        else std::cout << rand_phrase << std::endl;

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
        other -> setBodyChanges(body_part);
        staff->deletePerson(other);
    }
    void resetUsage() {
        usageCount = 0;
        std::cout << "SCP-040 was startled by the sudden appearance of the D-class and fell, " <<
        "hitting her head, which caused her to forget everything that had happened that day." << std::endl;
    }
};

#endif