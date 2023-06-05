#include <locale>
#include <time.h>
#include "Labirint.h"
#include "ConsoleApi.h"

MapSize mapSize{ 40, 110, 100 };

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
    std::wstring str = L"";
    
    console.clear_zone(1, 30, -(console.getCenterX()) + 15, -(console.getCenterY()));

    backToMenu:
    while (true)
    {
        labirint.mainMenu(console, msg);

        char choice = directInput();
        switch (choice)
        {
        case '1':
            if (!isLabirintLoaded)
                msg = L"To start, load the maze in Maze menu";
            else
            {
                labirint.printMaze(console, 0);

                Point point {};
                inputPoint(console, point);

                labirint.setPoint(point, Objects::HERO);
                labirint.printPoint(console, point);
                
                while (true)
                {
                    console.clear_zone(1, 30, 0, -mapSize.y / 2 - 3);
                    console.printStrCenter(msg, 0, -mapSize.y / 2 - 3);


                    msg = labirint.walk(console, point);
                    if (msg == L"esc")
                    {
                        msg = L"";
                        console.clear_zone(109, 39, 0, 0);
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
            labirint.settingsMenu(console);
            isLabirintLoaded = false;
            break;
        case '4':
            CONSOLE_SCREEN_BUFFER_INFO csbi = console.getCsbi();
            console.clear_zone(csbi.dwSize.Y, csbi.dwSize.X, -2, -(console.getCenterY()));
            exit(0);
        }
    }

    return 0;
}