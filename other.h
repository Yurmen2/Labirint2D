#pragma once

#define to_int(x) static_cast<int>(x)

namespace Constants
{
    // Максимальные значения x, y, === Зависят от буфера консоли
    // Значением z может быть только квадратный корень: 9, 16, 25 и тд

	const short y = 40;
	const short x = 110;
    const short z = 9;
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
    EMPTY,
    WALL,
    HERO,
    SNAKE,
    GRADE,
};

static int object_id[]
{
    to_int(Objects::EMPTY),
    to_int(Objects::WALL),
    to_int(Objects::HERO),
};

struct Point
{
    short x;
    short y;
    short z;
};

struct MapSize
{
    short y;
    short x;
    short z;
};