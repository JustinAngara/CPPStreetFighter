#include <iostream>
#include <Windows.h>

std::string path = "C:\\Users\\justi\\CLionProjects\\autoexec files\\";
const char* widePath;

void callAHK(std::string p){
    p = path + p +".exe";
    widePath = p.c_str();
    std::cout<<p;
}

int main() {
    path = "C:\\Users\\justi\\CLionProjects\\StreetFighter\\autoexec files\\CommandGrab.exe";
    const char* widePath = path.c_str();
    STARTUPINFO startInfo = {0};
    PROCESS_INFORMATION processInfo = {0};
    BOOL b = CreateProcess(TEXT(widePath), NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &startInfo, &processInfo);
    if(b){
        std::cout<<"done";
    } else {
        std::cout<<"failed";
    }
    callAHK("CommandGrab");
    return 0;
}