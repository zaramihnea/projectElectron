
//Electron is an open source project for the development of a 2D graphics circuit simulator
//Project created by Bursuc Eduarda & Zara Mihnea-Tudor, Faculty of Computer Sience, University "Alexandru Ioan Cuza" of Iasi, Romania, 2022

#include <iostream>
#include <fstream>
#include <graphics.h>
#include <winbgim.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

#define MAX1 10
#define MAX_NR 50
#define FUNDAL LIGHTGRAY

void languageMenu();
void initialWindow();
void changeLgEn();
void changeLgRo();
void changeLgFr();
void changeLgGe();
void changeLgRu();

void myOuttextXY(int x, int y, int cerneala, int hartie, char *text)
{
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    setcolor(cerneala);
    setbkcolor(hartie);
    outtextxy(x,y+3,text);
}

struct punctLegatura {
    int x,y;
};

struct nod {
    char info[MAX1];
    int x,y;
    int culoare;
    punctLegatura pLeg[2];
};

nod vecNoduri[MAX_NR]; int nrNoduri=10;

struct legatura {
    int nod1, nod2; // cele doua noduri ce se leaga
    int punct1, punct2; // punctele de legatura de la cele doua noduri
    int tipLegatura; // nu am folosit, dar va trebui folosit
};

legatura vecLegaturi[MAX_NR]; int nrLegaturi;

void deseneazaNod(nod N)
{
    setfillstyle(SOLID_FILL,N.culoare);
    fillellipse(N.x,N.y,10+2*textwidth(N.info),10+textheight(N.info));
    myOuttextXY(N.x,N.y,15-N.culoare,N.culoare,N.info);
    setcolor(WHITE);
    circle(N.pLeg[0].x,N.pLeg[0].y,5);
    circle(N.pLeg[1].x,N.pLeg[1].y,5);
}

void stergeNod(nod N)
{
    setfillstyle(SOLID_FILL,FUNDAL);
    fillellipse(N.x,N.y,10+2*textwidth(N.info),10+textheight(N.info));
}

void initNod(nod& N, char text[MAX1], int oCuloare)
{
    strcpy(N.info,text);
    N.culoare=oCuloare;
    N.x=100+rand()%(getmaxx()-200);
    N.y=100+rand()%(getmaxy()-200);
    N.pLeg[0].x=N.x-textwidth(N.info)-5;
    N.pLeg[0].y=N.y;
    N.pLeg[1].x=N.x+textwidth(N.info)+5;
    N.pLeg[1].y=N.y;
}

void drawLine(int x1, int y1, int x2, int y2, int cul)
{
    setcolor(cul);
    line(x1,y1,(x1+x2)/2,y1);
    line((x1+x2)/2,y1,(x1+x2)/2,y2);
    line((x1+x2)/2,y2,x2,y2);
}
void deseneazaLegatura(int &idNod1, int &p1, int &idNod2, int &p2)
{
    bool click=false;
    int i, xMouse,yMouse;
    // aleg un punct de legatura (p1) de la nodul 1 (idNod1)
    do {
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            Beep(2000,100);
            clearmouseclick(WM_LBUTTONDOWN);
            xMouse=mousex(); yMouse=mousey();
            for (i=1; i<=nrNoduri; i++)
                if (abs(vecNoduri[i].pLeg[0].x - xMouse)<=5
                    && abs(vecNoduri[i].pLeg[0].y - yMouse)<=5)
                    { idNod1=i; p1=0; click=true; }
                else if (abs(vecNoduri[i].pLeg[1].x - xMouse)<=5
                    && abs(vecNoduri[i].pLeg[1].y - yMouse)<=5)
                    { idNod1=i; p1=1; click=true; }
        }
    } while (!click);
    // aleg un punct de legatura (p2) de la nodul 2 (idNod2)
    // pana aleg, desenez mereu o linie
    click=false;
    int x1,y1,x2,y2;
    x1=vecNoduri[idNod1].pLeg[p1].x;
    y1=vecNoduri[idNod1].pLeg[p1].y;
    xMouse=mousex(); yMouse=mousey();
    do
    {
        drawLine(x1,y1,xMouse,yMouse, 15-FUNDAL);
        delay(50);drawLine(x1,y1,xMouse,yMouse,FUNDAL);
        xMouse=mousex(); yMouse=mousey();
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            Beep(1200,100);
            clearmouseclick(WM_LBUTTONDOWN);
            xMouse=mousex(); yMouse=mousey();
            for (i=1; i<=nrNoduri; i++)
                if (abs(vecNoduri[i].pLeg[0].x - xMouse)<=5
                    && abs(vecNoduri[i].pLeg[0].y - yMouse)<=5)
                    { idNod2=i; p2=0; click=true; }
                else if (abs(vecNoduri[i].pLeg[1].x - xMouse)<=5
                    && abs(vecNoduri[i].pLeg[1].y - yMouse)<=5)
                    { idNod2=i; p2=1; click=true; }
        }
    }
    while (!click);
    drawLine(x1,y1,xMouse,yMouse, 15-FUNDAL);
}

