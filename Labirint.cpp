#include "Labirint.h"

Labirint::Labirint(std::string filename)
    :m_f{ filename }, m_labirint{Constants::y, std::vector<Objects>(Constants::x)}
{
    if (!m_f)
    {
        std::ofstream ff(filename);
        m_f.open(filename, std::ios::in | std::ios::out);
    }

    if (!m_f)
    {
        std::cerr << filename, " could not be opened\n";
        exit(-1);
    }
}

void Labirint::create()
{
    for (int i = 0; i < Constants::y; i++)
    {
        for (int iii = 0; iii < Constants::x; iii++)
        {
            m_labirint[i][iii] = static_cast<Objects>(object_id[rand() % 2]);
        }
    }
}

void Labirint::print(Console& console)
{
    for (int i = 0; i < Constants::y; i++)
    {
        if (i == 0 || i == Constants::y)
        {
            for (int a = 0; a < Constants::y + 2; a++)

                std::cout << "~ ";
            std::cout << '\n';
        }
        std::cout << "| ";
        for (int iii = 0; iii < Constants::x; iii++)
        {
            std::cout << stringObject(m_labirint[i][iii]) << " ";
        }
        std::cout << "|\n";
    }
    for (int a = 0; a < Constants::y + 2; a++)
        std::cout << "~ ";
    std::cout << "\n\n";
}

void Labirint::inFile()
{
    for (int i = 0; i < Constants::y; i++)
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
        system("cls");
        print(console);


        std::string str = "Generate a new maze? Y/N";
        console.printStrCenter(str);

        char ch = directInput();
        switch (ch)
        {
        case 'Y':
            create();
            return true;

        case 'N':
            return false;
        }
    }
}

bool Labirint::saveNew(Console& console)
{
    while (true)
    {
        system("cls");
        print(console);

        std::string str = "Save maze in file? Y/N";
        console.printStrCenter(str);

        char ch = directInput();
        switch (ch)
        {
        case 'Y':
            inFile();
        case 'N':
            return false; // Умышленный fall-through: кейс N не выполняет никакой задачи
        }
    }
}

bool Labirint::mazeMenu(Console& console, bool isLabirintLoaded)
{
    while (true)
    {
        system("cls");

        if (isLabirintLoaded)
            print(console);


        std::string str;
        str = "Labirint2D";
        console.printStrCenter(str, 0, -3);

        str = "Load maze from file";
        console.printStrCenter(str, 0, -1);

        str = "Create maze";
        console.printStrCenter(str);

        if (isLabirintLoaded)
        {
            str = "Back to main menu";
            console.printStrCenter(str, 0, 1);
        }

        int choice = directInput();
        switch (choice)
        {
        case '1':
            if (isLabirintLoaded)
                return true;
            else
            {
                outFile();
                return true;
            }
        case '2':
            create();

            bool isChoice;
            isChoice = true;

            while (isChoice)
                isChoice = genNew(console);

            isChoice = true;
            while (isChoice)
                isChoice = saveNew(console);

            return true;
        case '3':
            if (isLabirintLoaded)
                return true;
            break;
        }
    }
}

void Labirint::mainMenu(Console& console, std::string& msg)
{
    std::string str;
    str = "Labirint2D";
    console.printStrCenter(str, 0, -3);

    str = "Start";
    console.printStrCenter(str, 0, -1);

    str = "Maze menu";
    console.printStrCenter(str);

    str = "Settings";
    console.printStrCenter(str, 0, 1);

    str = "Exit";
    console.printStrCenter(str, 0, 2);

    if (msg.length() > 0)
    {
        console.printStrCenter(msg, 0, 4);

    }
}


std::string Labirint::walk(Point& p)
{
    std::string msg;
    Keys key;

    key = static_cast<Keys>(directInput());

    if (key == Keys::ARROW_UP)
    {
        if (m_labirint[p.x - 1][p.y] == Objects::EMPTY)
        {
            m_labirint[p.x][p.y] = Objects::EMPTY;
            p.x = p.x - 1;
            m_labirint[p.x][p.y] = Objects::HERO;
        }
        else
        {
            msg = "You can't move higher.\n";
        }
    }

    else if (key == Keys::ARROW_LEFT)
    {
        if (m_labirint[p.x][p.y - 1] == Objects::EMPTY)
        {
            m_labirint[p.x][p.y] = Objects::EMPTY;
            p.y = p.y - 1;
            m_labirint[p.x][p.y] = Objects::HERO;
        }
        else
        {
            msg = "You can't move to the left.\n";
        }
    }

    else if (key == Keys::ARROW_BACK)
    {
        if (m_labirint[p.x + 1][p.y] == Objects::EMPTY)
        {
            m_labirint[p.x][p.y] = Objects::EMPTY;
            p.x = p.x + 1;
            m_labirint[p.x][p.y] = Objects::HERO;
        }
        else
        {
            msg = "You can't move to the lower.\n";
        }
    }

    else if (key == Keys::ARROW_RIGHT)
    {
        if (m_labirint[p.x][p.y + 1] == Objects::EMPTY)
        {
            m_labirint[p.x][p.y] = Objects::EMPTY;
            p.y = p.y + 1;
            m_labirint[p.x][p.y] = Objects::HERO;
        }
        else
        {
            msg = "You can't move to the right.\n";
        }
    }

    else if (key == Keys::ESC)
    {
        msg = "esc";
    }

    return msg;
}