#pragma once
#include <memory>
#include <iostream>
#include "../../../Support.h"

enum SpriteType
{
	SNAKE = 0,
	FOOD,
};

struct SpriteData
{
	SpriteType type = SpriteType::SNAKE;
	Vector2f position = { 0, 0 };
	Vector2f size = { 1, 1 };
	IntRect borders = { 0, 0, 10, 10 };
	bool originInCenter = true;
};

enum ShapeType
{
	RECTANGLE = 0,
	CIRCLE,
};

struct ShapeData
{
	ShapeType type = ShapeType::RECTANGLE;
	Vector2f position = { 0,0 };
	bool originInCenter = true;
};

class Picture : public Drawable
{
protected:
	std::unique_ptr<SpriteData> m_spriteData;
	std::unique_ptr<ShapeData> m_shapeData;
	std::unique_ptr<Sprite> m_sprite;
	std::unique_ptr<Texture> m_texture;

public:
	Picture(std::unique_ptr<SpriteData>);
	Picture(std::unique_ptr<ShapeData>);
	~Picture();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

