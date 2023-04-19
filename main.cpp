// Labirint - Программа, создающая 2д лабиринт в двумерном массиве.

#include <locale>
#include <time.h>
#include "Labirint.h"
#include "ConsoleApi.h"

int main()
{   
    _wsetlocale(LC_ALL, L"en-US.UTF8");
    system("chcp 65001");

    Console console {GetStdHandle(STD_OUTPUT_HANDLE)};

    console.title(L"Labirint2D");
    console.setFont(16, 22, L"Courier New");
    console.setBufferSize();
    console.fullScreen();
    console.cursorHide();
    console.initCenterXY();

    srand(static_cast<unsigned int>(time(NULL)));
    rand();

    Labirint labirint;

    bool isLabirintLoaded = false;
    std::wstring msg = L"";

    backToMenu:
    while (true)
    {
        system("cls");
        if (isLabirintLoaded)
            labirint.print(console);

        labirint.mainMenu(console, msg);

        char choice = directInput();
        switch (choice)
        {
        case '1':
            if (!isLabirintLoaded)
                msg = L"To start, load the maze in Maze menu";
            else
            {
                system("cls");
                labirint.print(console);
                std::cout << "Enter start point(x, y): \n";
                Point point {};

                inputPoint(point);

                labirint.setPoint(point, Objects::HERO);
                while (true)
                {
                    system("cls");
                    labirint.print(console);
                    std::wcout << msg;
                    msg = labirint.walk(point);
                    if (msg == L"esc")
                    {
                        msg = L"";
                        labirint.setPoint(point, Objects::EMPTY);
                        goto backToMenu;
                    }
                }
            }
            break;
        case '2':
           isLabirintLoaded = labirint.mazeMenu(console, isLabirintLoaded);
           msg = L"";
           break;
        case '3':
            break;
        case '4':
            exit(0);
        }
    }

    return 0;
}