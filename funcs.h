#pragma once
#include <iostream>
#include <cmath>
#include <conio.h>
#include "other.h"
#include "ConsoleApi.h"

// Считывание с клавиатуры напрямую без Enter
char directInput();

// получает целочисленного значения с обработкой ввода и указанием лимита до какого числа разрешен ввод
int inputNum(Console& console, short offsetX, short offsetY, const int limit = 0);

// Ввести точки для структуры Point(использует inputNum())
void inputPoint(Console& console, Point& point);

// Возвращает символ объекта
std::wstring wstrObject(Objects& object);

// Возвращает квадратный корень числа, возвращает -1 если корень не квадратный. Требуется в генерации лабиринта
int square(int num);

