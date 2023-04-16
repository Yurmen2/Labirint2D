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


std::string stringObject(Objects& object)
{
    std::string stringObject;
    switch (object)
    {
    case Objects::WALL:
        stringObject = 'W';
        break;
    case Objects::EMPTY:
        stringObject = 'E';
        break;
    case Objects::HERO:
        stringObject = '*';
        break;
    }

    return stringObject;
}