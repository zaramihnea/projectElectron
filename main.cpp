
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
        clear[20];
};
lang ro = {"Limba", "INCEPE", "Salveaza", "Incarca", "Mareste", "Micsoreaza", "Sterge", "Proprietati", "Iesire", "Goleste"},
     en = {"Language", "START", "Save", "Load", "Zoom in", "Zoom out", "Delete", "Properties", "Exit", "Clear"},
     ge = {"Sprache", "ANFANG", "Speichern", "Belastung", "Vergr��ern", "Verkleinern", "L�schen", "Eigenschaften", "Ausgang", "Klar"},
     fr = {"Langue", "DEBUT", "Sauvegarder", "Charger", "Agrandir", "R�duire", "Supprimer", "Propri�t�s", "Sortie", "Clair"};

struct prop
{
    char quantity[15];
    char measurement[21],
        name[21];
} properties;

struct object
{
    int x, y;
    char type[31];
    int leftConnector = -1, rightConnector = -1;
    prop properties;
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

/*<------------End global variables------------>*/

/*<------------Begin function definitions------------>*/

void startingPage();
void languageMenu();
void refresh();
void images();
void draw();
void connectionAnalyst(int i, int j);
void connectionLL(int i, int j);
void connectionRR(int i, int j);
void connectionRL(int i, int j, char connectorI);
void propertiesDisplay(int i);
void deleteObject(int i);
void exit();
void load();
void save();
int overlap(int x, int y);
void clear();

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

