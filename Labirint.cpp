#include "Labirint.h"

Labirint::Labirint(std::wstring filename)
    :m_f{ filename }, m_labirint{Constants::z, std::vector<std::vector<Objects>>(Constants::y, std::vector<Objects>(Constants::x))}
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
    int map_size = Constants::z;
    int map_mathRoot = square(Constants::z);
    // Внешний счетчик для определения боковых локаций
    int n, a;
    n = a = 1;
    // Внутренний счетчик для определения боковых локаций, 3 = Внешний_счетчик += 1
    int nnn, aaa;
    nnn = aaa = 0;
    if (map_mathRoot == -1)
        exit(-1);

    for (int i = 1; i <= map_size; ++i)
    {
        for (int j = 0; j < Constants::y; ++j)
        {
            for (int k = 0; k < Constants::x; ++k)
            {
                // Угловые края карты
                if (i == 1 || i == map_mathRoot || i == Constants::z + 1 - map_mathRoot || i == Constants::z)
                {
                    // Проходы верхний левый угол
                    if (i == 1 && j == Constants::y - 1 && k == Constants::x / 2)
                        m_labirint[i - 1][j][k] = Objects::EMPTY;
                    else if (i == 1 && j == Constants::y / 2 && k == Constants::x - 1)
                        m_labirint[i - 1][j][k] = Objects::EMPTY;

                    // Проходы верхний правый угол
                    else if (i == map_mathRoot && j == Constants::y - 1 && k == Constants::x / 2)
                        m_labirint[i - 1][j][k] = Objects::EMPTY;
                    else if (i == map_mathRoot && j == Constants::y / 2 && k == 0)
                        m_labirint[i - 1][j][k] = Objects::EMPTY;

                    // Проходы нижний левый угол
                    else if (i == Constants::z + 1 - map_mathRoot && j == 0 && k == Constants::x / 2)
                        m_labirint[i - 1][j][k] = Objects::EMPTY;
                    else if (i == Constants::z + 1 - map_mathRoot && j == Constants::y / 2 && k == Constants::x - 1)
                        m_labirint[i - 1][j][k] = Objects::EMPTY;

                    // Проходы нижний правый угол
                    else if (i == Constants::z && j == 0 && k == Constants::x / 2)
                        m_labirint[i - 1][j][k] = Objects::EMPTY;
                    else if (i == Constants::z && j == Constants::y / 2 && k == 0)
                        m_labirint[i - 1][j][k] = Objects::EMPTY;

                    // Заполнение края карты стенами
                    else if (j == 0 || j == Constants::y - 1)
                        m_labirint[i - 1][j][k] = Objects::WALL;
                    else if (k == 0 || k == Constants::x - 1)
                        m_labirint[i - 1][j][k] = Objects::WALL;

                    // Заполнение остальной части карты
                    else
                    {
                        m_labirint[i - 1][j][k] = static_cast<Objects>(object_id[1]);
                    }

                }
                // Верхние и нижние края карты 
                else if ((i > 1 && i < map_mathRoot) || (i > (Constants::z + 1 - map_mathRoot) && i << Constants::z))
                {
                    // Проходы верхние края
                    if((i > 1 && i < map_mathRoot) && j == Constants::y / 2 && k == 0 )
                        m_labirint[i - 1][j][k] = Objects::EMPTY;
                    else if((i > 1 && i < map_mathRoot) && j == Constants::y / 2 && k == Constants::x -1)
                        m_labirint[i - 1][j][k] = Objects::EMPTY;
                    else if((i > 1 && i < map_mathRoot) && j == Constants::y - 1 && k == Constants::x / 2)
                        m_labirint[i - 1][j][k] = Objects::EMPTY;

                    // Проходы нижние края
                    else if ((i > (Constants::z + 1 - map_mathRoot) && i << Constants::z) && j == Constants::y / 2 && k == 0)
                        m_labirint[i - 1][j][k] = Objects::EMPTY;
                    else if ((i > (Constants::z + 1 - map_mathRoot) && i << Constants::z) && j == Constants::y / 2 && k == Constants::x - 1)
                        m_labirint[i - 1][j][k] = Objects::EMPTY;
                    else if ((i > (Constants::z + 1 - map_mathRoot) && i << Constants::z) && j == 0 && k == Constants::x / 2)
                        m_labirint[i - 1][j][k] = Objects::EMPTY;

                    else if (j == 0 || j == Constants::y - 1)
                        m_labirint[i - 1][j][k] = Objects::WALL;
                    else if (k == 0 || k == Constants::x - 1)
                        m_labirint[i - 1][j][k] = Objects::WALL;

                    else
                    {
                        m_labirint[i - 1][j][k] = static_cast<Objects>(object_id[1]);
                    }

                }
                // левые края карты
                else if (i == 1 + (map_mathRoot * n))
                {
                    if (j == Constants::y / 2 && k == Constants::x - 1)
                    {
                        m_labirint[i - 1][j][k] = Objects::EMPTY;
                        ++nnn;
                    }
                    else if (j == 0 && k == Constants::x / 2)
                    {
                        m_labirint[i - 1][j][k] = Objects::EMPTY;
                        ++nnn;
                    }
                    else if (j == Constants::y - 1 && k == Constants::x / 2)
                    {
                        m_labirint[i - 1][j][k] = Objects::EMPTY;
                        ++nnn;
                    }

                    else if (j == 0 || j == Constants::y - 1)
                        m_labirint[i - 1][j][k] = Objects::WALL;
                    else if (k == 0 || k == Constants::x - 1)
                        m_labirint[i - 1][j][k] = Objects::WALL;

                    else
                    {
                        m_labirint[i - 1][j][k] = static_cast<Objects>(object_id[1]);
                    }

                    if (nnn == 3)
                    {
                        ++n;
                        nnn = 0;
                    }
                }
                // правые края карты
                else if (i == map_mathRoot + map_mathRoot * a)
                {
                    if (j == Constants::y / 2 && k == 0)
                    {
                        m_labirint[i - 1][j][k] = Objects::EMPTY;
                        ++aaa;
                    }
                    else if (j == 0 && k == Constants::x / 2)
                    {
                        m_labirint[i - 1][j][k] = Objects::EMPTY;
                        ++aaa;
                    }
                    else if (j == Constants::y - 1 && k == Constants::x / 2)
                    {
                        m_labirint[i - 1][j][k] = Objects::EMPTY;
                        ++aaa;
                    }

                    else if (j == 0 || j == Constants::y - 1)
                        m_labirint[i - 1][j][k] = Objects::WALL;
                    else if (k == 0 || k == Constants::x - 1)
                        m_labirint[i - 1][j][k] = Objects::WALL;

                    else
                    {
                        m_labirint[i - 1][j][k] = static_cast<Objects>(object_id[1]);
                    }

                    if (aaa == 3)
                    {
                        ++a;
                        aaa = 0;
                    }
                }
                // Центральные локации, вход в которые со всех 4 сторон
                else
                {
                    if (j == Constants::y / 2 && k == 0)
                        m_labirint[i - 1][j][k] = Objects::EMPTY;
                    else if (j == 0 && k == Constants::x / 2)
                        m_labirint[i - 1][j][k] = Objects::EMPTY;
                    else if (j == Constants::y - 1 && k == Constants::x / 2)
                        m_labirint[i - 1][j][k] = Objects::EMPTY;
                    else if (j == Constants::y / 2 && k == Constants::x - 1)
                        m_labirint[i - 1][j][k] = Objects::EMPTY;


                    else if (j == 0 || j == Constants::y - 1)
                        m_labirint[i - 1][j][k] = Objects::WALL;
                    else if (k == 0 || k == Constants::x - 1)
                        m_labirint[i - 1][j][k] = Objects::WALL;

                    else
                    {
                        m_labirint[i - 1][j][k] = static_cast<Objects>(object_id[1]);
                    }
                }
            }
        }

        // Закрашивание одиноких проходов без выхода
       /* for (int j = 1; j < Constants::y; ++j)
        {
            for (int k = 1; k < Constants::x; k++)
            {
                if (j >= 1 && j < Constants::y - 1 && k >= 1 && k < Constants::x - 1)
                {
                    if (m_labirint[i - 1][j - 1][k] == Objects::WALL && m_labirint[i - 1][j + 1][k] == Objects::WALL &&
                        m_labirint[i - 1][j][k - 1] == Objects::WALL && m_labirint[i - 1][j][k + 1] == Objects::WALL)
                        m_labirint[i - 1][j][k] = Objects::WALL;
                }
            }
        }*/
    }
}

