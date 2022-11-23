
//Electron is an open source project for the development of a 2D graphics circuit simulator
//Project created by Bursuc Eduarda & Zara Mihnea-Tudor, Faculty of Computer Sience, University "Alexandru Ioan Cuza" of Iasi, Romania, 2022

#include <iostream>
#include <fstream>
#include <graphics.h>
#include <winbgim.h>
using namespace std;

void languageMenu();
void initialWindow();

int main(){
    initialWindow();
    cout<<"hello world";
    if(getch()==46) closegraph();
}

void languageMenu(){
    //clear the screen and create a button for each language
    cleardevice();
    setcolor(WHITE);
    rectangle(100, 100, 300, 150);
    outtextxy(150, 110, "English");
    rectangle(100, 200, 300, 250);
    outtextxy(150, 210, "Romanian");
    rectangle(100, 300, 300, 350);
    outtextxy(150, 310, "French");
    rectangle(100, 400, 300, 450);
    outtextxy(150, 410, "German");
    //if the mouse is clicked on a button, the corresponding language will be chosen
}

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
    outtextxy(300, 200, "Electron");
    //write the text "Press any key to continue" in the center of the window
    outtextxy(150, 300, "Press any key to continue");
    //add a button that will enter another window
    setcolor(WHITE);
    rectangle(300, 400, 500, 450);
    outtextxy(320, 410, "Language");
    //look for a keabord click
    int x;
    //if a certain key is pressed, the language menu will appear
    x = getch();
    if(x==108 || x==76) languageMenu();
    //wait for a key to be pressed

}
