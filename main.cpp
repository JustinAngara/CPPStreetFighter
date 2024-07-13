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


void callAHK(string p){
    p = path + p +".exe";
    cout<<p<<endl;
    widePath = p.c_str();
    STARTUPINFO startInfo = {0};
    PROCESS_INFORMATION processInfo = {0};
    BOOL b = CreateProcess(TEXT(widePath), NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &startInfo, &processInfo);
    if(b){
        cout<<"done";
    } else {
        cout<<"failed";
    }
}

void setupConfig(){
    path = "C:\\Users\\justi\\CLionProjects\\autoexec files\\";
    isFacingRight = true;
    canChangeDir = true;
    combos['1'] = "Spin Dive Smasher";
    combos['2'] = "Delta Red Assault";
    combos['3'] = "Bolshoi Storm Buster";
    combos['e'] = "Screw Piledriver";
    combos['q'] = "CommandGrab";
    combos['z'] = "Quick Spin Knuckle";
    combos['c'] = "JumpGrab";

}

void start(){
    while(true){
//        if(GetKeyState('1') & 0x8000){
//            cout<<"test";
//        }
        for ( const auto &p : combos ){

            if(GetKeyState(p.first) & 0x8000){

                callAHK(p.second);
                _sleep(50);
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