    setbkcolor(BLACK);
    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR, 6);
    outtextxy(middleX - 130, 200, "Electron");
    setcolor(WHITE);
    rectangle(middleX - 380, 400, middleX - 100, 480);
    outtextxy(middleX - 370, 415, L.language);
    setcolor(WHITE);
    rectangle(middleX + 100, 400, middleX + 380, 480);
    outtextxy(middleX + 150, 415, L.start);
    bool click = false;
    while (1)
    {
        if (ismouseclick(WM_LBUTTONDOWN) && !click)
        {

            clearmouseclick(WM_LBUTTONDOWN);
            int xMouse = mousex();
            int yMouse = mousey();
            if (xMouse >= middleX - 380 && xMouse <= middleX - 100 && yMouse >= 400 && xMouse <= 480)
            {
                languageMenu();
                click = true;
            }
            if (click == false)
                if (xMouse >= middleX + 100 && xMouse <= middleX + 380 && yMouse >= 400 && yMouse <= 480)
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
    bar(middleX - 630, systemHeight - 515, middleX - 510, systemHeight - 475);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX - 600, systemHeight - 507, L.clear);

    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(middleX - 630, systemHeight - 465, middleX - 510, systemHeight - 425);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX - 598, systemHeight - 457, L.load);

    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(middleX - 630, systemHeight - 415, middleX - 510, systemHeight - 375);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX - 598, systemHeight - 407, L.save);

    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(middleX - 630, systemHeight - 365, middleX - 510, systemHeight - 325);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX - 608, systemHeight - 357, L.zoomIn);

    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(middleX - 630, systemHeight - 315, middleX - 510, systemHeight - 275);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX - 611, systemHeight - 307, L.zoomOut);

    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(middleX - 630, systemHeight - 265, middleX - 510, systemHeight - 225);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX - 600, systemHeight - 257, L.dele);

    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(middleX - 630, systemHeight - 215, middleX - 510, systemHeight - 175);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX - 590, systemHeight - 207, L.exit);

    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(middleX - 630, systemHeight - 165, middleX - 510, systemHeight - 50);
    setcolor(WHITE);
    rectangle(middleX - 631, systemHeight - 166, middleX - 510, systemHeight - 50);
    line(middleX - 631, systemHeight - 145, middleX - 510, systemHeight - 145);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX - 625, systemHeight - 165, L.props);
    setbkcolor(BLACK);
}

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
                    if (ismouseclick(WM_LBUTTONDOWN))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        if (mousex() < middleX - 410 || mousey() < 200 || mousex() > systemWidth - 85 || mousey() > systemHeight - 60)
                            continue;
                        if (!overlap(mousex(), mousey()))
                            continue;
                        readimagefile("condensator.bmp", mousex() - 75, mousey() - 75, mousex() + 75, mousey() + 75);
                        circle(mousex() - 78, mousey(), 6);
                        circle(mousex() + 78, mousey(), 6);
                        objects[objectsCount].x = mousex();
                        objects[objectsCount].y = mousey();
                        strcpy(objects[objectsCount].type, "condensator.bmp");
                        strcpy(objects[objectsCount].properties.measurement, "Farad     ");
                        strcpy(objects[objectsCount].properties.name, "condenser ");
                        propertiesDisplay(objectsCount);
                        setbkcolor(LIGHTGRAY);
                        outtextxy(middleX - 625, systemHeight - 120, "          ");
                        char key[15] = "";
                        int i = 0;
                        while (1)
                        {
                            if (kbhit())
                            {
                                key[i] = getch();
                                setbkcolor(DARKGRAY);
                                outtextxy(middleX - 625, systemHeight - 120, key);
                                // if you press "enter" the loop will break
                                if (key[i] == 13)
                                {
                                    key[i] = '\0';
                                    break;
                                }

                                i++;
                            }
                        }
                        strcpy(objects[objectsCount].properties.quantity, key);
                        propertiesDisplay(objectsCount);
                        objectsCount++;
                        break;
                    }
                }
            }
            if (x >= middleX - 470 && x <= middleX - 370 && y >= 10 && y <= 110)
            {
                while (1)
                {
                    if (ismouseclick(WM_LBUTTONDOWN))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        if (mousex() < middleX - 410 || mousey() < 200 || mousex() > systemWidth - 85 || mousey() > systemHeight - 60)
                            continue;
                        if (!overlap(mousex(), mousey()))
                            continue;
                        readimagefile("dioda.bmp", mousex() - 75, mousey() - 75, mousex() + 75, mousey() + 75);
                        circle(mousex() - 78, mousey(), 6);
                        circle(mousex() + 78, mousey(), 6);
                        objects[objectsCount].x = mousex();
                        objects[objectsCount].y = mousey();
                        strcpy(objects[objectsCount].type, "dioda.bmp");
                        strcpy(objects[objectsCount].properties.measurement, "Ohm       ");
                        strcpy(objects[objectsCount].properties.name, "diode     ");
                        propertiesDisplay(objectsCount);
                        setbkcolor(LIGHTGRAY);
                        outtextxy(middleX - 625, systemHeight - 120, "          ");
                        char key[15] = "";
                        int i = 0;
                        while (1)
                        {
                            if (kbhit())
                            {
                                key[i] = getch();
                                setbkcolor(DARKGRAY);
                                outtextxy(middleX - 625, systemHeight - 120, key);
                                // if you press "enter" the loop will break
                                if (key[i] == 13)
                                {
                                    key[i] = '\0';
                                    break;
                                }

                                i++;
                            }
                        }
                        strcpy(objects[objectsCount].properties.quantity, key);
                        propertiesDisplay(objectsCount);
                        objectsCount++;
                        break;
                    }
                }
            }
            if (x >= middleX - 350 && x <= middleX - 250 && y >= 10 && y <= 110)
            {
                while (1)
                {
                    if (ismouseclick(WM_LBUTTONDOWN))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        if (mousex() < middleX - 410 || mousey() < 200 || mousex() > systemWidth - 85 || mousey() > systemHeight - 60)
                            continue;
                        if (!overlap(mousex(), mousey()))
                            continue;
                        readimagefile("tranzistor.bmp", mousex() - 75, mousey() - 75, mousex() + 75, mousey() + 75);
                        circle(mousex() - 78, mousey(), 6);
                        circle(mousex() + 78, mousey(), 6);
                        objects[objectsCount].x = mousex();
                        objects[objectsCount].y = mousey();
                        strcpy(objects[objectsCount].type, "tranzistor.bmp");
                        strcpy(objects[objectsCount].properties.name, "transistor");
                        strcpy(objects[objectsCount].properties.measurement, "Ohm/A/V   ");
                        propertiesDisplay(objectsCount);
                        setbkcolor(LIGHTGRAY);
                        outtextxy(middleX - 625, systemHeight - 120, "          ");
                        char key[15] = "";
                        int i = 0;
                        while (1)
                        {
                            if (kbhit())
                            {
                                key[i] = getch();
                                setbkcolor(DARKGRAY);
                                outtextxy(middleX - 625, systemHeight - 120, key);
                                // if you press "enter" the loop will break
                                if (key[i] == 13)
                                {
                                    key[i] = '\0';
                                    break;
                                }

                                i++;
                            }
                        }
                        strcpy(objects[objectsCount].properties.quantity, key);
                        propertiesDisplay(objectsCount);
                        objectsCount++;
                        break;
                    }
                }
            }
            if (x >= middleX - 230 && x <= middleX - 130 && y >= 10 && y <= 110)
            {
                while (1)
                {
                    if (ismouseclick(WM_LBUTTONDOWN))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        if (mousex() < middleX - 410 || mousey() < 200 || mousex() > systemWidth - 85 || mousey() > systemHeight - 60)
                            continue;
                        if (!overlap(mousex(), mousey()))
                            continue;
                        readimagefile("inductor.bmp", mousex() - 75, mousey() - 75, mousex() + 75, mousey() + 75);
                        circle(mousex() - 78, mousey(), 6);
                        circle(mousex() + 78, mousey(), 6);
                        objects[objectsCount].x = mousex();
                        objects[objectsCount].y = mousey();
                        strcpy(objects[objectsCount].type, "inductor.bmp");
                        strcpy(objects[objectsCount].properties.measurement, "Henrys    ");
                        strcpy(objects[objectsCount].properties.name, "inductor  ");
                        propertiesDisplay(objectsCount);
                        setbkcolor(LIGHTGRAY);
                        outtextxy(middleX - 625, systemHeight - 120, "          ");
                        char key[15] = "";
                        int i = 0;
                        while (1)
                        {
                            if (kbhit())
                            {
                                key[i] = getch();
                                setbkcolor(DARKGRAY);
                                outtextxy(middleX - 625, systemHeight - 120, key);
                                // if you press "enter" the loop will break
                                if (key[i] == 13)
                                {
                                    key[i] = '\0';
                                    break;
                                }

                                i++;
                            }
                        }
                        strcpy(objects[objectsCount].properties.quantity, key);
                        propertiesDisplay(objectsCount);
                        objectsCount++;
                        break;
                    }
                }
            }
            if (x >= middleX - 110 && x <= middleX - 10 && y >= 10 && y <= 110)
            {
                while (1)
                {
                    if (ismouseclick(WM_LBUTTONDOWN))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        if (mousex() < middleX - 410 || mousey() < 200 || mousex() > systemWidth - 85 || mousey() > systemHeight - 60)
                            continue;
                        if (!overlap(mousex(), mousey()))
                            continue;
                        readimagefile("rezistor.bmp", mousex() - 75, mousey() - 75, mousex() + 75, mousey() + 75);
                        circle(mousex() - 78, mousey(), 6);
                        circle(mousex() + 78, mousey(), 6);
                        objects[objectsCount].x = mousex();
                        objects[objectsCount].y = mousey();
                        strcpy(objects[objectsCount].type, "rezistor.bmp");
                        strcpy(objects[objectsCount].properties.measurement, "Ohm       ");
                        strcpy(objects[objectsCount].properties.name, "resistor  ");
                        propertiesDisplay(objectsCount);
                        setbkcolor(LIGHTGRAY);
                        outtextxy(middleX - 625, systemHeight - 120, "          ");
                        char key[15] = "";
                        int i = 0;
                        while (1)
                        {
                            if (kbhit())
                            {
                                key[i] = getch();
                                setbkcolor(DARKGRAY);
                                outtextxy(middleX - 625, systemHeight - 120, key);
                                // if you press "enter" the loop will break
                                if (key[i] == 13)
                                {
                                    key[i] = '\0';
                                    break;
                                }

                                i++;
                            }
                        }
                        strcpy(objects[objectsCount].properties.quantity, key);
                        propertiesDisplay(objectsCount);
                        objectsCount++;
                        break;
                    }
                }
            }
            if (x >= middleX + 10 && x <= middleX + 110 && y >= 10 && y <= 110)
            {
                while (1)
                {
                    if (ismouseclick(WM_LBUTTONDOWN))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        if (mousex() < middleX - 410 || mousey() < 200 || mousex() > systemWidth - 85 || mousey() > systemHeight - 60)
                            continue;
                        if (!overlap(mousex(), mousey()))
                            continue;
                        readimagefile("voltmeter.bmp", mousex() - 75, mousey() - 75, mousex() + 75, mousey() + 75);
                        circle(mousex() - 78, mousey(), 6);
                        circle(mousex() + 78, mousey(), 6);
                        objects[objectsCount].x = mousex();
                        objects[objectsCount].y = mousey();
                        strcpy(objects[objectsCount].type, "voltmeter.bmp");
                        strcpy(objects[objectsCount].properties.measurement, "Volt      ");
                        strcpy(objects[objectsCount].properties.name, "voltmeter ");
                        propertiesDisplay(objectsCount);
                        setbkcolor(LIGHTGRAY);
                        outtextxy(middleX - 625, systemHeight - 120, "          ");
                        char key[15] = "";
                        int i = 0;
                        while (1)
                        {
                            if (kbhit())
                            {
                                key[i] = getch();
                                setbkcolor(DARKGRAY);
                                outtextxy(middleX - 625, systemHeight - 120, key);
                                // if you press "enter" the loop will break
                                if (key[i] == 13)
                                {
                                    key[i] = '\0';
                                    break;
                                }

                                i++;
                            }
                        }
                        strcpy(objects[objectsCount].properties.quantity, key);
                        propertiesDisplay(objectsCount);
                        objectsCount++;
                        break;
                    }
                }
            }
            if (x >= middleX + 130 && x <= middleX + 230 && y >= 10 && y <= 110)
            {
                while (1)
                {
                    if (ismouseclick(WM_LBUTTONDOWN))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        if (mousex() < middleX - 410 || mousey() < 200 || mousex() > systemWidth - 85 || mousey() > systemHeight - 60)
                            continue;
                        if (!overlap(mousex(), mousey()))
                            continue;
                        readimagefile("ammeter.bmp", mousex() - 75, mousey() - 75, mousex() + 75, mousey() + 75);
                        circle(mousex() - 78, mousey(), 6);
                        circle(mousex() + 78, mousey(), 6);
                        objects[objectsCount].x = mousex();
                        objects[objectsCount].y = mousey();
                        strcpy(objects[objectsCount].type, "ammeter.bmp");
                        strcpy(objects[objectsCount].properties.measurement, "Amperes   ");
                        strcpy(objects[objectsCount].properties.name, "ammeter   ");
                        propertiesDisplay(objectsCount);
                        setbkcolor(LIGHTGRAY);
                        outtextxy(middleX - 625, systemHeight - 120, "          ");
                        char key[15] = "";
                        int i = 0;
                        while (1)
                        {
                            if (kbhit())
                            {
                                key[i] = getch();
                                setbkcolor(DARKGRAY);
                                outtextxy(middleX - 625, systemHeight - 120, key);
                                // if you press "enter" the loop will break
                                if (key[i] == 13)
                                {
                                    key[i] = '\0';
                                    break;
                                }

                                i++;
                            }
                        }
                        strcpy(objects[objectsCount].properties.quantity, key);
                        propertiesDisplay(objectsCount);
                        objectsCount++;
                        break;
                    }
                }
            }
            if (x >= middleX + 250 && x <= middleX + 350 && y >= 10 && y <= 110)
            {
                while (1)
                {
                    if (ismouseclick(WM_LBUTTONDOWN))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        if (mousex() < middleX - 410 || mousey() < 200 || mousex() > systemWidth - 85 || mousey() > systemHeight - 60)
                            continue;
                        if (!overlap(mousex(), mousey()))
                            continue;
                        readimagefile("bulb.bmp", mousex() - 75, mousey() - 75, mousex() + 75, mousey() + 75);
                        circle(mousex() - 78, mousey(), 6);
                        circle(mousex() + 78, mousey(), 6);
                        objects[objectsCount].x = mousex();
                        objects[objectsCount].y = mousey();
                        strcpy(objects[objectsCount].type, "bulb.bmp");
                        strcpy(objects[objectsCount].properties.measurement, "Watts     ");
                        strcpy(objects[objectsCount].properties.name, "bulb      ");
                        propertiesDisplay(objectsCount);
                        setbkcolor(LIGHTGRAY);
                        outtextxy(middleX - 625, systemHeight - 120, "          ");
                        char key[15] = "";
                        int i = 0;
                        while (1)
                        {
                            if (kbhit())
                            {
                                key[i] = getch();
                                setbkcolor(DARKGRAY);
                                outtextxy(middleX - 625, systemHeight - 120, key);
                                // if you press "enter" the loop will break
                                if (key[i] == 13)
                                {
                                    key[i] = '\0';
                                    break;
                                }

                                i++;
                            }
                        }
                        strcpy(objects[objectsCount].properties.quantity, key);
                        propertiesDisplay(objectsCount);
                        objectsCount++;
                        break;
                    }
                }
            }
            if (x >= middleX + 370 && x <= middleX + 470 && y >= 10 && y <= 110)
            {
                while (1)
                {
                    if (ismouseclick(WM_LBUTTONDOWN))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        if (mousex() < middleX - 410 || mousey() < 200 || mousex() > systemWidth - 85 || mousey() > systemHeight - 60)
                            continue;
                        if (!overlap(mousex(), mousey()))
                            continue;
                        readimagefile("fuse.bmp", mousex() - 75, mousey() - 75, mousex() + 75, mousey() + 75);
                        circle(mousex() - 78, mousey(), 6);
                        circle(mousex() + 78, mousey(), 6);
                        objects[objectsCount].x = mousex();
                        objects[objectsCount].y = mousey();
                        strcpy(objects[objectsCount].type, "fuse.bmp");
                        strcpy(objects[objectsCount].properties.measurement, "Amperes   ");
                        strcpy(objects[objectsCount].properties.name, "fuse      ");
                        propertiesDisplay(objectsCount);
                        setbkcolor(LIGHTGRAY);
                        outtextxy(middleX - 625, systemHeight - 120, "          ");
                        char key[15] = "";
                        int i = 0;
                        while (1)
                        {
                            if (kbhit())
                            {
                                key[i] = getch();
                                setbkcolor(DARKGRAY);
                                outtextxy(middleX - 625, systemHeight - 120, key);
                                // if you press "enter" the loop will break
                                if (key[i] == 13)
                                {
                                    key[i] = '\0';
                                    break;
                                }

                                i++;
                            }
                        }
                        strcpy(objects[objectsCount].properties.quantity, key);
                        propertiesDisplay(objectsCount);
                        objectsCount++;
                        break;
                    }
                }
            }
            if (x >= middleX + 490 && x <= middleX + 590 && y >= 10 && y <= 110)
            {
                while (1)
                {
                    if (ismouseclick(WM_LBUTTONDOWN))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        if (mousex() < middleX - 410 || mousey() < 200 || mousex() > systemWidth - 85 || mousey() > systemHeight - 60)
                            continue;
                        if (!overlap(mousex(), mousey()))
                            continue;
                        readimagefile("battery.bmp", mousex() - 75, mousey() - 75, mousex() + 75, mousey() + 75);
                        circle(mousex() - 78, mousey(), 6);
                        circle(mousex() + 78, mousey(), 6);
                        objects[objectsCount].x = mousex();
                        objects[objectsCount].y = mousey();
                        strcpy(objects[objectsCount].type, "battery.bmp");
                        strcpy(objects[objectsCount].properties.measurement, "mAmps*H   ");
                        strcpy(objects[objectsCount].properties.name, "battery   ");
                        propertiesDisplay(objectsCount);
                        setbkcolor(LIGHTGRAY);
                        outtextxy(middleX - 625, systemHeight - 120, "          ");
                        char key[15] = "";
                        int i = 0;
                        while (1)
                        {
                            if (kbhit())
                            {
                                key[i] = getch();
                                setbkcolor(DARKGRAY);
                                outtextxy(middleX - 625, systemHeight - 120, key);
                                // if you press "enter" the loop will break
                                if (key[i] == 13)
                                {
                                    key[i] = '\0';
                                    break;
                                }

                                i++;
                            }
                        }
                        strcpy(objects[objectsCount].properties.quantity, key);
                        propertiesDisplay(objectsCount);
                        objectsCount++;
                        break;
                    }
                }
            }

            // if you click on an object change it's position

            for (int i = 0; i < objectsCount; i++)
            {
                if (x >= objects[i].x - 75 && x <= objects[i].x + 75 && y >= objects[i].y - 75 && y <= objects[i].y + 75)
                    while (1)
                    {
                        propertiesDisplay(i);
                        if (ismouseclick(WM_LBUTTONDOWN))
                        {
                            clearmouseclick(WM_LBUTTONDOWN);

                            if (mousex() < middleX - 410 || mousey() < 200 || mousex() > systemWidth - 85 || mousey() > systemHeight - 60)
                                break;

                            if (overlap(mousex(), mousey()) == 1)
                            {
                                objects[i].x = mousex();
                                objects[i].y = mousey();
                                draw();
                            }

                            propertiesDisplay(i);
                            break;
                        }
                    }
                if (x >= objects[i].x - 81 && x <= objects[i].x - 75 && y >= objects[i].y - 6 && y <= objects[i].y + 6)
                    while (1)
                    {
                        if (ismouseclick(WM_LBUTTONDOWN))
                        {
                            clearmouseclick(WM_LBUTTONDOWN);
                            for (int j = 0; j < objectsCount; j++)
                            {
                                if (mousex() >= objects[j].x - 81 && mousex() <= objects[j].x - 75 && mousey() >= objects[j].y - 6 && mousey() <= objects[j].y + 6)
                                {
                                    objects[i].leftConnector = j;
                                    objects[j].leftConnector = i;
                                    connectionAnalyst(i, j);
                                }
                                else if (mousex() <= objects[j].x + 81 && mousex() >= objects[j].x + 75 && mousey() >= objects[j].y - 6 && mousey() <= objects[j].y + 6)
                                {
                                    objects[i].leftConnector = j;
                                    objects[j].rightConnector = i;
                                    connectionAnalyst(i, j);
                                }
                            }
                            break;
                        }
                    }
                if (x <= objects[i].x + 81 && x >= objects[i].x + 75 && y >= objects[i].y - 6 && y <= objects[i].y + 6)
                    while (1)
                    {
                        if (ismouseclick(WM_LBUTTONDOWN))
                        {
                            clearmouseclick(WM_LBUTTONDOWN);
                            for (int j = 0; j < objectsCount; j++)
                            {
                                if (mousex() >= objects[j].x - 81 && mousex() <= objects[j].x - 75 && mousey() >= objects[j].y - 6 && mousey() <= objects[j].y + 6)
                                {

                                    objects[i].rightConnector = j;
                                    objects[j].leftConnector = i;
                                    connectionAnalyst(i, j);
                                }
                                else if (mousex() <= objects[j].x + 81 && mousex() >= objects[j].x + 75 && mousey() >= objects[j].y - 6 && mousey() <= objects[j].y + 6)
                                {
                                    objects[i].rightConnector = j;
                                    objects[j].rightConnector = i;
                                    connectionAnalyst(i, j);
                                }
                            }
                            break;
                        }
                    }
            }
            if(x>=middleX-630 && x<=middleX-510 && y>=systemHeight-515 && y<=systemHeight-475)
            {
                cout<<"pushed clear()"<<'\n';
                clear();
            }
            if (x >= middleX - 630 && x <= middleX - 510 && y >= systemHeight - 465 && y <= systemHeight - 425)
            {
                cout << "pushed load()"<<'\n';
                load();
            }
            if (x >= middleX - 630 && x <= middleX - 510 && y >= systemHeight - 415 && y <= systemHeight - 375)
            {
                cout << "pushed save()"<<'\n';
                save();
            }
            if (x >= middleX - 630 && x <= middleX - 510 && y >= systemHeight - 365 && y <= systemHeight - 325)
            {
                cout << "pushed zoomin()"<<'\n';
            }
            if (x >= middleX - 630 && x <= middleX - 510 && y >= systemHeight - 315 && y <= systemHeight - 275)
            {
                cout << "pushed zoomout()"<<'\n';
            }
            if (x >= middleX - 630 && x <= middleX - 510 && y >= systemHeight - 265 && y <= systemHeight - 225)
            {
                cout << "pushed delete()"<<'\n';
                while (1)
                {
                    if (ismouseclick(WM_LBUTTONDOWN))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        for (int j = 0; j < objectsCount; j++)
                        {
                            if (mousex() >= objects[j].x - 81 && mousex() <= objects[j].x - 75 && mousey() >= objects[j].y - 6 && mousey() <= objects[j].y + 6)
                            {
                                objects[j].leftConnector = -1;
                                draw();
                            }
                            else if (mousex() <= objects[j].x + 81 && mousex() >= objects[j].x + 75 && mousey() >= objects[j].y - 6 && mousey() <= objects[j].y + 6)
                            {
                                objects[j].rightConnector = -1;
                                draw();
                            }
                            else if (mousex() >= objects[j].x - 75 && mousex() <= objects[j].x + 75 && mousey() >= objects[j].y - 75 && mousey() <= objects[j].y + 75)
                            {
                                for (int i = j; i < objectsCount; i++)
                                {
                                    objects[i] = objects[i + 1];
                                }
                                objectsCount--;
                                draw();
                            }
                        }
                        break;
                    }
                }
            }

            if (x >= middleX - 630 && x <= middleX - 510 && y >= systemHeight - 215 && y <= systemHeight - 175)
            {
                cout << "pushed exit()"<<'\n';
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
        readimagefile(objects[j].type, objects[j].x - 75, objects[j].y - 75, objects[j].x + 75, objects[j].y + 75);
        circle(objects[j].x + 78, objects[j].y, 6);
        circle(objects[j].x - 78, objects[j].y, 6);
        if (objects[j].rightConnector > -1)
        {
            connectionAnalyst(j, objects[j].rightConnector);
        }
        if (objects[j].leftConnector > -1)
        {
            connectionAnalyst(j, objects[j].leftConnector);
        }
    }
}

