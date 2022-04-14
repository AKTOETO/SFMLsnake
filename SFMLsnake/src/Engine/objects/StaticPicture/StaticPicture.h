#pragma once
#include <memory>
#include <iostream>
#include "../BaseObject.h"

namespace Engine
{
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

	class StaticPicture : public Engine::BaseObject
	{
	protected:
		std::unique_ptr<SpriteData> m_spriteData;
		std::unique_ptr<ShapeData> m_shapeData;
	
		std::unique_ptr<Sprite> m_sprite;
		std::shared_ptr<Texture> m_texture;

		std::unique_ptr<RectangleShape> m_rectangle;
		std::unique_ptr<CircleShape> m_circle;

	public:

		StaticPicture();
		StaticPicture(std::shared_ptr<Engine::Context>);
		StaticPicture(const StaticPicture&); //copy constr
		StaticPicture(StaticPicture&&) noexcept; //move constr
		StaticPicture& operator=(StaticPicture&&) noexcept;

		StaticPicture(std::shared_ptr<Engine::Context>, std::unique_ptr<SpriteData>&);
		StaticPicture(std::shared_ptr<Engine::Context>, std::unique_ptr<ShapeData>&);
		~StaticPicture();
		void destruct();

		template<class T>
		void addData(std::unique_ptr<T>&);

		void setPosition(Vector2f);
		void setRotation(float);
		void setScale(Vector2f);

		Vector2f getPosition() const;
		float getRotation() const;
		Vector2f getScale() const;
		RectangleShape& getRectangleShape() const;

		void processEvent() override {};
		int processLogic(float time) override { return 0; }
		void draw(RenderTarget& target, RenderStates states) const override;
	};
}