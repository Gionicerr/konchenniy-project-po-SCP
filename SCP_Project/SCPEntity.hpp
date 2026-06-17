#ifndef SCPENTITY_HPP
#define SCPENTITY_HPP

#include <string>
#include <utility>

#include "ThreatClass.hpp"
#include "class_staff.hpp"

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

#endif