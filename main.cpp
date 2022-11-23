
//Electron is an open source project for the development of a 2D graphics circuit simulator
//Project created by Bursuc Eduarda & Zara Mihnea-Tudor, Faculty of Computer Sience, University "Alexandru Ioan Cuza" of Iasi, Romania, 2022

#include <iostream>
#include <fstream>
#include <graphics.h>
#include <winbgim.h>
using namespace std;

void languageMenu();
void initialWindow();
void changeLgEn();
void changeLgRo();
void changeLgFr();
void changeLgGe();
void changeLgRu();

int main(){
    initialWindow();
    //cout<<"hello world";
    system("pause");
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
    if(getch() == 76 || getch() == 108){
       
            languageMenu();
        
    }
    //wait for a key to be pressed
    getch();
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
    while(1){
        if(ismouseclick(WM_LBUTTONDBLCLK)){
            int x = mousex();
            int y = mousey();
            if(x >= 100 && x <= 300 && y >= 100 && y <= 150){
                changeLgEn();
                break;
            }
            if(x >= 100 && x <= 300 && y >= 200 && y <= 250){
                changeLgRo();
                break;
            }
            if(x >= 100 && x <= 300 && y >= 300 && y <= 350){
                changeLgFr();
                break;
            }
            if(x >= 100 && x <= 300 && y >= 400 && y <= 450){
                changeLgGe();
                break;
            }
            if(x >= 100 && x <= 300 && y >= 500 && y <= 550){
                changeLgRu();
                break;
            }
        }
    }

}

void changeLgEn(){
    cleardevice();
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
    getch();
}

void changeLgRo(){
    cleardevice();
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
    getch();
}

void changeLgGe(){
    cleardevice();
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
    getch();
}

void changeLgFr(){
    cleardevice();
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
    getch();
}

void changeLgRu(){
    cleardevice();
    //set the background color to black
    setbkcolor(BLACK);
    //set the color of the text to white
    setcolor(WHITE);
    //set the text style to bold
    settextstyle(3, HORIZ_DIR, 4);
    //write the text "Electron" in blue in the center of the window
    outtextxy(300, 200, "Electron");
    //write the text "Press any key to continue" in the center of the window
    outtextxy(150, 300, "d0 bd d0 b0 d0 b6 d0 bc d0 b8 d1 82 d0 b5 20 d0 bb d1 8e d0 b1 d1 83 d1 8e 20 d0 ba d0 bb d0 b0 d0 b2 d0 b8 d1 88 d1 83 20 d0 b4 d0 bb d1 8f 20 d0 bf d1 80 d0 be d0 b4 d0 be d0 bb d0 b6 d0 b5 d0 bd d0 b8 d1 8f");
    //add a button that will enter another window
    setcolor(WHITE);
    rectangle(300, 400, 500, 450);
    outtextxy(320, 410, "d0 af d0 b7 d1 8b d0 ba");
    //look for a keabord click
    int x;
    //if a certain key is pressed, the language menu will appear
    x = getch();
    if(x==108 || x==76) languageMenu();
    //wait for a key to be pressed
    getch();
}