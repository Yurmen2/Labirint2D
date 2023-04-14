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
        std::cout << '\n';
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
    void setPoint(int& ax, int& ay, const Objects object)
    {
        m_labirint[ax][ay] = object;
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

    std::string walk(int &ax, int &ay)
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
            if (m_labirint[ax - 1][ay] == Objects::EMPTY)
            {
                m_labirint[ax][ay] = Objects::EMPTY;
                ax = ax - 1;
                m_labirint[ax][ay] = Objects::HERO;
            }
            else
            {
                msg = "You can't move higher.\n";
            }
        }
        
        else if (key == Keys::ARROW_LEFT)
        {
            if (m_labirint[ax][ay - 1] == Objects::EMPTY)
            {
                m_labirint[ax][ay] = Objects::EMPTY;
                ay = ay - 1;
                m_labirint[ax][ay] = Objects::HERO;
            }
            else
            {
                msg = "You can't move to the left.\n";
            }
        }
        
        else if (key == Keys::ARROW_BACK)
        {
            if (m_labirint[ax + 1][ay] == Objects::EMPTY)
            {
                m_labirint[ax][ay] = Objects::EMPTY;
                ax = ax + 1;
                m_labirint[ax][ay] = Objects::HERO;
            }
            else
            {
                msg = "You can't move to the lower.\n";
            }
        }
        
        else if (key == Keys::ARROW_RIGHT)
        {
            if (m_labirint[ax][ay + 1] == Objects::EMPTY)
            {
                m_labirint[ax][ay] = Objects::EMPTY;
                ay = ay + 1;
                m_labirint[ax][ay] = Objects::HERO;
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

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));

    Labirint labirint;

    // ћеню загрузки лабиринта
    backToMenu:
    bool isChoiceLabirint = true;
    while (isChoiceLabirint)
    {
        std::cout << "Labirint2D\n";
        std::cout << "1)Load maze from file.\n" <<
                     "2)Create maze.\n";
        std::cout << "Enter a option: ";

        int choice = inputNum(2);

        switch (choice)
        {
        case 1:
            labirint.outFile();
            isChoiceLabirint = false;
            break;

        case 2:
            labirint.create();

            bool isChoice;
            isChoice = true;
            
            while (isChoice)
                isChoice = labirint.genNew();

            isChoice = true;
            while (isChoice)
                isChoice = labirint.saveNew();

            isChoiceLabirint = false;
            break;
        }
    }

    while (true)
    {
        system("cls");
        labirint.print();

        std::cout << "\nLabirint2D\n";
        std::cout << "1)Start game\n" <<
                     "2)Maze menu\n" <<
                     "3)Exit\n";
        
        std::cout << "Enter a option: ";
        char choice = inputNum(3);

        std::string msg;
        switch (choice)
        {
        case 1:
            int ax, ay;

            std::cout << "Enter start point(x,y): ";
            ax = inputNum();
            ay = inputNum();

            labirint.setPoint(ax, ay, Objects::HERO);
            while (true)
            {
                system("cls");
                labirint.print();
                std::cout << msg;
                msg = labirint.walk(ax, ay);
                if (msg == "esc")
                    exit(0);
            }
            break;
        case 2:
            system("cls");
            goto backToMenu;
        case 3:
            exit(0);
        }
    }

    return 0;
}