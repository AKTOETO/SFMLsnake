#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <cmath>

#include "../../Support.h"

using namespace sf;

struct CellData
{
	Vector2f pos = { WIDTH / 2, HEIGHT / 2 };
	Color color = Color::Green;
	float size = SOC;
	bool head = false;
};

struct RCellData
{
	bool wallCollision = false;
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
	    RectangleShape m_rect;
		std::shared_ptr<RenderWindow> m_window;
		std::unique_ptr<CellData> m_data;
		std::unique_ptr<RectangleShape> m_collisionRectangle;
		//temp
		//======
		Texture m_texture;
		Sprite m_sprite;
		//======
		bool m_head = false;
	
public:
	    Cell(std::shared_ptr<RenderWindow>, std::unique_ptr<CellData>);
		~Cell();

		void event();
		RCellData logic(float time);
		void draw();
		void setPos(Vector2f);
		void setSize(Vector2f);

		RectangleShape& getCollisionShape();
		RectangleShape& getRectangleShape();

		Vector2f getSize();
		Vector2f getPos();

		void setDirection(Direction);
		Direction getDirection();
};

