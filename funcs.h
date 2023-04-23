#pragma once
#include <iostream>
#include <cmath>
#include <conio.h>
#include "other.h"
#include "ConsoleApi.h"

// ���������� � ���������� �������� ��� Enter
char directInput();

// �������� �������������� �������� � ���������� ����� � ��������� ������ �� ������ ����� �������� ����
// !! ������������ ������� ���� � ������� iostream
int inputNum(Console& console, const int limit = 0);

// ������ ����� ��� ��������� Point(���������� inputNum())
void inputPoint(Console& console, Point& point);

// ���������� ������ �������
std::wstring wstrObject(Objects& object);

// ���������� ���������� ������ �����, ���������� -1 ���� ������ �� ����������. ��������� � ��������� ���������
int square(int num);

