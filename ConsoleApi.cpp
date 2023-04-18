#include "ConsoleApi.h"

void Console::printStrCenter(std::wstring const& str, SHORT offsetX, SHORT offsetY)
{
    COORD cPos;
    cPos = { static_cast<SHORT>(m_centerX - (str.length() / 2) + offsetX), static_cast<SHORT>(m_centerY + offsetY) };
    SetConsoleCursorPosition(m_hConsole, cPos);
    std::wcout << str;
}

void Console::setBufferSize()
{
    // Получение информации о размерах буфера консоли
    GetConsoleScreenBufferInfo(m_hConsole, &m_csbi);

    // настройка нового буфера консоли
    COORD sizeConsole{ m_csbi.dwSize.X, m_csbi.srWindow.Bottom + 1 };
    BOOL resizeSuccessful = SetConsoleScreenBufferSize(m_hConsole, sizeConsole);
    if (!resizeSuccessful)
    {
        DWORD error = GetLastError();
        printStrCenter(L"Error" + error);
        exit(-1);
    }
    // Обновление информации о размерах буфера консоли
    GetConsoleScreenBufferInfo(m_hConsole, &m_csbi);
}

void Console::cursorHide()
{
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(m_hConsole, &cci);

    cci.bVisible = false;
    SetConsoleCursorInfo(m_hConsole, &cci);
}

void Console::setFont(std::wstring font)
{
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(fontInfo);
    fontInfo.nFont = 0;
    fontInfo.dwFontSize.X = 8;
    fontInfo.dwFontSize.Y = 16;
    fontInfo.FontFamily = FF_DONTCARE;
    fontInfo.FontWeight = FW_NORMAL;
    wcscpy_s(fontInfo.FaceName, L"Consolas");

    SetCurrentConsoleFontEx(m_hConsole, FALSE, &fontInfo);
}

// Получение точек центра экрана
void Console::initCenterXY()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(m_hConsole, &csbi);
    Console::m_centerX = csbi.dwSize.X / 2;
    Console::m_centerY = csbi.dwSize.Y / 2;
}