#ifndef BREAKCYPHER_H
#define BREAKCYPHER_H

#include <string>
#include "StringUtility.h"
#include <iostream>

using namespace std;

const int alphabetLength = 26;

class BreakCypher {
    private:
    static string caesar(string);
    static string playfair(string);
    static string vigenere(string);    

    public:
    static string breakCypher(string, int);
};

string BreakCypher::breakCypher(string cypher, int mission) {
    string ans;
    switch (mission) {
        case 0: { //Turkey
            ans = caesar(cypher);
        }
        break;

        case 1: { //Portugal
            ans = playfair(cypher);
        }
        break;

        case 2: { //Italy
            ans = vigenere(cypher);
        }
        break;
    }
    return ans;
}

string BreakCypher::vigenere(string s) {
    const int keyLength = 10;
    const char key[keyLength + 1] = "lieutenant";
    string res;
    for (int i = 0; i < s.size(); i++) {
        res += ((s[i] - 'a') - (key[i % keyLength] - 'a') + alphabetLength) % alphabetLength + 'a';
    }
    return res;
}

string BreakCypher::playfair(string s) {
    const int n = 5;
    const int m = 5;
    const char keyMat[n][m] = {{'m', 'o', 'n', 'a', 'r'}, //i/j should be handeled later
                               {'c', 'h', 'y', 'b', 'd'},
                               {'e', 'f', 'g', 'i', 'k'},
                               {'l', 'p', 'q', 's', 't'},
                               {'u', 'v', 'w', 'x', 'z'}};
    string res;

    for (int i = 0; i < s.size(); i += 2) {
        
        // j=i
        if (s[i] == 'j') {
            s[i] = 'i';
        }
        if (s[i + 1] == 'j') {
            s[i + 1] = 'i';
        }

        s[i] = StringUtility::makeLower(s[i]);
        s[i + 1] = StringUtility::makeLower(s[i + 1]);

        //Search positions
        int x1, y1, x2, y2;        
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < m; k++) {
                if (keyMat[j][k] == s[i]) {
                    y1 = j;
                    x1 = k;
                }
                if (keyMat[j][k] == s[i + 1]) {
                    y2 = j;
                    x2 = k;
                }
            }
        }

        //Same row
        if (y1 == y2) {
            if (keyMat[y1][(x1 + 4) % 5] != 'x') {
                res += keyMat[y1][(x1 + 4) % 5];
            }
            if (keyMat[y2][(x2 + 4) % 5] != 'x') {
                res += keyMat[y2][(x2 + 4) % 5];
            }
        }

        //Same column
        if (x1 == x2) {
            if (keyMat[(y1 + 4) % 5][x1] != 'x') {
                res += keyMat[(y1 + 4) % 5][x1];
            }
            if (keyMat[(y2 + 4) % 5][x2] != 'x') {
                res += keyMat[(y2 + 4) % 5][x2];
            }
        }

        //Rectangle case
        if (x1 != x2 && y1 != y2) {
            if (keyMat[y1][x2] != 'x') {
                res += keyMat[y1][x2];
            }
            if (keyMat[y2][x1] != 'x') {
                res += keyMat[y2][x1];
            }           
        }
    }
    return res;
}

string BreakCypher::caesar(string s) {
    const int K = 5;
    for (int i = 0; i < s.size(); i++) {
        s[i] = StringUtility::makeLower(s[i]);
        s[i] = (s[i] - 'a' - K + alphabetLength) % alphabetLength + 'a';
    }
    return s;
}

#endif