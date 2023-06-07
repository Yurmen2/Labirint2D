#include "funcs.h"

extern MapSize mapSize;

char directInput()
{
    char ch = _getch();
    if (ch == 0xE0 || ch == -32)
        ch = _getch();
    ch = toupper(ch);
    return ch;
}

int inputNum(Console& console, short offsetX, short offsetY, const int limit, const int min)
{
    while (true)
    {
        int num;
        std::wstring wstr = L"";
        console.setCursorPosCenter(offsetX, offsetY);

        std::cin >> num;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            wstr = L"Incorrect enter. Retry again.";
            console.printStrCenter(wstr, 0, -mapSize.y / 2 - 4);
            console.clear_zone(1, 4, offsetX + 2, offsetY);
        }

        else if(limit > 0 && min > 0)
        {
            if (num > 0 && num >= min && num <= limit)
            {
                std::cin.ignore(32767, '\n');
                console.clear_zone(1, 30, 0, -mapSize.y / 2 - 4);
                return num;
            }
            else
            {
                std::cin.ignore(32767, '\n');
                wstr = L"Incorrect enter. Retry again.";
                console.printStrCenter(wstr, 0, -mapSize.y / 2 - 4);
                console.clear_zone(1, 4, offsetX + 2, offsetY);
            }
        }

        else if (limit > 0)
        {
            if (num > 0 && num <= limit)
            {
                std::cin.ignore(32767, '\n');
                console.clear_zone(1, 30, 0, -mapSize.y / 2 - 4);
                return num;
            }
            else
            {
                std::cin.ignore(32767, '\n');
                wstr = L"Incorrect enter. Retry again.";
                console.printStrCenter(wstr, 0, -mapSize.y / 2 - 4);
                console.clear_zone(1, 4, offsetX + 2, offsetY);
            }
        }

        else if (min > 0)
        {
            if (num > 0 && num >= min)
            {
                std::cin.ignore(32767, '\n');
                console.clear_zone(1, 30, 0, -mapSize.y / 2 - 4);
                return num;
            }
            else
            {
                std::cin.ignore(32767, '\n');
                wstr = L"Incorrect enter. Retry again.";
                console.printStrCenter(wstr, 0, -mapSize.y / 2 - 4);
                console.clear_zone(1, 4, offsetX + 2, offsetY);
            }
        }

        else if (num > 0)
        {
            std::cin.ignore(32767, '\n');
            console.clear_zone(1, 30, 0, -mapSize.y / 2 - 4);
            return num;

        }

        else
        {
            std::cin.ignore(32767, '\n');
            wstr = L"Incorrect enter. Retry again.";
            console.printStrCenter(wstr, 0, -mapSize.y / 2 - 2);
            console.clear_zone(1, 4, offsetX + 2, offsetY);
        }
    }
}

void inputPoint(Console& console, Point& point)
{
    std::wstring wstr;
   

    while (true)
    {
        wstr = L"x(2 - " + std::to_wstring(mapSize.x - 1) + L"):";
        console.printStrCenter(wstr, 0, -mapSize.y / 2 - 3);

        point.x = inputNum(console, 5, -mapSize.y / 2 - 3, mapSize.x - 1);
        if (point.x > 1)
        {
            --point.x;
            break;
        }
    }
    console.clear_zone(1, 30, 0, -mapSize.y / 2 - 3);

    while (true)
    {
        wstr = L"y(2 - " + std::to_wstring(mapSize.y - 1) + L"):";
        console.printStrCenter(wstr, 0, -mapSize.y / 2 - 3);
        point.y = inputNum(console, 5, -mapSize.y / 2 - 3,  mapSize.y - 1);
        if (point.y > 1)
        {
            --point.y;
            break;
        }
    }
    console.clear_zone(1, 30, 0, -mapSize.y / 2 - 3);
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