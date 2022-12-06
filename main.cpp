
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

struct prop{
    float quantity;
    char measurement[21],
         name[21];
}properties;

struct object{
    int x, y;
    char type[31];
    int leftConnector=-1, rightConnector=-1;
    char left, right;
    prop properties;
}objects[100];


/*<------------End structures------------>*/



/*<------------Begin global variables------------>*/

int systemWidth = GetSystemMetrics(SM_CXSCREEN);
int systemHeight = GetSystemMetrics(SM_CYSCREEN);

int middleX = systemWidth/2;
int middleY = systemHeight/2;

bool hasStarted = false;

int objectsCount = 0;

/*<------------End global variables------------>*/



/*<------------Begin function definitions------------>*/

void startingPage(lang Language);
void languageMenu();
void testMenu();
void movingImage();
void images();
void draw();
void connect(int i, char connectorI, int j,char connectorJ);
void propertiesDisplay(int i);


/*<------------End function definitions------------>*/



/*<---------------------------Begin cod ajutor--------------------------->*/
/*

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
*/

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

    setfillstyle(SOLID_FILL,DARKGRAY);
    bar(0, 0, systemWidth, 120);
    bar(0,0, middleX-500, systemHeight);

    settextstyle(8, HORIZ_DIR, 1);

    int yT = 10, yB = 110;

    //available electric devices

    readimagefile("condensator.bmp", middleX-590, yT , middleX-490, yB);

    readimagefile("dioda.bmp", middleX-470, yT, middleX-370, yB);

    readimagefile("tranzistor.bmp", middleX-350, yT, middleX-250, yB);

    readimagefile("inductor.bmp", middleX-230, yT, middleX-130, yB);

    readimagefile("rezistor.bmp", middleX-110, yT, middleX-10, yB);

    readimagefile("voltmeter.bmp", middleX+10, yT, middleX+110, yB);

    readimagefile("ammeter.bmp", middleX+130, yT, middleX+230, yB);

    readimagefile("bulb.bmp", middleX+250, yT, middleX+350, yB);

    readimagefile("fuse.bmp", middleX+370, yT, middleX+470, yB);

    readimagefile("battery.bmp", middleX+490, yT, middleX+590, yB);

    // circuit editing buttons

    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(middleX-630, systemHeight-465, middleX-510, systemHeight-425);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX-590, systemHeight-457, "SAVE");

    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(middleX-630, systemHeight-415, middleX-510, systemHeight-375);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX-590, systemHeight-407, "MOVE");

    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(middleX-630, systemHeight-365, middleX-510, systemHeight-325);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX-608, systemHeight-357, "ZOOM IN");

    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(middleX-630, systemHeight-315, middleX-510, systemHeight-275);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX-611, systemHeight-307, "ZOOM OUT");

    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(middleX-630, systemHeight-265, middleX-510, systemHeight-225);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX-600, systemHeight-257, "DELETE");

    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(middleX-630, systemHeight-215, middleX-510, systemHeight-175);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX-590, systemHeight-207, "EXIT");

    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(middleX-630, systemHeight-165, middleX-510, systemHeight-50);
    setcolor(WHITE);
    rectangle(middleX-631, systemHeight-166, middleX-510, systemHeight-50);
    line(middleX-631, systemHeight-145, middleX-510, systemHeight-145);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX-625, systemHeight-165, "properties");

    // number buttons for measurment units input

    setbkcolor(BLACK);
    settextstyle(8, HORIZ_DIR, 2);

    rectangle(systemWidth-60, middleY-120, systemWidth-20, middleY-80);
    outtextxy(systemWidth-46, middleY-110, "0");

    rectangle(systemWidth-60, middleY-80, systemWidth-20, middleY-40);
    outtextxy(systemWidth-46, middleY-70, "1");

    rectangle(systemWidth-60, middleY-40, systemWidth-20, middleY);
    outtextxy(systemWidth-46, middleY-30, "2");

    rectangle(systemWidth-60, middleY, systemWidth-20, middleY+40);
    outtextxy(systemWidth-46, middleY+10, "3");

    rectangle(systemWidth-60, middleY+40, systemWidth-20, middleY+80);
    outtextxy(systemWidth-46, middleY+50, "4");

    rectangle(systemWidth-60, middleY+80, systemWidth-20, middleY+120);
    outtextxy(systemWidth-46, middleY+90, "5");

    rectangle(systemWidth-60, middleY+120, systemWidth-20, middleY+160);
    outtextxy(systemWidth-46, middleY+130, "6");

    rectangle(systemWidth-60, middleY+160, systemWidth-20, middleY+200);
    outtextxy(systemWidth-46, middleY+170, "7");

    rectangle(systemWidth-60, middleY+200, systemWidth-20, middleY+240);
    outtextxy(systemWidth-46, middleY+210, "8");

    rectangle(systemWidth-60, middleY+240, systemWidth-20, middleY+280);
    outtextxy(systemWidth-46, middleY+250, "9");

    setbkcolor(BLACK);

    images();
}



