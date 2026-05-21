#ifndef test_h
#define test_h

class ThreatClass{
private:
    std::string name;
    std::string description;
    int dangerLevel;
    std::string number;
public:
    ThreatClass(std::string n, std::string desc, std::string num, int dn):name(n),description(desc),number(num),dangerLevel(dn){}
    std::string getName() const{return name;}
    std::string getDescription() const{return description;}
    std::string getSCPnumber() const{return number;}
    int getDl() const{return dangerLevel;}
};

class MTFunit{
protected:
    std::string Cname;
    int DlCanHandle;
    int isfixgroup;
public:
    MTFunit(std::string n, int dl,int fg): Cname(n), DlCanHandle(dl),isfixgroup(fg){}
    std::string getName() const{return Cname;}
    int getDl() const{return DlCanHandle;}
    int getIseng() const{return isfixgroup;}
};

class MTF9tailedFox: public MTFunit
{
private:
public:
    MTF9tailedFox():MTFunit("Nine tailed fox", 5,0){}
    
};
class EngerneerGroup: public MTFunit
{
private:
public:
    EngerneerGroup():MTFunit("Engeneer Group",1,1){}
};

class SCPEntity
{
protected:
    ThreatClass threatClass;
    std::string description;
    int containmentdifficulty;
    std::string number;
public:
    SCPEntity(ThreatClass tc,std::string desc, std::string num):threatClass(tc),description(desc),number(num){}
    virtual void triggerAnomaly()=0;
    virtual std::string getContainmentProcedure()=0;
    virtual void interact(SCPEntity *other)=0;
    virtual std::string getAnomalyType()=0;
    virtual int getIsbreach()=0;
    virtual void setIsbreach(int a)=0;
    

    ThreatClass getThreatClass() const {return threatClass;}
    std::string getSCPnumber() const{return threatClass.getSCPnumber();}
    std::string getDescprition() const{return description;}
    virtual ~SCPEntity()=default;
};

