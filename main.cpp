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

// fix later, for juri's drive impact code.

bool hasSufficientBlackPixels(){
    // Get the primary monitor's DC
    HDC hScreenDC = GetDC(NULL);

    // Create a compatible DC
    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);

    // Get screen dimensions
    int width = 2049-416;
    int height = 973-342;

    // Create a compatible bitmap
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);

    // Select the bitmap into the compatible DC
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);

    // BitBlt the screen to the memory DC
    BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY);

    // Get bitmap information
    BITMAPINFOHEADER bi;
    memset(&bi, 0, sizeof(BITMAPINFOHEADER));
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = width;
    bi.biHeight = -height; // Negative height for top-down bitmap
    bi.biPlanes = 1;
    bi.biBitCount = 24; // Assuming 24-bit bitmap
    bi.biCompression = BI_RGB;

    // Create a buffer for bitmap data
    int imageSize = width * height * 3; // Assuming 24-bit bitmap
    unsigned char* imageData = new unsigned char[imageSize];

    // Get bitmap bits
    GetDIBits(hMemoryDC, hBitmap, 0, height, imageData, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

    int count = 0;
    for (int y = 342; y < height; y+=2) {
        for (int x = 416; x < width; x+=2) {
            // Calculate the index of the pixel in the imageData array
            int index = (y * width + x) * 3; // Assuming 24-bit bitmap

            // Extract RGB values
            unsigned char blue = imageData[index];
            unsigned char green = imageData[index + 1];
            unsigned char red = imageData[index + 2];
            if(red+green+blue==0){
                count++;
            }
        }
    }


    // Clean up
    DeleteObject(hBitmap);
    SelectObject(hMemoryDC, hOldBitmap);
    DeleteDC(hMemoryDC);
    ReleaseDC(NULL, hScreenDC);
    delete[] imageData;

    return count <= 100000 && count >= 8000;
}




void start(){

    while(true){
        if(hasSufficientBlackPixels()){
            cout<<"found";
        }
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


int main() {
    setupConfig();
    start();

//    callAHK("CommandGrab");


    return 0;
}