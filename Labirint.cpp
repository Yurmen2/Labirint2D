#include "Labirint.h"

Labirint::Labirint(std::wstring filename)
    :m_f{ filename }, m_labirint{Constants::y, std::vector<Objects>(Constants::x)}
{
    if (!m_f)
    {
        std::ofstream ff(filename);
        m_f.open(filename, std::ios::in | std::ios::out);
    }

    if (!m_f)
    {
        std::wcerr << filename << L" could not be opened\n";
        exit(-1);
    }
}

void Labirint::create()
{
    for (int i = 0; i < Constants::y; ++i)
    {
        for (int iii = 0; iii < Constants::x; ++iii)
        {
            if (i == 0 || i == Constants::y - 1)
                m_labirint[i][iii] = Objects::WALL;

            else if(iii == 0 || iii == Constants::x - 1)
                m_labirint[i][iii] = Objects::WALL;
            else
            {
                m_labirint[i][iii] = static_cast<Objects>(object_id[rand() % 2]);
            }
        }   
     }

    // Закрашивание одиноких проходов без выхода
    for (int i = 1; i < Constants::y; i++)
    {
        for (int iii = 1; iii < Constants::x; iii++)
        {
            if (i >= 1 && i < Constants::y -1 && iii >= 1 && iii < Constants::x - 1)
            {
                if (m_labirint[i - 1][iii] == Objects::WALL && m_labirint[i + 1][iii] == Objects::WALL &&
                    m_labirint[i][iii - 1] == Objects::WALL && m_labirint[i][iii + 1] == Objects::WALL)
                    m_labirint[i][iii] = Objects::WALL;
            }
        }
    }
}

void Labirint::printMaze(Console& console)
{
    const CONSOLE_SCREEN_BUFFER_INFO csbi = console.getCsbi();

    for (int i = 0; i < Constants::y; ++i)
    {
        std::wstring str;

        //// Вывод ~ в первой и последней строке карты ПОСИМВОЛЬНО
        //if (i == 0)
        //{
        //    for (int aaa = 0; aaa < (Constants::x * 2 + 2); ++aaa)
        //    {
        //        str = "~";
        //        x = -(console.getCenterX()) + aaa + ((csbi.dwSize.X - (Constants::x * 2)) / 2) - 1;
        //        y = -(console.getCenterY()) + ((csbi.dwSize.Y - (Constants::y)) / 2) - 1;
        //        console.printStrCenter(str, x, y);
        //    }
        //    
        //    for (int aaa = 0; aaa < (Constants::x * 2 + 2); ++aaa)
        //    {
        //        str = "~";
        //        x = -(console.getCenterX()) + aaa + ((csbi.dwSize.X - (Constants::x * 2)) / 2) - 1;
        //        y = -(console.getCenterY()) + ((csbi.dwSize.Y - (Constants::y)) / 2) + Constants::y;
        //        console.printStrCenter(str, x, y);
        //    }

        //// Основной вывод лабиринта ПОСИМВОЛЬНО
        //for (int iii = 0; iii < Constants::x; ++iii)
        //{
        //    
        //    str = stringObject(m_labirint[i][iii]);
        //    SHORT x = -(console.getCenterX()) + iii + space + ((csbi.dwSize.X - (Constants::x * 2)) / 2);
        //    SHORT y = -(console.getCenterY()) + i + ((csbi.dwSize.Y - (Constants::y)) / 2);
        //    console.printStrCenter(str, x, y);
        //    ++space;
        //}
        //std::cout << '\n'; 

        // Вывод ГОРИЗОНТАЛЬНОЙ ЛИНИИ в первой и последней строке карты ПОСТРОЧНО
        if (i == 0)
        {
            // Закругляющая левая верхняя линия
            str = L"\u250c";
            // Горизонтальная линия
            for (int aaa = 0; aaa < (Constants::x); ++aaa)
                str += L"\u2500";
            
            // Закругляющая правая верхняя линия
            str += L"\u2510";
            console.printStrCenter(str, 0, -(console.getCenterY()) + ((csbi.dwSize.Y - (Constants::y)) / 2));


            // Закругляющая левая нижняя линия
            str[0] = L'\u2514';
            // Закругляющая правая нижняя линия
            str[Constants::x + 1] = L'\u2518';
            console.printStrCenter(str, 0, -(console.getCenterY()) + ((csbi.dwSize.Y - (Constants::y)) / 2) + Constants::y + 1);
        }

        // Вертикальная линия
        str = L"\u2502";

        // Основной вывод лабиринта ПОСТРОЧНО
        for (int iii = 0; iii < Constants::x; ++iii)
            str += wstrObject(m_labirint[i][iii]);
        // Вертикальная линия
        str += L"\u2502";
        console.printStrCenter(str, 0, -(console.getCenterY()) + i + ((csbi.dwSize.Y - (Constants::y)) / 2) + 1);
    }
}

