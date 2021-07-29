#pragma once
#include <SFML/Graphics.hpp>

struct RSceneData
{
	bool need_to_switch = false;
};

class BaseScene
{
protected:
	std::shared_ptr<sf::RenderWindow> m_window;

public:
	BaseScene(std::shared_ptr<sf::RenderWindow> window)
		:m_window(window) {};
	virtual ~BaseScene() {};

	virtual void activate() = 0;
	virtual void deactivate() = 0;

	virtual void processEvent() = 0;
	virtual RSceneData processLogic(float) = 0;
	virtual void processDraw() = 0;
};
