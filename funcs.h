#pragma once
#include <iostream>
#include <conio.h>
#include "other.h"

// ���������� � ���������� �������� ��� Enter
char directInput();

// �������� �������������� �������� � ���������� ����� � ��������� ������ �� ������ ����� �������� ����
// !! ������������ ������� ���� � ������� iostream
int inputNum(const int limit = 0);

// ������ ����� ��� ��������� Point(���������� inputNum())
void inputPoint(Point& point);

// ���������� ������ ����� �������
std::string stringObject(Objects& object);