class SCP094_2:public SCPEntity
{
private:
    int isbreach=0;
public:
    int getIsbreach() override{
        return isbreach;
    }
    void setIsbreach(int a) override{
        isbreach=a;
    }
    SCP094_2():SCPEntity(ThreatClass("Euclid","Zombie","049-2",2),"SCP-049-2 instances are reanimated corpses that have been operated on by SCP-049. These instances do not seem to retain any of their prior memories or mental functions, having only basic motor skills and response mechanisms. While these instances are generally inactive, moving very little and in a generally ambulatory fashion, they can become extremely aggressive if provoked, or if directed to by SCP-049. SCP-049-2 instances express active biological functions, though these are vastly different from currently understood human physiology. Despite these alterations, SCP-049 often remarks that the subjects have been \"cured\"","049-2")
    {}
    std::string getAnomalyType() override{
        return "Humanoid";
    }
    std::string getContainmentProcedure() override{
        return "TERMINATE";
    }
    void interact(SCPEntity *other) override{
        std::cout<<"SCP-049 groans at "<<other->getSCPnumber()<<std::endl;
    }
    void triggerAnomaly() override{
        std::cout<<"SCP-049-2 groans\n";
    }
};
class SCP049 : public SCPEntity{
private:
    int isbreach=0;
    std::vector<int> SCP049stances;
public:
    void setIsbreach(int a) override{
        isbreach=a;
    }
    int getIsbreach() override{
        return isbreach;
    }
    SCP049():SCPEntity(ThreatClass("Euclid", "Plague doctor", "049",3),
        "SCP-049 is a humanoid entity, roughly 1.9 meters in height, which bears the appearance of a medieval plague doctor. While SCP-049 appears to be wearing the thick robes and the ceramic mask indicative of that profession, the garments instead seem to have grown out of SCP-049's body over time, and are now nearly indistinguishable from whatever form is beneath them. X-rays indicate that despite this, SCP-049 does have a humanoid skeletal structure beneath its outer layer. SCP-049 is capable of speech in a variety of languages, though tends to prefer English or medieval French. While SCP-049 is generally cordial and cooperative with Foundation staff, it can become especially irritated or at times outright aggressive if it feels that it is in the presence of what it calls the \"Pestilence\". Although the exact nature of this Pestilence is currently unknown to Foundation researchers, it does seem to be an issue of immense concern to SCP-049. SCP-049 will become hostile with individuals it sees as being affected by the Pestilence, often having to be restrained should it encounter such. If left unchecked, SCP-049 will generally attempt to kill any such individual; SCP-049 is capable of causing all biological functions of an organism to cease through direct skin contact. How this occurs is currently unknown, and autopsies of SCP-049's victims have invariably been inconclusive. SCP-049 has expressed frustration or remorse after these killings, indicating that they have done little to kill \"The Pestilence\", though will usually seek to then perform a crude surgery on the corpse using the implements contained within a black doctor's bag it carries on its person at all timesWhile these surgeries are not always \"successful\", they often result in the creation of instances of SCP-049-2.","049")
        {SCP049stances={1, 0};}
    std::string getAnomalyType() override{
        return "Humanoid";
    }
    std::string getContainmentProcedure() override{
        return "SCP-049 is contained within a Standard Secure Humanoid Containment Cell in Research Sector-02 at Site-19. SCP-049 must be sedated before any attempts to transport it. During transport, SCP-049 must be secured within a Class III Humanoid Restriction Harness (including a locking collar and extension restraints) and monitored by no fewer than two armed guards.\nWhile SCP-049 is generally cooperative with most Foundation personnel, outbursts or sudden changes in behaviour are to be met with elevated force. Under no circumstances should any personnel come into direct contact with SCP-049 during these outbursts. In the event SCP-049 becomes aggressive, the application of lavender (L. multifida) has been shown to produce a calming effect on the entity. Once calmed, SCP-049 generally becomes compliant, and will return to containment with little resistance.\nIn order to facilitate the ongoing containment of SCP-049, the entity is to be provided with the corpse of a recently deceased animal (typically a bovine or other large mammal) once every two weeks for study. Corpses that become instances of SCP-049-2 are to be removed from SCP-049's containment cell and incinerated. SCP-049 is no longer permitted to interact with human subjects, and requests for human subjects are to be denied.\n ";
    }
    void triggerAnomaly() override{
        int stance = SCP049stances[rand() % SCP049stances.size()];
        if(isbreach==0 && stance==1){
            std::cout<<"SCP-049 is inside it's chamber and ready to talk"<<std::endl;
        }
        else if(isbreach==0 && stance==0){
            std::cout<<"SCP-049 is inside it's chamber, but not willing to talk"<<std::endl;
        }
        else if(isbreach==1){
            std::cout<<"SCP-049 not detetected inside it's chamber!"<<std::endl;
        }
    }
    int chance;
    int makechance(){
        chance=rand()%2;
        return chance;
    }
    void interact(SCPEntity* other) override{
        makechance();
        if(other->getAnomalyType()=="Humanoid"){
            if(chance==1){
                std::cout<<"SCP-049 found Pestilence in personel"<<std::endl;
            }
            else{
                std::cout<<"SCP-049 and personel had and conversation"<<std::endl;
            }
        }
        else std::cout<<"Nothing happened"<<std::endl;
    }
    int getChance() const{return chance;}
};

