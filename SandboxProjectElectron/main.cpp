
// Electron is an open source project for the development of a 2D graphics circuit simulator
// Project created by Bursuc Eduarda & Zara Mihnea-Tudor, Faculty of Computer Sience, University "Alexandru Ioan Cuza" of Iasi, Romania, 2022

/*<--Begin libraries-->*/
#include <iostream>
#include <fstream>
#include <graphics.h>
#include <winbgim.h>
#include <stdlib.h>
#include <time.h>
#include <cstring>
#include <fstream>
#include <windows.h>
/*<--End libraries-->*/

using namespace std;

/*<------------Begin structures------------>*/

struct lang
{
    char language[20],
        start[20],
        save[20],
        load[30],
        zoomIn[20],
        zoomOut[20],
        dele[20],
        props[20],
        exit[20],
        clearr[20],
        mov[20],
        edit[20];
};
lang ro = {"Limba", "INCEPE", "Salveaza", "Incarca", "Mareste", "Micsoreaza", "Sterge", "Proprietati", "Iesire", "Goleste", "Muta", "Editeaza"},
     en = {"Language", "START", "Save", "Load", "Zoom in", "Zoom out", "Delete", "Properties", "Exit", "Clear", "Move", "Edit"},
     ge = {"Sprache", "ANFANG", "Speichern", "Belastung", "Vergr��ern", "Verkleinern", "L�schen", "Eigenschaften", "Ausgang", "Klar", "Bewegen", "Bearbeiten"},
     fr = {"Langue", "DEBUT", "Sauvegarder", "Charger", "Agrandir", "R�duire", "Supprimer", "Propri�t�s", "Sortie", "Clair", "Bouger", "Modifier"};

struct prop
{
    char quantity[15];
    char measurement[21],
        name[21];
} properties;

struct object
{
    int x, y;
    char type[31], connection[2];
    struct connection
    {
        int index = -1;
        char type[3] = "AA";
    } leftConnector, rightConnector, topConnector, bottomConnector;
    prop properties;
    int rotateState = 1;
} objects[100];

/*<------------End structures------------>*/

/*<------------Begin global variables------------>*/

int systemWidth = GetSystemMetrics(SM_CXSCREEN);
int systemHeight = GetSystemMetrics(SM_CYSCREEN);

int middleX = systemWidth / 2;
int middleY = systemHeight / 2;

bool hasStarted = false;

int objectsCount = 0;

lang L = en;

const int DEFAULT_OBJECT_SIZE = 75;
int objectSize = DEFAULT_OBJECT_SIZE;

/*<------------End global variables------------>*/

/*<------------Begin function definitions------------>*/

void startingPage();
void languageMenu();
void refresh();
void images();
void draw();
void commonSet();
void connectionAnalyst(int i, int j);
void connectionLL(int i, int j);
void connectionRR(int i, int j);
void connectionRL(int i, int j, char connectorI);
void connectionS(int i, int j, char connectorI);
void connectionBT(int i, int j, char connectorI);
void connectionTT(int i, int j);
void connectionBB(int i, int j);
void connectionTL(int i, int j);
void connectionTR(int i, int j);
void connectionBL(int i, int j);
void connectionBR(int i, int j);
void propertiesDisplay(int i);
void deleteObject();
void exit();
void load();
void save();
void rotateObject();
int imageOverlap(int x, int y, int j);
void horizontalOverlap(int x1, int x2, int y, int &ok);
void verticalOverlap(int y1, int y2, int x, int &ok);
void cornerOverlap(int &x, int &y, int x1, int y1);
void clear();
void mov();
void edit();
int checkPointOverlap(int x, int y);
void handlePropertiesInsert(int j);
void zoomIn();
void zoomOut();

/*<------------End function definitions------------>*/

/// @brief Main function
/// @return 0
int main()
{
    startingPage();
    return 0;
}

/*<--------------------------Begin functions------------------------>*/

/// @brief Start of the program; initializez the window and
/// @param Language
void startingPage()
{
    if (hasStarted == false)
    {
        hasStarted = true;
        initwindow(systemWidth, systemHeight, "Electron", -3, -3, false, true);
    }
    else
        cleardevice();

    readimagefile("background.jpg", 0, 0, systemWidth, systemHeight);
    settextstyle(4, HORIZ_DIR, 4);
    setbkcolor(WHITE);
    bar(middleX - 380, middleY - 40, middleX - 100, middleY + 40);
    bar(middleX + 100, middleY - 40, middleX + 380, middleY + 40);
    setcolor(BLACK);
    outtextxy(middleX - 340, middleY - 12, L.language);
    outtextxy(middleX + 160, middleY - 12, L.start);
    rectangle(middleX - 380, middleY - 40, middleX - 100, middleY + 40);
    rectangle(middleX + 100, middleY - 40, middleX + 380, middleY + 40);
    bool click = false;
    setbkcolor(BLACK);
    setcolor(WHITE);
    while (1)
    {
        if (ismouseclick(WM_LBUTTONDOWN) && !click && !click)
        {

            clearmouseclick(WM_LBUTTONDOWN);
            int xMouse = mousex();
            int yMouse = mousey();
            if (xMouse >= middleX - 380 && xMouse <= middleX - 100 && yMouse >= middleY - 40 && yMouse <= middleY + 40)
            {
                languageMenu();
                click = true;
            }
            if (click == false)
                if (xMouse >= middleX + 100 && xMouse <= middleX + 380 && yMouse >= middleY - 40 && yMouse <= middleY + 40)
                {
                    click = true;
                    images();
                }
        }
    }
}

/// @brief Change the language of the menu on click
void languageMenu()
{
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

    // if the mouse is clicked on a button, the corresponding language will be chosen using coordonates
    // 150-230: English
    // 250-330: Romanian
    // 350-430: French
    // 450-530: German
    while (1)
    {
        if (ismouseclick(WM_LBUTTONDOWN) && !hello)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            int x = mousex();
            int y = mousey();
            if (x >= 100 && x <= 700 && y >= 150 && y <= 230)
            {
                L = en;
                startingPage();
                break;
            }
            if (x >= 100 && x <= 400)
            {
                if (y >= 250 && y <= 330)
                {
                    L = ro;
                    hello = true;
                }
                if (y >= 350 && y <= 430)
                {
                    L = fr;
                    hello = true;
                }
                if (y >= 450 && y <= 530)
                {
                    L = ge;
                    hello = true;
                }

                if (hello)
                {
                    startingPage();
                    break;
                }
            }
        }
    }
}

void refresh()
{
    cleardevice();

    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(0, 0, systemWidth, 120);
    bar(0, 0, middleX - 500, systemHeight);
    //

    settextstyle(8, HORIZ_DIR, 1);

    int yT = 10, yB = 110;

    // available electric devices

    readimagefile("condensator.bmp", middleX - 590, yT, middleX - 490, yB);

    readimagefile("dioda.bmp", middleX - 470, yT, middleX - 370, yB);

    readimagefile("tranzistor.bmp", middleX - 350, yT, middleX - 250, yB);

    readimagefile("inductor.bmp", middleX - 230, yT, middleX - 130, yB);

    readimagefile("rezistor.bmp", middleX - 110, yT, middleX - 10, yB);

    readimagefile("voltmeter.bmp", middleX + 10, yT, middleX + 110, yB);

    readimagefile("ammeter.bmp", middleX + 130, yT, middleX + 230, yB);

    readimagefile("bulb.bmp", middleX + 250, yT, middleX + 350, yB);

    readimagefile("fuse.bmp", middleX + 370, yT, middleX + 470, yB);

    readimagefile("battery.bmp", middleX + 490, yT, middleX + 590, yB);

    // circuit editing buttons

    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(middleX - 630, systemHeight - 600, middleX - 510, systemHeight - 560);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX - 600, systemHeight - 592, L.edit);

    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(middleX - 630, systemHeight - 550, middleX - 510, systemHeight - 510);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX - 600, systemHeight - 542, L.clearr);

    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(middleX - 630, systemHeight - 500, middleX - 510, systemHeight - 460);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX - 590, systemHeight - 492, L.load);

    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(middleX - 630, systemHeight - 450, middleX - 510, systemHeight - 410);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX - 590, systemHeight - 442, L.save);

    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(middleX - 630, systemHeight - 400, middleX - 510, systemHeight - 360);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX - 608, systemHeight - 392, "Rotate");

    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(middleX - 630, systemHeight - 350, middleX - 580, systemHeight - 310);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX - 608, systemHeight - 342, "+");

    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(middleX - 560, systemHeight - 350, middleX - 510, systemHeight - 310);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX - 538, systemHeight - 342, "-");

    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(middleX - 630, systemHeight - 300, middleX - 510, systemHeight - 260);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX - 590, systemHeight - 292, L.mov);

    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(middleX - 630, systemHeight - 250, middleX - 510, systemHeight - 210);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX - 600, systemHeight - 242, L.dele);

    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(middleX - 630, systemHeight - 200, middleX - 510, systemHeight - 160);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX - 590, systemHeight - 192, L.exit);

    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(middleX - 630, systemHeight - 150, middleX - 510, systemHeight - 30);
    setcolor(WHITE);
    rectangle(middleX - 631, systemHeight - 151, middleX - 510, systemHeight - 30);
    line(middleX - 631, systemHeight - 130, middleX - 510, systemHeight - 130);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX - 625, systemHeight - 150, L.props);
    setbkcolor(BLACK);
}

