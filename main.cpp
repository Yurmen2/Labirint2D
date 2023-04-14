// Labirint - ѕрограмма, создающа€ 2д лабиринт в двумерном массиве.
// √енерирует лабиринт(размеры указываютс€ переменными str и tab в constants.h)
// ѕредлагает возможные действи€ с ним 

#include <iostream>
#include <fstream>
#include <time.h>
#include <conio.h>
#include <cctype>
#include "constants.h"

// ћакросы дл€ быстрого преобразовани€
#define to_key(x) static_cast<Keys>(x)
#define to_object(x) static_cast<Objects>(x)

enum class Keys
{
    ARROW_UP    = 72,
    ARROW_LEFT  = 75,
    ARROW_BACK  = 80,
    ARROW_RIGHT = 77,
    ESC         = 27,
};

enum class Objects
{
    WALL  = 'W',
    EMPTY = 'E',
    HERO  = '*',
};

static int object_id[]
{
    'W',
    'E',
    '*',
};

struct Point
{
    int x;
    int y;
};

// получение целочисленного значени€ с обработкой ввода
int inputNum(int limit = 0)
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
    std::cout << "x:";
    point.x = inputNum();
    std::cout << "y: ";
    point.y = inputNum();
}


std::string stringObject(Objects object)
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

class Labirint
{
private:
    Objects m_labirint[str][tab];
    std::fstream m_f;

public:

    Labirint(std::string filename = "labirint.txt")
        :m_f{ filename }, m_labirint{to_object(0)}
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
   
    // создание случайного лабиринта: стены и проходы
    void create()
    {
        for (int i = 0; i < str; i++)
        {
            for (int iii = 0; iii < tab; iii++)
            {
                m_labirint[i][iii] = to_object(object_id[rand() % 2]);
            }
        }
    }

    // ¬ывод изображени€ лабиринта
    void print()
    {
        for (int i = 0; i < str; i++)
        {
            if (i == 0 || i == str)
            {
                for (int a = 0; a < str + 2; a++)
                    std::cout << "~ ";
                std::cout << '\n';
            }
            std::cout << "| ";
            for (int iii = 0; iii < tab; iii++)
            {
                std::cout << stringObject(m_labirint[i][iii]) << " ";
            }
            std::cout << "|\n";
        }
        for (int a = 0; a < str + 2; a++)
            std::cout << "~ ";
        std::cout << "\n\n";
    }

    // «аписать данные лабиринта в файл
    void inFile()
    {
        for (int i = 0; i < str; i++)
        {
            for (int iii = 0; iii < tab; iii++)
            {
                m_f << static_cast<char>(m_labirint[i][iii]);
            }
            m_f << "\n";
        }
    }

    // считать данные лабиринта из файла
    void outFile()
    {
        for (int i = 0; i < str; i++)
        {
            for (int iii = 0; iii < tab; iii++)
            {
                char ch;
                m_f >> ch;
                m_labirint[i][iii] = static_cast<Objects>(ch);
            }
        }
    }

    // ”становить определенной точке в лабиринте значение value
    void setPoint(const Point& p, const Objects object)
    {
        m_labirint[p.x][p.y] = object;
    }

    // —прашивает пользовател€, нужно ли сгенерировать новый лабиринт
    bool genNew()
    {   
        while(true)
        {
            system("cls");
            print();

            std::cout << "Generate a new maze? Y/N:";

            char ch;
            std::cin >> ch;
            ch = toupper(ch);

            switch (ch)
            {
            case 'Y':
                create();
                std::cin.ignore(32767, '\n');
                return true;

            case 'N':
                std::cin.ignore(32767, '\n');
                return false;

            default:
                std::cin.ignore(32767, '\n');
                break;
            }
        }
    }

    // —прашивает пользовател€, сохранить ли получившийс€ лабиринт
    bool saveNew()
    {
        while (true)
        {
            system("cls");
            print();

            std::cout << "Save maze in file? Y/N:";

            char ch;
            std::cin >> ch;
            ch = toupper(ch);

            switch (ch)
            {
            case 'Y':
                inFile();
            case 'N':
                std::cin.ignore(32767, '\n');
                return false; // ”мышленный fall-through: кейс N не выполн€ет никакой задачи

            default:
                std::cin.ignore(32767, '\n');
                break;
            }
        }
    }

    bool mazeMenu(bool isLabirintLoaded)
    {
        while (true)
        {
            system("cls");

            if (isLabirintLoaded)
                print();

            std::cout << "Labirint2D\n";
            std::cout << "1)Load maze from file.\n" <<
                         "2)Create maze.\n";
            
            if (isLabirintLoaded)
                std::cout << "3)Back to main menu.\n";
            
            std::cout << "Enter a option: ";

            int choice;
            
            if (!isLabirintLoaded)
                choice = inputNum(2);
            else
                choice = inputNum(3);

            switch (choice)
            {
            case 1:
                if (isLabirintLoaded)
                    return true;
                else
                {
                    outFile();
                    return true;
                }
            case 2:
                create();

                bool isChoice;
                isChoice = true;

                while (isChoice)
                    isChoice = genNew();

                isChoice = true;
                while (isChoice)
                    isChoice = saveNew();

                return true;
            case 3:
                return true;
            default:
                std::cin.ignore(32767, '\n');
                break;
            }
        }
    }

    std::string walk(Point& p)
    {
        std::string msg;
        Keys key;
            
        // —читывание с клавиатуры напр€мую без Enter
        key = to_key(_getch());
        if (key == to_key(-32))
        {
            key = to_key(_getch());
            key = to_key(toupper(static_cast<char>(key)));
        }

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

};

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));
    rand();
    Labirint labirint;

    bool isLabirintLoaded = false;
    std::string msg = "";

    backToMenu:
    while (true)
    {

        system("cls");
        if (isLabirintLoaded)
            labirint.print();
        
        std::cout << "Labirint2D\n";
        std::cout << "1)Start game\n" <<
                     "2)Maze menu\n" <<
                     "3)Settings\n" << 
                     "4)Exit\n";
        std::cout << msg;

        std::cout << "Enter a option: ";
        char choice = inputNum(4);

        switch (choice)
        {
        case 1:
            if (!isLabirintLoaded)
                msg = "\nTo start, load the maze in Maze menu\n";
            else
            {
                system("cls");
                labirint.print();
                std::cout << "Enter start point(x, y): \n";
                Point point {};

                inputPoint(point);

                labirint.setPoint(point, Objects::HERO);
                while (true)
                {
                    system("cls");
                    labirint.print();
                    std::cout << msg;
                    msg = labirint.walk(point);
                    if (msg == "esc")
                    {
                        msg = "";
                        labirint.setPoint(point, Objects::EMPTY);
                        goto backToMenu;
                    }
                }
            }
            break;
        case 2:
           isLabirintLoaded = labirint.mazeMenu(isLabirintLoaded);
           msg = "";
           break;
        case 3:
            break;
        case 4:
            exit(0);
        }
    }

    return 0;
}