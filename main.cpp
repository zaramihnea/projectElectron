
//Electron is an open source project for the development of a 2D graphics circuit simulator
//Project created by Bursuc Eduarda & Zara Mihnea-Tudor, Faculty of Computer Sience, University "Alexandru Ioan Cuza" of Iasi, Romania, 2022

#include <iostream>
#include <fstream>
#include <graphics.h>
#include <winbgim.h>
using namespace std;

void languageMenu();
void initialWindowEn();
void initialWindowRo();
void initialWindowGe();
void initialWindowFr();
void initialWindowRu();

int main(){
    initialWindowEn();
    cout<<"hello world";

}

void languageMenu(){
    //clear the screen and create a button for each language
    cleardevice();
    setcolor(WHITE);
    rectangle(100, 100, 300, 150);
    outtextxy(150, 110, "E for English - default");
    rectangle(100, 200, 300, 250);
    outtextxy(150, 210, "R for Romanian");
    rectangle(100, 300, 300, 350);
    outtextxy(150, 310, "F for French");
    rectangle(100, 400, 300, 450);
    outtextxy(150, 410, "G for German");
    rectangle(100, 500, 300, 550);
    outtextxy(150, 510, "X for Russian");
    //if the mouse is clicked on a button, the corresponding language will be chosen
    int y;
    y=getch();
    if(y==101){
        initialWindowEn();
    }
    if(y==114){
        initialWindowRo();
    }
    if(y==102){
        initialWindowFr();
    }
    if(y==103){
        initialWindowGe();
    }
    if(y==120){
        initialWindowRu();
    }
}

void initialWindowEn(){
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

void initialWindowRo(){
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
    outtextxy(150, 300, "Apasa orice tasta pentru a continua");
    //add a button that will enter another window
    setcolor(WHITE);
    rectangle(300, 400, 500, 450);
    outtextxy(320, 410, "Limba");
    //look for a keabord click
    int x;
    //if a certain key is pressed, the language menu will appear
    x = getch();
    if(x==108 || x==76) languageMenu();
    //wait for a key to be pressed
}

void initialWindowGe(){
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
    outtextxy(150, 300, "Drücken Sie eine beliebige Taste, um fortzufahren");
    //add a button that will enter another window
    setcolor(WHITE);
    rectangle(300, 400, 500, 450);
    outtextxy(320, 410, "Sprache");
    //look for a keabord click
    int x;
    //if a certain key is pressed, the language menu will appear
    x = getch();
    if(x==108 || x==76) languageMenu();
    //wait for a key to be pressed
}

void initialWindowFr(){
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
    outtextxy(150, 300, "Appuyez sur n'importe quelle touche pour continuer");
    //add a button that will enter another window
    setcolor(WHITE);
    rectangle(300, 400, 500, 450);
    outtextxy(320, 410, "Langue");
    //look for a keabord click
    int x;
    //if a certain key is pressed, the language menu will appear
    x = getch();
    if(x==108 || x==76) languageMenu();
    //wait for a key to be pressed
}

void initialWindowRu(){
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
    outtextxy(150, 300, "нажмите любую клавишу для продолжения");
    //add a button that will enter another window
    setcolor(WHITE);
    rectangle(300, 400, 500, 450);
    outtextxy(320, 410, "Язык");
    //look for a keabord click
    int x;
    //if a certain key is pressed, the language menu will appear
    x = getch();
    if(x==108 || x==76) languageMenu();
    //wait for a key to be pressed
}
