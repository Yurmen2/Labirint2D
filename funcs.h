#pragma once
#include <iostream>
#include <cmath>
#include <conio.h>
#include "other.h"
#include "ConsoleApi.h"

// ���������� � ���������� �������� ��� Enter
char directInput();

// �������� �������������� �������� � ���������� ����� � ��������� ������ �� ������ ����� �������� ����
int inputNum(Console& console, short offsetX, short offsetY, const int limit = 0);

// ������ ����� ��� ��������� Point(���������� inputNum())
void inputPoint(Console& console, Point& point);

// ���������� ������ �������
std::wstring wstrObject(Objects& object);

// ���������� ���������� ������ �����, ���������� -1 ���� ������ �� ����������. ��������� � ��������� ���������
int square(int num);