void Labirint::printPoint(Console& console, Point& p)
{
    SHORT x, y;
    CONSOLE_SCREEN_BUFFER_INFO csbi = console.getCsbi();

    x = -(console.getCenterX()) + p.x + ((csbi.dwSize.X - (Constants::x)) / 2);
    y = -(console.getCenterY()) + p.y + ((csbi.dwSize.Y - (Constants::y)) / 2) + 1;

    console.printStrCenter(wstrObject(m_labirint[p.y][p.x]), x + 2, y);
}

void Labirint::inFile()
{
    for (int i = 0;  i < Constants::y; i++)
    {
        for (int iii = 0; iii < Constants::x; iii++)
        {
            m_f << static_cast<char>(m_labirint[i][iii]);
        }
        m_f << "\n";
    }
}

void Labirint::outFile()
{
    for (int i = 0; i < Constants::y; i++)
    {
        for (int iii = 0; iii < Constants::x; iii++)
        {
            char ch;
            m_f >> ch;
            m_labirint[i][iii] = static_cast<Objects>(ch);
        }
    }
}

bool Labirint::genNew(Console& console)
{
    while (true)
    {
        printMaze(console);


        std::wstring str = L"Generate a new maze? Y/N";
        console.printStrCenter(str, 0, -Constants::y / 2 - 3);

        char ch = directInput();

        int str_size = static_cast<int>(str.length());
        switch (ch)
        {
        case 'Y':
            create();
            console.clear_zone(1, str_size, 0, -Constants::y / 2 - 3);
            break;
        case 'N':
            console.clear_zone(1, str_size, 0, -Constants::y / 2 - 3);
            return false;
        }
    }
}

bool Labirint::saveNew(Console& console)
{
    while (true)
    {
        std::wstring str = L"Save maze in file? Y/N";
        console.printStrCenter(str, 0, -Constants::y / 2 - 3);

        char ch = directInput();

        int str_size = static_cast<int>(str.length());
        switch (ch)
        {
        case 'Y':
            inFile();
        case 'N':
            console.clear_zone(1 ,str_size, 0, -Constants::y / 2 - 3);
            return false;
        }
    }
}

bool Labirint::mazeMenu(Console& console, bool isLabirintLoaded)
{
    while (true)
    {

        if (isLabirintLoaded)
            printMaze(console);

        std::wstring str;
        short clear_zone_size;
        if (isLabirintLoaded)
            clear_zone_size = 6;
        else
            clear_zone_size = 10;

        short str_size = 20;
        console.clear_zone(clear_zone_size, str_size, 0, -5 );

        // Верхняя линия
        str = L"\u250c";
        for (int i = 0; i < str_size; ++i)
        {
            str += L"\u2500";
        }
        str += L"\u2510";
        console.printStrCenter(str, 0, -5);


        str = L"\u2502                    \u2502";
        console.printStrCenter(str, 0, -4);

        str = L"\u2502     Labirint2D     \u2502";
        console.printStrCenter(str, 0, -3);

        str = L"\u2502                    \u2502";
        console.printStrCenter(str, 0, -2);

        str = L"\u2502Load maze from file \u2502";
        console.printStrCenter(str, 0, -1);

        str = L"\u2502    Create maze     \u2502";
        console.printStrCenter(str, 0, 0);

        if (isLabirintLoaded)
        {
            str = L"\u2502 Back to main menu  \u2502";
            console.printStrCenter(str, 0, 1);
        }
        else
        {
            str = L"\u2502                    \u2502";
            console.printStrCenter(str, 0, 1);
        }

        // Нижняя линия
        str = L"\u2514";
        for (int i = 0; i < str_size; ++i)
        {
            str += L"\u2500";
        }
        str += L"\u2518";
        console.printStrCenter(str, 0, 2);

        int choice = directInput();
        switch (choice)
        {
        case '1':
                outFile();
                return true;
        case '2':
            create();

            genNew(console);

            saveNew(console);

            return true;
        case '3':
            if (isLabirintLoaded)
            {
                printMaze(console);
                return true;
            }
            break;
        }
    }
}

