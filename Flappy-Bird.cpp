// Flappy-Bird.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 30
#define WIN_WIDTH 70
#define MENIU_WIDTH 20
#define GAP_SIZE 7
#define PIPE_DIF 45

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int pipePos[3];
int gapPos[3];
int pipeFlag[3];
char bird[2][5] = { '/', '-', '-', 'o', '\\', ' ', '|', '_', ' ', '>' };
int birdPos = 6;
int score = 0;

void play();

void goTo_xy(int x, int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void setCursor(bool visible, DWORD size) {
    if (size == 0)
        size = 20;

    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

void drawBorder() {
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        goTo_xy(i, 0); cout << "x";
        goTo_xy(i, SCREEN_HEIGHT); cout << "x";
    }

    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        goTo_xy(0, i); cout << "x";
        goTo_xy(SCREEN_WIDTH, i); cout << "x";
    }

    for (int i = 0; i < SCREEN_WIDTH; i++) {
        goTo_xy(WIN_WIDTH, i); cout << "x";
    }
}

void generatePipe(int random) {
    gapPos[random] = 3 + rand() % 14;
}

void drawPipe(int random) {
    if (pipeFlag[random] == true) {
        for (int i = 0; i < gapPos[random]; i++) {
            goTo_xy(WIN_WIDTH - pipePos[random], i + 1); cout << "***";
        }
        for (int i = gapPos[random] + GAP_SIZE; i < SCREEN_HEIGHT - 1; i++) {
            goTo_xy(WIN_WIDTH - pipePos[random], i + 1); cout << "***";
        }
    }
}

void erasePipe(int random) {
    if (pipeFlag[random] == true) {
        for (int i = 0; i < gapPos[random]; i++) {
            goTo_xy(WIN_WIDTH - pipePos[random], i + 1); cout << "   ";
        }
        for (int i = gapPos[random] + GAP_SIZE; i < SCREEN_HEIGHT - 1; i++) {
            goTo_xy(WIN_WIDTH - pipePos[random], i + 1); cout << "   ";
        }
    }
}

void drawBird() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            goTo_xy(j + 2, i + birdPos); cout << bird[i][j];
        }
    }
}

void eraseBird() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            goTo_xy(j + 2, i + birdPos); cout << "   ";
        }
    }
}

int collision() {
    if (pipePos[0] >= 61) {
        if (birdPos < gapPos[0] || birdPos > gapPos[0] + GAP_SIZE) {
            return 1;
        }
    }
    return 0;
}

void debug() {
    //gotoxy(SCREEN_WIDTH + 3, 4); cout << "Pipe Pos: " << pipePos[0];
}

void gameOver() {
    system("cls");
    cout << endl;
    cout << "\t\t------------------------" << endl;
    cout << "\t\t--------Game Over-------" << endl;
    cout << "\t\t------------------------" << endl;
    cout << "\t\tPress any key to go back" << endl;


    if (_getch()) {
        play();
    }
}

void updateScore() {
    goTo_xy(WIN_WIDTH + 7, 5); cout << "Score: " << score << endl;
}

void play() {
    birdPos = 6;
    score = 0;
    pipeFlag[0] = 1;
    pipeFlag[1] = 0;
    pipePos[0] = pipePos[1] = 4;

    system("cls");
    drawBorder();
    generatePipe(0);
    updateScore();

    goTo_xy(WIN_WIDTH + 5, 2); cout << "FLAPPY BIRD";
    goTo_xy(WIN_WIDTH + 6, 4); cout << "-----------";
    goTo_xy(WIN_WIDTH + 6, 6); cout << "-----------";
    goTo_xy(WIN_WIDTH + 7, 12); cout << "Control";
    goTo_xy(WIN_WIDTH + 7, 13); cout << "-----------";
    goTo_xy(WIN_WIDTH + 2, 14); cout << "Spacebar - jump";

    goTo_xy(10, 5); cout << "Press any key to start";
    _getch();
    goTo_xy(10, 5); cout << "                      ";

    while (1) {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 32) {
                if (birdPos > 3)
                    birdPos -= 3;
            }
            if (ch == 27) {
                break;
            }
        }

        drawBird(); drawPipe(0);
        drawPipe(1); debug();
        if (collision() == 1) {
            gameOver();
            return;
        }
        Sleep(100);
        eraseBird(); erasePipe(0);
        erasePipe(1); birdPos += 1;

        if (birdPos > SCREEN_HEIGHT - 2) {
            gameOver();
            return;
        }

        if (pipeFlag[0] == 1)
            pipePos[0] += 2;
        if (pipeFlag[1] == 1)
            pipePos[1] += 2;

        if (pipePos[0] >= 40 && pipePos[0] < 42) {
            pipeFlag[1] = 1;
            pipePos[1] = 4;
            generatePipe(1);
        }

        if (pipePos[0] > 68) {
            score++;
            updateScore();
            pipeFlag[1] = 0;
            pipePos[0] = pipePos[1];
            gapPos[0] = gapPos[1];
        }
    }
}

int main()
{
    // play game 
    setCursor(0, 0);
    srand((unsigned)time(NULL));
    play();

    return 0;
}