class SCP939:public SCPEntity
{
private:
    int isbreach=0;
    int ChamberCondition=5;
public:
    int getIsbreach() override{
        return isbreach;
    }
    void setIsbreach(int a) override{
        isbreach=a;
    }
    int getChamberCondition(){
        return ChamberCondition;
    }
    void MaintainChamber(){
        ChamberCondition=5;
    }
    void decreeseChamberCondition(){
        ChamberCondition=ChamberCondition-1;
    }
    void fixChamber(int a){
        if (a==1){
            ChamberCondition=5;
        }
        else{
            std::cout<<"Group can't fix that\n";
        }
    }
    SCP939():SCPEntity(ThreatClass("Keter","With many voices","939",4),
        "SCP-939 are endothermic, pack-based predators which display atrophy of various systems similar to troglobitic organisms. The skins of SCP-939 are highly permeable to moisture and translucent red, owing to a compound chemically similar to hemoglobin. SCP-939 average 2.2 meters tall standing upright and weigh an average of 250 kg, though weight is highly variable. Each of their four limbs end in three-fingered claws with a fourth, opposable digit, and are covered in setae which considerably augment climbing ability. Their heads are elongated, devoid of even vestigial eyes or eye sockets, and contain no brain casing. The jaws of SCP-939 are lined with red, faintly luminescent fang-like teeth, similar to those belonging to specimens of the genus Chauliodus, up to 6 cm in length, and encircled by heat-sensitive pit organs. Eye spots, sensitive to light and dark, run the length of their spined dorsal ridges. These spines may be up to 16 cm long and are believed to be sensitive to changes in air pressure and flow.\nSCP-939 do not possess many vital organ systems; central and peripheral nervous systems, circulatory system, and digestive tract are all absent. SCP-939's respiratory system is atrophied and serves no apparent purpose beyond spreading AMN-C227 (see below). SCP-939 have no apparent physiological need to feed, nor any way to digest consumed tissue. Ingested material typically accumulates in the respiratory system of SCP-939 and is regurgitated once the amount is sufficient to markedly inhibit its function. Despite the absence of many vital organ systems, SCP-939 are capable of bearing live young.\nSCP-939's primary method of luring prey is the imitation of human speech in the voices of prior victims, though imitation of other species and active nocturnal hunts have been documented. SCP-939 vocalizations often imply significant distress; whether SCP-939 understand their vocalizations or are repeating previously heard phrases is the subject of ongoing study. How SCP-939 acquire voices is not currently understood; specimens have been documented imitating victims despite never hearing the victim speak. Analysis of SCP-939 vocalizations cannot distinguish between SCP-939 and samples of known victims' voices. The use of biometric voice-recognition security or identification systems at any installation housing SCP-939 is strongly discouraged for this reason. Prey is usually killed with a single bite to the cranium or neck; bite forces have been measured in excess of 35 MPa.\n","939")
        {}
    std::string getContainmentProcedure() override{
        return "SCP-939-1, -3, -19, -53, -89, -96, -98, -99, and -109 are kept in Cell 1163-A or 1163-B, 10 m x 10 m x 3 m containment chambers within Armed Bio-Containment Area-14. Both cells are environmentally regulated and negatively pressurized, with walls constructed of reinforced concrete. Access to these cells is regulated by an outer decontamination chamber and inner gas-tight steel security doors. Observation windows are constructed of laminated ballistics glass 10 cm in thickness protected by a 100kV electrified mesh. Humidity is maintained at 100% at a temperature of 16° C. Specimens are monitored at all times via infrared cameras. Level Four authorization is required to access SCP-939, their containment areas, or the observation chambers.\nSCP-939-101 is dismembered and stored in Cryogenic Preservation Tanks 939-101A to 939-101M within Bio-Research Area-12. Access to SCP-939-101 requires authorization by two Clearance Level 3 personnel, one of which must be present for all research and testing. The contents of only one (1) 939-101 tank may be accessed at any given time. Core temperature of SCP-939-101 tissues must be monitored while removed from cryogenic preservation; should core temperature exceed 10° C, tissues are to be returned to their corresponding tank and all testing suspended for a period of seventy-two (72) hours. Barring core temperature exceeding 10° C, research of SCP-939-101 tissues may continue as long as its ramblings and pleas for release may be tolerated.\n";
    }
    std::string getAnomalyType() override{
        return "Anomalous creature";
    }
    void triggerAnomaly() override{
        if(isbreach==0){
            std::cout<<"SCP-939 inside it's chamber"<<std::endl;
            std::cout<<"SCP-939 chamber condition is "<<ChamberCondition<<std::endl;
        }
        else{
            std::cout<<"SCP-939 has breached!"<<std::endl;
        }
    }
    void interact(SCPEntity *other) override{
        if(isbreach==0){
            std::cout<<"Nothing happened"<<std::endl;
        }
        else{
            std::cout<<"Unavialable"<<std::endl;
        }
    }
};

class SCP173 : public SCPEntity{
private:
    int isbreach=0;
    std::vector<std::string> SCP173stances;
public:
    void setIsbreach(int a) override{
        isbreach=a;
    }
    int getIsbreach() override{
        return isbreach;
    }
    SCP173():SCPEntity(ThreatClass("Euclid","Anomalous statue","173",3), "It is constructed from concrete and rebar with traces of Krylon brand spray paint. SCP-173 is animate and extremely hostile. The object cannot move while within a direct line of sight. Line of sight must not be broken at any time with SCP-173. Personnel assigned to enter container are instructed to alert one another before blinking. Object is reported to attack by snapping the neck at the base of the skull, or by strangulation. In the event of an attack, personnel are to observe Class 4 hazardous object containment procedures.","173")
        {SCP173stances={"SCP-173 is inside it's container","SCP-173 secreted the substance"};}
    std::string getAnomalyType() override {
        return "Anomalous creature";
    }

