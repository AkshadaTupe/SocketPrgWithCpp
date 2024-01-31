//Logger Class

#pragma once

#include "stdafx.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

using namespace std;
// Define color codes
enum Color {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHTGRAY = 7,
    DARKGRAY = 8,
    LIGHTBLUE = 9,
    LIGHTGREEN = 10,
    LIGHTCYAN = 11,
    LIGHTRED = 12,
    LIGHTMAGENTA = 13,
    YELLOW = 14,
    WHITE = 15
};


class Logger
{

private:
    void setColor(Color color) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, static_cast<int>(color));
    }
public:
    void Debug(string msg)
    {
        setColor(LIGHTGREEN);
        std::cout << msg << std::endl;
        setColor(WHITE);
    }

    void Error(string msg)
    {
        setColor(LIGHTRED);
        std::cout << msg << std::endl;
        setColor(WHITE); 
    }

    void display(string msg)
    {
        // Reset color to default
        setColor(WHITE);
        std::cout << msg << std::endl;
    }
};