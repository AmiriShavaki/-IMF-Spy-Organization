#ifndef SPY_H
#define SPY_H

#include <string>
#include "StringUtility.h"

using namespace std;

const int snnLength = 6;

class Spy {
    private:
    char* name;
    char* family;
    char* snn;
    int missionInd;
    char* personalCode;
    int tag;
    int nameLength;
    int familyLength;
    bool removed;

    public:
    Spy(string name, string family, string snn);
    bool validGivenInfo;
    const bool operator==(Spy given) const;
    const char* getSnn() const;
    const int getMissionInd() const;
    const string operator+(string personalInfo);
    const char* getName() const;
    const char* getFamily() const;
    const int getTag() const;
    void setMission(int ind);
    const int setTag(int tag);
    const int getNameLength() const;
    const int getFamilyLength() const;
    const bool isRemoved() const;
    void remove();
    const char* getPersonalCode() const;
};

const char* Spy::getPersonalCode() const {
    return personalCode;
}

void Spy::remove() {
    removed = true;
}

const bool Spy::isRemoved() const {
    return removed;
}

const int Spy::getNameLength() const {
    return nameLength;
}

const int Spy::getFamilyLength() const {
    return familyLength;
}

const int Spy::setTag(int tag) {
    return this -> tag = tag;
}

void Spy::setMission(int ind) {
    missionInd = ind;
}

const int Spy::getTag() const {
    return tag;
}

const string Spy::operator+(string personalInfo) {
    personalCode = new char [snnLength + 3];
    for (int i = 0; i < snnLength + 2; i++) {
        personalCode[i] = personalInfo[i];
    }
    personalCode[snnLength + 2] = '\0';
    return personalInfo;
}

const char* Spy::getName() const {
    return name;
}

const char* Spy::getFamily() const {
    return family;
}

const int Spy::getMissionInd() const {
    return missionInd;
}

const char* Spy::getSnn() const {
    return snn;
}

const bool Spy::operator==(Spy given) const {
    for (int i = 0; i < snnLength; i++) {
        if (snn[i] != given.snn[i]) {
            return false;
        }
    }
    return true;
}

Spy::Spy(string name, string family, string snn) {
    //Check for validity
    validGivenInfo = snn.size() == snnLength && StringUtility::isAllLetters(name) && StringUtility::isAllLetters(family) 
    && StringUtility::isAllDigit(snn);

    if (validGivenInfo) {
        //Copy given info

        nameLength = name.size();
        familyLength = family.size();

        this -> name = new char [name.size()];
        for (int i = 0; i < name.size(); i++) {
            (this -> name)[i] = name[i];
        }

        this -> family = new char [family.size()];
        for (int i = 0; i < family.size(); i++) {
            (this -> family)[i] = family[i];
        }        

        this -> snn = new char [snnLength];
        for (int i = 0; i < snnLength; i++) {
            (this -> snn)[i] = snn[i];
        }

        missionInd = -1;
        tag = -1;
        personalCode = NULL;
        removed = false;
    }
}

#endif