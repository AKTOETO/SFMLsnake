#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

#define WIDTH 800  // 800 1920
#define HEIGHT 600 // 600 1080

#define SPEED 0.2 // 0.2
#define SOCHX 28 
#define SOCHY 33 

#define SOCBX 12 
#define SOCBY 40 
#define OBC 10 // offset between cells

#define PI 3.14159265

#define SHB false //show hit boxes

namespace SupportFunc
{
	static bool intersectRectShapes(RectangleShape f, RectangleShape s)
	{
		return f.getGlobalBounds().intersects(s.getGlobalBounds());
	}
	static bool intersectRectShapePoint(Vector2f f, RectangleShape s)
	{
		return s.getGlobalBounds().contains(f);
	}
}
