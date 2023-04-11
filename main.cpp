// Labirint - Программа, создающая 2д лабиринт в двумерном массиве.
// Генерирует лабиринт(размеры указываются переменными str и tab в constants.h)
// Предлагает возможные действия с ним(*= в разработке): 
// 1*)Найти возможные выходы из А в В 2*) Найти все выходы из А 3*)Найти самый короткий выход из А в В 4) режим прогулки(в перспективе мини-игра) 

#include <iostream>
#include <fstream>
#include <time.h>
#include <conio.h>
#include <cctype>
#include "constants.h"

// Макросы для быстрого преобразования
#define to_key(x) static_cast<Keys>(x)
#define to_int(x) static_cast<int>(x)

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
    WALL  = 1,
    EMPTY = 0,
    HERO  = 5,
};

class Labirint
{
private:
    int m_labirint[str][tab];
    std::fstream m_f;

public:

    Labirint(std::string filename = "labirint.txt")
        :m_f{filename}
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

    void create()
    {
        for (int i = 0; i < str; i++)
        {
            for (int iii = 0; iii < tab; iii++)
            {
                m_labirint[i][iii] = rand() % 2;
            }
        }
    }

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
                std::cout << m_labirint[i][iii] << " ";
            }
            std::cout << "|\n";
        }
        for (int a = 0; a < str + 2; a++)
            std::cout << "~ ";
        std::cout << '\n';
    }

    // Записать данные лабиринта в файл
    void write()
    {
        for (int i = 0; i < str; i++)
        {
            for (int iii = 0; iii < tab; iii++)
            {
                m_f << m_labirint[i][iii] << " ";
            }
            m_f << "\n";
        }
    }

    void read()
    {
        for (int i = 0; i < str; i++)
        {
            for (int iii = 0; iii < tab; iii++)
            {
                m_f >> m_labirint[i][iii];
            }
        }
    }

    // Установить определенной точке в лабиринте значение value
    void setPoint(int& ax, int& ay, const int value)
    {
        m_labirint[ax][ay] = value;
    }

    std::string walk(int &ax, int &ay)
    {
        std::string msg;
        Keys key;
            
        // Считывание с клавиатуры напрямую без Enter
        key = to_key(_getch());
        if (key == to_key(-32))
        {
            key = to_key(_getch());
            key = to_key(toupper(static_cast<char>(key)));
        }

        if (key == Keys::ARROW_UP)
        {
            if (m_labirint[ax - 1][ay] == to_int(Objects::EMPTY))
            {
                m_labirint[ax][ay] = to_int(Objects::EMPTY);
                ax = ax - 1;
                m_labirint[ax][ay] = to_int(Objects::HERO);
            }
            else
            {
                msg = "You can't move higher.\n";
            }
        }
        
        else if (key == Keys::ARROW_LEFT)
        {
            if (m_labirint[ax][ay - 1] == to_int(Objects::EMPTY))
            {
                m_labirint[ax][ay] = to_int(Objects::EMPTY);
                ay = ay - 1;
                m_labirint[ax][ay] = to_int(Objects::HERO);
            }
            else
            {
                msg = "You can't move to the left.\n";
            }
        }
        
        else if (key == Keys::ARROW_BACK)
        {
            if (m_labirint[ax + 1][ay] == to_int(Objects::EMPTY))
            {
                m_labirint[ax][ay] = to_int(Objects::EMPTY);
                ax = ax + 1;
                m_labirint[ax][ay] = to_int(Objects::HERO);
            }
            else
            {
                msg = "You can't move to the lower.\n";
            }
        }
        
        else if (key == Keys::ARROW_RIGHT)
        {
            if (m_labirint[ax][ay + 1] == to_int(Objects::EMPTY))
            {
                m_labirint[ax][ay] = to_int(Objects::EMPTY);
                ay = ay + 1;
                m_labirint[ax][ay] = to_int(Objects::HERO);
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

//получение символьного значения в виде цифры с обработкой ввода 
char inputChoice()
{
    while (true) 
    {
        char choice;
        std::cin >> choice;
        if (isdigit(choice))
        {
            std::cin.ignore(32767, '\n');
            return choice;
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Incorrect enter. Retry again.\n";
        }
    }
}

// получение целочисленного значения с обработкой ввода
int inputNum()
{
    while (true)
    {
        int choice;
        std::cin >> choice;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Incorrect enter. Retry again.\n";
        }
        if(choice >= 0)
        {
            std::cin.ignore(32767, '\n');
            return choice;
           
        }
        std::cin.ignore(32767, '\n');
        std::cout << "Incorrect enter. Retry again.\n";
    }
}
int main()
{
    srand(static_cast<unsigned int>(time(NULL)));

    Labirint labirint;

    // Меню генерирования лабиринта
    std::cout << "1)Load labirint from file\n2)Create new labirint with no save\n3)Create new labirint and save it\n\n";
    std::cout << "Enter a option: ";

    bool good = false;
    while (good == false)
    {
        char choice = inputChoice();

        switch (choice)
        {
        case '1':
            labirint.read();
            good = true;
            break;
        
        case '2':
            labirint.create();
            good = true;
            break;
        
        case '3':
            labirint.create();
            labirint.write();
            good = true;
            break;
        
        default:
            std::cerr << "Unknown input.\n";
        }
    }

    while (true)
    {
        system("cls");
        labirint.print();
        std::cout << "\n\n1)find way from A to B\n2)find all exit's from A\n3)find shortest way from A to B\n4)Walk in labirint\n9)Close the program\n\n";
        std::cout << "Enter a option: ";
        char choice = inputChoice();


        int ax, ay;
        std::string msg;
        bool isWalk = false;
        switch (choice)
        {
        case '1':
            std::cout << "Enter point A(x,y): ";
            ax = inputNum();
            ay = inputNum();

            std::cout << "Enter point B(x,y): ";
            int bx, by;
            bx = inputNum();
            by = inputNum();

            system("pause");
            break;
        case '2':
            break;
        case '3':
            break;
        case '4':
            std::cout << "Enter start point(x,y): ";
            ax = inputNum();
            ay = inputNum();
            labirint.setPoint(ax, ay, 5);
            isWalk = true;
            while (isWalk)
            {
                system("cls");
                labirint.print();
                std::cout << msg;
                msg = labirint.walk(ax, ay);
                if (msg == "esc")
                    exit(0);
            }
            break;
        case '9':
            exit(0);
        default:
            std::cerr << "Unknown error.\n";
        }
    }

    return 0;
}