void clear(){
    for(int i=0; i<objectsCount; ++i){
        memset(&objects[i], 0, sizeof(objects[i]));
    }
    refresh();
}

void connectionAnalyst(int i, int j)
{

    if (objects[i].leftConnector == j)
    {
        if (objects[j].leftConnector == i)
            connectionLL(i, j);

        else if (objects[j].rightConnector == i)
        {
            if (objects[j].x + 81 < objects[i].x - 81)
                connectionRL(i, j, 'l');
            else
            {
                objects[j].leftConnector = i;
                objects[j].rightConnector = -1;
                connectionLL(i, j);
            }
        }
    }
    else if (objects[i].rightConnector == j)
    {
        if (objects[j].leftConnector == i)
        {
            if (objects[i].x + 81 < objects[j].x - 81)
                connectionRL(i, j, 'r');
            else
            {
                objects[j].rightConnector = i;
                objects[j].leftConnector = -1;
                connectionRR(i, j);
            }
        }

        else if (objects[j].rightConnector == i)
            connectionRR(i, j);
    }
}

void connectionRR(int i, int j)
{

    if (objects[i].x > objects[j].x)
        swap(i, j);

    line(objects[j].x + 81, objects[j].y, objects[j].x + 100, objects[j].y);
    int ok = 0;

    for (int k = 0; k < objectsCount; k++)
    {
        if (objects[k].x + 81 > objects[j].x + 100 && objects[k].x - 81 < objects[j].x + 100)
        {
            int y1 = objects[j].y, y2 = objects[i].y;
            if (y1 > y2)
                swap(y1, y2);
            if (objects[k].y > y1 && objects[k].y < y2)
            {
                float dif = objects[k].x + 81 - objects[j].x - 100;
                line(objects[j].x + 100, objects[j].y, objects[j].x + 100, objects[k].y - 80);
                line(objects[j].x + 100, objects[k].y - 80, objects[j].x + 110 + dif, objects[k].y - 80);
                line(objects[j].x + 110 + dif, objects[k].y - 80, objects[j].x + 110 + dif, objects[k].y + 80);
                line(objects[j].x + 110 + dif, objects[k].y + 80, objects[j].x + 100, objects[k].y + 80);
                line(objects[j].x + 100, objects[k].y + 80, objects[j].x + 100, objects[i].y);
                ok = 1;
            }
        }
    }
    if (ok == 0)
        line(objects[j].x + 100, objects[j].y, objects[j].x + 100, objects[i].y);
    line(objects[i].x + 81, objects[i].y, objects[j].x + 100, objects[i].y);
}

