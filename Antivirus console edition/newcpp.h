#pragma once
#pragma once
#ifndef NEWCPP
#define NEWCPP

#include <iostream>
#include <windows.h>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <time.h>
#include <sstream>

#include <sys/stat.h>
#include <vector>
#include <stdexcept> //For exceptions

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

const int fileInitializeStartTime = (int)time(0);
#define STARTTIME fileInitializeStartTime

namespace COLORS {
    #define CLASSIC (-1) //WORD

    #define INVISIBLEBLACK 0

    #define BLUE 1
    #define GREEN 2
    #define LIGHTBLUE 3
    #define RED 4
    #define PURPLE 5
    #define YELLOW 6
    #define WHITE 7
    #define GREY 8
    #define LIGHTBLUE 9
    #define LIGHTGREEN 10
    #define CYAN 11
    #define LIGHTRED 12
    #define PINK 13
    #define LIGHTYELLOW 14
    #define WHITE2 15
}

using namespace COLORS;

#define PRESSTIMESLEEP 10

#ifdef _WIN32
#include <io.h>
#define access _access_s
#else
#include <unistd.h>
#endif

//Gives true if folder exist.
bool DirExist(const string& path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0); //return PathFileExists(path.c_str());
}

//Returns string converted to wstring.
wstring StringToWString(const string s) {
    std::wstring wsTmp(s.begin(), s.end());
    return wsTmp;
}

LPCWSTR s2ws(const std::string& s) {
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    //return r;

    std::wstring stemp = s2ws(s);
    return stemp.c_str();
}

//Returns string converted to LPSTR
LPSTR StrToLPSTR(string s) {
    return const_cast <char*> (s.c_str());
}

//Returns true if given char is number
bool isCharNumber(char c) {
    //int a = 100;
    //a = c - '0';
    return isdigit(c);
}

//Deleting all given chars from string and returns it.
string DeleteAllChars(string s, char c) {
    s.erase(std::remove(s.begin(), s.end(), c), s.end());
    /*for(int i = 0; i < s.length(); i++)
      if(s[i] == c)
          s[i] = '\0';*/
    return s;
}

//Deleting chars from first parameter that are in second.
string DeleteAllChars(string s, string chars) {
    for (int i = 0; i < chars.length(); i++)
        s = DeleteAllChars(s, chars[i]);
    return s;
}

/*Replacing string in text to another string. Not fully tested.
Usage:
ReplaceAll(string("Hi and hi"), string(" "), string("_"))
Returns:
"Hi_and_hi"*/
string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

//Returns a chracter table length.
int CharacterTableLength() {
    //return int(char(0) - 1);
    char a = 'a' + 1;
    int counter = 1;
    while (a != 'a') {
        a++;
        counter++;
    }

    return counter;
}

//Returns string to uppercase
string UpperString(string s) {
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}

//Changes the string to uppercase
void UpStr(string& s) {
    transform(s.begin(), s.end(), s.begin(), ::toupper);
}

template <typename T>
string NumberToString(T pNumber) {
    ostringstream oOStrStream;
    oOStrStream << pNumber;
    return oOStrStream.str();
}

//Returns true if element is part of array.
template <class element, class container>
bool PartOfArray(element elem, container array, int arraySize = 0) {
    if (!arraySize) arraySize = sizeof(array) / sizeof(array[0]);

    for (int i = 0; i < arraySize; i++)
        if (elem == array[i])
            return true;

    return false;
}

//Returns true if __access_s function returns 0 (~file exists)
bool FileExists(const std::string& Filename) {
    return _access(Filename.c_str(), 0) == 0;
}

//Changing console text color. For changing it back, ChangeColor(COLORS::CLASSIC) or SetDefaultColor
void ChangeColor(int color = CLASSIC) {
    SetConsoleTextAttribute(hConsole, color);
}

//Setting standart color
void SetDefaultColor() {
    SetConsoleTextAttribute(hConsole, CLASSIC);
}

////Printing text with setted color
//template<class type>
//void Print(type s, int color=CLASSIC) {
//    SetConsoleTextAttribute(hConsole, color);
//    cout << s;
//    SetConsoleTextAttribute(hConsole, CLASSIC);
//}

//Writes each symbol in string with function Sleep
void Write(string s, int maxTime = 100) {
    if (maxTime <= 0) maxTime = 1; //Previous version was without it
    srand(time(0));
    for (int i = 0; i < s.length(); i++) {
        cout << s[i];
        Sleep(rand() % maxTime);
    }
}

//Writes string in setted color with Sleep.
void Print(string s, int color = CLASSIC, int maxT = 0, int colorAfter = CLASSIC) {
    ChangeColor(color); //WARNING: Calling SetConsoleTextAttribute insead should speed up.
    Write(s, maxT); //Slows down output.
    ChangeColor(colorAfter);
}

bool Contains(string s, string part) {
    return s.find(part) != std::string::npos;
}

//Simulating user press
void Press(BYTE key) {
    keybd_event(key, 0, 0, 0);
    Sleep(PRESSTIMESLEEP);
    keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
}

//Simulating 2 presses
void DoublePress(BYTE key, BYTE key2) {
    keybd_event(key, 0, 0, 0);
    keybd_event(key2, 0, 0, 0);

    Sleep(PRESSTIMESLEEP);

    keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(key2, 0, KEYEVENTF_KEYUP, 0);
}

//Class for bruteforcing.
class BruteForce {
private:
    const char pzc = 1;
    const char pnc = 0;
public:
    string res = ""; //Bruteforce guess

    //Give next string guess
    string GiveNextGuess() {
        PlusPlus();
        return res;
    }

    string CurrentGuess() {
        return res;
    }

    //Setting start length of brute-force string. Can be given as normal(parameter 2 but s is maybe ['', ''])
    void SetStartLength(int l) {
        if (l <= 0) throw std::invalid_argument("Received incorrect value.");//return;
        res.clear();
        for (int i = 0; i < l; i++)
            res += pzc;
    }

    void PlusPlus() {
        int a = 0;
        while (true) {
            if (a > res.length()) {
                res += pzc;
                break;
            }
            else if (res[a] == pnc) {
                res[a] = pzc;
                a++;
            }
            else {
                res[a]++;
                break;
            }
        }
    }
};
namespace sortfunctions {
    template<class T>
    vector<T> GnomeSort(vector<T> arr, bool (*compare)(T, T)) {
        const int s = arr.size();
        for (int i = 1; i < s; i++) {
            if (compare(arr[i], arr[i - 1])) {
                T helper = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = helper;
                if (i != 1) i -= 2;
            }
        }
        return arr;
    }
}
//Returns last value somewhere in program used. Needs to give any string. Untested.
template<class T>
const int GetLastValueInt(T r) { if (r == "false") return 10; }
#endif