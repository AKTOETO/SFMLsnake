#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <cmath>

#include "../BaseObject.h"
#include "../../managers/AnimationManager/AnimationManager.h"

using namespace sf;

struct CellData
{
	Vector2f pos = { W_WIDTH / 2, W_HEIGHT / 2 },
		size = { SOCHX, SOCHY };
	Color color = Color::Green;
	bool head = false;
	float rotation = 0;
};

class Cell : public BaseObject
{
private:
	Direction m_dir;
	Vector2f m_newPos;

	std::unique_ptr<CellData> m_data;

	std::unique_ptr<Vector2f> m_collisionPoint, m_posBackPoint, m_posFrontPoint;
	std::unique_ptr<StaticPicture> m_rect;
	std::unique_ptr<AnimationManager> m_animManager;

	bool m_wallCollision;
	float m_rotation = 0;
	float m_deltaX = 0;
	float m_deltaY = 0;

public:
	Cell(std::unique_ptr<CellData>);
	~Cell();

	virtual void processEvent() override;
	virtual int processLogic(float time) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setPos(Vector2f);
	void setSize(Vector2f);
	void setDirection(Direction);
	void setRotation(float);

	Vector2f getCollisionPoint();
	RectangleShape& getRectangleShape();
	Vector2f getSize() const;
	Vector2f getBackPos() const;
	Vector2f getCenterPos() const;
	Vector2f getFrontPos() const;
	Direction getDirection() const;
	float getRotation() const;
	float getDeltaX() const;
	float getDeltaY() const;
	bool getWallCollision() const;
};
