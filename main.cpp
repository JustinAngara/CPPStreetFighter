#include <iostream>
#include <Windows.h>
#include <map>
#include <string>
#include <conio.h>
#include <stdio.h>
using namespace std;

typedef WINAPI COLORREF (*GETPIXEL)(HDC, int, int);


string path;

bool canChangeDir, isFacingRight;

const char* widePath;

// <letter, path>
map<char, string> combos;


void callAHK(string p, bool isFacingRight){

    if(!isFacingRight){ // facing left
        p = "L" + p;
    }

    p+=".exe";
    cout<<p<<endl;
    widePath = (path+p).c_str();
    STARTUPINFO startInfo = {0};
    PROCESS_INFORMATION processInfo = {0};
    BOOL b = CreateProcess(TEXT(widePath), NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &startInfo, &processInfo);
    if(b){
        cout<<"done" << endl;
    }
}

void setupConfig(){
    path = "C:\\Users\\justi\\CLionProjects\\autoexec files\\";
    isFacingRight = true;
    canChangeDir = true;
    combos['1'] = "Spin Dive Smasher";
    combos['2'] = "Delta Red Assault";
    combos['3'] = "Bolshoi Storm Buster";
    combos['E'] = "Screw Piledriver";
    combos['Q'] = "CommandGrab";
    combos['Z'] = "Quick Spin Knuckle";
    combos['C'] = "JumpGrab";

}

void start(){

    while(true){
        if(GetKeyState('0') & 0x8000){
            canChangeDir = false;
        }else if(GetKeyState('9') & 0x8000){
            canChangeDir = true;
        }

        if(GetKeyState('A') & 0x8000 && canChangeDir){
            isFacingRight = false;
        } else if (GetKeyState('D') & 0x8000 && canChangeDir){
            isFacingRight = true;
        }


        for ( const auto &p : combos ){

            if(GetKeyState(p.first) & 0x8000){
                canChangeDir = false;
                callAHK(p.second, isFacingRight);
                canChangeDir = true;
                _sleep(500);
            }
        }
    }
}

// fix later, for juri's drive impact code.
/*
bool hasSufficientBlackPixels(){
    int num = 0;
    int r,g,b;
    HDC dcScreen = GetDC(0);
    HDC dcTarget = CreateCompatibleDC(dcScreen);
    HBITMAP bmpTarget = CreateCompatibleBitmap(dcScreen);
    HGDIOBJ oldBmp = SelectObject(dcTarget, bmpTarget);
    BitBlt(dcTarget, 0, 0, cx, cy, dcDesktop, x, y, SRCCOPY | CAPTUREBLT);
    SelectObject(dcTarget, oldBmp);
    COLORREF color;
    for(int x = 416; x<2049; x+=2) {
        for(int y = 342; y<973; y+=2) {
            color = GetPixel(hdc, x, y);
            r = (color>>16) & 0xFF;
            g = (color>>8) & 0xFF;
            b = color & 0xFF;
            cout<<"r, g , b: (" << r << ", " << g << ", "<<b << ")\n";

            if(r+g+b==0) { // is black pixel
                num++;
            }

        }
    }
    cout<<num;
    return num <= 100000 && num >= 8000;
}
*/


int main() {
    setupConfig();
    start();

//    callAHK("CommandGrab");


    return 0;
}