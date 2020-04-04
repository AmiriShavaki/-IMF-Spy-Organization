#include <iostream>
#include <string>
#include "Spy.h"
#include <vector>
#include "StringUtility.h"
#include "BreakCypher.h"

using namespace std;

const int numOfMissions = 3;
const string missions[numOfMissions] = {"IdiotErdogan", "SaveRonaldo", "PizzaHell"};
const string countries[numOfMissions] = {"Turkey", "Portugal", "Italy"};

const string getCountry(int ind) {
    return countries[ind];
}

Spy* findTag(const int tag, vector <Spy> &spies) { //Return pointer to the spy with given tag
    for (int i = 0; i < spies.size(); i++) {
        if (spies[i].getTag() == tag && !spies[i].isRemoved()) {
            return &spies[i]; //Found
        }
    }
    return NULL; //Not found
}

const long long SUM_ASCII(const char* s, int n) {
    long long res = 0;
    for (int i = 0; i < n; i++) {
        res += s[i];
    }
    return res;
}

const long long SUM_ASCII(const string s) {
    long long res = 0;
    for (int i = 0; i < s.size(); i++) {
        res += s[i];
    }
    return res;
}

const int findMission(const string mission) { //Return index to the mission with given code
    for (int i = 0; i < numOfMissions; i++) {
        if (mission == missions[i]) { //Found
            return i;
        }
    }
    return -1; //Not found
}

Spy* findSpy(const string snn, vector <Spy> &spies) { //Return pointer to the spy with given snn
    for (int i = 0; i < spies.size(); i++) {
        
        if (spies[i].isRemoved()) {
            continue;
        }

        bool res = true;
        for (int j = 0; j < snnLength; j++) {
            res &= spies[i].getSnn()[j] == snn[j];
        }

        if (res) { //Found
            return &spies[i];
        }
    }
    return NULL; //Not found
}

int main() {
    vector <Spy> spies, members;

    char op; //Operation number
    while (cin >> op) {
        switch (op) {
            case '1': { //registeration spies
                int n; //Number of given spies
                cin >> n;

                for (int i = 0; i < n; i++) {
                    string name, family, snn;
                    cin >> name >> family >> snn;

                    Spy given(name, family, snn);

                    if (given.validGivenInfo) {
                        for (int i = 0; i < spies.size(); i++) { //Check for previous occurness
                            if (spies[i] == given) {
                                given.validGivenInfo = false;
                            }
                        }
                    }

                    if (given.validGivenInfo) { //Successful
                        spies.push_back(given);
                        cout << "Spy " << name << ' ' << family << " with SSN:" << snn << " was registered successfully";
                    } else { //Unsuccessful
                        cout << "Your registration was unsuccessful";
                    }
                    cout << endl;
                }
            }
            break;

            case '2': { //Become member
                int n; //Number of given spies
                cin >> n;

                for (int i = 0; i < n; i++) {                
                    string snn, mission;
                    cin >> snn >> mission;

                    Spy* spyPtr = findSpy(snn, spies);

                    if (spyPtr != NULL && (spyPtr -> getMissionInd()) == -1 && findMission(mission) != -1) { //Check all validity conditions
                        spyPtr -> setMission(findMission(mission));

                        //Calculate personal code
                        string personalCode;
                        for (int i = 0; i < snnLength / 2; i++) {
                            personalCode += (spyPtr -> getSnn())[i];
                        }
                        personalCode += StringUtility::makeLower((spyPtr -> getName())[0]);
                        personalCode += StringUtility::makeLower((spyPtr -> getFamily())[0]);
                        for (int i = snnLength / 2; i < snnLength; i++) {
                            personalCode += (spyPtr -> getSnn())[i];
                        }

                        //Calculate tag
                        const char* name = spyPtr -> getName();
                        int n = spyPtr -> getNameLength();
                        const char* family = spyPtr -> getFamily();
                        int m = spyPtr -> getFamilyLength();
                        int tag = (SUM_ASCII(name, n) + SUM_ASCII(family, m) + SUM_ASCII(personalCode)) % SUM_ASCII("IMF");

                        while (findTag(tag, spies) != NULL) { //Check for same tag
                            tag = (tag + 1) % SUM_ASCII("IMF");
                        }

                        cout << "Agent with personal code:" << (*spyPtr) + personalCode << " and tag:" << spyPtr -> setTag(tag) <<
                        ", We call you for an operation in " << getCountry(findMission(mission));
                    } else {
                        cout << "You couldn't register as an agent";
                    }
                    cout << endl;
                }
            }
            break;

            case '3': { //Break the cypher
                int n; //Number of given cyphers
                cin >> n;

                for (int i = 0; i < n; i++) { 
                    string tag, cypher;
                    cin >> tag >> cypher;
                    
                    //Check all validity conditions
                    if (StringUtility::isAllDigit(tag) && StringUtility::isAllLetters(cypher) && 
                    findTag(StringUtility::convertStringToNumber(tag), spies) != NULL &&
                    (findTag(StringUtility::convertStringToNumber(tag), spies) -> getMissionInd()) != -1) {
                        int mission = findTag(StringUtility::convertStringToNumber(tag), spies) -> getMissionInd();
                        cout << BreakCypher::breakCypher(cypher, mission);
                    } else {
                        cout << "WRONG";
                    }
                    cout << endl;
                }
            }
            break;

            case '4': { //Remove agent(s)
                int n; //Number of given agents
                cin >> n;                

                for (int i = 0; i < n; i++) {
                    string tag, cypher;
                    cin >> tag >> cypher;

                    //Check all validity conditions
                    if (StringUtility::isAllDigit(tag) && StringUtility::isAllLetters(cypher) && 
                    findTag(StringUtility::convertStringToNumber(tag), spies) != NULL &&
                    (findTag(StringUtility::convertStringToNumber(tag), spies) -> getMissionInd()) != -1) {
                        int mission = findTag(StringUtility::convertStringToNumber(tag), spies) -> getMissionInd();
                        if (StringUtility::subStr(BreakCypher::breakCypher(cypher, mission), "imf")) {
                            findTag(StringUtility::convertStringToNumber(tag), spies) -> remove();
                            cout << "We get rid of tag:" << tag;
                        } else {
                            cout << "WRONG";
                        }
                    } else {
                        cout << "WRONG";
                    }                   
                    cout << endl;                   
                }
            }
            break;

            case '5': { //Print number of active spies
                int ans = 0;
                for (int i = 0; i < spies.size(); i++) {
                    ans += !spies[i].isRemoved() && spies[i].getMissionInd() != -1;
                }
                cout << "We had " << ans << " agent(s) in 2020\n";
            }
            break;

            case '6': { //Print number of spies of a specific mission
                string mission;
                cin >> mission;

                if (findMission(mission) == -1) { //Bad input
                    cout << "WRONG\n";
                } else {
                    //Searching
                    vector <Spy*> ans;
                    for (int i = 0; i < spies.size(); i++) {
                        if (!spies[i].isRemoved() && spies[i].getMissionInd() == findMission(mission)) {
                            ans.push_back(&spies[i]);
                        }
                    }

                    //Printing
                    cout << "We had " << ans.size() << " agent(s) in " << countries[findMission(mission)] << " in 2020:\n";
                    for (int i = 0; i < ans.size(); i++) {
                        cout << "Agent with personal code:" << ans[i] -> getPersonalCode() << " and tag:" << ans[i] -> getTag() << endl;
                    }
                }
            }
            break;
        }
    }
}