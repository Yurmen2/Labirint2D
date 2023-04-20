#include "funcs.h"

char directInput()
{
    char ch = _getch();
    if (ch == 0xE0 || ch == -32)
        ch = _getch();
    ch = toupper(ch);
    return ch;
}

int inputNum(Console& console, const int limit)
{
    while (true)
    {
        int num;
        std::wstring wstr = L"";
        console.setCursorPosCenter(1, -Constants::y / 2 - 3);
        std::cin >> num;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            wstr = L"Incorrect enter. Retry again.";
            console.printStrCenter(wstr, 0, -Constants::y / 2 - 2);
        }
        else if (limit > 0)
        {
            if (num >= 0 && num <= limit)
            {
                std::cin.ignore(32767, '\n');
                console.clear_zone(1, 5, 1, -Constants::y / 2 - 3);
                return num;
            }
            else
            {
                std::cin.ignore(32767, '\n');
                wstr = L"Incorrect enter. Retry again.";
                console.printStrCenter(wstr, 0, -Constants::y / 2 - 2);

            }
        }
        else if (num >= 0)
        {
            std::cin.ignore(32767, '\n');
            console.clear_zone(1, 5, 1, -Constants::y / 2 - 3);
            return num;

        }
        else
        {
            std::cin.ignore(32767, '\n');
            wstr = L"Incorrect enter. Retry again.";
            console.printStrCenter(wstr, 0, -Constants::y / 2 - 2);

        }
    }
}

void inputPoint(Console& console, Point& point)
{
    std::wstring wstr;
    wstr = L"x:";
    console.printStrCenter(wstr, 0, -Constants::y / 2 - 3);

    point.x = inputNum(console);
    --point.x;

    console.clear_zone(2, 30, 0, -Constants::y / 2 - 3);

    wstr =  L"y:";
    console.printStrCenter(wstr, 0, -Constants::y / 2 - 3);

    point.y = inputNum(console);
    --point.y;

    console.clear_zone(2, 30, 0, -Constants::y / 2 - 3);

}


std::wstring wstrObject(Objects& object)
{
    std::wstring wstrObject;
    switch (object)
    {
    case Objects::WALL:
        wstrObject = L"\u2588";
        break;
    case Objects::EMPTY:
        wstrObject = L" ";
        break;
    case Objects::HERO:
        wstrObject = L"*";
        break;
    }

    return wstrObject;
}