    void triggerAnomaly() override {
        std::string stance = SCP173stances[rand() % SCP173stances.size()];
        if(isbreach==0){
            std::cout<<stance<<std::endl;
        }
        else{
            std::cout<<"SCP-173 breach detected!"<<std::endl;
        }
    }
    std::string getContainmentProcedure() override {
        return "Item SCP-173 is to be kept in a locked container at all times. When personnel must enter SCP-173's container, no fewer than 3 may enter at any time and the door is to be relocked behind them. At all times, two persons must maintain direct eye contact with SCP-173 until all personnel have vacated and relocked the container.";
    }
    void interact(SCPEntity* other) override {
        if (other->getAnomalyType()=="Humanoid") {
            std::cout << "SCP-173 killed "<<other->getSCPnumber()<<std::endl;
        }
        else std::cout<<"Nothing happened"<<std::endl;
    }
};

class SCP294 : public SCPEntity{
private:
    int isbreach=0;
    std::vector<std::string> availableLiquids;
    int usageCount;
public:
    void setIsbreach(int a) override{
        isbreach=a;
    }
    int getIsbreach() override{
        return isbreach;
    }
    SCP294(): SCPEntity(
        ThreatClass("Euclid", "Anomalous liquid generation","294",2),
        "Coffee machine producing any liquid","294"),
        usageCount(0){
        availableLiquids = {"coffee", "water", "[DATA EXPUNGED]", "amogus"};
    }

    std::string getAnomalyType() override {
        return "Anomalous Device";
    }

    void triggerAnomaly() override {
        std::string liquid = availableLiquids[rand() % availableLiquids.size()];
        std::cout << "SCP-294 produces: " << liquid << std::endl;
        usageCount++;
    }

    std::string getContainmentProcedure() override {
        return "Store in secured area. Prohibited to request [DATA EXPUNGED] liquids.";
    }

    void interact(SCPEntity* other) override {
        if (other->getAnomalyType() == "Humanoid") {
            std::cout << "SCP-294 offers drink to humanoid\n";
        }
        else std::cout<<"Nothing happened"<<std::endl;
    }

    void resetUsage() {
        usageCount = 0;
    }
};


class DclassPersonel:public SCPEntity
{
private:
    int isbreach=0;
public:
    int getIsbreach() override{
        return isbreach;
    }
    void setIsbreach(int a) override{
        isbreach=a;
    }
    DclassPersonel():SCPEntity(ThreatClass("None","Mere human",std::to_string(rand()%9000+1000),0),"D-Class personnel are hired individuals — often selected from prisons — whose task is to participate in Foundation activities that involve life-threatening risk.",std::to_string(rand()%9000+1000))
    {}

    std::string getAnomalyType() override{
        return "Humanoid";
    }
    std::string getContainmentProcedure() override{
        return "Contain in D-class block";
    }
    void triggerAnomaly() override{
        std::cout<<"D-class is in D-block\n";
    }
    void interact(SCPEntity *other) override{
        if(other->getDescprition()==this->getDescprition()){
            std::cout<<"D-"<<this->getSCPnumber()<<" staring at D-"<<other->getSCPnumber()<<std::endl;
        }
        else std::cout<<"D-class looking at "<<other->getSCPnumber()<<std::endl;
    }
};


class ContainmentUnit{
private:
    std::vector<SCPEntity*>anomalies;
    std::vector<MTFunit*>FoundSquads;
    friend SCP049;
public:
    ContainmentUnit(){
        FoundSquads.push_back(new MTF9tailedFox());
        FoundSquads.push_back(new EngerneerGroup());
    }
    bool isEmpty() const {return anomalies.empty();}
    int SCPcount() const {return anomalies.size();}
    void addAnomaly (SCPEntity *anomaly){anomalies.push_back(anomaly);}
    void simulateMassInteraction(){
        for (auto *anomaly:anomalies) {
            anomaly->triggerAnomaly();
        }
    }
    void simulateInteraction(int n){
        if(n<0 || n>=anomalies.size()) {std::cout<<"Input error 1"<<std::endl; return;}{
            anomalies[n]->triggerAnomaly();
        }
    }