/// @brief Function that is used to draw the images and takes
void images()
{
    refresh();
    int x, y;
    bool click = false;
    while (1)
    {
        if (ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x = mousex();
            y = mousey();
            if (x >= middleX - 590 && x <= middleX - 490 && y >= 10 && y <= 110)
            {
                while (1)
                {
                    if (ismouseclick(WM_LBUTTONDOWN) && !click)
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        if (mousex() < middleX - 410 || mousey() < 200 || mousex() > systemWidth - 85 || mousey() > systemHeight - 60)
                            continue;
                        if (!imageOverlap(mousex(), mousey(), objectsCount))
                            continue;
                        readimagefile("condensator.bmp", mousex() - objectSize, mousey() - objectSize, mousex() + objectSize, mousey() + objectSize);
                        circle(mousex() - (objectSize + 2), mousey(), 6);
                        circle(mousex() + (objectSize + 2), mousey(), 6);
                        objects[objectsCount].x = mousex();
                        objects[objectsCount].y = mousey();
                        strcpy(objects[objectsCount].type, "condensator.bmp");
                        strcpy(objects[objectsCount].properties.measurement, "Farad     ");
                        strcpy(objects[objectsCount].properties.name, "condenser ");
                        commonSet();
                        break;
                    }
                }
            }
            if (x >= middleX - 470 && x <= middleX - 370 && y >= 10 && y <= 110)
            {
                while (1)
                {
                    if (ismouseclick(WM_LBUTTONDOWN) && !click)
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        if (mousex() < middleX - 410 || mousey() < 200 || mousex() > systemWidth - 85 || mousey() > systemHeight - 60)
                            continue;
                        if (!imageOverlap(mousex(), mousey(), objectsCount))
                            continue;
                        readimagefile("dioda.bmp", mousex() - objectSize, mousey() - objectSize, mousex() + objectSize, mousey() + objectSize);
                        circle(mousex() - 78, mousey(), 6);
                        circle(mousex() + 78, mousey(), 6);
                        objects[objectsCount].x = mousex();
                        objects[objectsCount].y = mousey();
                        strcpy(objects[objectsCount].type, "dioda.bmp");
                        strcpy(objects[objectsCount].properties.measurement, "Ohm       ");
                        strcpy(objects[objectsCount].properties.name, "diode     ");
                        commonSet();
                        break;
                    }
                }
            }
            if (x >= middleX - 350 && x <= middleX - 250 && y >= 10 && y <= 110)
            {
                while (1)
                {
                    if (ismouseclick(WM_LBUTTONDOWN) && !click)
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        if (mousex() < middleX - 410 || mousey() < 200 || mousex() > systemWidth - 85 || mousey() > systemHeight - 60)
                            continue;
                        if (!imageOverlap(mousex(), mousey(), objectsCount))
                            continue;
                        readimagefile("tranzistor.bmp", mousex() - objectSize, mousey() - objectSize, mousex() + objectSize, mousey() + objectSize);
                        circle(mousex() - 78, mousey(), 6);
                        circle(mousex() + 78, mousey(), 6);
                        objects[objectsCount].x = mousex();
                        objects[objectsCount].y = mousey();
                        strcpy(objects[objectsCount].type, "tranzistor.bmp");
                        strcpy(objects[objectsCount].properties.name, "transistor");
                        strcpy(objects[objectsCount].properties.measurement, "Ohm/A/V   ");
                        commonSet();
                        break;
                    }
                }
            }
            if (x >= middleX - 230 && x <= middleX - 130 && y >= 10 && y <= 110)
            {
                while (1)
                {
                    if (ismouseclick(WM_LBUTTONDOWN) && !click)
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        if (mousex() < middleX - 410 || mousey() < 200 || mousex() > systemWidth - 85 || mousey() > systemHeight - 60)
                            continue;
                        if (!imageOverlap(mousex(), mousey(), objectsCount))
                            continue;
                        readimagefile("inductor.bmp", mousex() - objectSize, mousey() - objectSize, mousex() + objectSize, mousey() + objectSize);
                        circle(mousex() - 78, mousey(), 6);
                        circle(mousex() + 78, mousey(), 6);
                        objects[objectsCount].x = mousex();
                        objects[objectsCount].y = mousey();
                        strcpy(objects[objectsCount].type, "inductor.bmp");
                        strcpy(objects[objectsCount].properties.measurement, "Henrys    ");
                        strcpy(objects[objectsCount].properties.name, "inductor  ");
                        commonSet();
                        break;
                    }
                }
            }
            if (x >= middleX - 110 && x <= middleX - 10 && y >= 10 && y <= 110)
            {
                while (1)
                {
                    if (ismouseclick(WM_LBUTTONDOWN) && !click)
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        if (mousex() < middleX - 410 || mousey() < 200 || mousex() > systemWidth - 85 || mousey() > systemHeight - 60)
                            continue;
                        if (!imageOverlap(mousex(), mousey(), objectsCount))
                            continue;
                        readimagefile("rezistor.bmp", mousex() - objectSize, mousey() - objectSize, mousex() + objectSize, mousey() + objectSize);
                        circle(mousex() - 78, mousey(), 6);
                        circle(mousex() + 78, mousey(), 6);
                        objects[objectsCount].x = mousex();
                        objects[objectsCount].y = mousey();
                        strcpy(objects[objectsCount].type, "rezistor.bmp");
                        strcpy(objects[objectsCount].properties.measurement, "Ohm       ");
                        strcpy(objects[objectsCount].properties.name, "resistor  ");
                        commonSet();
                        break;
                    }
                }
            }
            if (x >= middleX + 10 && x <= middleX + 110 && y >= 10 && y <= 110)
            {
                while (1)
                {
                    if (ismouseclick(WM_LBUTTONDOWN) && !click)
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        if (mousex() < middleX - 410 || mousey() < 200 || mousex() > systemWidth - 85 || mousey() > systemHeight - 60)
                            continue;
                        if (!imageOverlap(mousex(), mousey(), objectsCount))
                            continue;
                        readimagefile("voltmeter.bmp", mousex() - objectSize, mousey() - objectSize, mousex() + objectSize, mousey() + objectSize);
                        circle(mousex() - 78, mousey(), 6);
                        circle(mousex() + 78, mousey(), 6);
                        objects[objectsCount].x = mousex();
                        objects[objectsCount].y = mousey();
                        strcpy(objects[objectsCount].type, "voltmeter.bmp");
                        strcpy(objects[objectsCount].properties.measurement, "Volt      ");
                        strcpy(objects[objectsCount].properties.name, "voltmeter ");
                        commonSet();
                        break;
                    }
                }
            }
            if (x >= middleX + 130 && x <= middleX + 230 && y >= 10 && y <= 110)
            {
                while (1)
                {
                    if (ismouseclick(WM_LBUTTONDOWN) && !click)
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        if (mousex() < middleX - 410 || mousey() < 200 || mousex() > systemWidth - 85 || mousey() > systemHeight - 60)
                            continue;
                        if (!imageOverlap(mousex(), mousey(), objectsCount))
                            continue;
                        readimagefile("ammeter.bmp", mousex() - objectSize, mousey() - objectSize, mousex() + objectSize, mousey() + objectSize);
                        circle(mousex() - 78, mousey(), 6);
                        circle(mousex() + 78, mousey(), 6);
                        objects[objectsCount].x = mousex();
                        objects[objectsCount].y = mousey();
                        strcpy(objects[objectsCount].type, "ammeter.bmp");
                        strcpy(objects[objectsCount].properties.measurement, "Amperes   ");
                        strcpy(objects[objectsCount].properties.name, "ammeter   ");
                        commonSet();
                        break;
                    }
                }
            }
            if (x >= middleX + 250 && x <= middleX + 350 && y >= 10 && y <= 110)
            {
                while (1)
                {
                    if (ismouseclick(WM_LBUTTONDOWN) && !click)
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        if (mousex() < middleX - 410 || mousey() < 200 || mousex() > systemWidth - 85 || mousey() > systemHeight - 60)
                            continue;
                        if (!imageOverlap(mousex(), mousey(), objectsCount))
                            continue;
                        readimagefile("bulb.bmp", mousex() - objectSize, mousey() - objectSize, mousex() + objectSize, mousey() + objectSize);
                        circle(mousex() - 78, mousey(), 6);
                        circle(mousex() + 78, mousey(), 6);
                        objects[objectsCount].x = mousex();
                        objects[objectsCount].y = mousey();
                        strcpy(objects[objectsCount].type, "bulb.bmp");
                        strcpy(objects[objectsCount].properties.measurement, "Watts     ");
                        strcpy(objects[objectsCount].properties.name, "bulb      ");
                        commonSet();
                        break;
                    }
                }
            }
            if (x >= middleX + 370 && x <= middleX + 470 && y >= 10 && y <= 110)
            {
                while (1)
                {
                    if (ismouseclick(WM_LBUTTONDOWN) && !click)
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        if (mousex() < middleX - 410 || mousey() < 200 || mousex() > systemWidth - 85 || mousey() > systemHeight - 60)
                            continue;
                        if (!imageOverlap(mousex(), mousey(), objectsCount))
                            continue;
                        readimagefile("fuse.bmp", mousex() - objectSize, mousey() - objectSize, mousex() + objectSize, mousey() + objectSize);
                        circle(mousex() - 78, mousey(), 6);
                        circle(mousex() + 78, mousey(), 6);
                        objects[objectsCount].x = mousex();
                        objects[objectsCount].y = mousey();
                        strcpy(objects[objectsCount].type, "fuse.bmp");
                        strcpy(objects[objectsCount].properties.measurement, "Amperes   ");
                        strcpy(objects[objectsCount].properties.name, "fuse      ");
                        commonSet();
                        break;
                    }
                }
            }
            if (x >= middleX + 490 && x <= middleX + 590 && y >= 10 && y <= 110)
            {
                while (1)
                {
                    if (ismouseclick(WM_LBUTTONDOWN) && !click)
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        if (mousex() < middleX - 410 || mousey() < 200 || mousex() > systemWidth - 85 || mousey() > systemHeight - 60)
                            continue;
                        if (!imageOverlap(mousex(), mousey(), objectsCount))
                            continue;
                        readimagefile("battery.bmp", mousex() - objectSize, mousey() - objectSize, mousex() + objectSize, mousey() + objectSize);
                        circle(mousex() - 78, mousey(), 6);
                        circle(mousex() + 78, mousey(), 6);
                        objects[objectsCount].x = mousex();
                        objects[objectsCount].y = mousey();
                        strcpy(objects[objectsCount].type, "battery.bmp");
                        strcpy(objects[objectsCount].properties.measurement, "mAmps*H   ");
                        strcpy(objects[objectsCount].properties.name, "battery   ");
                        commonSet();
                        break;
                    }
                }
            }

            for (int i = 0; i < objectsCount; i++)
            {
                if (x >= objects[i].x - objectSize && x <= objects[i].x + objectSize && y >= objects[i].y - objectSize && y <= objects[i].y + objectSize)
                {
                    propertiesDisplay(i);
                }
                // LEFT connection in I
                if (x >= objects[i].x - (objectSize + 6) && x <= objects[i].x - objectSize && y >= objects[i].y - 6 && y <= objects[i].y + 6 && objects[i].rotateState % 2 != 0)
                    while (1)
                    {
                        if (ismouseclick(WM_LBUTTONDOWN))
                        {
                            clearmouseclick(WM_LBUTTONDOWN);
                            for (int j = 0; j < objectsCount; j++)
                            {
                                if (mousex() >= objects[j].x - (objectSize + 6) && mousex() <= objects[j].x - objectSize && mousey() >= objects[j].y - 6 && mousey() <= objects[j].y + 6 && objects[j].rotateState % 2 != 0)
                                {
                                    objects[i].leftConnector.index = j;
                                    objects[j].leftConnector.index = i;
                                    strcpy(objects[i].leftConnector.type, "LL");
                                    strcpy(objects[j].leftConnector.type, "LL");
                                    connectionLL(i, j);
                                }
                                else if (mousex() <= objects[j].x + (objectSize + 6) && mousex() >= objects[j].x + objectSize && mousey() >= objects[j].y - 6 && mousey() <= objects[j].y + 6 && objects[j].rotateState % 2 != 0)
                                {
                                    objects[i].leftConnector.index = j;
                                    objects[j].rightConnector.index = i;
                                    strcpy(objects[i].leftConnector.type, "RL");
                                    strcpy(objects[j].rightConnector.type, "RL");
                                    connectionAnalyst(i, j);
                                }
                                else if (mousex() >= objects[j].x - 6 && mousex() <= objects[j].x + 6 && mousey() >= objects[j].y + objectSize && mousey() <= objects[j].y + (objectSize + 6) && objects[j].rotateState % 2 == 0)
                                {
                                    objects[i].leftConnector.index = j;
                                    objects[j].bottomConnector.index = i;
                                    strcpy(objects[i].leftConnector.type, "BL");
                                    strcpy(objects[j].bottomConnector.type, "BL");
                                    connectionBL(i, j);
                                }
                                else if (mousex() >= objects[j].x - 6 && mousex() <= objects[j].x + 6 && mousey() >= objects[j].y - (objectSize + 6) && mousey() <= objects[j].y - objectSize && objects[j].rotateState % 2 == 0)
                                {
                                    objects[i].leftConnector.index = j;
                                    objects[j].topConnector.index = i;
                                    strcpy(objects[i].leftConnector.type, "TL");
                                    strcpy(objects[j].topConnector.type, "TL");
                                    connectionTL(i, j);
                                }
                            }
                            break;
                        }
                    }
                // RIGHT connection in I
                if (x <= objects[i].x + (objectSize + 6) && x >= objects[i].x + objectSize && y >= objects[i].y - 6 && y <= objects[i].y + 6 && objects[i].rotateState % 2 != 0)
                    while (1)
                    {
                        if (ismouseclick(WM_LBUTTONDOWN))
                        {
                            clearmouseclick(WM_LBUTTONDOWN);
                            for (int j = 0; j < objectsCount; j++)
                            {
                                if (mousex() >= objects[j].x - (objectSize + 6) && mousex() <= objects[j].x - objectSize && mousey() >= objects[j].y - 6 && mousey() <= objects[j].y + 6 && objects[j].rotateState % 2 != 0)
                                {

                                    objects[i].rightConnector.index = j;
                                    objects[j].leftConnector.index = i;
                                    strcpy(objects[i].rightConnector.type, "RL");
                                    strcpy(objects[j].leftConnector.type, "RL");
                                    connectionAnalyst(i, j);
                                }
                                else if (mousex() <= objects[j].x + (objectSize + 6) && mousex() >= objects[j].x + objectSize && mousey() >= objects[j].y - 6 && mousey() <= objects[j].y + 6 && objects[j].rotateState % 2 != 0)
                                {
                                    objects[i].rightConnector.index = j;
                                    objects[j].rightConnector.index = i;
                                    strcpy(objects[i].rightConnector.type, "RR");
                                    strcpy(objects[j].rightConnector.type, "RR");
                                    connectionRR(i, j);
                                }
                                else if (mousex() >= objects[j].x - 6 && mousex() <= objects[j].x + 6 && mousey() >= objects[j].y + objectSize && mousey() <= objects[j].y + (objectSize + 6) && objects[j].rotateState % 2 == 0)
                                {
                                    objects[i].rightConnector.index = j;
                                    objects[j].bottomConnector.index = i;
                                    strcpy(objects[i].rightConnector.type, "BR");
                                    strcpy(objects[j].bottomConnector.type, "BR");
                                    connectionBR(i, j);
                                }
                                else if (mousex() >= objects[j].x - 6 && mousex() <= objects[j].x + 6 && mousey() >= objects[j].y - (objectSize + 6) && mousey() <= objects[j].y - objectSize && objects[j].rotateState % 2 == 0)
                                {
                                    objects[i].rightConnector.index = j;
                                    objects[j].topConnector.index = i;
                                    strcpy(objects[i].rightConnector.type, "TR");
                                    strcpy(objects[j].topConnector.type, "TR");
                                    connectionTR(i, j);
                                }
                            }
                            break;
                        }
                    }

                // BOTTOM connection in I
                if (mousex() >= objects[i].x - 6 && mousex() <= objects[i].x + 6 && mousey() >= objects[i].y + objectSize && mousey() <= objects[i].y + (objectSize + 6) && objects[i].rotateState % 2 == 0)
                    while (1)
                    {
                        if (ismouseclick(WM_LBUTTONDOWN))
                        {
                            clearmouseclick(WM_LBUTTONDOWN);
                            for (int j = 0; j < objectsCount; j++)
                            {
                                if (mousex() >= objects[j].x - (objectSize + 6) && mousex() <= objects[j].x - objectSize && mousey() >= objects[j].y - 6 && mousey() <= objects[j].y + 6 && objects[j].rotateState % 2 != 0)
                                {
                                    objects[i].bottomConnector.index = j;
                                    objects[j].leftConnector.index = i;
                                    strcpy(objects[i].bottomConnector.type, "BL");
                                    strcpy(objects[j].leftConnector.type, "BL");
                                    connectionBL(i, j);
                                }
                                else if (mousex() <= objects[j].x + (objectSize + 6) && mousex() >= objects[j].x + objectSize && mousey() >= objects[j].y - 6 && mousey() <= objects[j].y + 6 && objects[j].rotateState % 2 != 0)
                                {
                                    objects[i].bottomConnector.index = j;
                                    objects[j].rightConnector.index = i;
                                    strcpy(objects[i].bottomConnector.type, "BR");
                                    strcpy(objects[j].rightConnector.type, "BR");
                                    connectionBR(i, j);
                                }
                                else if (mousex() >= objects[j].x - 6 && mousex() <= objects[j].x + 6 && mousey() >= objects[j].y + objectSize && mousey() <= objects[j].y + (objectSize + 6) && objects[j].rotateState % 2 == 0)
                                {
                                    objects[i].bottomConnector.index = j;
                                    objects[j].bottomConnector.index = i;
                                    strcpy(objects[i].bottomConnector.type, "BB");
                                    strcpy(objects[j].bottomConnector.type, "BB");
                                    connectionBB(i, j);
                                }
                                else if (mousex() >= objects[j].x - 6 && mousex() <= objects[j].x + 6 && mousey() >= objects[j].y - (objectSize + 6) && mousey() <= objects[j].y - objectSize && objects[j].rotateState % 2 == 0)
                                {
                                    objects[i].bottomConnector.index = j;
                                    objects[j].topConnector.index = i;
                                    strcpy(objects[i].bottomConnector.type, "BT");
                                    strcpy(objects[j].topConnector.type, "BT");
                                    connectionBT(i, j, 'B');
                                }
                            }
                            break;
                        }
                    }
                // TOP connection in I
                if (mousex() >= objects[i].x - 6 && mousex() <= objects[i].x + 6 && mousey() >= objects[i].y - (objectSize + 6) && mousey() <= objects[i].y - objectSize && objects[i].rotateState % 2 == 0)
                    while (1)
                    {
                        if (ismouseclick(WM_LBUTTONDOWN))
                        {
                            clearmouseclick(WM_LBUTTONDOWN);
                            for (int j = 0; j < objectsCount; j++)
                            {
                                if (mousex() >= objects[j].x - (objectSize + 6) && mousex() <= objects[j].x - objectSize && mousey() >= objects[j].y - 6 && mousey() <= objects[j].y + 6 && objects[j].rotateState % 2 != 0)
                                {

                                    objects[i].topConnector.index = j;
                                    objects[j].leftConnector.index = i;
                                    strcpy(objects[i].topConnector.type, "TL");
                                    strcpy(objects[j].leftConnector.type, "TL");
                                    connectionTL(i, j);
                                }
                                else if (mousex() <= objects[j].x + (objectSize + 6) && mousex() >= objects[j].x + objectSize && mousey() >= objects[j].y - 6 && mousey() <= objects[j].y + 6 && objects[j].rotateState % 2 != 0)
                                {
                                    objects[i].topConnector.index = j;
                                    objects[j].rightConnector.index = i;
                                    strcpy(objects[i].topConnector.type, "TR");
                                    strcpy(objects[j].rightConnector.type, "TR");
                                    connectionTR(i, j);
                                }
                                else if (mousex() >= objects[j].x - 6 && mousex() <= objects[j].x + 6 && mousey() >= objects[j].y + objectSize && mousey() <= objects[j].y + (objectSize + 6) && objects[j].rotateState % 2 == 0)
                                {
                                    objects[i].topConnector.index = j;
                                    objects[j].bottomConnector.index = i;
                                    strcpy(objects[i].topConnector.type, "BT");
                                    strcpy(objects[j].bottomConnector.type, "BT");
                                    connectionBT(i, j, 'T');
                                }
                                else if (mousex() >= objects[j].x - 6 && mousex() <= objects[j].x + 6 && mousey() >= objects[j].y - (objectSize + 6) && mousey() <= objects[j].y - objectSize && objects[j].rotateState % 2 == 0)
                                {
                                    objects[i].topConnector.index = j;
                                    objects[j].topConnector.index = i;
                                    strcpy(objects[i].topConnector.type, "TT");
                                    strcpy(objects[j].topConnector.type, "TT");
                                    connectionTT(i, j);
                                }
                            }
                            break;
                        }
                    }
            }

            if (x >= middleX - 630 && x <= middleX - 510 && y >= systemHeight - 600 && y <= systemHeight - 560)
            {
                cout << "pushed edit()" << '\n';
                edit();
            }
            if (x >= middleX - 630 && x <= middleX - 510 && y >= systemHeight - 550 && y <= systemHeight - 510)
            {
                cout << "pushed clear()" << '\n';
                clear();
            }
            if (x >= middleX - 630 && x <= middleX - 510 && y >= systemHeight - 500 && y <= systemHeight - 460)
            {
                cout << "pushed load()" << '\n';
                load();
            }
            if (x >= middleX - 630 && x <= middleX - 510 && y >= systemHeight - 450 && y <= systemHeight - 410)
            {
                cout << "pushed save()" << '\n';
                save();
            }
            if (x >= middleX - 630 && x <= middleX - 510 && y >= systemHeight - 400 && y <= systemHeight - 360)
            {
                cout << "pushed rotateObject()" << '\n';
                rotateObject();
            }
            if (x >= middleX - 630 && x <= middleX - 580 && y >= systemHeight - 350 && y <= systemHeight - 310)
            {
                cout << "pushed zoomIn()" << '\n';
                zoomIn();
            }
            if (x >= middleX - 560 && x <= middleX - 510 && y >= systemHeight - 350 && y <= systemHeight - 310)
            {
                cout << "pushed zoomOut()" << '\n';
                zoomOut();
            }
            if (x >= middleX - 630 && x <= middleX - 510 && y >= systemHeight - 300 && y <= systemHeight - 260)
            {
                cout << "pushed move()" << '\n';
                mov();
            }
            if (x >= middleX - 630 && x <= middleX - 510 && y >= systemHeight - 250 && y <= systemHeight - 210)
            {
                cout << "pushed delete()" << '\n';
                deleteObject();
            }

            if (x >= middleX - 630 && x <= middleX - 510 && y >= systemHeight - 200 && y <= systemHeight - 160)
            {
                cout << "pushed exit()" << '\n';
                exit();
            }
        }
    }
}

