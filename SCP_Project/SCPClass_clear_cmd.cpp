#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#endif

#include "AllClasses.hpp"

using namespace std;

void clearConsole() {
#ifdef _WIN32
    system("color 6");
    system("cls");
#endif
}

void enter() {
    cout << endl;
}

void sleep(){
#ifdef _WIN32
    Sleep(5000);
#else
    std::this_thread::sleep_for(std::chrono::seconds(5));
#endif
}

void clearInput() {
    cin.clear();
    cin.ignore(10000, '\n');
}

const char* scp_logo_and_menu =
    "=================================== [SCIENTIST INTERFACE] ===================================  \n"
    "AVAILABLE COMMANDS:                                             _ _ _ _ _ _ _ _ _              \n"
    " 1. to add an employee                                         |                 |             \n"
    " 2. to delete an employee                                      |                 |             \n"
    " 3. to trigger every person                                    |                 |             \n"
    " 4. to print staff information                               _/                   \\_          \n"
    " 5. to add the SCP                                         _/                       \\_        \n"
    " 6. to delete the SCP                                     /                           \\       \n"
    " 7. to simulate massive breach                           /             | |             \\      \n"
    " 8. to interact the SCP with other SCP/staff            |             _| |_             |      \n"
    " 9. to print SCPs threat report                        |            _~ | | ~_            |     \n"
    " 0. to print menu                                      |           /   | |   \\           |    \n"
    " 10. exit                                             |           /    \\ /    \\           |  \n"
    "                                                      |          |             |          |    \n"
    "                                                      |           \\  / | | \\  /           |  \n"
    "                                                      |            ~/ /   \\ \\~            |  \n"
    "                                                       |           / /~_ _~\\ \\           |   \n"
    "                                                       |          / /       \\ \\          |   \n"
    "                                                      /                                   \\   \n"
    "                                                     /                                     \\  \n"
    "                                                    /                _______                \\ \n"
    "                                                     ~ ~_ _         /       \\         _ _~ ~  \n"
    "                                                          _ _   ~  /         \\  ~   _ _       \n"
    "                                                             ~ ~                  ~ ~          \n"
    "                                                                THE SCP FOUNDATION             \n"
    "\n"
    "ENTER COMMAND > ";


void rules(){
    cout << scp_logo_and_menu;
}

void SCPs(){
    cout << "Which do you want to add" << endl;
    cout << "1. SCP-999" << endl;
    cout << "2. SCP-682" << endl;
    cout << "3. SCP-040" << endl;
    cout << "4. SCP-294" << endl;
    cout << "5. SCP-106" << endl;
    cout << "ENTER NUMBER > ";
}

