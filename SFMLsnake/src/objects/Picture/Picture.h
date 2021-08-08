#pragma once
#include <memory>
#include <iostream>
#include "../../../Support.h"

struct StandartData
{
	Vector2f position = { 0, 0 };
	Vector2f size = { 1, 1 };
	bool originInCenter = true;
	float angle = 0;
	Color color = Color::White;
};

enum SpriteType
{
	SNAKE = 0,
	FOOD,
};

struct SpriteData : public StandartData
{
	SpriteType type = SpriteType::SNAKE;
	IntRect borders = { 0, 0, 10, 10 };
};

enum ShapeType
{
	RECTANGLE = 0,
	CIRCLE,
};

struct ShapeData : public StandartData
{
	ShapeType type = ShapeType::RECTANGLE;
};

class Picture : public Drawable
{
protected:
	std::unique_ptr<SpriteData> m_spriteData;
	std::unique_ptr<ShapeData> m_shapeData;
	
	std::unique_ptr<Sprite> m_sprite;
	std::unique_ptr<Texture> m_texture;

	std::unique_ptr<RectangleShape> m_rectangle;
	std::unique_ptr<CircleShape> m_circle;

public:
	template<typename T>
	void addData(std::unique_ptr<T>&);

	Picture();
	Picture(std::unique_ptr<SpriteData>);
	Picture(std::unique_ptr<ShapeData>);
	~Picture();

	void setPosition(Vector2f);
	void setRotation(float);
	void setScale(Vector2f);

	Vector2f getPosition() const;
	float getRotation() const;
	Vector2f getScale() const;
	RectangleShape& getRectangleShape() const;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