void draw()
{
    refresh();

    for (int j = 0; j < objectsCount; j++)
    {
        readimagefile(objects[j].type, objects[j].x - objectSize, objects[j].y - objectSize, objects[j].x + objectSize, objects[j].y + objectSize);
        if (objects[j].rotateState % 2 == 0)
        {
            circle(objects[j].x, objects[j].y + (objectSize + 2), 6);
            circle(objects[j].x, objects[j].y - (objectSize + 2), 6);
        }
        else
        {
            circle(objects[j].x + (objectSize + 2), objects[j].y, 6);
            circle(objects[j].x - (objectSize + 2), objects[j].y, 6);
        }

        if (objects[j].rightConnector.index > -1)
        {
            if (objects[j].rightConnector.type[1] == 'R' && objects[j].rightConnector.type[0] == 'R' && objects[objects[j].rightConnector.index].rightConnector.index == j)
                connectionRR(j, objects[j].rightConnector.index);
            else if (objects[j].rightConnector.type[1] == 'L' && objects[objects[j].rightConnector.index].leftConnector.index == j)
                connectionAnalyst(j, objects[j].rightConnector.index);
            else if (objects[j].rightConnector.type[0] == 'T' && objects[objects[j].rightConnector.index].topConnector.index == j)
                connectionTR(j, objects[j].rightConnector.index);
            else if (objects[j].rightConnector.type[0] == 'B' && objects[objects[j].rightConnector.index].bottomConnector.index == j)
                connectionBR(j, objects[j].rightConnector.index);
        }
        if (objects[j].leftConnector.index > -1)
        {
            if (objects[j].leftConnector.type[0] == 'L' && objects[objects[j].leftConnector.index].leftConnector.index == j)
                connectionLL(j, objects[j].leftConnector.index);
            else if (objects[j].leftConnector.type[0] == 'R' && objects[objects[j].leftConnector.index].rightConnector.index == j)
                connectionAnalyst(j, objects[j].leftConnector.index);
            else if (objects[j].leftConnector.type[0] == 'T' && objects[objects[j].leftConnector.index].topConnector.index == j)
                connectionTL(j, objects[j].leftConnector.index);
            else if (objects[j].leftConnector.type[0] == 'B' && objects[objects[j].leftConnector.index].bottomConnector.index == j)
                connectionBL(j, objects[j].leftConnector.index);
        }
        if (objects[j].topConnector.index > -1)
        {
            if (objects[j].topConnector.type[1] == 'T' && objects[j].topConnector.type[0] == 'T' && objects[objects[j].topConnector.index].topConnector.index == j)
                connectionTT(j, objects[j].topConnector.index);
            else if (objects[j].topConnector.type[0] == 'B' && objects[objects[j].topConnector.index].bottomConnector.index == j)
                connectionBT(j, objects[j].topConnector.index, 'T');
            else if (objects[j].topConnector.type[1] == 'R' && objects[objects[j].topConnector.index].rightConnector.index == j)
                connectionTR(j, objects[j].topConnector.index);
            else if (objects[j].topConnector.type[1] == 'L' && objects[objects[j].topConnector.index].leftConnector.index == j)
                connectionTL(j, objects[j].topConnector.index);
        }
        if (objects[j].bottomConnector.index > -1)
        {
            if (objects[j].bottomConnector.type[1] == 'B' && objects[objects[j].bottomConnector.index].bottomConnector.index == j)
                connectionBB(j, objects[j].bottomConnector.index);
            else if (objects[j].bottomConnector.type[1] == 'T' && objects[objects[j].bottomConnector.index].topConnector.index == j)
                connectionBT(j, objects[j].bottomConnector.index, 'B');
            else if (objects[j].bottomConnector.type[1] == 'R' && objects[objects[j].bottomConnector.index].rightConnector.index == j)
                connectionBR(j, objects[j].bottomConnector.index);
            else if (objects[j].bottomConnector.type[1] == 'L' && objects[objects[j].bottomConnector.index].leftConnector.index == j)
                connectionBL(j, objects[j].bottomConnector.index);
        }
    }
}