int main() {
    srand(time(nullptr));
    StaffFoundation staff;
    ContainmentUnit unit(&staff);
    size_t index;
    int input = 0;
    
    clearConsole();
    rules();
    
    while (input != 10) {
        if (!(cin >> input)) {
            clearInput();
            continue;
        }
        
        switch (input) {
            case 0:
                clearConsole();
                rules();
                break;
                
            case 1: {
                enter();
                D_class* person = new D_class();
                string name = person->getHumanName();
                staff.addPerson(person);
                enter();
                cout << "D_class " << name << " successfully was delivered to your complex" << endl;
                sleep();
                clearConsole();
                rules();
                break;
            }
            
            case 2: {
                enter();
                cout << "Print number of employee you want to delete " << endl;
                enter();
                cout << " === FOUNDATION EMPLOYEES === " << endl;
                staff.printPersonalInformation();
                enter();
                if (!(cin >> index)) {
                    clearInput();
                    break;
                }
                
                Human* person = staff.returnHumanByIndex(index - 1);
                if (person) {
                    string name = person->getHumanName();
                    staff.releasePersonByIndex(index - 1);
                    enter();
                    cout << name << " was fired" << endl;
                }
                sleep();
                clearConsole();
                rules();
                break;
            }
            
            case 3:
                enter();
                staff.triggerEveryPerson();
                sleep();
                clearConsole();
                rules();
                break;
                
            case 4:
                enter();
                cout << " === FOUNDATION EMPLOYEES === " << endl;
                staff.printPersonalInformation();
                sleep();
                clearConsole();
                rules();
                break;
                
            case 5: {
                enter();
                SCPs();
                if (!(cin >> input)) {
                    clearInput();
                    break;
                }
                
                switch (input) {
                    case 1: {
                        SCP999* scp = new SCP999();
                        string name = scp->getAnomalyName();
                        unit.addAnomaly(scp);
                        enter();
                        cout << name << " was successfully delivered to your complex" << endl;
                        break;
                    }
                    
                    case 2: {
                        SCP682* scp = new SCP682(&staff);
                        string name = scp->getAnomalyName();
                        unit.addAnomaly(scp);
                        enter();
                        cout << name << " was successfully delivered to your complex" << endl;
                        break;
                    }
                    
                    case 3: {
                        SCP040* scp = new SCP040(&staff);
                        string name = scp->getAnomalyName();
                        unit.addAnomaly(scp);
                        enter();
                        cout << name << " was successfully delivered to your complex" << endl;
                        break;
                    }
                    
                    case 4: {
                        SCP294* scp = new SCP294(&staff);
                        string name = scp->getAnomalyName();
                        unit.addAnomaly(scp);
                        enter();
                        cout << name << " was successfully delivered to your complex" << endl;
                        break;
                    }
                    
                    case 5: {
                        SCP106* scp = new SCP106(&staff);
                        string name = scp->getAnomalyName();
                        unit.addAnomaly(scp);
                        enter();
                        cout << name << " was successfully delivered to your complex" << endl;
                        break;
                    }
                }
                sleep();
                clearConsole();
                rules();
                break;
            }
            
            case 6: {
                enter();
                cout << "Print number of SCP you want to delete " << endl;
                enter();
                cout << " === FOUNDATION ANOMALIES === " << endl;
                unit.printThreatReport();
                enter();
                cout << "ENTER NUMBER > ";
                if (!(cin >> index)) {
                    clearInput();
                    break;
                }
                
                SCPentity* scp = unit.returnAnomalyByIndex(index - 1);
                if (scp) {
                    string name = scp->getAnomalyName();
                    unit.releaseAnomalyByIndex(index - 1);
                    enter();
                    cout << name << " was threw out from the complex" << endl;
                }
                sleep();
                clearConsole();
                rules();
                break;
            }
            
            case 7:
                enter();
                unit.simulateMassBreach();
                sleep();
                clearConsole();
                rules();
                break;
                
            case 8: {
                enter();
                cout << "Pick the SCP that will interact with other" << endl;
                enter();
                cout << " === FOUNDATION ANOMALIES === " << endl;
                unit.printThreatReport();
                enter();
                cout << "ENTER NUMBER > ";
                if (!(cin >> index)) {
                    clearInput();
                    break;
                }
                
                SCPentity* scp = unit.returnAnomalyByIndex(index - 1);
                if (!scp) {
                    sleep();
                    rules();
                    break;
                }
                
                enter();
                cout << "Choose with whom " << scp->getAnomalyName() << " will interact" << endl;
                enter();
                cout << "1. Other SCP" << endl;
                cout << "2. Employee" << endl;
                enter();
                cout << "ENTER NUMBER > ";
                if (!(cin >> input)) {
                    clearInput();
                    break;
                }
                
                switch(input) {
                    case 1: {
                        enter();
                        cout << " === FOUNDATION ANOMALIES === " << endl;
                        cout << "Pick the SCP " << scp->getAnomalyName() << " will interact" << endl;
                        enter();
                        unit.printThreatReport();
                        enter();
                        cout << "ENTER NUMBER > ";
                        if (!(cin >> index)) {
                            clearInput();
                            break;
                        }
                        
                        SCPentity* otherscp = unit.returnAnomalyByIndex(index - 1);
                        if (otherscp) {
                            enter();
                            scp->interact(otherscp);
                        }
                        break;
                    }
                    
                    case 2: {
                        enter();
                        cout << "Pick the employee " << scp->getAnomalyName() << " will interact" << endl;
                        enter();
                        cout << " === FOUNDATION EMPLOYEES === " << endl;
                        staff.printPersonalInformation();
                        enter();
                        cout << "ENTER NUMBER > ";
                        if (!(cin >> index)) {
                            clearInput();
                            break;
                        }
                        
                        Human* person = staff.returnHumanByIndex(index - 1);
                        if (person) {
                            enter();
                            scp->interact(person);
                        }
                        break;
                    }
                }
                sleep();
                clearConsole();
                rules();
                break;
            }
            
            case 9:
                enter();
                cout << " === FOUNDATION ANOMALIES === " << endl;
                unit.printThreatReport();
                sleep();
                clearConsole();
                rules();
                break;
        }
    }
    
    return 0;
}