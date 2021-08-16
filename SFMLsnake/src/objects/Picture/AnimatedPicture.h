#pragma once
#include <memory>
#include <vector>
#include <iostream>
#include "Picture.h"
#include "../../../Support.h"

enum class AnimationType
{
	FOODSTAY = 0,
};

enum class TextureOffset
{
	RIGHT = 0,
	LEFT,
	UP,
	DOWN
};

struct AnimationData
{
	AnimationType animType;
	SpriteData data;
	TextureOffset offset = TextureOffset::RIGHT;
	int numberOfFrame = 1;
};

class AnimatedPicture : public StaticPicture
{
protected:
	std::vector<StaticPicture> m_frames;
	std::unique_ptr<AnimationData> m_data;
	float m_currentFrame;
	bool m_isStart, m_isPause, m_isStop;

public:
	AnimatedPicture();
	AnimatedPicture(std::unique_ptr<AnimationData>& data);
	~AnimatedPicture();

	void processLogic(float time);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setPosition(Vector2f);
	void setRotation(float);
	void setScale(Vector2f);

	Vector2f getPosition() const;
	float getRotation() const;
	Vector2f getScale() const;
	RectangleShape& getRectangleShape() const;

	void start();
	void pause();
	void stop();
	void restart();
};

