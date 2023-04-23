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
        console.setCursorPosCenter(6, -Constants::y / 2 - 3);

        std::cin >> num;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            wstr = L"Incorrect enter. Retry again.";
            console.printStrCenter(wstr, 0, -Constants::y / 2 - 2);
            console.clear_zone(1, 4, 8, -Constants::y / 2 - 3);
        }
        else if (limit > 0)
        {
            if (num >= 0 && num <= limit)
            {
                std::cin.ignore(32767, '\n');
                console.clear_zone(1, 12, 6, -Constants::y / 2 - 3);
                return num;
            }
            else
            {
                std::cin.ignore(32767, '\n');
                wstr = L"Incorrect enter. Retry again.";
                console.printStrCenter(wstr, 0, -Constants::y / 2 - 2);
                console.clear_zone(1, 4, 8, -Constants::y / 2 - 3);
            }
        }
        else if (num >= 0)
        {
            std::cin.ignore(32767, '\n');
            console.clear_zone(1, 12, 6, -Constants::y / 2 - 3);
            return num;

        }
        else
        {
            std::cin.ignore(32767, '\n');
            wstr = L"Incorrect enter. Retry again.";
            console.printStrCenter(wstr, 0, -Constants::y / 2 - 2);
            console.clear_zone(1, 4, 8, -Constants::y / 2 - 3);
        }
    }
}

void inputPoint(Console& console, Point& point)
{
    std::wstring wstr;
   

    while (true)
    {
        wstr = L"x(1 - " + std::to_wstring(Constants::x - 1) + L"):";
        console.printStrCenter(wstr, 0, -Constants::y / 2 - 3);

        point.x = inputNum(console, Constants::x - 1);
        if (point.x > 0)
        {
            --point.x;
            break;
        }
    }
    console.clear_zone(2, 30, 0, -Constants::y / 2 - 3);

    while (true)
    {
        wstr = L"y(1 - " + std::to_wstring(Constants::y - 1) + L"):";
        console.printStrCenter(wstr, 0, -Constants::y / 2 - 3);
        point.y = inputNum(console, Constants::y - 1);
        if (point.y > 0)
        {
            --point.y;
            break;
        }
    }
    console.clear_zone(2, 30, 0, -Constants::y / 2 - 3);
    point.z = 0;
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
        wstrObject = L"\u263a";
        break;
    }

    return wstrObject;
}

int square(int num)
{
    int sqNum = sqrt(num);
    if (sqNum * sqNum == num)
        return sqNum;
    else
        return -1;
}