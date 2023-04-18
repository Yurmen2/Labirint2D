#pragma once
#include <iostream>
#include <conio.h>
#include "other.h"

// Считывание с клавиатуры напрямую без Enter
char directInput();

// получает целочисленного значения с обработкой ввода и указанием лимита до какого числа разрешен ввод
// !! Используется обычный ввод с помощью iostream
int inputNum(const int limit = 0);

// Ввести точки для структуры Point(использует inputNum())
void inputPoint(Point& point);

// Возвращает символ объекта
std::wstring wcstrObject(Objects& object);

