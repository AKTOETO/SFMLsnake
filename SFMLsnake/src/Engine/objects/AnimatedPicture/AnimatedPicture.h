#pragma once
#include <memory>
#include <vector>
#include <iostream>
#include <algorithm>
#include "../StaticPicture/StaticPicture.h"

namespace Engine
{
	enum class TextureOffset
	{
		RIGHT = 0,
		LEFT,
		UP,
		DOWN
	};

	enum class AnimationType
	{
		LOOP = 0,
		ONCE,
	};

	struct AnimationData
	{
		SpriteData data;
		TextureOffset offset = TextureOffset::RIGHT;
		AnimationType type = AnimationType::LOOP;
		int numberOfFrame = 1;
		float animSpeed = 0.01;
	};

	class AnimatedPicture : public BaseObject
	{
	private:
		std::vector<StaticPicture*> m_frames;
		std::unique_ptr<AnimationData> m_data;
		float m_currentFrame;
		bool m_isStart, m_isPause, m_isStop;

	public:
		AnimatedPicture(std::shared_ptr<Engine::Context>, std::unique_ptr<AnimationData>& data);
		~AnimatedPicture();

		void start();
		void pause();
		void stop();
		void restart();

		void processEvent() {};
		int processLogic(float time);

		void setPosition(Vector2f);
		void setRotation(float);
		void setScale(Vector2f);

		Vector2f getPosition() const;
		float getRotation() const;
		Vector2f getScale() const;
		RectangleShape& getRectangleShape() const;

		void draw(RenderTarget& target, RenderStates states) const override;
	};
}