/*<-----------------------Connection--------------------->*/

void connectionAnalyst(int i, int j)
{

    if (objects[i].leftConnector.index == j)
    {

        if (objects[j].rightConnector.index == i)
        {
            if (objects[j].x + (objectSize + 6) < objects[i].x - (objectSize + 6))
                connectionRL(i, j, 'l');
            else
                connectionS(i, j, 'l');
        }
    }
    else if (objects[i].rightConnector.index == j)
    {
        if (objects[j].leftConnector.index == i)
        {
            if (objects[i].x + (objectSize + 6) < objects[j].x - (objectSize + 6))
                connectionRL(i, j, 'r');
            else
                connectionS(i, j, 'r');
        }
    }
}

void connectionRR(int i, int j)
{

    if (objects[i].x > objects[j].x)
        swap(i, j);

    line(objects[j].x + (objectSize + 6), objects[j].y, objects[j].x + 100, objects[j].y);
    int ok;
    int x = objects[j].x + 100, y = objects[i].y;

    cornerOverlap(x, y, objects[i].x + (objectSize + 6), objects[j].y);

    verticalOverlap(objects[j].y, y, objects[j].x + 100, ok);
    if (ok == 0)
        line(objects[j].x + 100, objects[j].y, objects[j].x + 100, y);

    horizontalOverlap(objects[i].x + (objectSize + 6), x, objects[i].y, ok);
    if (ok == 0)
        line(objects[i].x + (objectSize + 6), objects[i].y, x, objects[i].y);

    cout << "connected RR \n"
         << i << endl
         << j << endl;
}

void connectionLL(int i, int j)
{

    if (objects[j].x > objects[i].x)
        swap(i, j);

    line(objects[j].x - (objectSize + 6), objects[j].y, objects[j].x - 100, objects[j].y);

    int ok, x = objects[j].x - 100, y = objects[i].y;

    cornerOverlap(x, y, objects[i].x - (objectSize + 6), objects[j].y);

    verticalOverlap(objects[j].y, y, objects[j].x - 100, ok);
    if (ok == 0)
        line(objects[j].x - 100, objects[j].y, objects[j].x - 100, y);
    horizontalOverlap(x, objects[i].x - (objectSize + 6), objects[i].y, ok);
    if (ok == 0)
        line(x, objects[i].y, objects[i].x - (objectSize + 6), objects[i].y);

    cout << "connected LL \n";
}

void connectionRL(int i, int j, char connectorI)
{
    if (connectorI == 'l')
        swap(i, j);

    float difference = (objects[j].x - objects[i].x - 162) / 2;
    int ok;
    int x = objects[i].x + (objectSize + 6) + difference, y = objects[i].y;
    cornerOverlap(x, y, objects[i].x + (objectSize + 6), objects[j].y);
    horizontalOverlap(objects[i].x + (objectSize + 6), x, objects[i].y, ok);
    if (ok == 0)
        line(objects[i].x + (objectSize + 6), objects[i].y, x, objects[i].y);
    x = objects[i].x + (objectSize + 6) + difference;
    int y1 = objects[j].y;
    cornerOverlap(x, y1, objects[j].x - (objectSize + 6), objects[i].y);
    verticalOverlap(y, y1, objects[i].x + (objectSize + 6) + difference, ok);
    if (ok == 0)
        line(objects[i].x + (objectSize + 6) + difference, y, objects[i].x + (objectSize + 6) + difference, y1);
    horizontalOverlap(x, objects[j].x - (objectSize + 6), objects[j].y, ok);
    if (ok == 0)
        line(x, objects[j].y, objects[j].x - (objectSize + 6), objects[j].y);

    cout << "connected RL \n";
}

