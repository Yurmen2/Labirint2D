#include "ConsoleApi.h"

void Console::printStrCenter(std::string const& str, SHORT offsetX, SHORT offsetY)
{
    COORD cPos;
    cPos = { static_cast<SHORT>(m_centerX - (str.length() / 2) + offsetX), static_cast<SHORT>(m_centerY + offsetY) };
    SetConsoleCursorPosition(m_hConsole, cPos);
    std::cout << str;
}

void Console::setBufferSize()
{
    // Получение информации о размерах буфера консоли
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(m_hConsole, &csbi);

    // настройка нового буфера консоли
    COORD sizeConsole{ csbi.dwSize.X, csbi.srWindow.Bottom + 1 };
    BOOL resizeSuccessful = SetConsoleScreenBufferSize(m_hConsole, sizeConsole);
    if (!resizeSuccessful)
    {
        DWORD error = GetLastError();
        printStrCenter("Error" + error);
        exit(-1);
    }
}

void Console::cursorHide()
{
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(m_hConsole, &cci);

    cci.bVisible = false;
    SetConsoleCursorInfo(m_hConsole, &cci);
}






// Получение точек центра экрана
void Console::initCenterXY()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(m_hConsole, &csbi);
    Console::m_centerX = csbi.dwSize.X / 2;
    Console::m_centerY = csbi.dwSize.Y / 2;
}