#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <atomic>
#include <ctime>
#include <cstdio>
#include "test.h"

ContainmentUnit c;
std::atomic<int> timeMinutes(0);

void timeThread(){
    while (true){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        timeMinutes++;
        if (timeMinutes.load()%2==0){
            int chance=rand()%2;
            if(chance==1){
                int var=rand()%c.SCPcount();
                c.randomInterecation(var);
            }
        }
    }
}


void printtime(){
    int timic=timeMinutes.load();
    std::cout<<timic<<std::endl;
}
int scp173=0;
int scp294=0;
int scp049=0;
int scp939=0;
int temptime=0;
int temtime2=0;
void action2(int pick, ContainmentUnit& c){
    int a;
    switch(pick){
        case 1:
            std::cout<<"Pick an SCP to add"<<std::endl;
            std::cout<<"1) SCP-173"<<std::endl;
            std::cout<<"2) SCP-294"<<std::endl;
            std::cout<<"3) SCP-049"<<std::endl;
            std::cout<<"4) SCP-939"<<std::endl;
            std::cout<<"5) D-class Personnel"<<std::endl;
            std::cout<<"\n";
            std::cin>>a;
            if(a==1 and scp173==0){c.addAnomaly(new SCP173()); scp173=1;}
            else if(a==2 and scp294==0){c.addAnomaly(new SCP294()); scp294=1;}
            else if(a==3 and scp049==0){c.addAnomaly(new SCP049()); scp049=1;}
            else if(a==4 and scp939==0){c.addAnomaly(new SCP939()); scp939=1;}
            else if(a==5){c.addAnomaly(new DclassPersonel());}
            else std::cout<<"SCP already here or invalid choice"<<std::endl;
            std::cout<<"\n";
                break;   
        case 2:
            if(c.isEmpty()){
                std::cout<<"No SCPs"<<std::endl;
                std::cout<<"\n";
                break;
            }
            else{c.printList();
                std::cin>>a;
                if(a==0){break;}
                else{
                    c.exterminateSCP(a-1);
                    std::cout<<"SCP terminated"<<std::endl;
                    std::cout<<"\n";
                    break;
                }
            }
        case 3:
            c.printThreatReport();
            std::cout<<"\n";
            break;
        case 4:
            if(c.isEmpty()){
                std::cout<<"No SCPs"<<std::endl;
                std::cout<<"\n";
                break;
            }
            else{
                c.printList();
                std::cout<<"\n";
                std::cin>>a;
                c.checkInfo(a-1);
                std::cout<<"\n";
                break;
            }
        
    }
}
void action(int pick, ContainmentUnit& c){
    int a;
    int pick2;
    switch(pick){
        case 1:
            while(true){
                std::cout<<"Time: "<<timeMinutes.load()<<"\n\n";
                std::cout<<"1) Manage SCP and personen\n";
                std::cout<<"2) Delete SCP\n";
                std::cout<<"3) List SCP\n";
                std::cout<<"4) Get descrition\n";
                std::cout<<"0) Back\n";
                std::cout<<"\n";
                std::cin>>pick2;
                std::cout<<"\n";
                if(pick2==0) break;
                action2(pick2,c);
                
            }
            break;
        case 2:
            c.checkInteractions();
            std::cout<<"\n";
            break;
        case 3:
            if(c.isEmpty()){
                std::cout<<"No SCPs"<<std::endl;
                std::cout<<"\n";
                break;
            }
            else{c.printList();
                std::cin>>a;
                c.simulateInteraction(a-1);
                std::cout<<"\n";
                break;
            }
        case 4:
            if(temptime==0){
                c.FixBreach();
                temptime=timeMinutes.load();
            }
            else if(timeMinutes.load()-temptime<5){
                std::cout<<"Group isn't ready, wait "<<6-(timeMinutes.load()-temptime)<<std::endl;
            }
            else if(timeMinutes.load()-temptime>=5){
                c.FixBreach();
                temptime=timeMinutes.load();
            }
            break;
        case 5:
            if(temtime2==0){
                c.Sendpatrol();
                temtime2=timeMinutes.load();
            }
            else if(timeMinutes.load()-temtime2<10){
                std::cout<<"You've sent a patrol recently, wait "<<11-(timeMinutes.load()-temtime2)<<std::endl;
            }
            else if(timeMinutes.load()-temtime2>=10){
                c.Sendpatrol();
                temtime2=timeMinutes.load();
            }
            break;
        case 7:
            printtime();
            std::cout<<"\n";
            break;
        default: std::cout<<std::endl; break;    
    }
}

int main()
{
    std::srand(std::time(0));
    
    std::thread timer(timeThread);
    timer.detach();
    int pick;
    c.addAnomaly(new SCP049());
    c.addAnomaly(new SCP939());
    scp049=1;
    scp939=1;
    c.addAnomaly(new DclassPersonel());
    while(true){
        
        std::cout<<"\n===== MENU =====\n";
        std::cout<<"Time: ";
        printtime();
        std::cout<<"\n";
        std::cout<<"1) Manage SCP and personen\n";
        std::cout<<"2) Make someone interact with an SCP\n";
        std::cout<<"3) Get status\n";
        std::cout<<"4) Fix breach\n";
        std::cout<<"5) Send patrol\n";
        std::cout<<"0) EXIT\n";
        std::cin>>pick;
        std::cout<<"\n";
        if (pick==0) break;
        action(pick,c);
    }
    return 0;
}