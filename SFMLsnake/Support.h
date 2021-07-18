#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

#define WIDTH 800  // 800 1920
#define HEIGHT 600 // 600 1080

#define SPEED 0.2 // 0.2
#define SOC 20 // 20 size of cell (px)
#define OBC SOC / 2 // offset between cells

#define PI 3.14159265

#define SHB false //show hit boxes

namespace SupportFunc
{
	static bool intersectRectangleShape(RectangleShape f, RectangleShape s)
	{
		return f.getGlobalBounds().intersects(s.getGlobalBounds());
	}
}