void connectionS(int i, int j, char connectorI) // this is a S type connection which means the left object is connected with the right one by left-right connectors
{
    if (objects[j].y < objects[i].y)
    {
        swap(i, j);
        if (connectorI == 'r')
            connectorI = 'l';
        else
            connectorI = 'r';
    }

    if (objects[i].y + objectSize > objects[j].y - objectSize)
    {
        if (objects[i].x > objects[j].x)
            swap(i, j);
        int mx = max(objects[i].y + objectSize + 5, objects[j].y + objectSize + 5), x = objects[i].x - (objectSize + 16), y = mx, ok;

        line(objects[i].x - (objectSize + 6), objects[i].y, objects[i].x - (objectSize + 16), objects[i].y);
        cornerOverlap(x, y, objects[j].x + (objectSize + 16), objects[i].y);
        line(objects[i].x - (objectSize + 16), objects[i].y, objects[i].x - (objectSize + 16), y);
        int x1 = objects[j].x + (objectSize + 16);
        y = mx;
        cornerOverlap(x1, y, x, objects[j].y);
        horizontalOverlap(x, x1, mx, ok);
        if (ok == 0)
            line(x, mx, x1, mx);
        line(objects[j].x + (objectSize + 16), y, objects[j].x + (objectSize + 16), objects[j].y);
        line(objects[j].x + (objectSize + 16), objects[j].y, objects[j].x + (objectSize + 6), objects[j].y);

        cout << "done" << endl;
    }

    else if (connectorI == 'l')
    {
        float difY = (objects[j].y - objects[i].y) / 2, difX = (objects[j].x - objects[i].x + (objectSize + 16));
        int ok;
        line(objects[i].x - (objectSize + 6), objects[i].y, objects[i].x - (objectSize + 16), objects[i].y);
        int x = objects[i].x - (objectSize + 16), y = objects[i].y + difY;
        cornerOverlap(x, y, objects[i].x + difX, objects[i].y);
        verticalOverlap(objects[i].y, y, objects[i].x - (objectSize + 16), ok);
        if (ok == 0)
            line(objects[i].x - (objectSize + 16), objects[i].y, objects[i].x - (objectSize + 16), y);
        y = objects[i].y + difY;
        int x1 = objects[j].x + (objectSize + 16);
        cornerOverlap(x1, y, x, objects[j].y);
        horizontalOverlap(x, x1, objects[i].y + difY, ok);
        if (ok == 0)
            line(x, objects[i].y + difY, x1, objects[i].y + difY);
        verticalOverlap(y, objects[j].y, objects[j].x + (objectSize + 16), ok);
        if (ok == 0)
            line(objects[j].x + (objectSize + 16), objects[j].y, objects[i].x + difX, y);
        line(objects[j].x + (objectSize + 6), objects[j].y, objects[j].x + (objectSize + 16), objects[j].y);
    }
    else if (connectorI == 'r')
    {

        float difY = (objects[j].y - objects[i].y) / 2, difX = (objects[i].x - objects[j].x + (objectSize + 16));
        line(objects[i].x + (objectSize + 6), objects[i].y, objects[i].x + (objectSize + 16), objects[i].y);
        int ok;
        int x = objects[i].x + (objectSize + 16), y = objects[i].y + difY;
        cornerOverlap(x, y, objects[i].x - difX, objects[i].y);
        verticalOverlap(objects[i].y, y, objects[i].x + (objectSize + 16), ok);
        if (ok == 0)
            line(objects[i].x + (objectSize + 16), objects[i].y, objects[i].x + (objectSize + 16), y);
        int x1 = objects[j].x - (objectSize + 16);
        y = objects[i].y + difY;
        cornerOverlap(x1, y, x, objects[j].y);
        horizontalOverlap(x1, x, objects[i].y + difY, ok);
        if (ok == 0)
            line(x1, objects[i].y + difY, x, objects[i].y + difY);
        line(objects[j].x - (objectSize + 6), objects[j].y, objects[j].x - (objectSize + 16), objects[j].y);
        verticalOverlap(objects[j].y, y, objects[i].x - difX, ok);
        if (ok == 0)
            line(objects[j].x - (objectSize + 16), objects[j].y, objects[i].x - difX, y);
    }
    cout << "connected S \n";
}

void connectionBT(int i, int j, char connectorI)
{
    if (objects[i].y > objects[j].y)
    {
        swap(i, j);
        if (connectorI == 'B')
            connectorI = 'T';
        else
            connectorI = 'B';
    }

    if (objects[i].y + 81 < objects[j].y - 81 && connectorI == 'B')
    {
        float dif = abs(objects[j].y - objects[i].y) / 2;
        int ok, x = objects[i].x, y = objects[i].y + dif;
        cornerOverlap(x, y, objects[j].x, objects[i].y + (objectSize + 6));
        line(objects[i].x, objects[i].y + (objectSize + 6), objects[i].x, y);
        y = objects[i].y + dif;
        int x1 = objects[j].x;
        cornerOverlap(x1, y, x, objects[j].y - (objectSize + 6));
        horizontalOverlap(x, x1, objects[i].y + dif, ok);
        if (ok == 0)
            line(x, objects[i].y + dif, x1, objects[i].y + dif);
        line(objects[j].x, y, objects[j].x, objects[j].y - (objectSize + 6));
    }
    else
    {
        if (connectorI == 'B')
            swap(i, j);

        int a;
        if (objects[i].x < objects[j].x)
            a = 80;
        else
            a = -80;
        line(objects[i].x, objects[i].y - (objectSize + 6), objects[i].x, objects[i].y - (objectSize + 16));
        line(objects[i].x, objects[i].y - (objectSize + 16), objects[i].x + a, objects[i].y - (objectSize + 16));
        int x = objects[i].x + a, y = objects[j].y + (objectSize + 16), ok;
        cornerOverlap(x, y, objects[j].x, objects[i].y - (objectSize + 16));
        verticalOverlap(objects[i].y - (objectSize + 16), y, objects[i].x + a, ok);
        if (ok == 0)
            line(objects[i].x + a, objects[i].y - (objectSize + 16), objects[i].x + a, y);
        horizontalOverlap(x, objects[j].x, objects[j].y + (objectSize + 16), ok);
        if (ok == 0)
            line(x, objects[j].y + (objectSize + 16), objects[j].x, objects[j].y + (objectSize + 16));
        line(objects[j].x, objects[j].y + (objectSize + 16), objects[j].x, objects[j].y + (objectSize + 6));
    }

    cout << "connected BT \n";
}

void connectionTT(int i, int j)
{
    if (objects[i].y > objects[j].y)
        swap(i, j);

    line(objects[i].x, objects[i].y - (objectSize + 6), objects[i].x, objects[i].y - (objectSize + 16));
    int x = objects[j].x, y = objects[i].y - (objectSize + 16);
    cornerOverlap(x, y, objects[i].x, objects[j].y - (objectSize + 6));
    int ok;
    horizontalOverlap(objects[i].x, x, objects[i].y - (objectSize + 16), ok);
    if (ok == 0)
        line(objects[i].x, objects[i].y - (objectSize + 16), x, objects[i].y - (objectSize + 16));
    verticalOverlap(y, objects[j].y - (objectSize + 6), objects[j].x, ok);
    if (ok == 0)
        line(objects[j].x, y, objects[j].x, objects[j].y - (objectSize + 6));

    cout << "connected TT \n";
}

void connectionBB(int i, int j)
{
    if (objects[i].y < objects[j].y)
        swap(i, j);

    line(objects[i].x, objects[i].y + (objectSize + 6), objects[i].x, objects[i].y + (objectSize + 16));
    int x = objects[j].x, y = objects[i].y + (objectSize + 16), ok;
    cornerOverlap(x, y, objects[i].x, objects[j].y + (objectSize + 6));
    horizontalOverlap(x, objects[i].x, objects[i].y + (objectSize + 16), ok);
    if (ok == 0)
        line(objects[i].x, objects[i].y + (objectSize + 16), x, objects[i].y + (objectSize + 16));
    verticalOverlap(y, objects[j].y + (objectSize + 6), objects[j].x, ok);
    if (ok == 0)
        line(objects[j].x, y, objects[j].x, objects[j].y + (objectSize + 6));

    cout << "connected BB \n";
}

void connectionTL(int i, int j)
{
    if (objects[i].leftConnector.index == j)
        swap(i, j);
    if (objects[i].y - (objectSize + 6) > objects[j].y && objects[i].x < objects[j].x - (objectSize + 6))
    {
        int x = objects[i].x, y = objects[j].y, ok;
        cornerOverlap(x, y, objects[j].x - (objectSize + 6), objects[i].y - (objectSize + 6));
        verticalOverlap(objects[i].y - (objectSize + 6), y, objects[i].x, ok);
        if (ok == 0)
            line(objects[i].x, objects[i].y - (objectSize + 6), objects[i].x, y);
        horizontalOverlap(x, objects[j].x - (objectSize + 6), objects[j].y, ok);
        if (ok == 0)
            line(x, objects[j].y, objects[j].x - (objectSize + 6), objects[j].y);
    }
    else
    {
        line(objects[i].x, objects[i].y - (objectSize + 6), objects[i].x, objects[i].y - (objectSize + 16));
        int x = objects[j].x - (objectSize + 16), y = objects[i].y - (objectSize + 16), ok;
        cornerOverlap(x, y, objects[i].x, objects[j].y);
        horizontalOverlap(objects[i].x, x, objects[i].y - (objectSize + 16), ok);
        if (ok == 0)
            line(objects[i].x, objects[i].y - (objectSize + 16), x, objects[i].y - (objectSize + 16));
        verticalOverlap(y, objects[j].y, objects[j].x - (objectSize + 16), ok);
        if (ok == 0)
            line(objects[j].x - (objectSize + 16), y, objects[j].x - (objectSize + 16), objects[j].y);
        line(objects[j].x - (objectSize + 16), objects[j].y, objects[j].x - (objectSize + 6), objects[j].y);
    }

    cout << "connected TL \n";
}