void Labirint::printMaze(Console& console, int i)
{
    const CONSOLE_SCREEN_BUFFER_INFO csbi = console.getCsbi();

    for (int j = 0; j < Constants::y; ++j)
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
        if (j == 0)
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
        for (int k = 0; k < Constants::x; ++k)
            str += wstrObject(m_labirint[i][j][k]);
        // Вертикальная линия
        str += L"\u2502";
        console.printStrCenter(str, 0, -(console.getCenterY()) + j + ((csbi.dwSize.Y - (Constants::y)) / 2) + 1);
    }
}

void Labirint::printPoint(Console& console, Point& p)
{
    SHORT x, y;
    CONSOLE_SCREEN_BUFFER_INFO csbi = console.getCsbi();

    x = -(console.getCenterX()) + p.x + ((csbi.dwSize.X - (Constants::x)) / 2);
    y = -(console.getCenterY()) + p.y + ((csbi.dwSize.Y - (Constants::y)) / 2) + 1;

    console.printStrCenter(wstrObject(m_labirint[p.z][p.y][p.x]), x + 2, y);
}

void Labirint::inFile()
{
    for (int i = 0; i < Constants::z; ++i)
    {
        for (int j = 0; j < Constants::y; ++j)
        {
            for (int k = 0; k < Constants::x; ++k)
            {
                m_f << static_cast<char>(m_labirint[i][j][k]);
            }
            m_f << "\n";
        }
    }
}

