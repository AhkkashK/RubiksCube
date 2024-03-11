//
// Created by Clara on 05/05/2021.
//


#ifdef _WIN32

#include <windows.h>
#include <conio.h>
#include "conio.h"
#include <limits.h>
#include <stdbool.h>

/*windows 10 can use VT100*/

bool EnableVTMode() {
    // Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
    {
        return false;
    }

    DWORD ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode))
    {
        return false;
    }
    return true;
}

static void clearbits(unsigned char * v,
                      int bit_index,
                      int nbits)
{
    unsigned mask = ~((unsigned char)(0)) << (sizeof(v) * CHAR_BIT - (unsigned char)(nbits));
    mask = mask >> (sizeof(v) * CHAR_BIT - (unsigned char)(bit_index)-(unsigned char)(nbits));
    *v &= ~mask;
}


static void setbits(unsigned char *v,
                    int bit_index,
                    int nbits,
                    unsigned char number)
{
    clearbits(&number, nbits, sizeof(number) * CHAR_BIT - nbits);

    unsigned char big = number;
    big = (big << bit_index);

    clearbits(v, bit_index, nbits);
    *v |= big;
}


static unsigned char getbits(unsigned char v, int bit_index, int nbits)
{
    unsigned char r = v >> bit_index;
    clearbits(&r, nbits, sizeof(unsigned char) * CHAR_BIT - nbits);
    return r;
}


void c_gettextinfo(struct text_info *r)
{
    if (r == 0)
        return;

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    r->attribute = (unsigned char)csbi.wAttributes;
    r->curx = (unsigned char)csbi.dwCursorPosition.X;
    r->cury = (unsigned char)csbi.dwCursorPosition.Y;
    r->screenwidth = (unsigned char)csbi.dwMaximumWindowSize.X;
    r->screenheight = (unsigned char)csbi.dwMaximumWindowSize.X;
    r->normattr = 0;
}

int c_kbhit(void)
{
    return _kbhit();
}
int c_getch(void)
{
    return _getch();
}

int c_getche(void)
{
    return _getche();
}

void c_setcursortype(int cur_t)
{
    CONSOLE_CURSOR_INFO ci;

    switch (cur_t)
    {
        case _NOCURSOR://     (turns off the cursor)
            ci.bVisible = FALSE;
            ci.dwSize = 1;
            break;

        case _SOLIDCURSOR://  (solid block cursor)
            ci.bVisible = TRUE;
            ci.dwSize = 100;
            break;

        default:
        case _NORMALCURSOR: // (normal underscore cursor)
            ci.bVisible = TRUE;
            ci.dwSize = 50;
            break;
    }

    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}

void c_textattr(int newattr)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), newattr);
}

void c_textbackground(int newcolor)
{
    struct text_info ti;
    c_gettextinfo(&ti);
    unsigned char wColor = ti.attribute;
    unsigned char old = getbits(wColor, 4, 4);
    setbits(&wColor, 4, 4, newcolor);
    c_textattr(wColor);
}

void c_textcolor(int newcolor)
{
    struct text_info ti;
    c_gettextinfo(&ti);
    unsigned char wColor = ti.attribute;
    int old = getbits(wColor, 0, 4);
    setbits(&wColor, 0, 4, newcolor);
    c_textattr(wColor);
}


int c_wherex()
{
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi))
    {
        return cbsi.dwCursorPosition.X + 1;
    }
    return -1;
}

int c_wherey()
{
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi))
    {
        return cbsi.dwCursorPosition.Y;
    }
    return -1;
}

void c_gotoxy(int x, int y)
{
    COORD point;
    point.X = x - (short)1;
    point.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

void c_clrscr()
{
    COORD coordScreen = { 0, 0 };
    unsigned long cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    unsigned long dwConSize;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
}

#endif

