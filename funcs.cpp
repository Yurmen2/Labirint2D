#include "funcs.h"

char directInput()
{
    char ch = _getch();
    if (ch == 0xE0 || ch == -32)
        ch = _getch();
    ch = toupper(ch);
    return ch;
}

int inputNum(const int limit)
{
    while (true)
    {
        int num;
        std::cin >> num;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Incorrect enter. Retry again.\n";
        }
        else if (limit > 0)
        {
            if (num >= 0 && num <= limit)
            {
                std::cin.ignore(32767, '\n');
                return num;
            }
            else
            {
                std::cin.ignore(32767, '\n');
                std::cout << "Incorrect enter. Retry again.\n";
            }
        }
        else if (num >= 0)
        {
            std::cin.ignore(32767, '\n');
            return num;

        }
        else
        {
            std::cin.ignore(32767, '\n');
            std::cout << "Incorrect enter. Retry again.\n";
        }
    }
}

void inputPoint(Point& point)
{
    std::cout << "x: ";
    point.x = inputNum();
    std::cout << "y: ";
    point.y = inputNum();
}


std::wstring wcstrObject(Objects& object)
{
    std::wstring wcstrObject;
    switch (object)
    {
    case Objects::WALL:
        wcstrObject = L"\u2588";
        break;
    case Objects::EMPTY:
        wcstrObject = L" ";
        break;
    case Objects::HERO:
        wcstrObject = L"*";
        break;
    }

    return wcstrObject;
}