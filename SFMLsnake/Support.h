#pragma once
#include <SFML/Graphics.hpp>
#include "Logger.hpp"
using namespace sf;

#define W_WIDTH 800  // 800 1920
#define W_HEIGHT 600 // 600 1080

#define CENTER W_WIDTH / 2 , W_HEIGHT / 2

#define ANIMSPEED 0.01
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

// ===== CELL =====

struct CellData
{
	Vector2f pos = { W_WIDTH / 2, W_HEIGHT / 2 },
		size = { SOCHX, SOCHY };
	Color color = Color::Green;
	bool head = false;
	float rotation = 0;
};

struct RCellData
{
	bool wallCollision = false;
	float
		rotation = 0,
		deltaX = 0,
		deltaY = 0;
};

enum class Direction
{
	STOP = 0,
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

// ================
// =====PICTURE====

static void loadTexture(std::shared_ptr<Texture> texture, std::string file)
{
	if (!texture->loadFromFile("assets/textures/" + file))
		ERROR("failed to load " + file)
}

// ================

