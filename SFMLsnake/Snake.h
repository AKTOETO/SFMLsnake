#pragma once
#include <iostream>
#include <vector>

#include "Cell.h"

class Snake
{
private:
	std::shared_ptr<RenderWindow> m_window;
	std::vector<std::unique_ptr<Cell>> m_units;

public:
	Snake(std::shared_ptr<RenderWindow>);
	~Snake();

	std::unique_ptr<Cell> &operator[](int);

	void event();
	void logic(float time);
	void draw();

	void addUnit(Vector2f);

	int size();

};

