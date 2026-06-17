#ifndef CLASS_D_CLASS_HPP
#define CLASS_D_CLASS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "class_staff.hpp"

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

#endif