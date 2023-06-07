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

    // создание лабиринта
    // mode 1 - пустая локация с проходами
    // mode 2 - лабиринт
    // mode 3 - змейка
    void create(SHORT mode);

    // Вывод изображения лабиринта
    void printMaze(Console& console, int i);

    // Вывод одной точки лабиринта
    void printPoint(Console& console, Point& p);

    // Установить определенной точке в лабиринте обьект
    void setPoint(const Point& p, const Objects object) { m_labirint[p.z][p.y][p.x] = object; }

    // Записать данные лабиринта в файл
    void inFile();

    // считать данные лабиринта из файла
    void outFile();

    // Спрашивают пользователя, нужно ли сгенерировать/сохранить новый лабиринт, возвращает false если выбор сделан
    // Работают в связке с mazeMenu
    bool genNew(Console& console, SHORT mode);
    bool saveNew(Console& console);

    // Меню выбора режима игры, возвращает номер режима, влияет на функцию create
    SHORT modeMenu(Console& console);

    // Отображает меню генерации лабиринта, возвращает true = лабиринт загружен
    bool mazeMenu(Console& console, bool isLabirintLoaded, SHORT mode);
    
    // Отображает основное меню 
    void mainMenu(Console& console, std::wstring& msg);

    // Меню настроек
    bool settingsMenu(Console& console);

    // Позволяет передвигаться на стрелочки по лабиринту
    std::wstring walk(Console& console, Point& p);

    // Позволяет выбирать направление скольжения
    std::wstring slide(Console& console, Point& p);
};