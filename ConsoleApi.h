#pragma once
#include <string>
#include <Windows.h>
#include <iostream>

class Console
{
private:
	HANDLE m_hConsole;
	SHORT m_centerX;
	SHORT m_centerY;

	
public:
	Console(HANDLE hConsole)
		: m_hConsole {hConsole}, m_centerX{0}, m_centerY{0}
	{
	}

	// ���������� ������ � ������� ������� �� ������
	void printStrCenter(std::string const& str, SHORT offsetX = 0, SHORT offsetY = 0);

	// ������������� �����
	void fullScreen() { SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000); }

	// ��������� ��������� �������
	void title(LPCWSTR cTitle) { SetConsoleTitle(cTitle); }

	// ��������� ������ ������� ��� �����
	void setBufferSize();

	// ������ ������ �� �������
	void cursorHide();

	
	// �������� �������� x y ������ ������ � ����� ������
	void initCenterXY();
};