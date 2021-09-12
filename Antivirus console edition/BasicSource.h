#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <filesystem>

#include <thread>

#include <filesystem> //#include <experimental/filesystem> 
//namespace fs = std::experimental::filesystem;
namespace fs = std::filesystem;

using namespace std;

#ifdef _WIN32
#include <io.h> 
#define access    _access_s
#else
#include <unistd.h>
#endif

#pragma comment(lib, "urlmon.lib")

int DirExists(const char* const path) {
    struct stat info;

    int statRC = stat(path, &info);
    if (statRC != 0) {
        if (errno == ENOENT) { return 0; } // something along the path does not exist
        if (errno == ENOTDIR) { return 0; } // something in path prefix is not a dir
        return -1;
    }

    return (info.st_mode & S_IFDIR) ? 1 : 0;
}

int DirExists(const string const p) {//WARNING
    const char* path = p.c_str();
    struct stat info;

    int statRC = stat(path, &info);
    if (statRC != 0) {
        if (errno == ENOENT) { return 0; } // something along the path does not exist
        if (errno == ENOTDIR) { return 0; } // something in path prefix is not a dir
        return -1;
    }

    return (info.st_mode & S_IFDIR) ? 1 : 0;
}

//bool FileExists(const std::string& Filename) {
//    //cout << Filename << " is " << ((access(Filename.c_str(), 0) == 0) ? "a file" : "not a file") << endl;
//    return access(Filename.c_str(), 0) == 0;
//}

//WARNING: Bad function;
bool IsDir(const string path) {
    struct stat s;
    if (stat(path.c_str(), &s) == 0) {
        if (s.st_mode & S_IFDIR)
            return true; //it's a directory      
        else if (s.st_mode & S_IFREG)
            return false; //it's a file
        else
            return false;//something else
    }
    else
        cerr << "Error in getting access or something else to " << path << endl;//error

}

void CopyFile(string where, string to) {
    if (FileExists(to))
        remove(to.c_str());

    ofstream res(to, ios::binary);
    ifstream start(where, ios::binary);

    res << start.rdbuf(); //Or it can be just copy by string because its simple text file.
}

//void ProcessKill(string name) {
//    std::wstring windowName;
//
//    StringToWString(windowName, name);
//    HWND windowHandle = FindWindowW(NULL, windowName.c_str());
//    DWORD* processID = new DWORD;
//    GetWindowThreadProcessId(windowHandle, processID);
//
//    HANDLE tmpHandle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, *processID);
//    if (NULL != tmpHandle) {
//        TerminateProcess(tmpHandle, 0);
//    }
//}

int FileSize(const string s) {
    if (!FileExists(s) || s.find("$Recycle.Bin") != std::string::npos) //WARNING: Valunerbillity
        return -1;
    fs::path p{ s };
    cout << s << endl;
    return fs::file_size(p); //WARNING: Possible loss data(Visual Studio warning)
}

string ReadSource(string name) {
    if (!FileExists(name) || FileSize(name) <= 1)
        return "NULL"; //WARNING: Valunerbillity

    string res = "", s;
    ifstream file(name.c_str());
    while (!file.eof() && file.is_open()) {
        file >> s;
        res += s;
    }
    return res;
}