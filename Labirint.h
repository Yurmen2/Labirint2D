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

    // создание случайного лабиринта: стены и проходы
    void create();

    // ¬ывод изображени€ лабиринта
    void print(Console& console);

    // «аписать данные лабиринта в файл
    void inFile();

    // считать данные лабиринта из файла
    void outFile();

    // —прашивают пользовател€, нужно ли сгенерировать/сохранить новый лабиринт, возвращает false если выбор сделан
    // –аботают в св€зке с mazeMenu
    bool genNew(Console& console);
    bool saveNew(Console& console);

    // ќтображает меню генерации лабиринта, возвращает true = лабиринт загружен
    bool mazeMenu(Console& console, bool isLabirintLoaded);
    
    // ќтображает основное меню 
    void mainMenu(Console& console, std::wstring& msg);

    // ”становить определенной точке в лабиринте обьект
    void setPoint(const Point& p, const Objects object) { m_labirint[p.x][p.y] = object; }

    // ѕозвол€ет передвигатьс€ на стрелочки по лабиринту
    std::wstring walk(Point& p);

};