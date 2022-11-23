
//Electron is an open source project for the development of a 2D graphics circuit simulator
//Project created by Bursuc Eduarda & Zara Mihnea-Tudor, Faculty of Computer Sience, University "Alexandru Ioan Cuza" of Iasi, Romania, 2022

#include <iostream>
#include <fstream>
#include <graphics.h>
#include <winbgim.h>
using namespace std;
void initialWindow(){
    //create a window
    initwindow(800, 600, "Electron");
    //set the background color to black
    setbkcolor(BLACK);
    //set the color of the text to white
    setcolor(WHITE);
    //set the text style to bold
    settextstyle(3, HORIZ_DIR, 4);
    //write the text "Electron" in blue in the center of the window
    outtextxy(200, 200, "Electron");
    //write the text "Press any key to continue" in the center of the window
    outtextxy(200, 300, "Press any key to continue");
    //wait for a key to be pressed
    getch();
}

int main(){
    initialWindow();
    cout<<"hello world";
}