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

enum class SpriteType
{
	NONE = 0,
	SNAKE,
	FOOD,
};

struct SpriteData : public StandartData
{
	SpriteType type = SpriteType::SNAKE;
	IntRect borders = { 0, 0, 10, 10 };
	std::shared_ptr<Texture> texture = nullptr;

	SpriteData() {};

	SpriteData(const SpriteData& data)
		:type(data.type),
		borders(data.borders),
		texture(data.texture)
	{
		position = data.position;
		size = data.size;
		originInCenter = data.originInCenter;
		angle = data.angle;
		color = data.color;
	}
};

enum class ShapeType
{
	RECTANGLE = 0,
	CIRCLE,
};

struct ShapeData : public StandartData
{
	ShapeType type = ShapeType::RECTANGLE;
};

class StaticPicture : public Drawable
{
protected:
	std::unique_ptr<SpriteData> m_spriteData;
	std::unique_ptr<ShapeData> m_shapeData;
	
	std::unique_ptr<Sprite> m_sprite;
	std::shared_ptr<Texture> m_texture;

	std::unique_ptr<RectangleShape> m_rectangle;
	std::unique_ptr<CircleShape> m_circle;

public:
	template<typename T>
	void addData(std::unique_ptr<T>&);

	StaticPicture();
	StaticPicture(const StaticPicture&); //copy constr
	StaticPicture(StaticPicture&&) noexcept; //move constr
	StaticPicture& operator=(StaticPicture&&) noexcept;

	StaticPicture(std::unique_ptr<SpriteData>&);
	StaticPicture(std::unique_ptr<ShapeData>&);
	~StaticPicture();
	void destruct();

	virtual void setPosition(Vector2f);
	virtual void setRotation(float);
	virtual void setScale(Vector2f);

	virtual Vector2f getPosition() const;
	virtual float getRotation() const;
	virtual Vector2f getScale() const;
	virtual RectangleShape& getRectangleShape() const;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
