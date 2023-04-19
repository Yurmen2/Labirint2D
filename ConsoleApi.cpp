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
    // Установка окна 1920x1080 для корректного вычисления буфера консоли
    HWND wConsole = GetConsoleWindow();

    RECT r;
    GetWindowRect(wConsole, &r);
    MoveWindow(wConsole, r.left, r.top, 1920, 1080, true);

    // Получение информации о размерах буфера консоли
    GetConsoleScreenBufferInfo(m_hConsole, &m_csbi);

    // настройка нового буфера консоли

    COORD sizeConsole{ m_csbi.srWindow.Right + 1, m_csbi.srWindow.Bottom + 1 };
    BOOL resizeSuccessful = SetConsoleScreenBufferSize(m_hConsole, sizeConsole);
    if (!resizeSuccessful)
    {
        DWORD error = GetLastError();
        std::wcerr << error;
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

void Console::setFont(SHORT x, SHORT y, const std::wstring font)
{
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(fontInfo);
    fontInfo.nFont = 0;
    fontInfo.dwFontSize.X = x;
    fontInfo.dwFontSize.Y = y;
    fontInfo.FontFamily = FF_DONTCARE;
    fontInfo.FontWeight = FW_NORMAL;
    wcscpy_s(fontInfo.FaceName, font.c_str());

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