#pragma once
#include <fstream>
#include <vector>
#include "funcs.h"
#include "other.h"
#include "ConsoleApi.h"

class Labirint
{
private:
    std::vector<std::vector<Objects>> m_labirint;
    std::fstream m_f;

public:
    
    Labirint(std::wstring filename = L"labirint.maze");

    // �������� ���������� ���������: ����� � �������
    void create();

    // ����� ����������� ���������
    void print(Console& console);

    // �������� ������ ��������� � ����
    void inFile();

    // ������� ������ ��������� �� �����
    void outFile();

    // ���������� ������������, ����� �� �������������/��������� ����� ��������, ���������� false ���� ����� ������
    // �������� � ������ � mazeMenu
    bool genNew(Console& console);
    bool saveNew(Console& console);

    // ���������� ���� ��������� ���������, ���������� true = �������� ��������
    bool mazeMenu(Console& console, bool isLabirintLoaded);
    
    // ���������� �������� ���� 
    void mainMenu(Console& console, std::wstring& msg);

    // ���������� ������������ ����� � ��������� ������
    void setPoint(const Point& p, const Objects object) { m_labirint[p.x][p.y] = object; }

    // ��������� ������������� �� ��������� �� ���������
    std::wstring walk(Point& p);

};