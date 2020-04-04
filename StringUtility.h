//Just check if this class decleared before
#ifndef STRINGUTILITY_H
#define STRINGUTILITY_H

#include <string>

using namespace std;

class StringUtility {
    public:

    //Change type of given string to integer
    static int convertStringToNumber(string s);

    //Determine all characters of given string are digit or not
    static bool isAllDigit(string s);

    //Determine all characters of given string are letter/space or not
    static bool isAllLetters(string s);

    static char makeLower(char c);

    static bool subStr(const string s1, const string s2);//Is string s2 one of subStrings of string s1?
};

bool StringUtility::subStr(const string s1, const string s2) {
    for (int i = 0; i < s1.size() - s2.size() + 1; i++) {
        bool res = true;
        for (int j = 0; j < s2.size(); j++) {
            if (s1[i + j] != s2[j]) {
                res = false;
            }
        }
        if (res) {
            return true; //Found
        }
    }
    return false; //Not found
}

char StringUtility::makeLower(char c) {
    return (c < 'Z' && c > 'A') ? c - 'A' + 'a' : c;
}

int StringUtility::convertStringToNumber(string s) {
    int n = s.size(), ans = 0;
    for (int i = n - 1, j = 1; i >= 0; i--, j *= 10) {
        ans += (s[i] - '0') * j;
    }
    return ans;
}

bool StringUtility::isAllDigit(string s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] < '0' || s[i] > '9') {
            return false;
        }
    }
    return s.size();
}

bool StringUtility::isAllLetters(string s) {
    bool ans = true;
    for (int i = 0; i < s.size(); i++) {
        ans &= s[i] <= 'Z' && s[i] >= 'A' || s[i] <= 'z' && s[i] >= 'a' || s[i] == ' ';
    }
    return ans;
}

#endif