void images(){

    int x, y;
    bool click = false;
    /*
    1 - condensator
    2 - dioda
    3 - tranzistor
    4 - inductor
    5 - rezistor
    6 - voltmeter
    7 - ammeter
    8 - bulb
    9 - fuse
    10 - battery
    */
    while (1){
        if (ismouseclick(WM_LBUTTONDOWN) && !click){
            clearmouseclick(WM_LBUTTONDOWN);
            x = mousex();
            y = mousey();
            if (x >= middleX - 590 && x <= middleX - 490 && y >= 10 && y <= 110){
                while (1){
                    if (ismouseclick(WM_LBUTTONDOWN)){
                        clearmouseclick(WM_LBUTTONDOWN);
                        readimagefile("condensator.bmp", mousex() - 75, mousey() - 75, mousex() + 75, mousey() + 75);
                        circle(mousex()-78, mousey(), 6);
                        circle(mousex()+78, mousey(), 6);
                        objects[objectsCount].x = mousex();
                        objects[objectsCount].y = mousey();
                        strcpy(objects[objectsCount].type, "condensator.bmp");
                        strcpy(objects[objectsCount].properties.measurement, "Farad     ");
                        strcpy(objects[objectsCount].properties.name , "condenser ");
                        propertiesDisplay(objectsCount);
                        objectsCount++;
                        break;
                    }
                }
            }
            if (x >= middleX - 470 && x <= middleX - 370 && y >= 10 && y <= 110){
                while (1){
                    if (ismouseclick(WM_LBUTTONDOWN)){
                        clearmouseclick(WM_LBUTTONDOWN);
                        readimagefile("dioda.bmp", mousex() - 75, mousey() - 75, mousex() + 75, mousey() + 75);
                        circle(mousex()-78, mousey(), 6);
                        circle(mousex()+78, mousey(), 6);
                        objects[objectsCount].x = mousex();
                        objects[objectsCount].y = mousey();
                        strcpy(objects[objectsCount].type ,"dioda.bmp");
                        strcpy(objects[objectsCount].properties.measurement , "Ohm       ");
                        strcpy(objects[objectsCount].properties.name , "diode     ");
                        propertiesDisplay(objectsCount);
                        objectsCount++;
                        break;
                    }
                }
            }
            if (x >= middleX - 350 && x <= middleX - 250 && y >= 10 && y <= 110){
                while (1){
                    if (ismouseclick(WM_LBUTTONDOWN)){
                        clearmouseclick(WM_LBUTTONDOWN);
                        readimagefile("tranzistor.bmp", mousex() - 75, mousey() - 75, mousex() + 75, mousey() + 75);
                        circle(mousex()-78, mousey(), 6);
                        circle(mousex()+78, mousey(), 6);
                        objects[objectsCount].x = mousex();
                        objects[objectsCount].y = mousey();
                        strcpy(objects[objectsCount].type , "tranzistor.bmp");
                        strcpy(objects[objectsCount].properties.name , "transistor");
                        strcpy(objects[objectsCount].properties.measurement , "          ");
                        propertiesDisplay(objectsCount);
                        objectsCount++;
                        break;
                    }
                }
            }
            if (x >= middleX - 230 && x <= middleX - 130 && y >= 10 && y <= 110){
                while (1){
                    if (ismouseclick(WM_LBUTTONDOWN)){
                        clearmouseclick(WM_LBUTTONDOWN);
                        readimagefile("inductor.bmp", mousex() - 75, mousey() - 75, mousex() + 75, mousey() + 75);
                        circle(mousex()-78, mousey(), 6);
                        circle(mousex()+78, mousey(), 6);
                        objects[objectsCount].x = mousex();
                        objects[objectsCount].y = mousey();
                        strcpy(objects[objectsCount].type ,"inductor.bmp");
                        strcpy(objects[objectsCount].properties.measurement, "Henrys    ");
                        strcpy(objects[objectsCount].properties.name , "inductor  ");
                        propertiesDisplay(objectsCount);
                        objectsCount++;
                        break;
                    }
                }
            }
            if (x >= middleX - 110 && x <= middleX - 10 && y >= 10 && y <= 110){
                while (1){
                    if (ismouseclick(WM_LBUTTONDOWN)){
                        clearmouseclick(WM_LBUTTONDOWN);
                        readimagefile("rezistor.bmp", mousex() - 75, mousey() - 75, mousex() + 75, mousey() + 75);
                        circle(mousex()-78, mousey(), 6);
                        circle(mousex()+78, mousey(), 6);
                        objects[objectsCount].x = mousex();
                        objects[objectsCount].y = mousey();
                        strcpy(objects[objectsCount].type, "rezistor.bmp");
                        strcpy(objects[objectsCount].properties.measurement , "Ohm       ");
                        strcpy(objects[objectsCount].properties.name , "resistor  ");
                        propertiesDisplay(objectsCount);
                        objectsCount++;
                        break;
                    }
                }
            }
            if (x >= middleX + 10 && x <= middleX + 110 && y >= 10 && y <= 110){
                while (1){
                    if (ismouseclick(WM_LBUTTONDOWN)){
                        clearmouseclick(WM_LBUTTONDOWN);
                        readimagefile("voltmeter.bmp", mousex() - 75, mousey() - 75, mousex() + 75, mousey() + 75);
                        circle(mousex()-78, mousey(), 6);
                        circle(mousex()+78, mousey(), 6);
                        objects[objectsCount].x = mousex();
                        objects[objectsCount].y = mousey();
                        strcpy(objects[objectsCount].type , "voltmeter.bmp");
                        strcpy(objects[objectsCount].properties.measurement , "Volt      ");
                        strcpy(objects[objectsCount].properties.name , "voltmeter ");
                        propertiesDisplay(objectsCount);
                        objectsCount++;
                        break;
                    }
                }
            }
            if (x >= middleX + 130 && x <= middleX + 230 && y >= 10 && y <= 110){
                while (1){
                    if (ismouseclick(WM_LBUTTONDOWN)){
                        clearmouseclick(WM_LBUTTONDOWN);
                        readimagefile("ammeter.bmp", mousex() - 75, mousey() - 75, mousex() + 75, mousey() + 75);
                        circle(mousex()-78, mousey(), 6);
                        circle(mousex()+78, mousey(), 6);
                        objects[objectsCount].x = mousex();
                        objects[objectsCount].y = mousey();
                        strcpy(objects[objectsCount].type ,"ammeter.bmp");
                        strcpy(objects[objectsCount].properties.measurement , "Amperes   ");
                        strcpy(objects[objectsCount].properties.name , "ammeter   ");
                        propertiesDisplay(objectsCount);
                        objectsCount++;
                        break;
                    }
                }
            }
            if (x >= middleX + 250 && x <= middleX + 350 && y >= 10 && y <= 110){
                while (1){
                    if (ismouseclick(WM_LBUTTONDOWN)){
                        clearmouseclick(WM_LBUTTONDOWN);
                        readimagefile("bulb.bmp", mousex() - 75, mousey() - 75, mousex() + 75, mousey() + 75);
                        circle(mousex()-78, mousey(), 6);
                        circle(mousex()+78, mousey(), 6);
                        objects[objectsCount].x = mousex();
                        objects[objectsCount].y = mousey();
                        strcpy(objects[objectsCount].type , "bulb.bmp");
                        strcpy(objects[objectsCount].properties.measurement , "Watts     ");
                        strcpy(objects[objectsCount].properties.name , "bulb      ");
                        propertiesDisplay(objectsCount);
                        objectsCount++;
                        break;
                    }
                }
            }
            if (x >= middleX + 370 && x <= middleX + 470 && y >= 10 && y <= 110){
                while (1){
                    if (ismouseclick(WM_LBUTTONDOWN)){
                        clearmouseclick(WM_LBUTTONDOWN);
                        readimagefile("fuse.bmp", mousex() - 75, mousey() - 75, mousex() + 75, mousey() + 75);
                        circle(mousex()-78, mousey(), 6);
                        circle(mousex()+78, mousey(), 6);
                        objects[objectsCount].x = mousex();
                        objects[objectsCount].y = mousey();
                        strcpy(objects[objectsCount].type ,"fuse.bmp");
                        strcpy(objects[objectsCount].properties.measurement , "Amperes   ");
                        strcpy(objects[objectsCount].properties.name , "fuse      ");
                        propertiesDisplay(objectsCount);
                        objectsCount++;
                        break;
                    }
                }
            }
            if (x >= middleX + 490 && x <= middleX + 590 && y >= 10 && y <= 110){
                while (1){
                    if (ismouseclick(WM_LBUTTONDOWN)){
                        clearmouseclick(WM_LBUTTONDOWN);
                        readimagefile("battery.bmp", mousex() - 75, mousey() - 75, mousex() + 75, mousey() + 75);
                        circle(mousex()-78, mousey(), 6);
                        circle(mousex()+78, mousey(), 6);
                        objects[objectsCount].x = mousex();
                        objects[objectsCount].y = mousey();
                        strcpy(objects[objectsCount].type , "battery.bmp");
                        strcpy(objects[objectsCount].properties.measurement , "mAmps*H   ");
                        strcpy(objects[objectsCount].properties.name , "battery   ");
                        propertiesDisplay(objectsCount);
                        objectsCount++;
                        break;
                    }
                }
            }
        //if you click on an object change it's position

        for(int i = 0; i < objectsCount; i++)
        {
            if( x >= objects[i].x-75 && x <= objects[i].x+75 && y >= objects[i].y-75 && y <= objects[i].y+75 )
            while (1){
                    if (ismouseclick(WM_LBUTTONDOWN)){
                        clearmouseclick(WM_LBUTTONDOWN);
                        objects[i].x = mousex();
                        objects[i].y = mousey();

                        draw();
                        break;
                        }
                    }
            if( x >= objects[i].x-81 && x <= objects[i].x-75 && y >= objects[i].y-6 && y <= objects[i].y+6 )
            while (1){
                    if (ismouseclick(WM_LBUTTONDOWN)){
                        clearmouseclick(WM_LBUTTONDOWN);
                        for( int j = 0; j < objectsCount; j++){
                        if( mousex() >= objects[j].x-81 && mousex() <= objects[j].x-75 && mousey() >= objects[j].y-6 && mousey() <= objects[j].y+6 )
                            {connect(i, 'l', j, 'l'); objects[i].leftConnector = j; objects[j].leftConnector = i;}
                        else if(mousex() <= objects[j].x+81 && mousex() >= objects[j].x+75 && mousey() >= objects[j].y-6 && mousey() <= objects[j].y+6)
                            {connect(i, 'l', j, 'r'); objects[i].leftConnector = j; objects[j].rightConnector = i;}
                        }
                     break;
                        }
                    }
            if( x <= objects[i].x+81 && x >= objects[i].x+75 && y >= objects[i].y-6 && y <= objects[i].y+6 )
            while (1){
                    if (ismouseclick(WM_LBUTTONDOWN)){
                        clearmouseclick(WM_LBUTTONDOWN);
                        for( int j = 0; j < objectsCount; j++){
                        if( mousex() >= objects[j].x-81 && mousex() <= objects[j].x-75 && mousey() >= objects[j].y-6 && mousey() <= objects[j].y+6 )
                            {connect(i, 'r', j, 'l'); objects[i].rightConnector = j; objects[j].leftConnector = i;}
                        else if(mousex() <= objects[j].x+81 && mousex() >= objects[j].x+75 && mousey()>= objects[j].y-6 && mousey() <= objects[j].y+6)
                            {connect(i, 'r', j, 'r'); objects[i].rightConnector = j; objects[j].rightConnector = i;}

                        }
                     break;
                        }
                    }

        }



}

}
}



