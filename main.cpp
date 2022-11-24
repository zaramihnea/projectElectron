
//Electron is an open source project for the development of a 2D graphics circuit simulator
//Project created by Bursuc Eduarda & Zara Mihnea-Tudor, Faculty of Computer Sience, University "Alexandru Ioan Cuza" of Iasi, Romania, 2022


/*<--Begin libraries-->*/
#include <iostream>
#include <fstream>
#include <graphics.h>
#include <winbgim.h>
#include <stdlib.h>
#include <time.h>
#include <cstring>
/*<--End libraries-->*/

using namespace std;



/*<------------Begin structures------------>*/

struct lang{
    char language[10],
            start[10];
};
lang ro = {"Limba","INCEPE"},
     en = {"Language", "START"},
     ge = {"Sprache","ANFANG"},
     fr = {"Langue","DEBUT"};

/*<------------End structures------------>*/



/*<------------Begin global variables------------>*/

int systemWidth = GetSystemMetrics(SM_CXSCREEN);
int systemHeight = GetSystemMetrics(SM_CYSCREEN);

int middleX = systemWidth/2;
int middleY = systemHeight/2;

bool hasStarted = false;

/*<------------End global variables------------>*/



/*<------------Begin function definitions------------>*/

void startingPage(lang Language);
void languageMenu();
void testMenu();

/*<------------End function definitions------------>*/



/*<---------------------------Begin cod ajutor--------------------------->*/

#define MAX1 10
#define MAX_NR 50
#define FUNDAL LIGHTGRAY

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

void gamePage(){
    setbkcolor(FUNDAL);
    cleardevice();
    int i, j, r;
    for (i = 1; i <= nrNoduri; i++){
        r = rand() % 4;
        switch (r){
        case 0:
            initNod(vecNoduri[i], "Tip1", 2 + rand() % 12);
            break;
        case 1:
            initNod(vecNoduri[i], "Tip2", 2 + rand() % 12);
            break;
        case 2:
            initNod(vecNoduri[i], "Tip3", 2 + rand() % 12);
            break;
        case 3:
            initNod(vecNoduri[i], "Tip4", 2 + rand() % 12);
            break;
        }
        deseneazaNod(vecNoduri[i]);
    }
    int idNod1, idNod2, p1, p2;

    myOuttextXY(getmaxx() / 2, 50, BLUE, YELLOW, "Click pe un cerculet de la un nod, apoi click pe altul de la alt nod.");
    nrLegaturi = 0;
    do{
        deseneazaLegatura(idNod1, p1, idNod2, p2);
        nrLegaturi++;
        vecLegaturi[nrLegaturi].nod1 = idNod1;
        vecLegaturi[nrLegaturi].nod2 = idNod2;
        vecLegaturi[nrLegaturi].punct1 = p1;
        vecLegaturi[nrLegaturi].punct2 = p2;
        cout << "Am trasat legatura de la punctul " << p1 << " al nodului " << idNod1;
        cout << " la punctul " << p2 << " al nodului " << idNod2 << ".\n";
        for (j = 1; j <= nrNoduri; j++)
            deseneazaNod(vecNoduri[j]);
    } while (nrLegaturi <= 10);
    getch();
    closegraph();
}

/*<---------------------------End cod ajutor--------------------------->*/



/// @brief Main function
/// @return 0
int main(){

    startingPage(en);
    return 0;

}


/*<--------------------------Begin functions------------------------>*/

/// @brief Start of the program; initializez the window and
/// @param Language


void startingPage(lang L){
    if (hasStarted == false){
        hasStarted = true;
        initwindow(systemWidth, systemHeight, "Electron", -3, -3, false, true);
    }
    else cleardevice();

    setbkcolor(BLACK);
    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR, 6);
    outtextxy(middleX-130, 200, "Electron");
    setcolor(WHITE);
    rectangle(middleX-380, 400, middleX-100, 480);
    outtextxy(middleX-370, 415, L.language);
    setcolor(WHITE);
    rectangle(middleX+100, 400, middleX+380, 480);
    outtextxy(middleX+150, 415, L.start);
    bool click = false;
    while (1){
        if (ismouseclick(WM_LBUTTONDOWN) && !click){

            clearmouseclick(WM_LBUTTONDOWN);
            int xMouse = mousex();
            int yMouse = mousey();
            if (xMouse >= middleX-380 && xMouse <= middleX-100 && yMouse >= 400 && xMouse <= 480){
                languageMenu();
                click = true;
            }
            if (click == false)
                if (xMouse >= middleX+100 && xMouse <= middleX+380 && yMouse >= 400 && yMouse <= 480){
                    click = true;
                    //gamePage();
                    testMenu();
                }
        }
    }
}

/// @brief Change the language of the menu on click
void languageMenu(){
    cleardevice();
    setcolor(WHITE);
    rectangle(100, 150, 700, 230);
    outtextxy(110, 160, "English - default");
    rectangle(100, 250, 400, 330);
    outtextxy(110, 260, "Romanian");
    rectangle(100, 350, 400, 430);
    outtextxy(110, 360, "French");
    rectangle(100, 450, 400, 530);
    outtextxy(110, 460, "German");

    bool hello = false;
    lang language;
    // if the mouse is clicked on a button, the corresponding language will be chosen using coordonates
    //150-230: English
    //250-330: Romanian
    //350-430: French
    //450-530: German
    while (1){
        if (ismouseclick(WM_LBUTTONDOWN) && !hello){
            clearmouseclick(WM_LBUTTONDOWN);
            int x = mousex();
            int y = mousey();
            if(x >= 100 && x <= 700 && y >= 150 && y <= 230){
                language=en;
                startingPage(language);
                break;
                }
                if (x >= 100 && x <= 400)
                {
                    if (y >= 250 && y <= 330)
                    {language = ro; hello = true;}
                    if (y >= 350 && y <= 430)
                    {language = fr; hello = true;}
                    if (y >= 450 && y <= 530)
                    {language = ge; hello = true;}

                    if(hello)
                    {startingPage(language);
                    break;}
                }
        }
    }
}

void testMenu ()
{
    cleardevice();
    readimagefile("condensator.bmp", 0, 0 , 150, 150);
    readimagefile("dioda.bmp", 150, 0, 300, 150);
    readimagefile("tranzistor.bmp", 0, 150, 150, 300);
    readimagefile("inductor.bmp", 150, 150, 300, 300);
    readimagefile("rezistor.bmp", 0, 300, 150, 450);

}
/*<--------------------------End functions------------------------>*/

