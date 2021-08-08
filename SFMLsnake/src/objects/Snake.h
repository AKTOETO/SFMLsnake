#pragma once
#include <iostream>
#include <vector>

#include "Cell.h"

struct RSnakeData
{
	bool isAlive = true;
};

class Snake
{
private:
	std::shared_ptr<RenderWindow> m_window;
	std::vector<std::unique_ptr<Cell>> m_units;

public:
	Snake(std::shared_ptr<RenderWindow>);
	~Snake();

	std::unique_ptr<Cell>& operator[](int);

	void processEvent();
	RSnakeData processLogic(float time);
	void processDraw();

	void addUnit(Vector2f, float);

	int getSize();
};