void connectionTR(int i, int j)
{
    if (objects[i].rightConnector.index == j)
        swap(i, j);
    if (objects[i].y - (objectSize + 6) > objects[j].y && objects[i].x > objects[j].x + (objectSize + 6))
    {
        int x = objects[i].x, y = objects[j].y, ok;
        cornerOverlap(x, y, objects[j].x + (objectSize + 6), objects[i].y - (objectSize + 6));
        verticalOverlap(objects[i].y - (objectSize + 6), y, objects[i].x, ok);
        if (ok == 0)
            line(objects[i].x, objects[i].y - (objectSize + 6), objects[i].x, y);
        horizontalOverlap(x, objects[j].x + (objectSize + 6), objects[j].y, ok);
        if (ok == 0)
            line(x, objects[j].y, objects[j].x + (objectSize + 6), objects[j].y);
    }
    else
    {
        line(objects[i].x, objects[i].y - (objectSize + 6), objects[i].x, objects[i].y - (objectSize + 16));
        int x = objects[j].x + (objectSize + 16), y = objects[i].y - (objectSize + 16), ok;
        cornerOverlap(x, y, objects[i].x, objects[j].y);
        horizontalOverlap(objects[i].x, x, objects[i].y - (objectSize + 16), ok);
        if (ok == 0)
            line(objects[i].x, objects[i].y - (objectSize + 16), x, objects[i].y - (objectSize + 16));
        verticalOverlap(y, objects[j].y, objects[j].x + (objectSize + 16), ok);
        if (ok == 0)
            line(objects[j].x + (objectSize + 16), y, objects[j].x + (objectSize + 16), objects[j].y);
        line(objects[j].x + (objectSize + 16), objects[j].y, objects[j].x + (objectSize + 6), objects[j].y);
    }
    cout << "connected TR \n";
}

void connectionBL(int i, int j)
{
    if (objects[i].leftConnector.index == j)
        swap(i, j);
    if (objects[i].y + (objectSize + 6) < objects[j].y && objects[i].x < objects[j].x - (objectSize + 6))
    {
        int x = objects[i].x, y = objects[j].y, ok;
        cornerOverlap(x, y, objects[j].x - (objectSize + 6), objects[i].y + (objectSize + 6));
        verticalOverlap(objects[i].y + (objectSize + 6), y, objects[i].x, ok);
        if (ok == 0)
            line(objects[i].x, objects[i].y + (objectSize + 6), objects[i].x, y);
        horizontalOverlap(x, objects[j].x - (objectSize + 6), objects[j].y, ok);
        if (ok == 0)
            line(x, objects[j].y, objects[j].x - (objectSize + 6), objects[j].y);
    }
    else
    {
        line(objects[i].x, objects[i].y + (objectSize + 6), objects[i].x, objects[i].y + (objectSize + 16));
        int x = objects[j].x - (objectSize + 16), y = objects[i].y + (objectSize + 16), ok;
        cornerOverlap(x, y, objects[i].x, objects[j].y);
        horizontalOverlap(objects[i].x, x, objects[i].y + (objectSize + 16), ok);
        if (ok == 0)
            line(objects[i].x, objects[i].y + (objectSize + 16), x, objects[i].y + (objectSize + 16));
        verticalOverlap(y, objects[j].y, objects[j].x - (objectSize + 16), ok);
        if (ok == 0)
            line(objects[j].x - (objectSize + 16), y, objects[j].x - (objectSize + 16), objects[j].y);
        line(objects[j].x - (objectSize + 16), objects[j].y, objects[j].x - (objectSize + 6), objects[j].y);
    }

    cout << "connected BL \n";
}

void connectionBR(int i, int j)
{
    if (objects[i].rightConnector.index == j)
        swap(i, j);
    if (objects[i].y + (objectSize + 6) < objects[j].y && objects[i].x > objects[j].x + (objectSize + 6))
    {
        int x = objects[i].x, y = objects[j].y, ok;
        cornerOverlap(x, y, objects[j].x + (objectSize + 6), objects[i].y + (objectSize + 6));
        verticalOverlap(objects[i].y + (objectSize + 6), y, objects[i].x, ok);
        if (ok == 0)
            line(objects[i].x, objects[i].y + (objectSize + 6), objects[i].x, y);
        horizontalOverlap(x, objects[j].x + (objectSize + 6), objects[j].y, ok);
        if (ok == 0)
            line(x, objects[j].y, objects[j].x + (objectSize + 6), objects[j].y);
    }
    else
    {
        line(objects[i].x, objects[i].y + (objectSize + 6), objects[i].x, objects[i].y + (objectSize + 16));
        int x = objects[j].x + (objectSize + 16), y = objects[i].y + (objectSize + 16), ok;
        cornerOverlap(x, y, objects[i].x, objects[j].y);
        horizontalOverlap(objects[i].x, x, objects[i].y + (objectSize + 16), ok);
        if (ok == 0)
            line(objects[i].x, objects[i].y + (objectSize + 16), x, objects[i].y + (objectSize + 16));
        verticalOverlap(y, objects[j].y, objects[j].x + (objectSize + 16), ok);
        if (ok == 0)
            line(objects[j].x + (objectSize + 16), y, objects[j].x + (objectSize + 16), objects[j].y);
        line(objects[j].x + (objectSize + 16), objects[j].y, objects[j].x + (objectSize + 6), objects[j].y);
    }
    cout << "connected BR \n";
}

/*<-----------------------End Connection--------------------->*/

/*<-----------------------Overlap--------------------->*/

int imageOverlap(int x, int y, int j)
{

    for (int i = 0; i < objectsCount; i++)
    {
        if (i != j && abs(objects[i].x - x) < 162 && abs(objects[i].y - y) < 150)
            return 0;
    }
    return 1;
}

void horizontalOverlap(int x1, int x2, int y, int &ok)
{
    ok = 0;
    if (x1 > x2)
        swap(x1, x2);
    int mx = 0, xF = systemWidth, xL = 0;
    for (int k = 0; k < objectsCount; k++)
        if (objects[k].x >= x1 && objects[k].x <= x2 && objects[k].y + objectSize >= y && objects[k].y - objectSize <= y)
        {
            ok = 1;
            float dif = objects[k].y - y + 80;
            if (dif > mx)
                mx = dif;
            if (objects[k].x < xF)
                xF = objects[k].x;
            if (objects[k].x > xL)
                xL = objects[k].x;
        }
    if (ok == 1)
    {
        line(x1, y, xF - (objectSize + 16), y);
        line(xF - (objectSize + 16), y, xF - (objectSize + 16), y + mx);
        line(xF - (objectSize + 16), y + mx, xL + (objectSize + 16), y + mx);
        line(xL + (objectSize + 16), y + mx, xL + (objectSize + 16), y);
        line(xL + (objectSize + 16), y, x2, y);
    }
}

void verticalOverlap(int y1, int y2, int x, int &ok)
{
    ok = 0;
    int yF = systemHeight, yL = 0, mx = 0;
    if (y2 < y1)
        swap(y1, y2);
    for (int k = 0; k < objectsCount; k++)
    {
        if (objects[k].x + (objectSize + 6) >= x && objects[k].x - (objectSize + 6) <= x && objects[k].y > y1 && objects[k].y < y2)
        {
            float dif = x - objects[k].x - 86;
            if (dif < mx)
                mx = dif;
            if (yF > objects[k].y)
                yF = objects[k].y;
            if (yL < objects[k].y)
                yL = objects[k].y;
            ok = 1;
        }
    }
    if (ok)
    {
        line(x, y1, x, yF - 80);
        line(x, yF - 80, x - mx, yF - 80);
        line(x - mx, yF - 80, x - mx, yL + 80);
        line(x - mx, yL + 80, x, yL + 80);
        line(x, yL + 80, x, y2);
    }
}

void cornerOverlap(int &x, int &y, int x1, int y1)
{
    for (int k = 0; k <= objectsCount; k++)
    {
        if (abs(objects[k].x - x) <= (objectSize + 6) && abs(objects[k].y - y) <= objectSize)
        {
            if (objects[k].x + (objectSize + 6) > x && objects[k].x < x1)
            {
                if (objects[k].y + objectSize > y && objects[k].y + objectSize < y1)
                {
                    line(objects[k].x + (objectSize + 16), y, objects[k].x + (objectSize + 16), objects[k].y + 80);
                    line(objects[k].x + (objectSize + 16), objects[k].y + 80, x, objects[k].y + 80);
                    x = objects[k].x + (objectSize + 16);
                    y = objects[k].y + 80;
                }
                else if (objects[k].y - objectSize < y && objects[k].y - objectSize > y1)
                {
                    line(objects[k].x + (objectSize + 16), y, objects[k].x + (objectSize + 16), objects[k].y - 80);
                    line(objects[k].x + (objectSize + 16), objects[k].y - 80, x, objects[k].y - 80);
                    x = objects[k].x + (objectSize + 16);
                    y = objects[k].y - 80;
                }
            }
            else
            {

                if (objects[k].y + objectSize > y && objects[k].y + objectSize < y1)
                {
                    line(objects[k].x - (objectSize + 16), y, objects[k].x - (objectSize + 16), objects[k].y + 80);
                    line(objects[k].x - (objectSize + 16), objects[k].y + 80, x, objects[k].y + 80);
                    x = objects[k].x - (objectSize + 16);
                    y = objects[k].y + 80;
                }
                else if (objects[k].y - objectSize < y && objects[k].y - objectSize > y1)
                {
                    line(objects[k].x - (objectSize + 16), y, objects[k].x - (objectSize + 16), objects[k].y - 80);
                    line(objects[k].x - (objectSize + 16), objects[k].y - 80, x, objects[k].y - 80);
                    x = objects[k].x - (objectSize + 16);
                    y = objects[k].y - 80;
                }
            }
        }
    }
}