void connectionLL(int i, int j)
{

    if (objects[j].x > objects[i].x)
        swap(i, j);

    line(objects[j].x - 81, objects[j].y, objects[j].x - 100, objects[j].y);
    int ok = 0;

    for (int k = 0; k < objectsCount; k++)
    {
        if (objects[k].x + 81 > objects[j].x - 100 && objects[k].x - 81 < objects[j].x - 100)
        {
            int y1 = objects[j].y, y2 = objects[i].y;
            if (y1 > y2)
                swap(y1, y2);
            if (objects[k].y > y1 && objects[k].y < y2)
            {
                float dif = abs(objects[k].x - 81 - objects[j].x + 100);
                line(objects[j].x - 100, objects[j].y, objects[j].x - 100, objects[k].y - 80);
                line(objects[j].x - 100, objects[k].y - 80, objects[j].x - 110 - dif, objects[k].y - 80);
                line(objects[j].x - 110 - dif, objects[k].y - 80, objects[j].x - 110 - dif, objects[k].y + 80);
                line(objects[j].x - 110 - dif, objects[k].y + 80, objects[j].x - 100, objects[k].y + 80);
                line(objects[j].x - 100, objects[k].y + 80, objects[j].x - 100, objects[i].y);
                ok = 1;
            }
        }
    }
    if (ok == 0)
        line(objects[j].x - 100, objects[j].y, objects[j].x - 100, objects[i].y);
    line(objects[j].x - 100, objects[i].y, objects[i].x - 81, objects[i].y);
}

