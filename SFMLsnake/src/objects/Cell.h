#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <cmath>

#include "../../Support.h"
#include "AnimationManager/AnimationManager.h"

using namespace sf;

class Cell
{
private:
	Direction m_dir;
	Vector2f m_newPos;

	std::shared_ptr<RenderWindow> m_window;
	std::unique_ptr<CellData> m_data;

	std::unique_ptr<Vector2f> m_collisionPoint, m_posBackPoint, m_posFrontPoint;
	std::unique_ptr<StaticPicture> m_rect;
	std::unique_ptr<AnimationManager> m_animManager;

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

	Vector2f getCollisionPoint();
	RectangleShape& getRectangleShape();
	Vector2f getSize();
	Vector2f getBackPos();
	Vector2f getCenterPos();
	Vector2f getFrontPos();
	Direction getDirection();
	float getRotation();
};
