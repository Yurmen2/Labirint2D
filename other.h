#pragma once

namespace Constants
{
	const short y = 40;
	const short x = 110;
}

enum class Keys
{
    ARROW_UP = 72,
    ARROW_LEFT = 75,
    ARROW_BACK = 80,
    ARROW_RIGHT = 77,
    ESC = 27,
};

enum class Objects
{
    WALL = 'W',
    EMPTY = 'E',
    HERO = '*',
};

static int object_id[]
{
    'W',
    'E',
    '*',
};

struct Point
{
    long long x;
    long long y;
};