void connectionRL(int i, int j, char connectorI)
{
    if (connectorI == 'l')
        swap(i, j);

    float difference = (objects[j].x - objects[i].x - 162) / 2;

    line(objects[i].x + 81, objects[i].y, objects[i].x + 81 + difference, objects[i].y);
    line(objects[i].x + 81 + difference, objects[i].y, objects[i].x + 81 + difference, objects[j].y);
    line(objects[j].x - 81 - difference, objects[j].y, objects[j].x - 81, objects[j].y);
}

void propertiesDisplay(int i)
{
    settextstyle(8, HORIZ_DIR, 1);
    setbkcolor(LIGHTGRAY);
    outtextxy(middleX - 625, systemHeight - 120, objects[i].properties.quantity);
    outtextxy(middleX - 625, systemHeight - 140, objects[i].properties.name);
    outtextxy(middleX - 625, systemHeight - 100, objects[i].properties.measurement);

    setbkcolor(BLACK);
}

int overlap(int x, int y)
{
    if (objectsCount == 0)
        return -1;
    for (int i = 0; i < objectsCount; i++)
    {
        if (x > objects[i].x - 81 && x < objects[i].x + 81 && y > objects[i].y - 81 && y < objects[i].y + 81)
            return 0;
    }
    return 1;
}