    void Sendpatrol(){
        int a;
        if(FoundSquads.size()!=0){
            std::cout<<"Choose patrol squad"<<std::endl;
            for(int i=0;i<FoundSquads.size();++i){
                std::cout<<i+1<<") "<<FoundSquads[i]->getName()<<std::endl;
            }
        }
        else std::cout<<"\nNo MTF units left\n\n";
        std::cin>>a;
        if(a>FoundSquads.size()){
            std::cout<<"Input error 1"<<std::endl;
            return;
        }
        if(FoundSquads[a-1]->getDl()>2){
            bool flag=true;
            for(int n=0;n<anomalies.size();++n){
                if(anomalies[n]->getIsbreach()==1){
                    std::cout<<FoundSquads[a-1]->getName()<<" detected breach of SCP-"<<anomalies[n]->getSCPnumber()<<std::endl;
                    flag=false;
                    if(FoundSquads[a-1]->getDl()<anomalies[n]->getThreatClass().getDl()){
                        delete FoundSquads[a-1];
                        FoundSquads.erase(FoundSquads.begin()+(a-1));
                        std::cout<<"The group died in process\n\n";
                    }
                }
            }
            if(flag) std::cout<<"Group hasn't detected anything\n";
        }
    }
    void FixBreach(){
        int a;
        int b;
        if(FoundSquads.size()!=0){
            std::cout<<"Choose squad to react"<<std::endl;
            for(int i=0;i<FoundSquads.size();++i){
                std::cout<<i+1<<") "<<FoundSquads[i]->getName()<<std::endl;
            }
        }
        else std::cout<<"\nNo MTF units left\n";
        std::cin>>a;
        std::cout<<"Pick to what ro react askndanda\n";
        printList();
        std::cin>>b;
        if(a>FoundSquads.size() || b>anomalies.size()){
            std::cout<<"Input error 2"<<std::endl;
            return;
        }
        if(anomalies[b-1]->getIsbreach()==1){
            if(FoundSquads[a-1]->getDl()>anomalies[b-1]->getThreatClass().getDl()){
                anomalies[b-1]->setIsbreach(0);
                std::cout<<"Group managed to contain an SCP\n\n";
            }
            else{
                delete FoundSquads[a-1];
                FoundSquads.erase(FoundSquads.begin()+(a-1));
                std::cout<<"Group has failed\n\n";
            }
        }
        else if(anomalies[b-1]->getSCPnumber()=="939"){
            SCP939 *scp939p=dynamic_cast<SCP939*>(anomalies[b-1]);
            if(scp939p->getChamberCondition()<5){
                std::cout<<"Chamber needs a maintanse\nCurrent condition is "<<scp939p->getChamberCondition()<<std::endl;
                scp939p->fixChamber(FoundSquads[a-1]->getIseng());
            }
        }
        else{
            std::cout<<"Command: Do not send group without any need\n\n";
        }
    }
    void randomInterecation(int n){
        if(anomalies[n]->getSCPnumber()=="939"){
            SCP939 *scp939p=dynamic_cast<SCP939*>(anomalies[n]);
            if(scp939p->getChamberCondition()==0){
                anomalies[n]->setIsbreach(1);
            }
            else{
                int chance=rand()%100;
                if(chance<40){
                    scp939p->decreeseChamberCondition();
                }
            }
        }
        else if(anomalies[n]->getSCPnumber()=="049"){
            //SCP049 *scp049p=dynamic_cast<SCP049*>(anomalies[n]);
            if(anomalies[n]->getIsbreach()==0){
                int chance=rand()%100;
                if(chance<35){
                    anomalies[n]->setIsbreach(1);
                }
            }
            else if(anomalies[n]->getIsbreach()==1){
                auto it=std::find_if(anomalies.begin(),anomalies.end(),[](SCPEntity *obj){
                    DclassPersonel *dcalss=dynamic_cast<DclassPersonel*>(obj);
                    return dcalss!=nullptr;
                }
            );
                if(it!=anomalies.end()){
                    provideInteraction("049");
                }
            }
        }
        else if(anomalies[n]->getSCPnumber()=="173"){
            //SCP173 *scp173p=dynamic_cast<SCP173*>(anomalies[n]);
            if(anomalies[n]->getIsbreach()==0){
                int chance=rand()%100;
                if(chance<45){
                    anomalies[n]->setIsbreach(1);
                }
            }
            else if(anomalies[n]->getIsbreach()==1){
                auto it=std::find_if(anomalies.begin(),anomalies.end(),[](SCPEntity *obj){
                    DclassPersonel *dcalss=dynamic_cast<DclassPersonel*>(obj);
                    return dcalss!=nullptr;
                }
            );
                if(it!=anomalies.end()){
                    provideInteraction("173");
                }
            }
        }
    }
    void provideInteraction(std::string name){
        int a;
        int b;
        if(name=="049"){
            for(size_t i=0;i<anomalies.size();++i){
                if(anomalies[i]->getSCPnumber()=="049") a=i;
                else if(anomalies[i]->getThreatClass().getDescription()=="Mere human") b=i;
            }
            anomalies[a]->interact(anomalies[b]);
            SCP049 *scp049p=dynamic_cast<SCP049*>(anomalies[a]);
            if(scp049p->getChance()==1){
                delete anomalies[b];
                anomalies.erase(anomalies.begin()+b);
                return addAnomaly(new SCP094_2());
            }
        }
        else if(name=="173"){
            for(size_t i=0;i<anomalies.size();++i){
                if(anomalies[i]->getSCPnumber()=="173") a=i;
                else if(anomalies[i]->getThreatClass().getDescription()=="Mere human") b=i;
            }
            anomalies[a]->interact(anomalies[b]);
        }
    }
    void checkInteractions(){
        if(anomalies.size()<2){
            std::cout<<"Not enough SCP"<<std::endl;
            return;
        }
        std::cout<<"Available SCPs: "<<std::endl;
        printList();
        size_t a,b;
        std::cout<<"Input first SCP"<<std::endl;
        std::cin>>a;
        std::cout<<"Input second SCP"<<std::endl;
        std::cin>>b;
        a=a-1;
        b=b-1;
        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(1000,'\n');
            std::cout<<"Input error1"<<std::endl;
            }
        if(a>=anomalies.size() or b>=anomalies.size()){
            std::cout<<"Input error2"<<std::endl;
            return;
        }
        else anomalies[a]->interact(anomalies[b]);
        if(anomalies[a]->getSCPnumber()=="049"&&anomalies[b]->getThreatClass().getDescription()=="Mere human"){
            SCP049 *scp049p=dynamic_cast<SCP049*>(anomalies[a]);
            if(scp049p->getChance()==1){
                delete anomalies[b];
                anomalies.erase(anomalies.begin()+b);
                return addAnomaly(new SCP094_2());
            }
        }
        else if(anomalies[a]->getSCPnumber()=="173"&&anomalies[b]->getThreatClass().getDescription()=="Mere human"){
            //SCP173 *scp173p=dynamic_cast<SCP173*>(anomalies[a]);
            if(anomalies[a]->getIsbreach()==1){
                delete anomalies[b];
                anomalies.erase(anomalies.begin()+b);
            }
        }
    }
    void exterminateSCP(int a){
        delete anomalies[a];
        anomalies.erase(anomalies.begin()+a);
    }
    void printThreatReport(){
        for(auto *anomaly:anomalies){
            if(anomaly->getThreatClass().getDescription()=="Mere human"){
                std::cout<<"D-"<<anomaly->getThreatClass().getSCPnumber()<<"  "<<anomaly->getThreatClass().getName()<<" | Type: "<<anomaly->getAnomalyType()<<std::endl;
            }
            else std::cout<<"SCP-"<<anomaly->getThreatClass().getSCPnumber()<<"  "<<anomaly->getThreatClass().getName()<<" | Type: "<<anomaly->getAnomalyType()<<std::endl;
        }
    }
    void printList(){
        for(size_t i=0;i<anomalies.size();++i){
            if(anomalies[i]->getThreatClass().getDescription()=="Mere human"){
                std::cout<<i+1<<") "<<"D-"<<anomalies[i]->getThreatClass().getSCPnumber()<<" "<<anomalies[i]->getThreatClass().getName()<<std::endl;
            }
            else std::cout<<i+1<<") "<<"SCP-"<<anomalies[i]->getThreatClass().getSCPnumber()<<" "<<anomalies[i]->getThreatClass().getName()<<std::endl;
        }
        std::cout<<"Press 0 to cancel\n";
    }
    void checkInfo(int a){
        std::cout<<"Description: "<<anomalies[a]->getDescprition()<<"\n\nContainment procedure: s"<<anomalies[a]->getContainmentProcedure()<<std::endl;
    }

    ~ContainmentUnit(){
        for(auto *anomaly:anomalies){
            delete anomaly;
        }
    }
};

#endif