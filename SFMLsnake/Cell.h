#pragma once
#include <SFML/Graphics.hpp>

#include "Constans.h"

using namespace sf;

class Cell
{
private:
	    enum class Direction
	    {
	        STOP = 0,
	        UP,
	        DOWN,
	        LEFT,
	        RIGHT,
	    };
	    Direction m_dir;
	    RectangleShape m_rect;
	
	public:
	    Cell(Vector2i pos);
		~Cell();


};

