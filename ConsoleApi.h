#pragma once
#include <string>
#include <Windows.h>
#include <iostream>

class Console
{
private:
	HANDLE m_hConsole;
	CONSOLE_SCREEN_BUFFER_INFO m_csbi;
	SHORT m_centerX;
	SHORT m_centerY;

	
public:
	Console(HANDLE hConsole)
		: m_hConsole {hConsole}, m_centerX{0}, m_centerY{0}, m_csbi {0}
	{
	}

	// Напечатать строку в позиции курсора от центра
	void printStrCenter(std::wstring const& str, SHORT offsetX = 0, SHORT offsetY = 0);

	// Полноэкранный режим
	void fullScreen() { SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000); }

	// Изменение заголовка консоли
	void title(LPCWSTR cTitle) { SetConsoleTitle(cTitle); }

	// Настройка буфера консоли под экран
	void setBufferSize();

	// Скрыть курсор из консоли
	void cursorHide();

	// Изменение шрифта в консоли
	void setFont( SHORT x = 8, SHORT y = 16, std::wstring font = L"Consolas");

	// получить значения x y центра экрана в члены класса
	void initCenterXY();

	// Геттеры
	SHORT getCenterX() { return m_centerX; }
	SHORT getCenterY() { return m_centerY; }
	CONSOLE_SCREEN_BUFFER_INFO& getCsbi() { return m_csbi; }
};