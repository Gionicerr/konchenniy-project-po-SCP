#ifndef CONTAINMENTUNIT_HPP
#define CONTAINMENTUNIT_HPP

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "SCPEntity.hpp"
#include "class_staff.hpp"

class ContainmentUnit { 
private:
    std::vector<std::unique_ptr<SCPentity>> anomalies;
    StaffFoundation* staff;

public:
    ContainmentUnit(StaffFoundation* staff) : staff(staff) {}

    void addAnomaly(std::unique_ptr<SCPentity> anomaly) {
        anomalies.push_back(std::move(anomaly));
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
        return anomalies[index].get();
    }

    std::unique_ptr<SCPentity> releaseAnomalyByIndex(std::size_t index) {
        if (index >= anomalies.size()) {
            return nullptr;
        }
        auto it = anomalies.begin() + static_cast<long>(index);
        std::unique_ptr<SCPentity> anomaly = std::move(*it);
        anomalies.erase(it);
        return anomaly;
    }

    bool deleteAnomaly(SCPentity* anomaly) {
        for (auto it = anomalies.begin(); it != anomalies.end(); ++it) {
            if (it->get() == anomaly) {
                anomalies.erase(it);
                return true;
            }
        }
        return false;
    }
};

#endif