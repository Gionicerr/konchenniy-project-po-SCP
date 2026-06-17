#ifndef THREATCLASS_HPP
#define THREATCLASS_HPP

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>

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
    void escalateThreat() { if (dangerlvl < 5) dangerlvl ++; }
};

#endif