/*<-----------------------End Overlap--------------------->*/

/*<-----------------------Properties--------------------->*/

void commonSet()
{
    objectsCount++;
    draw();
    objectsCount--;
    propertiesDisplay(objectsCount);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX - 625, systemHeight - 105, "          ");
    handlePropertiesInsert(objectsCount);
    propertiesDisplay(objectsCount);
    objectsCount++;
}

void propertiesDisplay(int i)
{
    settextstyle(8, HORIZ_DIR, 1);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX - 625, systemHeight - 105, objects[i].properties.quantity);
    outtextxy(middleX - 625, systemHeight - 125, objects[i].properties.name);
    outtextxy(middleX - 625, systemHeight - 85, objects[i].properties.measurement);
    setbkcolor(BLACK);
}

/// @brief This function is used for inserting the properties of an object
void handlePropertiesInsert(int j)
{
    setbkcolor(DARKGRAY);
    char key[15] = "";
    int i = 0;
    while (1)
    {
        if (kbhit())
        {
            key[i] = getch();
            // if you press "enter" the loop will break
            if (key[i] == 13)
            {
                key[i] = '\0';
                break;
            }
            setbkcolor(DARKGRAY);
            outtextxy(middleX - 625, systemHeight - 105, key);
            if (key[i] == 8)
            {
                key[i] = '\0';
                key[i - 1] = '\0';
                setbkcolor(LIGHTGRAY);
                outtextxy(middleX - 625, systemHeight - 105, "          ");
                setbkcolor(DARKGRAY);
                outtextxy(middleX - 625, systemHeight - 105, key);
                i--;
                continue;
            }
            i++;
        }
    }
    strcpy(objects[j].properties.quantity, key);
    setbkcolor(LIGHTGRAY);
}

/*<-----------------------End Properties--------------------->*/

/*<-----------------------Buttons--------------------->*/
void load()
{
    // open a FileOpenDialog box and load the file
    OPENFILENAME ofn = {};
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = new TCHAR[MAX_PATH];
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrDefExt = "txt";
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
    ifstream circuitFile;
    // Display the Open dialog box
    if (GetOpenFileName(&ofn) == TRUE)
    {
        string fileName = ofn.lpstrFile;
        circuitFile.open(fileName);
    }
    else
    {
        cout << "Dialog cancelled" << std::endl;
        return;
    }
    if (circuitFile.is_open())
    {
        // Read the objectsCount variable from the file
        circuitFile >> objectsCount;
        cout << objectsCount << endl;
        // Read the information for each object from the file
        for (int i = 0; i < objectsCount; ++i)
        {
            circuitFile >> objects[i].x >>objects[i].y >> objects[i].type;
            circuitFile >> objects[i].leftConnector.index >> objects[i].rightConnector.index >>objects[i].topConnector.index >> objects[i].bottomConnector.index;
            circuitFile >> objects[i].leftConnector.type >> objects[i].rightConnector.type >> objects[i].topConnector.type >> objects[i].bottomConnector.type;
            circuitFile >> objects[i].properties.quantity >> objects[i].properties.measurement;
            circuitFile >> objects[i].properties.name;
            circuitFile >> objects[i].rotateState;

            cout<<objects[i].x<<" "<<objects[i].y<<" "<<objects[i].type<<" "<<objects[i].leftConnector.index<<" "<<objects[i].rightConnector.index<<" "<<objects[i].topConnector.index<<" "<<objects[i].bottomConnector.index<<" "<<objects[i].leftConnector.type<<" "<<objects[i].rightConnector.type<<" "<<objects[i].topConnector.type<<" "<<objects[i].bottomConnector.type<<" "<<objects[i].properties.quantity<<" "<<objects[i].properties.measurement<<" "<<objects[i].properties.name<<" "<<objects[i].rotateState<<'\n';
        }
        // Close the file
        circuitFile.close();
        draw();
        return;
    }
    else
    {
        cout << "Error: Unable to open file" << endl;
        return;
    }
}

void save()
{
    // open a save as dialogue box and save the file
    OPENFILENAME ofn = {};
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = new TCHAR[MAX_PATH];
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrDefExt = "txt";
    ofn.Flags = OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;
    ofstream circuitFile;
    // Display the Save As dialog box
    if (GetSaveFileName(&ofn) == TRUE)
    {
        string fileName = ofn.lpstrFile;
        circuitFile.open(fileName);
    }
    else
    {
        cout << "Dialog cancelled" << std::endl;
        return;
    }

    // if the user presses the OK button, save the file
    circuitFile << "";
    if (circuitFile.is_open())
    {
        // Write the objectsCount variable to the file
        circuitFile << objectsCount << endl;

        // Write the information for each object to the file
        for (int i = 0; i < objectsCount; ++i)
        {
            circuitFile << objects[i].x << " " << objects[i].y << " " << objects[i].type << " ";
            circuitFile << objects[i].leftConnector.index << " " << objects[i].rightConnector.index << " " << objects[i].topConnector.index << " " << objects[i].bottomConnector.index << " ";
            circuitFile << objects[i].leftConnector.type << " " << objects[i].rightConnector.type << " " << objects[i].topConnector.type << " " << objects[i].bottomConnector.type << " ";
            circuitFile << objects[i].properties.quantity << " " << objects[i].properties.measurement << " ";
            circuitFile << objects[i].properties.name << " ";
            circuitFile << objects[i].rotateState << '\n';
        }

        if (circuitFile.good())
        {
            // Close the file
            circuitFile.close();
            cout << "saved" << '\n';
            return;
        }
        else
        {
            // Close the file
            circuitFile.close();
            cout << "Error: Unable to write data to file" << endl;
            return;
        }
    }
    else
    {
        cout << "Error: Unable to open file" << endl;
        return;
    }
}

/// @brief This function is used for the edit button
void edit()
{
    int x, y;
    while (!ismouseclick(WM_LBUTTONDOWN))
    {
        delay(100); // Reduce CPU usage by waiting 100 milliseconds before checking again
    }
    x = mousex();
    y = mousey();
    clearmouseclick(WM_LBUTTONDOWN);
    for (int i = 0; i < objectsCount; ++i)
    {
        if (x >= objects[i].x - objectSize && x <= objects[i].x + objectSize && y >= objects[i].y - objectSize && y <= objects[i].y + objectSize)
        {
            propertiesDisplay(i);
            setbkcolor(LIGHTGRAY);
            outtextxy(middleX - 625, systemHeight - 105, "          ");
            handlePropertiesInsert(i);
            propertiesDisplay(i);
            return;
        }
    }
    // Mouse is not within range of any object
    cout << "No object was edited" << endl;
}

/// @brief This function is used for the clear button
void clear()
{
    for (int i = 0; i < objectsCount; ++i)
    {
        memset(&objects[i], 0, sizeof(objects[i])); // sets objects[i] memory block to 0
    }
    refresh();
}

/// @brief This function is used for the move button
void mov()
{
    bool shouldExit = false;

    while (!shouldExit)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            int x = mousex(), y = mousey();
            for (int i = 0; i < objectsCount && !shouldExit; i++)
            {
                if (x >= objects[i].x - objectSize && x <= objects[i].x + objectSize && y >= objects[i].y - objectSize && y <= objects[i].y + objectSize)
                {
                    while (!shouldExit)
                    {
                        if (ismouseclick(WM_LBUTTONDOWN))
                        {
                            clearmouseclick(WM_LBUTTONDOWN);
                            int newX = mousex(), newY = mousey();
                            if (newX < middleX - 410 || newY < 200 || newX > systemWidth - 85 || newY > systemHeight - 60)
                                break;
                            if (imageOverlap(newX, newY, i) == 0)
                                break;
                            objects[i].x = newX;
                            objects[i].y = newY;
                            draw();
                            propertiesDisplay(i);
                            shouldExit = true;
                        }
                    }
                }
            }
        }
    }
}

