#pragma once
#include <fstream>
#include <vector>
#include "funcs.h"
#include "other.h"
#include "ConsoleApi.h"

class Labirint
{
private:
    std::vector<std::vector<std::vector<Objects>>> m_labirint;
    std::fstream m_f;

public:
    
    Labirint(std::wstring filename = L"labirint.maze");

    // �������� ���������� ���������: ����� � �������
    void create();

    // ����� ����������� ���������
    void printMaze(Console& console, int i);

    // ����� ����� ����� ���������
    void printPoint(Console& console, Point& p);

    // ���������� ������������ ����� � ��������� ������
    void setPoint(const Point& p, const Objects object) { m_labirint[p.z][p.y][p.x] = object; }

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

    // ���� ��������
    bool settingsMenu(Console& console, bool isLabirintLoaded);

    // ��������� ������������� �� ��������� �� ���������
    std::wstring walk(Console& console, Point& p);

};