void draw()
{
    cleardevice();

    setfillstyle(SOLID_FILL,DARKGRAY);
    bar(0, 0, systemWidth, 120);
    bar(0,0, middleX-500, systemHeight);

    settextstyle(8, HORIZ_DIR, 1);

    int yT = 10, yB = 110;

    readimagefile("condensator.bmp", middleX-590, yT , middleX-490, yB);


    readimagefile("dioda.bmp", middleX-470, yT, middleX-370, yB);

    readimagefile("tranzistor.bmp", middleX-350, yT, middleX-250, yB);

    readimagefile("inductor.bmp", middleX-230, yT, middleX-130, yB);

    readimagefile("rezistor.bmp", middleX-110, yT, middleX-10, yB);

    readimagefile("voltmeter.bmp", middleX+10, yT, middleX+110, yB);

    readimagefile("ammeter.bmp", middleX+130, yT, middleX+230, yB);

    readimagefile("bulb.bmp", middleX+250, yT, middleX+350, yB);

    readimagefile("fuse.bmp", middleX+370, yT, middleX+470, yB);

    readimagefile("battery.bmp", middleX+490, yT, middleX+590, yB);

    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(middleX-630, systemHeight-465, middleX-510, systemHeight-425);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX-590, systemHeight-457, "SAVE");

    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(middleX-630, systemHeight-415, middleX-510, systemHeight-375);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX-590, systemHeight-407, "MOVE");

    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(middleX-630, systemHeight-365, middleX-510, systemHeight-325);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX-608, systemHeight-357, "ZOOM IN");

    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(middleX-630, systemHeight-315, middleX-510, systemHeight-275);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX-611, systemHeight-307, "ZOOM OUT");

    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(middleX-630, systemHeight-265, middleX-510, systemHeight-225);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX-600, systemHeight-257, "DELETE");

    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(middleX-630, systemHeight-215, middleX-510, systemHeight-175);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX-590, systemHeight-207, "EXIT");

    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(middleX-630, systemHeight-165, middleX-510, systemHeight-50);
    setcolor(WHITE);
    rectangle(middleX-631, systemHeight-166, middleX-510, systemHeight-50);
    line(middleX-631, systemHeight-145, middleX-510, systemHeight-145);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX-625, systemHeight-165, "properties");

    setbkcolor(BLACK);

    for(int j = 0; j < objectsCount; j++)
    {readimagefile(objects[j].type, objects[j].x - 75, objects[j].y - 75, objects[j].x + 75, objects[j].y + 75 );
     circle(objects[j].x + 78, objects[j].y, 6);
     circle(objects[j].x - 78, objects[j].y, 6);
     if(objects[j].rightConnector > -1)
     {
         char type;
         if(j == objects[objects[j].rightConnector].leftConnector)
            type = 'l';
         else if( j == objects[objects[j].rightConnector].rightConnector)
               type = 'r';
         connect(j, 'r', objects[j].rightConnector, type);
     }
     if(objects[j].leftConnector > -1)
     {
         char type;
         if(j == objects[objects[j].leftConnector].leftConnector)
            type = 'l';
         else if( j == objects[objects[j].leftConnector].rightConnector)
               type = 'r';
         connect(j, 'l' , objects[j].leftConnector, type);
     }

     }


}

