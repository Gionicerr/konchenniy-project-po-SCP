#ifndef CLASS_SCP_999_HPP
#define CLASS_SCP_999_HPP

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../SCPEntity.hpp"
#include "../class_staff.hpp"

class SCP999 : public SCPentity {
private: 
    std::vector<std::string> possibleodors;
    std::vector<std::string> possibleforms;
public:
    SCP999() : SCPentity(ThreatClass("Safe", "Causes euphoria", 1), "A tickly orange gelatinous monster", 1) {
        possibleodors = {"chocolate", "fresh laundry", "bacon", "roses", "Play-Doh", "[DATA EXPUNGED]"}; 
        possibleforms = {"oblate spheroid", "humanoid", "[DATA EXPUNGED]"};
    }
    std::string getAnomalyName() override {
        return "SCP-999";
    }
    std::string getAnomalyType() override { 
        return "Biological anonaly"; 
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
        if (other->getAnomalyType() == "Reptilian entity" or other->getAnomalyType() == "Humanoid entity") {
            if (other->getThreatClass().getDangerLevel() > 3) 
                std::cout << "SCP-999 calmed the " << other->getAnomalyName() << std::endl;
            else 
                std::cout << "SCP-999 amused the " << other->getAnomalyName() << std::endl;
        }
        else std::cout << "SCP-999 cant interact with this object" << std::endl;
    }
    void interact(Human *other) override {
        std::cout << other->getHumanName() << " is got euphoria" << std::endl;
        other->setMentalState("Euphoria");
    }
};

#endif