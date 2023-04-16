// Labirint - Программа, создающая 2д лабиринт в двумерном массиве.
// Генерирует лабиринт(размеры указываются переменными str и tab в constants.h)
// Предлагает возможные действия с ним 

#include <iostream>
#include <fstream>
#include <cctype>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include "constants.h"

// Макросы для быстрого преобразования
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

// получение целочисленного значения с обработкой ввода
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
    std::cout << "x: ";
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

void cursorHide(HANDLE hConsole)
{
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hConsole, &cci);
        
    cci.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cci);
}


//struct strCoord
//{
//    std::string str;
//    SHORT centerX;
//    SHORT centerY;
//    SHORT offsetX = 0;
//    SHORT offsetY = 0;
//};

// Напечатать строку в позиции курсора от центра
void printStrCenter(HANDLE hConsole, std::string str, SHORT centerX, SHORT centerY, SHORT offsetX = 0, SHORT offsetY = 0)
{
    COORD cPos;
    cPos = { static_cast<SHORT>(centerX - (str.length() / 2) + offsetX), static_cast<SHORT>(centerY + offsetY) };
    SetConsoleCursorPosition(hConsole, cPos);
    std::cout << str;
}

// Считывание с клавиатуры напрямую без Enter
char directInput()
{
    char ch = _getch();
    if(ch == 0xE0 || ch == -32)
        ch = _getch();
    ch = toupper(ch);
    return ch;
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

    // Вывод изображения лабиринта
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

    // Записать данные лабиринта в файл
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

    // Спрашивает пользователя, нужно ли сгенерировать новый лабиринт
    bool genNew(HANDLE hConsole, SHORT centerX, SHORT centerY)
    {   
        while(true)
        {
            system("cls");
            print();

            std::string str = "Generate a new maze? Y/N";
            printStrCenter(hConsole, str, centerX, centerY);

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

    // Спрашивает пользователя, сохранить ли получившийся лабиринт
    bool saveNew(HANDLE hConsole, SHORT centerX, SHORT centerY)
    {
        while (true)
        {
            system("cls");
            print();

            std::string str = "Save maze in file? Y/N";
            printStrCenter(hConsole, str, centerX, centerY);

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

    bool mazeMenu(HANDLE hConsole, SHORT centerX, SHORT centerY,bool isLabirintLoaded)
    {
        while (true)
        {
            system("cls");

            if (isLabirintLoaded)
                print();

            std::string str;
            str = "Labirint2D";
            printStrCenter(hConsole, str, centerX, centerY, 0, -3);

            str = "Load maze from file";
            printStrCenter(hConsole, str, centerX, centerY, 0, -1);

            str = "Create maze";
            printStrCenter(hConsole, str, centerX, centerY);

            if (isLabirintLoaded)
            {
                str = "Back to main menu";
                printStrCenter(hConsole, str, centerX, centerY, 0, 1);
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
                    isChoice = genNew(hConsole, centerX, centerY);

                isChoice = true;
                while (isChoice)
                    isChoice = saveNew(hConsole, centerX, centerY);

                return true;
            case '3':
                if(isLabirintLoaded)
                    return true;
                break;
            }
        }
    }

    // Установить определенной точке в лабиринте обьект
    void setPoint(const Point& p, const Objects object)
    {
        m_labirint[p.x][p.y] = object;
    }

    std::string walk(Point& p)
    {
        std::string msg;
        Keys key;
            
        key = to_key(directInput());

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
   // Полноэкранный режим
    SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);  
   
   // Изменение заголовка консоли
   TCHAR cTitle[] = L"Labirint2D";
   SetConsoleTitle(cTitle);

   // Изменение буфера консоли чтобы убрать полосу прокрутки
   HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

   // Получение информации о размерах буфера консоли
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   GetConsoleScreenBufferInfo(hConsole, &csbi);

   // настройка нового буфера консоли
    COORD sizeConsole{ csbi.dwSize.X, csbi.srWindow.Bottom + 1}; 
    BOOL resizeSuccessful = SetConsoleScreenBufferSize(hConsole, sizeConsole);
    if (!resizeSuccessful)
    {
        DWORD error = GetLastError();
        std::cout << "Error " << error;
        exit(-1);
    }

    // Скрыть курсор из консоли
    cursorHide(hConsole);

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
        
        // Получение точек центра экрана
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        SHORT centerX = csbi.dwSize.X / 2;
        SHORT centerY = csbi.dwSize.Y / 2;
        
        std::string str = "Labirint2D";
        printStrCenter(hConsole, str, centerX, centerY, 0, -3);

        str = "Start";
        printStrCenter(hConsole, str, centerX, centerY, 0, -1);

        str = "Maze menu";
        printStrCenter(hConsole, str, centerX, centerY);
        
        str = "Settings";
        printStrCenter(hConsole, str, centerX, centerY, 0, 1);

        str = "Exit";
        printStrCenter(hConsole, str, centerX, centerY, 0, 2);

        if (msg.length() > 0)
        {
            printStrCenter(hConsole, msg, centerX, centerY, 0, 4);

        }

        char choice = directInput();
        switch (choice)
        {
        case '1':
            if (!isLabirintLoaded)
                msg = "To start, load the maze in Maze menu";
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
        case '2':
           isLabirintLoaded = labirint.mazeMenu(hConsole, centerX, centerY, isLabirintLoaded);
           msg = "";
           break;
        case '3':
            break;
        case '4':
            exit(0);
        }
    }

    return 0;
}