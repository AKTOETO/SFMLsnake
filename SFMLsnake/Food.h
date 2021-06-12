#pragma once
#include <SFML/Graphics.hpp>

#include "Support.h"

using namespace sf;

struct FoodData
{
	Color color = Color::Yellow;
	Vector2f pos = { 50, 50 };
	float size;
};

class Food
{
private:
	std::shared_ptr<RenderWindow> m_window;
	std::unique_ptr<FoodData> m_data;
	RectangleShape m_rect;

public:
	Food(std::shared_ptr<RenderWindow>, std::unique_ptr<FoodData>);
	~Food();

	void event();
	void logic(float time);
	void draw();

	void setPos(Vector2f);

	RectangleShape& getRectangleShape();
};