int checkPointOverlap(int x, int y)
{
    // Loop through each object in the array
    for (int i = 0; i < objectsCount; i++)
    {
        // Check if the point is within the specified range of the object's coordinates
        if (x > objects[i].x - 81 && x < objects[i].x + 81 &&
            y > objects[i].y - 75 && y < objects[i].y + 75)
        {
            // If the point overlaps with the object, return the object's index
            return 0;
        }
    }

    // If the point does not overlap with any of the objects, return -1
    return -1;
}

void load()
{
    ifstream circuitFile("my_circuit.txt");
    if (circuitFile.is_open())
    {
        // Read the objectsCount variable from the file
        circuitFile >> objectsCount;

        // Read the information for each object from the file
        for (int i = 0; i < objectsCount; ++i)
        {
            circuitFile >> objects[i].x >> objects[i].y >> objects[i].type;
            circuitFile >> objects[i].leftConnector >> objects[i].rightConnector;
            circuitFile >> objects[i].properties.quantity >> objects[i].properties.measurement;
            circuitFile >> objects[i].properties.name;
            cout << objects[i].x << " " << objects[i].y <<'\n';
        }

        // Close the file
        circuitFile.close();
        draw();
    }
}

void save()
{
    ofstream circuitFile("my_circuit.txt");
    circuitFile << "";
    if (circuitFile.is_open())
    {
        // Write the objectsCount variable to the file
        circuitFile << objectsCount << endl;

        // Write the information for each object to the file
        for (int i = 0; i < objectsCount; ++i)
        {
            circuitFile << objects[i].x << " " << objects[i].y << " " << objects[i].type << " ";
            circuitFile << objects[i].leftConnector << " " << objects[i].rightConnector << " ";
            circuitFile << objects[i].properties.quantity << " " << objects[i].properties.measurement << " ";
            circuitFile << objects[i].properties.name << endl;
        }

        // Close the file
        circuitFile.close();
        cout << "saved"<<'\n';
    }
}

void exit()
{
    closegraph();
    return;
}

/*<--------------------------End functions------------------------>*/