void Labirint::mainMenu(Console& console, std::wstring& msg)
{
    std::wstring str;

    short str_size = 12;
    short clear_zone_size = 10;
    
    console.clear_zone(clear_zone_size, str_size, 0, -5);


    // Верхняя линия
    str = L"\u250c";
    for (int i = 0; i < str_size; ++i)
        str += L"\u2500";

    str += L"\u2510";
    console.printStrCenter(str, 0, -5);
    
    str = L"\u2502            \u2502";
    console.printStrCenter(str, 0, -4);

    str = L"\u2502 Labirint2D \u2502";
    console.printStrCenter(str, 0, -3);

    str = L"\u2502            \u2502";
    console.printStrCenter(str, 0, -2);

    str = L"\u2502    Start   \u2502";
    console.printStrCenter(str, 0, -1);

    str = L"\u2502  Maze menu \u2502";
    console.printStrCenter(str, 0, 0);

    str = L"\u2502  Settings  \u2502";
    console.printStrCenter(str, 0, 1);

    str = L"\u2502    Exit    \u2502";
    console.printStrCenter(str, 0, 2);

    str = L"\u2502            \u2502";
    console.printStrCenter(str, 0, 3);

    // Нижняя линия
    str = L"\u2514";
    for (int i = 0; i < str_size; ++i)
        str += L"\u2500";

    str += L"\u2518";
    console.printStrCenter(str, 0, 4);

    if (msg.length() > 0)
        console.printStrCenter(msg, 0, -Constants::y / 2 - 3);
}


std::wstring Labirint::walk(Console& console,Point& p)
    {
    
    std::wstring msg;
    Keys key;

    key = static_cast<Keys>(directInput());

    if (key == Keys::ARROW_UP)
    {
        if (m_labirint[p.y - 1][p.x] == Objects::EMPTY)
        {
            m_labirint[p.y][p.x] = Objects::EMPTY;
            printPoint(console, p);

            p.y = p.y - 1;
            m_labirint[p.y][p.x] = Objects::HERO;

            printPoint(console, p);
        }
        else
        {
            msg = L"You can't move higher.\n";
        }
    }

    else if (key == Keys::ARROW_LEFT)
    {
        if (m_labirint[p.y][p.x - 1] == Objects::EMPTY)
        {
            m_labirint[p.y][p.x] = Objects::EMPTY;
            printPoint(console, p);

            p.x = p.x - 1;
            m_labirint[p.y][p.x] = Objects::HERO;
            printPoint(console, p);

        }
        else
        {
            msg = L"You can't move to the left.\n";
        }
    }

    else if (key == Keys::ARROW_BACK)
    {
        if (m_labirint[p.y + 1][p.x] == Objects::EMPTY)
        {
            m_labirint[p.y][p.x] = Objects::EMPTY;
            printPoint(console, p);


            p.y = p.y + 1;
            m_labirint[p.y][p.x] = Objects::HERO;
            printPoint(console, p);
        }
        else
        {
            msg = L"You can't move to the lower.\n";
        }
    }

    else if (key == Keys::ARROW_RIGHT)
    {
        if (m_labirint[p.y][p.x + 1] == Objects::EMPTY)
        {
            m_labirint[p.y][p.x] = Objects::EMPTY;
            printPoint(console, p);

            p.x = p.x + 1;
            m_labirint[p.y][p.x] = Objects::HERO;
            printPoint(console, p);
        }
        else
        {
            msg = L"You can't move to the right.\n";
        }
    }

    else if (key == Keys::ESC)
    {
        msg = L"esc";
    }

    return msg;
}