void connect(int i, char connectorI, int j, char connectorJ)
{
   if(connectorI == connectorJ)
   {
       if(connectorI == 'r')
        {if(objects[i].x > objects[j].x)
        swap(i, j);

            line(objects[j].x + 81, objects[j].y, objects[j].x + 100, objects[j].y);
            line(objects[j].x + 100, objects[j].y, objects[j].x + 100, objects[i].y);
            line(objects[i].x + 81, objects[i].y, objects[j].x + 100, objects[i].y);
        }
       if(connectorI == 'l')
        {if(objects[j].x > objects[i].x)
        swap(i,j);

            line(objects[j].x - 81, objects[j].y, objects[j].x - 100, objects[j].y);
            line(objects[j].x - 100, objects[j].y, objects[j].x - 100, objects[i].y);
            line(objects[j].x - 100, objects[i].y, objects[i].x - 81, objects[i].y);
        }
   }
   else {
        if(connectorI == 'l')
        swap(i, j);

        float difference = (objects[j].x - objects[i].x - 162)/2;

            line(objects[i].x+81, objects[i].y, objects[i].x+81+difference, objects[i].y);
            line(objects[i].x+81+difference, objects[i].y, objects[i].x+81+difference, objects[j].y);
            line(objects[j].x-81-difference, objects[j].y, objects[j].x-81, objects[j].y);
        }

}

void propertiesDisplay(int i)
{
    settextstyle(8, HORIZ_DIR, 1);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX-625, systemHeight-140, objects[i].properties.name);
    outtextxy(middleX-625, systemHeight-120, objects[i].properties.measurement);
    //outtextxy(middleX-625, systemHeight-100, char(objects[i].properties.quantity));
    setbkcolor(BLACK);
}

/*<--------------------------End functions------------------------>*/
