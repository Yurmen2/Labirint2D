#pragma once

#define to_int(x) static_cast<int>(x)

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
    WALL,
    EMPTY,
    HERO,
};

static int object_id[]
{
    to_int(Objects::WALL),
    to_int(Objects::EMPTY),
    to_int(Objects::HERO),
};

struct Point
{
    short x;
    short y;
};