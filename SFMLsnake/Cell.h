#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "Constans.h"

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
		bool m_canRotate = false,
			m_canRemember = true,
			m_head = false;
	
	public:
	    Cell(std::shared_ptr<RenderWindow>, std::unique_ptr<CellData>);
		~Cell();

		void event();
		void logic(float time);
		void draw();

		void setDirection(Direction, Vector2f);
		Direction getDirection();

		Vector2f getSize();
		Vector2f getPos();

		void setNewPos(Vector2f);

		void canRotate();

		RectangleShape& getRectangleShape();
};

