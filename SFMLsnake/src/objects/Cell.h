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
	    Direction m_newDir;
		Vector2f m_newPos;
	    RectangleShape m_rect;
		std::shared_ptr<RenderWindow> m_window;
		std::unique_ptr<CellData> m_data;
		std::unique_ptr<RectangleShape> m_collisionRectangle;
		bool m_head = false;
	
public:
	    Cell(std::shared_ptr<RenderWindow>, std::unique_ptr<CellData>);
		~Cell();

		void event();
		void logic(float time);
		void draw();

		RectangleShape& getCollisionShape();

		Vector2f getSize();
		Vector2f getPos();

		void setPos(Vector2f);

		RectangleShape& getRectangleShape();
};

