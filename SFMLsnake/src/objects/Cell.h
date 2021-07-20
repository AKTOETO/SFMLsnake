#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <cmath>

#include "../../Support.h"

using namespace sf;

struct CellData
{
	Vector2f pos = { WIDTH / 2, HEIGHT / 2 },
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

class Cell
{
private:
	Direction m_dir;
	Vector2f m_newPos;
	RectangleShape m_rect, m_posBackPoint, m_posFrontPoint;
	std::shared_ptr<RenderWindow> m_window;
	std::unique_ptr<CellData> m_data;
	std::unique_ptr<RectangleShape> m_collisionRectangle;
	//temp
	//======
	Texture m_texture;
	Sprite m_sprite;
	//======

public:
	Cell(std::shared_ptr<RenderWindow>, std::unique_ptr<CellData>);
	~Cell();

	void event();
	RCellData logic(float time);
	void draw();

	void setPos(Vector2f);
	void setSize(Vector2f);
	void setDirection(Direction);
	void setRotation(float);

	RectangleShape& getCollisionShape();
	RectangleShape& getRectangleShape();
	Vector2f getSize();
	Vector2f getBackPos();
	Vector2f getCenterPos();
	Vector2f getFrontPos();
	Direction getDirection();
	float getRotation();
};