int main(){

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
    else{
        cleardevice();
    }
    srand(time(NULL));
    initwindow(1000,800,"Legaturi",100,100);
    setbkcolor(FUNDAL);
    cleardevice();

    int i,j,r;
    for (i=1; i<=nrNoduri; i++)
    {
        r=rand()%4;
        switch(r) {
            case 0: initNod(vecNoduri[i],"Tip1", 2+rand()%12); break;
            case 1: initNod(vecNoduri[i],"Tip2", 2+rand()%12); break;
            case 2: initNod(vecNoduri[i],"Tip3", 2+rand()%12); break;
            case 3: initNod(vecNoduri[i],"Tip4", 2+rand()%12); break;
        }
        deseneazaNod(vecNoduri[i]);
    }
    int idNod1, idNod2, p1, p2;

    myOuttextXY(getmaxx()/2,50,BLUE,YELLOW,"Click pe un cerculet de la un nod, apoi click pe altul de la alt nod.");
    nrLegaturi=0;
    do {
        deseneazaLegatura(idNod1,p1,idNod2,p2);
        nrLegaturi++;
        vecLegaturi[nrLegaturi].nod1=idNod1;
        vecLegaturi[nrLegaturi].nod2=idNod2;
        vecLegaturi[nrLegaturi].punct1=p1;
        vecLegaturi[nrLegaturi].punct2=p2;
        cout<<"Am trasat legatura de la punctul "<<p1<<" al nodului "<<idNod1;
        cout<<" la punctul "<<p2<<" al nodului "<<idNod2<<".\n";
        for (j=1;j<=nrNoduri;j++)
            deseneazaNod(vecNoduri[j]);
    } while (nrLegaturi<=10);
    getch();
    closegraph();
    return 0;
    //cout<<"hello world";
    system("pause");
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
        }
        if(ismouseclick(WM_LBUTTONDBLCLK)){
            int x = mousex();
            int y = mousey();
            if(x >= 100 && x <= 300 && y >= 200 && y <= 250){
                changeLgRo();
                break;
            }
        }
        if(ismouseclick(WM_LBUTTONDBLCLK)){
            int x = mousex();
            int y = mousey();
            if(x >= 100 && x <= 300 && y >= 300 && y <= 350){
                changeLgFr();
                break;
            }
        }
        if(ismouseclick(WM_LBUTTONDBLCLK)){
            int x = mousex();
            int y = mousey();
            if(x >= 100 && x <= 300 && y >= 400 && y <= 450){
                changeLgGe();
                break;
            }
        }
        if(ismouseclick(WM_LBUTTONDBLCLK)){
            int x = mousex();
            int y = mousey();
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