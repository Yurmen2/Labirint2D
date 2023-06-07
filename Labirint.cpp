#include "Labirint.h"

extern MapSize mapSize;

Labirint::Labirint(std::wstring filename)
    :m_f{ filename }, m_labirint{mapSize.z, std::vector<std::vector<Objects>>(mapSize.y, std::vector<Objects>(mapSize.x))}
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

void Labirint::create(SHORT mode)
{
    int map_size = mapSize.z;
    int map_mathRoot = square(mapSize.z);

    // Внешний счетчик для определения боковых локаций
    int n, a;
    n = a = 1;

    // Внутренний счетчик для определения боковых локаций, 3 -- Внешний_счетчик += 1
    int nnn, aaa;
    nnn = aaa = 0;
    if (map_mathRoot == -1)
        exit(-1);

    if (mode == 1)
    {
        for (int i = 1; i <= map_size; ++i)
        {
            for (int j = 0; j < mapSize.y; ++j)
            {
                for (int k = 0; k < mapSize.x; ++k)
                {
                    // Угловые края карты
                    if (i == 1 || i == map_mathRoot || i == mapSize.z + 1 - map_mathRoot || i == mapSize.z)
                    {
                        // Проходы верхний левый угол
                        if (i == 1 && j == mapSize.y - 1 && k == mapSize.x / 2)
                            m_labirint[i - 1][j][k] = Objects::EMPTY;
                        else if (i == 1 && j == mapSize.y / 2 && k == mapSize.x - 1)
                            m_labirint[i - 1][j][k] = Objects::EMPTY;

                        // Проходы верхний правый угол
                        else if (i == map_mathRoot && j == mapSize.y - 1 && k == mapSize.x / 2)
                            m_labirint[i - 1][j][k] = Objects::EMPTY;
                        else if (i == map_mathRoot && j == mapSize.y / 2 && k == 0)
                            m_labirint[i - 1][j][k] = Objects::EMPTY;

                        // Проходы нижний левый угол
                        else if (i == mapSize.z + 1 - map_mathRoot && j == 0 && k == mapSize.x / 2)
                            m_labirint[i - 1][j][k] = Objects::EMPTY;
                        else if (i == mapSize.z + 1 - map_mathRoot && j == mapSize.y / 2 && k == mapSize.x - 1)
                            m_labirint[i - 1][j][k] = Objects::EMPTY;

                        // Проходы нижний правый угол
                        else if (i == mapSize.z && j == 0 && k == mapSize.x / 2)
                            m_labirint[i - 1][j][k] = Objects::EMPTY;
                        else if (i == mapSize.z && j == mapSize.y / 2 && k == 0)
                            m_labirint[i - 1][j][k] = Objects::EMPTY;

                        // Заполнение края карты стенами
                        else if (j == 0 || j == mapSize.y - 1)
                            m_labirint[i - 1][j][k] = Objects::WALL;
                        else if (k == 0 || k == mapSize.x - 1)
                            m_labirint[i - 1][j][k] = Objects::WALL;

                        // Заполнение остальной части карты
                        else
                        {
                            m_labirint[i - 1][j][k] = static_cast<Objects>(object_id[0]);
                        }

                    }
                    // Верхние и нижние края карты 
                    else if ((i > 1 && i < map_mathRoot) || (i > (mapSize.z + 1 - map_mathRoot) && i << mapSize.z))
                    {
                        // Проходы верхние края
                        if ((i > 1 && i < map_mathRoot) && j == mapSize.y / 2 && k == 0)
                            m_labirint[i - 1][j][k] = Objects::EMPTY;
                        else if ((i > 1 && i < map_mathRoot) && j == mapSize.y / 2 && k == mapSize.x - 1)
                            m_labirint[i - 1][j][k] = Objects::EMPTY;
                        else if ((i > 1 && i < map_mathRoot) && j == mapSize.y - 1 && k == mapSize.x / 2)
                            m_labirint[i - 1][j][k] = Objects::EMPTY;

                        // Проходы нижние края
                        else if ((i > (mapSize.z + 1 - map_mathRoot) && i << mapSize.z) && j == mapSize.y / 2 && k == 0)
                            m_labirint[i - 1][j][k] = Objects::EMPTY;
                        else if ((i > (mapSize.z + 1 - map_mathRoot) && i << mapSize.z) && j == mapSize.y / 2 && k == mapSize.x - 1)
                            m_labirint[i - 1][j][k] = Objects::EMPTY;
                        else if ((i > (mapSize.z + 1 - map_mathRoot) && i << mapSize.z) && j == 0 && k == mapSize.x / 2)
                            m_labirint[i - 1][j][k] = Objects::EMPTY;

                        else if (j == 0 || j == mapSize.y - 1)
                            m_labirint[i - 1][j][k] = Objects::WALL;
                        else if (k == 0 || k == mapSize.x - 1)
                            m_labirint[i - 1][j][k] = Objects::WALL;

                        else
                        {
                            m_labirint[i - 1][j][k] = static_cast<Objects>(object_id[0]);
                        }

                    }
                    // левые края карты
                    else if (i == 1 + (map_mathRoot * n))
                    {
                        if (j == mapSize.y / 2 && k == mapSize.x - 1)
                        {
                            m_labirint[i - 1][j][k] = Objects::EMPTY;
                            ++nnn;
                        }
                        else if (j == 0 && k == mapSize.x / 2)
                        {
                            m_labirint[i - 1][j][k] = Objects::EMPTY;
                            ++nnn;
                        }
                        else if (j == mapSize.y - 1 && k == mapSize.x / 2)
                        {
                            m_labirint[i - 1][j][k] = Objects::EMPTY;
                            ++nnn;
                        }

                        else if (j == 0 || j == mapSize.y - 1)
                            m_labirint[i - 1][j][k] = Objects::WALL;
                        else if (k == 0 || k == mapSize.x - 1)
                            m_labirint[i - 1][j][k] = Objects::WALL;

                        else
                        {
                            m_labirint[i - 1][j][k] = static_cast<Objects>(object_id[0]);
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
                        if (j == mapSize.y / 2 && k == 0)
                        {
                            m_labirint[i - 1][j][k] = Objects::EMPTY;
                            ++aaa;
                        }
                        else if (j == 0 && k == mapSize.x / 2)
                        {
                            m_labirint[i - 1][j][k] = Objects::EMPTY;
                            ++aaa;
                        }
                        else if (j == mapSize.y - 1 && k == mapSize.x / 2)
                        {
                            m_labirint[i - 1][j][k] = Objects::EMPTY;
                            ++aaa;
                        }

                        else if (j == 0 || j == mapSize.y - 1)
                            m_labirint[i - 1][j][k] = Objects::WALL;
                        else if (k == 0 || k == mapSize.x - 1)
                            m_labirint[i - 1][j][k] = Objects::WALL;

                        else
                        {
                            m_labirint[i - 1][j][k] = static_cast<Objects>(object_id[0]);
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
                        if (j == mapSize.y / 2 && k == 0)
                            m_labirint[i - 1][j][k] = Objects::EMPTY;
                        else if (j == 0 && k == mapSize.x / 2)
                            m_labirint[i - 1][j][k] = Objects::EMPTY;
                        else if (j == mapSize.y - 1 && k == mapSize.x / 2)
                            m_labirint[i - 1][j][k] = Objects::EMPTY;
                        else if (j == mapSize.y / 2 && k == mapSize.x - 1)
                            m_labirint[i - 1][j][k] = Objects::EMPTY;


                        else if (j == 0 || j == mapSize.y - 1)
                            m_labirint[i - 1][j][k] = Objects::WALL;
                        else if (k == 0 || k == mapSize.x - 1)
                            m_labirint[i - 1][j][k] = Objects::WALL;

                        else
                        {
                            m_labirint[i - 1][j][k] = static_cast<Objects>(object_id[0]);
                        }
                    }
                }
            }

            // Закрашивание одиноких проходов без выхода
           /* for (int j = 1; j < mapSize.y; ++j)
            {
                for (int k = 1; k < mapSize.x; k++)
                {
                    if (j >= 1 && j < mapSize.y - 1 && k >= 1 && k < mapSize.x - 1)
                    {
                        if (m_labirint[i - 1][j - 1][k] == Objects::WALL && m_labirint[i - 1][j + 1][k] == Objects::WALL &&
                            m_labirint[i - 1][j][k - 1] == Objects::WALL && m_labirint[i - 1][j][k + 1] == Objects::WALL)
                            m_labirint[i - 1][j][k] = Objects::WALL;
                    }
                }
            }*/
        }
    }
    else if (mode == 2)
    {

    }
    else if (mode == 3)
    {
        for (int i = 1; i < 2; ++i)
        {
            for (int j = 0; j < mapSize.y; ++j)
            {
                for (int k = 0; k < mapSize.x; ++k)
                {
                    if (j == 0 || j == mapSize.y - 1)
                        m_labirint[i - 1][j][k] = Objects::WALL;
                    else if (k == 0 || k == mapSize.x - 1)
                        m_labirint[i - 1][j][k] = Objects::WALL;
                    
                    else
                        m_labirint[i - 1][j][k] = static_cast<Objects>(object_id[0]);
                }
            }
        }
    }
}

void Labirint::printMaze(Console& console, int i)
{
    const CONSOLE_SCREEN_BUFFER_INFO csbi = console.getCsbi();

    for (int j = 0; j < mapSize.y; ++j)
    {
        std::wstring str;

        //// Вывод ~ в первой и последней строке карты ПОСИМВОЛЬНО
        //if (i == 0)
        //{
        //    for (int aaa = 0; aaa < (mapSize.x * 2 + 2); ++aaa)
        //    {
        //        str = "~";
        //        x = -(console.getCenterX()) + aaa + ((csbi.dwSize.X - (mapSize.x * 2)) / 2) - 1;
        //        y = -(console.getCenterY()) + ((csbi.dwSize.Y - (mapSize.y)) / 2) - 1;
        //        console.printStrCenter(str, x, y);
        //    }
        //    
        //    for (int aaa = 0; aaa < (mapSize.x * 2 + 2); ++aaa)
        //    {
        //        str = "~";
        //        x = -(console.getCenterX()) + aaa + ((csbi.dwSize.X - (mapSize.x * 2)) / 2) - 1;
        //        y = -(console.getCenterY()) + ((csbi.dwSize.Y - (mapSize.y)) / 2) + mapSize.y;
        //        console.printStrCenter(str, x, y);
        //    }

        //// Основной вывод лабиринта ПОСИМВОЛЬНО
        //for (int iii = 0; iii < mapSize.x; ++iii)
        //{
        //    
        //    str = stringObject(m_labirint[i][iii]);
        //    SHORT x = -(console.getCenterX()) + iii + space + ((csbi.dwSize.X - (mapSize.x * 2)) / 2);
        //    SHORT y = -(console.getCenterY()) + i + ((csbi.dwSize.Y - (mapSize.y)) / 2);
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
            for (int aaa = 0; aaa < (mapSize.x); ++aaa)
                str += L"\u2500";
            
            // Закругляющая правая верхняя линия
            str += L"\u2510";
            console.printStrCenter(str, 0, -(console.getCenterY()) + ((csbi.dwSize.Y - (mapSize.y)) / 2));


            // Закругляющая левая нижняя линия
            str[0] = L'\u2514';
            // Закругляющая правая нижняя линия
            str[mapSize.x + 1] = L'\u2518';
            console.printStrCenter(str, 0, -(console.getCenterY()) + ((csbi.dwSize.Y - (mapSize.y)) / 2) + mapSize.y + 1);
        }

        // Вертикальная линия
        str = L"\u2502";

        // Основной вывод лабиринта ПОСТРОЧНО
        for (int k = 0; k < mapSize.x; ++k)
            str += wstrObject(m_labirint[i][j][k]);
        // Вертикальная линия
        str += L"\u2502";
        console.printStrCenter(str, 0, -(console.getCenterY()) + j + ((csbi.dwSize.Y - (mapSize.y)) / 2) + 1);
    }
}

void Labirint::printPoint(Console& console, Point& p)
{
    SHORT x, y;
    CONSOLE_SCREEN_BUFFER_INFO csbi = console.getCsbi();

    x = -(console.getCenterX()) + p.x + ((csbi.dwSize.X - (mapSize.x)) / 2);
    y = -(console.getCenterY()) + p.y + ((csbi.dwSize.Y - (mapSize.y)) / 2) + 1;

    console.printStrCenter(wstrObject(m_labirint[p.z][p.y][p.x]), x + 2, y);
}

void Labirint::inFile()
{
    for (int i = 0; i < mapSize.z; ++i)
    {
        for (int j = 0; j < mapSize.y; ++j)
        {
            for (int k = 0; k < mapSize.x; ++k)
            {
                m_f << static_cast<int>(static_cast<Objects>(m_labirint[i][j][k]));
            }
            m_f << "\n";
        }
        m_f << "\n";
    }
}

void Labirint::outFile()
{

    for (int i = 0; i < mapSize.z; ++i)
    {
        for (int j = 0; j < mapSize.y; ++j)
        {
            for (int k = 0; k < mapSize.x; ++k)
            {
                char ch;
                m_f >> ch;
                if (ch != '\n')
                {
                    ch = ch - '0';
                    m_labirint[i][j][k] = static_cast<Objects>(static_cast<int>(ch));
                }
            }
        }
    }
}

bool Labirint::genNew(Console& console, SHORT mode)
{
    while (true)
    {
        printMaze(console, 0);


        std::wstring str = L"Generate a new maze? Y/N";
        console.printStrCenter(str, 0, -mapSize.y / 2 - 3);

        char ch = directInput();

        int str_size = static_cast<int>(str.length());
        switch (ch)
        {
        case 'Y':
            create(mode);
            console.clear_zone(1, str_size, 0, -mapSize.y / 2 - 3);
            break;
        case 'N':
            console.clear_zone(1, str_size, 0, -mapSize.y / 2 - 3);
            return false;
        }
    }
}

bool Labirint::saveNew(Console& console)
{
    while (true)
    {
        printMaze(console, 0);

        std::wstring str = L"Save maze in file? Y/N";
        console.printStrCenter(str, 0, -mapSize.y / 2 - 3);

        char ch = directInput();

        int str_size = static_cast<int>(str.length());
        switch (ch)
        {
        case 'Y':
            inFile();
        case 'N':
            console.clear_zone(1 ,str_size, 0, -mapSize.y / 2 - 3);
            return false;
        }
    }
}

SHORT Labirint::modeMenu(Console& console)
{
    short clear_zone_size = 12;
    short str_size = 35;

    console.clear_zone(clear_zone_size, str_size, 0, -5);

    // Верхняя линия
    std::wstring str = L"\u250c";
    for (int i = 0; i < str_size; ++i)
    {
        str += L"\u2500";
    }
    str += L"\u2510";
    console.printStrCenter(str, 0, -5);


    str = L"\u2502                                   \u2502";
    console.printStrCenter(str, 0, -4);

    str = L"\u2502            Labirint2D             \u2502";
    console.printStrCenter(str, 0, -3);

    str = L"\u2502                                   \u2502";
    console.printStrCenter(str, 0, -2);

    str = L"\u2502 1 - Empty location with aisles    \u2502";
    console.printStrCenter(str, 0, -1);

    str = L"\u2502 2 - Maze                          \u2502";
    console.printStrCenter(str, 0, 0);

    str = L"\u2502 3 - Snake                         \u2502";
    console.printStrCenter(str, 0, 1);

    str = L"\u2502 Select game mode:                 \u2502";
    console.printStrCenter(str, 0, 2);

    str = L"\u2502                                   \u2502";
    console.printStrCenter(str, 0, 3);

    // Нижняя линия
    str = L"\u2514";
    for (int i = 0; i < str_size; ++i)
    {
        str += L"\u2500";
    }
    str += L"\u2518";
    console.printStrCenter(str, 0, 3);

    SHORT mode;
    mode = inputNum(console, 1, 2, 3);

    console.clear_zone(clear_zone_size, str_size + 2, 0, -5);

    return mode;
}

bool Labirint::mazeMenu(Console& console, bool isLabirintLoaded, SHORT mode)
{
    // Очистка верхней строки, где выводится сообщение пользователю
    console.clear_zone(1, 36, 0, -mapSize.y / 2 - 3);

    std::wstring str;
    short clear_zone_size = 10;

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

            str = L"\u2502 Back to main menu  \u2502";
            console.printStrCenter(str, 0, 1);

            str = L"\u2502                    \u2502";
            console.printStrCenter(str, 0, 2);

            // Нижняя линия
            str = L"\u2514";
            for (int i = 0; i < str_size; ++i)
            {
                str += L"\u2500";
            }
            str += L"\u2518";
            console.printStrCenter(str, 0, 3);

            int choice = directInput();
            switch (choice)
            {
            case '1':
                outFile();
                printMaze(console, 0);
                
                str = L"Press any key to continue///";
                console.printStrCenter(str, 0, -mapSize.y / 2 - 3);

                directInput();

                console.clear_zone(109, 39, 0, 0);


                return true;
            case '2':

                console.clear_zone(clear_zone_size, str_size + 2, 0, -5);

                create(mode);

                if (mode == 2)
                {
                    genNew(console, mode);
                    saveNew(console);
                }
                else
                    printMaze(console, 0);

                str = L"Press any key to continue///";
                console.printStrCenter(str, 0, -mapSize.y / 2 - 3);
                directInput();

                console.clear_zone(109, 39, 0, 0);

                return true;
            case '3':
                console.clear_zone(clear_zone_size, str_size + 2, 0, -5);
                return true;
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
        console.printStrCenter(msg, 0, -mapSize.y / 2 - 3);
}

bool Labirint::settingsMenu(Console& console)
{
    std::wstring wstr;
    short clear_zone_size = 10;
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

        wstr = L"\u2502      Map size      \u2502";
        console.printStrCenter(wstr, 0, -1);

        wstr = L"\u2502 Back to main menu  \u2502";
        console.printStrCenter(wstr, 0, 0);

        wstr = L"\u2502                    \u2502";
        console.printStrCenter(wstr, 0, 1);

        // Нижняя линия
        wstr = L"\u2514";
        for (int i = 0; i < str_size; ++i)
            wstr += L"\u2500";

        wstr += L"\u2518";
        console.printStrCenter(wstr, 0, 2);

        int choice = directInput();
        std::wstring wstr2, wstr3;
        switch (choice)
        {
        case '1':

            console.clear_zone(109, 39, 0, 0);

            for (int i = 0; i < 3; ++i)
            {
                clear_zone_size = 8;
                str_size = 41;
                console.clear_zone(clear_zone_size, str_size + 2, 0, -5);

                // Верхняя линия
                wstr = L"\u250c";
                for (int i = 0; i < str_size; ++i)
                    wstr += L"\u2500";
                wstr += L"\u2510";
                console.printStrCenter(wstr, 0, -5);

                wstr = L"\u2502                                         \u2502";
                console.printStrCenter(wstr, 0, -4);

                wstr = L"\u2502               Labirint2D                \u2502";
                console.printStrCenter(wstr, 0, -3);

                wstr = L"\u2502                                         \u2502";
                console.printStrCenter(wstr, 0, -2);

                if (i == 0)
                {
                    wstr3 = L"\u2502                 Length                  \u2502";
                    wstr2 = L"\u2502               x(5 - 110):               \u2502";
                    console.printStrCenter(wstr3, 0, -1);
                    console.printStrCenter(wstr2, 0, 0);

                }
                else if (i == 1)
                {
                    wstr3 = L"\u2502                 Height                  \u2502";
                    wstr2 = L"\u2502               y(5 - 40):                \u2502";
                    console.printStrCenter(wstr3, 0, -1);
                    console.printStrCenter(wstr2, 0, 0);

                }
                else if (i == 2)
                {
                    wstr3 = L"\u2502   Number of blocks, only square root!   \u2502";
                    wstr2 = L"\u2502               z(9 - 100):               \u2502";
                    console.printStrCenter(wstr3, 0, -1);
                    console.printStrCenter(wstr2, 0, 0);

                }

                wstr = L"\u2502                                         \u2502";
                console.printStrCenter(wstr, 0, 1);

                // Нижняя линия
                wstr = L"\u2514";
                for (int i = 0; i < str_size; ++i)
                    wstr += L"\u2500";

                wstr += L"\u2518";
                console.printStrCenter(wstr, 0, 2);

                if (i == 0)
                    mapSize.x = inputNum(console, 6, 0, 110, 5);
                else if (i == 1)
                    mapSize.y = inputNum(console, 5, 0, 40, 5);
                else if (i == 2)
                    while(1)
                    {
                        mapSize.z = inputNum(console, 6, 0, 100, 9);
                        if (square(mapSize.z) != -1)
                        {
                            console.clear_zone(1, 30 + 2, 0, -mapSize.y / 2 - 5);
                            break;
                        }
                        else
                        {
                            wstr = L"Incorrect enter. Retry again.";
                            console.printStrCenter(wstr, 0, -mapSize.y / 2 - 5);
                            console.clear_zone(1, 4, 6 + 2, 0);
                        }
                    }
            }
            console.clear_zone(2, str_size, 0, -1);

            wstr =  L"             x=" + std::to_wstring(mapSize.x) + L" y=" + 
                    std::to_wstring(mapSize.y) + L" z=" + std::to_wstring(mapSize.z) + 
                    L"              ";

            console.printStrCenter(wstr, 0, -1);

            directInput();
            console.clear_zone(clear_zone_size, str_size + 2, 0, -5);
            return true;

        case '2':
            console.clear_zone(clear_zone_size, str_size + 2, 0, -5);
            return true;
        }
    }
}


std::wstring Labirint::walk(Console& console,Point& p)
    {
    
    std::wstring msg;
    Keys key;
    int map_mathRoot = square(mapSize.z);
    key = static_cast<Keys>(directInput());

    if (key == Keys::ARROW_UP)
    {
        if (m_labirint[p.z][p.y - 1][p.x] == Objects::EMPTY)
        {
            if (p.y - 1 == 0)
            {
                m_labirint[p.z][p.y][p.x] = Objects::EMPTY;

                p.z -= map_mathRoot;
                p.y = mapSize.y - 2;
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
                p.x = mapSize.x - 2;
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
            if (p.y + 1 == mapSize.y - 1)
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
            if (p.x + 1 == mapSize.x - 1)
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

std::wstring Labirint::slide(Console& console, Point& p)
{
    std::wstring msg = L"";


    return msg;
}