/// @brief This function is used for the delete button
void deleteObject()
{
    while (1)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            for (int j = 0; j < objectsCount; j++)
            {
                if (mousex() >= objects[j].x - (objectSize + 6) && mousex() <= objects[j].x - objectSize && mousey() >= objects[j].y - 6 && mousey() <= objects[j].y + 6 && objects[j].rotateState % 2 != 0)
                {
                    objects[j].leftConnector.index = -1;
                    draw();
                }
                else if (mousex() <= objects[j].x + (objectSize + 6) && mousex() >= objects[j].x + objectSize && mousey() >= objects[j].y - 6 && mousey() <= objects[j].y + 6 && objects[j].rotateState % 2 != 0)
                {
                    objects[j].rightConnector.index = -1;
                    draw();
                }
                else if (mousex() <= objects[j].x + 6 && mousex() >= objects[j].x - 6 && mousey() <= objects[j].y - objectSize && mousey() >= objects[j].y - (objectSize + 6) && objects[j].rotateState % 2 == 0)
                {
                    objects[j].topConnector.index = -1;
                    draw();
                }
                else if (mousex() <= objects[j].x + 6 && mousex() >= objects[j].x - 6 && mousey() >= objects[j].y + objectSize && mousey() <= objects[j].y + (objectSize + 6) && objects[j].rotateState % 2 == 0)
                {
                    objects[j].bottomConnector.index = -1;
                    draw();
                }
                else if (mousex() >= objects[j].x - objectSize && mousex() <= objects[j].x + objectSize && mousey() >= objects[j].y - objectSize && mousey() <= objects[j].y + objectSize)
                {
                    if (objects[j].rotateState % 2 != 0)
                    {
                        if (objects[j].leftConnector.index > -1)
                        {
                            if (objects[objects[j].leftConnector.index].bottomConnector.index == j)
                                objects[objects[j].leftConnector.index].bottomConnector.index = -1;

                            if (objects[objects[j].leftConnector.index].topConnector.index == j)
                                objects[objects[j].leftConnector.index].topConnector.index = -1;

                            if (objects[objects[j].leftConnector.index].leftConnector.index == j)
                                objects[objects[j].leftConnector.index].leftConnector.index = -1;

                            if (objects[objects[j].leftConnector.index].rightConnector.index == j)
                                objects[objects[j].leftConnector.index].rightConnector.index = -1;
                        }

                        if (objects[j].rightConnector.index > -1)
                        {
                            if (objects[objects[j].rightConnector.index].bottomConnector.index == j)
                                objects[objects[j].rightConnector.index].bottomConnector.index = -1;

                            if (objects[objects[j].rightConnector.index].topConnector.index == j)
                                objects[objects[j].rightConnector.index].topConnector.index = -1;

                            if (objects[objects[j].rightConnector.index].leftConnector.index == j)
                                objects[objects[j].rightConnector.index].leftConnector.index = -1;

                            if (objects[objects[j].rightConnector.index].rightConnector.index == j)
                                objects[objects[j].rightConnector.index].rightConnector.index = -1;
                        }
                    }

                    else
                    {
                        if (objects[j].topConnector.index > -1)
                        {
                            if (objects[objects[j].topConnector.index].bottomConnector.index == j)
                                objects[objects[j].topConnector.index].bottomConnector.index = -1;

                            if (objects[objects[j].topConnector.index].topConnector.index == j)
                                objects[objects[j].topConnector.index].topConnector.index = -1;

                            if (objects[objects[j].topConnector.index].leftConnector.index == j)
                                objects[objects[j].topConnector.index].leftConnector.index = -1;

                            if (objects[objects[j].topConnector.index].rightConnector.index == j)
                                objects[objects[j].topConnector.index].rightConnector.index = -1;
                        }

                        if (objects[j].bottomConnector.index > -1)
                        {
                            if (objects[objects[j].bottomConnector.index].bottomConnector.index == j)
                                objects[objects[j].bottomConnector.index].bottomConnector.index = -1;

                            if (objects[objects[j].bottomConnector.index].topConnector.index == j)
                                objects[objects[j].bottomConnector.index].topConnector.index = -1;

                            if (objects[objects[j].bottomConnector.index].leftConnector.index == j)
                                objects[objects[j].bottomConnector.index].leftConnector.index = -1;

                            if (objects[objects[j].bottomConnector.index].rightConnector.index == j)
                                objects[objects[j].bottomConnector.index].rightConnector.index = -1;
                        }
                    }

                    for (int i = j; i < objectsCount; i++)
                        objects[i] = objects[i + 1];

                    objectsCount--;
                    for (int i = 0; i < objectsCount; i++)
                    {
                        if (objects[i].bottomConnector.index >= j)
                            objects[i].bottomConnector.index--;
                        if (objects[i].topConnector.index >= j)
                            objects[i].topConnector.index--;
                        if (objects[i].leftConnector.index >= j)
                            objects[i].leftConnector.index--;
                        if (objects[i].rightConnector.index >= j)
                            objects[i].rightConnector.index--;
                    }
                    draw();
                }
            }
            break;
        }
    }
}

void exit()
{
    closegraph();
    return;
}

void rotateObject()
{
    bool found = false;
    int i;
    while (1)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            for (i = 0; i < objectsCount; i++)
            {
                if (mousex() >= objects[i].x - objectSize && mousex() <= objects[i].x + objectSize && mousey() >= objects[i].y - objectSize && mousey() <= objects[i].y + objectSize)
                {
                    found = true;
                    break;
                }
            }
            break;
        }
    }
    if (found)
    {
        char *type;
        type = strtok(objects[i].type, "234.");
        if (strstr(objects[i].type, "battery") != NULL || strstr(objects[i].type, "dioda") != NULL || strstr(objects[i].type, "tranzistor") != NULL || strstr(objects[i].type, "inductor") != NULL)
        {
            if (objects[i].rotateState == 4)
            {
                strcat(type, ".bmp");
                strcpy(objects[i].type, type);
                objects[i].rotateState = 1;
            }
            else
            {
                char ext[6];
                objects[i].rotateState++;
                ext[0] = objects[i].rotateState + '0';
                strcat(ext, ".bmp");
                strcat(type, ext);
                strcpy(objects[i].type, type);
            }
        }
        else
        {

            if (objects[i].rotateState % 2 == 0)
            {
                strcat(type, ".bmp");
                strcpy(objects[i].type, type);
                objects[i].rotateState = 1;
            }
            else
            {
                strcat(type, "2.bmp");
                strcpy(objects[i].type, type);
                objects[i].rotateState = 2;
            }
        }
        if (objects[i].rotateState % 2 != 0)
        {
            swap(objects[i].topConnector.index, objects[i].rightConnector.index);
            swap(objects[i].bottomConnector.index, objects[i].leftConnector.index);

            if (objects[i].topConnector.type[0] == 'T')
            {
                if (objects[i].topConnector.type[1] == 'L')
                {
                    strcpy(objects[i].rightConnector.type, "RL");
                    strcpy(objects[objects[i].rightConnector.index].leftConnector.type, "RL");
                }
                else if (objects[i].topConnector.type[1] == 'R')
                {
                    strcpy(objects[i].rightConnector.type, "RR");
                    strcpy(objects[objects[i].rightConnector.index].rightConnector.type, "RR");
                }
                else if (objects[i].topConnector.type[1] == 'T')
                {
                    strcpy(objects[i].rightConnector.type, "TR");
                    strcpy(objects[objects[i].rightConnector.index].topConnector.type, "TR");
                }
            }
            else if (objects[i].topConnector.type[0] == 'B' && objects[i].topConnector.type[1] == 'T')
            {
                strcpy(objects[i].rightConnector.type, "BR");
                strcpy(objects[objects[i].rightConnector.index].bottomConnector.type, "BR");
            }

            if (objects[i].bottomConnector.type[0] == 'B')
            {
                if (objects[i].bottomConnector.type[1] == 'L')
                {
                    strcpy(objects[i].leftConnector.type, "LL");
                    strcpy(objects[objects[i].leftConnector.index].leftConnector.type, "LL");
                }
                else if (objects[i].bottomConnector.type[1] == 'R')
                {
                    strcpy(objects[i].leftConnector.type, "RL");
                    strcpy(objects[objects[i].leftConnector.index].rightConnector.type, "RL");
                }
                else if (objects[i].bottomConnector.type[1] == 'T')
                {
                    strcpy(objects[i].leftConnector.type, "TL");
                    strcpy(objects[objects[i].leftConnector.index].topConnector.type, "TL");
                }
                else if (objects[i].bottomConnector.type[1] == 'B')
                {
                    strcpy(objects[i].leftConnector.type, "BL");
                    strcpy(objects[objects[i].leftConnector.index].bottomConnector.type, "BL");
                }
            }

            objects[i].topConnector.index = -1;
            objects[i].bottomConnector.index = -1;
            strcpy(objects[i].topConnector.type, "AA");
            strcpy(objects[i].bottomConnector.type, "AA");
            cout << objects[i].rightConnector.type << endl;
            cout << objects[i].leftConnector.type << endl;
        }

        if (objects[i].rotateState % 2 == 0)
        {
            swap(objects[i].leftConnector.index, objects[i].topConnector.index);
            swap(objects[i].rightConnector.index, objects[i].bottomConnector.index);

            if (objects[i].leftConnector.type[1] == 'L')
            {
                if (objects[i].leftConnector.type[0] == 'T')
                {
                    strcpy(objects[i].topConnector.type, "TT");
                    strcpy(objects[objects[i].topConnector.index].topConnector.type, "TT");
                }
                else if (objects[i].leftConnector.type[0] == 'R')
                {
                    strcpy(objects[i].topConnector.type, "TR");
                    strcpy(objects[objects[i].topConnector.index].rightConnector.type, "TR");
                }
                else if (objects[i].leftConnector.type[0] == 'L')
                {
                    strcpy(objects[i].topConnector.type, "TL");
                    strcpy(objects[objects[i].topConnector.index].leftConnector.type, "TL");
                }
                else if (objects[i].leftConnector.type[0] == 'B')
                {
                    strcpy(objects[i].topConnector.type, "BT");
                    strcpy(objects[objects[i].topConnector.index].bottomConnector.type, "BT");
                }
            }

            if (objects[i].rightConnector.type[1] == 'R')
            {

                if (objects[i].rightConnector.type[0] == 'R')
                {
                    strcpy(objects[i].bottomConnector.type, "BR");
                    strcpy(objects[objects[i].bottomConnector.index].rightConnector.type, "BR");
                }
                else if (objects[i].rightConnector.type[0] == 'T')
                {
                    strcpy(objects[i].bottomConnector.type, "BT");
                    strcpy(objects[objects[i].bottomConnector.index].topConnector.type, "BT");
                }
                else if (objects[i].rightConnector.type[0] == 'B')
                {
                    strcpy(objects[i].bottomConnector.type, "BB");
                    strcpy(objects[objects[i].bottomConnector.index].bottomConnector.type, "BB");
                }
            }
            else if (objects[i].rightConnector.type[0] == 'R' && objects[i].rightConnector.type[1] == 'L')
            {
                strcpy(objects[i].bottomConnector.type, "BL");
                strcpy(objects[objects[i].bottomConnector.index].leftConnector.type, "BL");
            }

            objects[i].leftConnector.index = -1;
            objects[i].rightConnector.index = -1;
            strcpy(objects[i].rightConnector.type, "AA");
            strcpy(objects[i].leftConnector.type, "AA");
            cout << objects[i].topConnector.type << endl;
            cout << objects[i].bottomConnector.type << endl;
            cout << objects[i].leftConnector.type << endl;
            cout << objects[i].rightConnector.type << endl;
        }
        draw();
    }
}

void zoomIn()
{
    if (objectSize < 85)
    {
        objectSize += 5;
        draw();
        cout << objectSize << '\n';
    }
}

void zoomOut()
{
    if (objectSize > 65)
    {
        objectSize -= 5;
        draw();
        cout << objectSize << '\n';
    }
}

/*<-----------------------End Buttons--------------------->*/

/*<--------------------------End functions------------------------>*/