void Labirint::outFile()
{
    for(int i = 0; i < Constants::z; ++i)
    for (int j = 0; j < Constants::y; ++j)
    {
        for (int k = 0; k < Constants::x; ++k)
        {
            char ch;
            m_f >> ch;
            m_labirint[i][j][k] = static_cast<Objects>(ch);
        }
    }
}

bool Labirint::genNew(Console& console)
{
    while (true)
    {
        printMaze(console, 0);


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
    // Очистка верхней строки, где выводится сообщение пользователю
    console.clear_zone(1, 36, 0, -Constants::y / 2 - 3);

    if (isLabirintLoaded)
    printMaze(console, 0);

    std::wstring str;
    short clear_zone_size;
    if (isLabirintLoaded)
        clear_zone_size = 6;
    else
        clear_zone_size = 10;

    short str_size = 20;

    console.clear_zone(clear_zone_size, str_size, 0, -5);

        while (true)
        {
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
                printMaze(console, 0);
                return true;
            case '2':
                create();

                genNew(console);

                saveNew(console);

                return true;
            case '3':
                if (isLabirintLoaded)
                {
                    printMaze(console, 0);
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

bool Labirint::settingsMenu(Console& console, bool isLabirintLoaded)
{

    if (isLabirintLoaded)
        printMaze(console, 0);

    std::wstring wstr;
    short clear_zone_size;
    if (isLabirintLoaded)
        clear_zone_size = 6;
    else
        clear_zone_size = 10;
    short str_size = 20;

    console.clear_zone(clear_zone_size, str_size, 0, -5);
    while (true)
    {
        // Верхняя линия
        wstr = L"\u250c";
        for (int i = 0; i < str_size; ++i)
            wstr += L"\u2500";
        wstr += L"\u2510";
        console.printStrCenter(wstr, 0, -5);

        wstr = L"\u2502                    \u2502";
        console.printStrCenter(wstr, 0, -4);

        wstr = L"\u2502     Labirint2D     \u2502";
        console.printStrCenter(wstr, 0, -3);

        wstr = L"\u2502                    \u2502";
        console.printStrCenter(wstr, 0, -2);

        wstr = L"\u2502      map size      \u2502";
        console.printStrCenter(wstr, 0, -1);

        wstr = L"\u2502 Back to main menu  \u2502";
        console.printStrCenter(wstr, 0, 0);

        // Нижняя линия
        wstr = L"\u2514";
        for (int i = 0; i < str_size; ++i)
            wstr += L"\u2500";

        wstr += L"\u2518";
        console.printStrCenter(wstr, 0, 1);

        int choice = directInput();
        switch (choice)
        {
        case '1':

            return true;
        case '2':
            if (isLabirintLoaded)
                 printMaze(console, 0);
             else
             {
                 clear_zone_size = 7;
                 console.clear_zone(clear_zone_size, str_size + 2, 0, -5);
             }
            return true;
        }
    }
}


std::wstring Labirint::walk(Console& console,Point& p)
    {
    
    std::wstring msg;
    Keys key;
    int map_mathRoot = square(Constants::z);
    key = static_cast<Keys>(directInput());

    if (key == Keys::ARROW_UP)
    {
        if (m_labirint[p.z][p.y - 1][p.x] == Objects::EMPTY)
        {
            if (p.y - 1 == 0)
            {
                m_labirint[p.z][p.y][p.x] = Objects::EMPTY;

                p.z -= map_mathRoot;
                p.y = Constants::y - 2;
                printMaze(console, p.z);

                m_labirint[p.z][p.y][p.x] = Objects::HERO;
                printPoint(console, p);
            }
            else
            {
                m_labirint[p.z][p.y][p.x] = Objects::EMPTY;
                printPoint(console, p);

                p.y = p.y - 1;
                m_labirint[p.z][p.y][p.x] = Objects::HERO;
                printPoint(console, p);
            }

            msg = L"";
        }
        else
        {
            msg = L"You can't move higher.\n";
        }
    }

    else if (key == Keys::ARROW_LEFT)
    {
        if (m_labirint[p.z][p.y][p.x - 1] == Objects::EMPTY)
        {
            if (p.x - 1 == 0)
            {
                m_labirint[p.z][p.y][p.x] = Objects::EMPTY;

                p.z -= 1;
                p.x = Constants::x - 2;
                printMaze(console, p.z);

                m_labirint[p.z][p.y][p.x] = Objects::HERO;
                printPoint(console, p);
            }
            else
            {
                m_labirint[p.z][p.y][p.x] = Objects::EMPTY;
                printPoint(console, p);

                p.x = p.x - 1;
                m_labirint[p.z][p.y][p.x] = Objects::HERO;
                printPoint(console, p);
            }
            msg = L"";
        }
        else
        {
            msg = L"You can't move to the left.\n";
        }
    }

    else if (key == Keys::ARROW_BACK)
    {
        if (m_labirint[p.z][p.y + 1][p.x] == Objects::EMPTY)
        {
            if (p.y + 1 == Constants::y - 1)
            {
                m_labirint[p.z][p.y][p.x] = Objects::EMPTY;

                p.z += map_mathRoot;
                p.y = 1;
                printMaze(console, p.z);

                m_labirint[p.z][p.y][p.x] = Objects::HERO;
                printPoint(console, p);
            }
            else
            {
                m_labirint[p.z][p.y][p.x] = Objects::EMPTY;
                printPoint(console, p);


                p.y = p.y + 1;
                m_labirint[p.z][p.y][p.x] = Objects::HERO;
                printPoint(console, p);
            }
            msg = L"";
        }
        else
        {
            msg = L"You can't move to the lower.\n";
        }
    }

    else if (key == Keys::ARROW_RIGHT)
    {
        if (m_labirint[p.z][p.y][p.x + 1] == Objects::EMPTY)
        {
            if (p.x + 1 == Constants::x - 1)
            {
                m_labirint[p.z][p.y][p.x] = Objects::EMPTY;
                
                p.z += 1;
                p.x = 1;
                printMaze(console, p.z);

                m_labirint[p.z][p.y][p.x] = Objects::HERO;
                printPoint(console, p);
            }
            else
            {
                m_labirint[p.z][p.y][p.x] = Objects::EMPTY;
                printPoint(console, p);

                p.x = p.x + 1;
                m_labirint[p.z][p.y][p.x] = Objects::HERO;
                printPoint(console, p);
            }
            msg = L"";
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