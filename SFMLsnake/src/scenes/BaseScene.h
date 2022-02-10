#pragma once
#include <SFML/Graphics.hpp>

class BaseScene
{
protected:
	std::shared_ptr<sf::RenderWindow> m_window;

	bool need_to_switch = false;

public:
	BaseScene(std::shared_ptr<sf::RenderWindow> window)
		:m_window(window) {};
	virtual ~BaseScene() {};

	virtual void activate() = 0;
	virtual void deactivate() = 0;

	virtual void processEvent() = 0;
	virtual int processLogic(float) = 0;
	virtual void processDraw() = 0;

	bool getNeedToSwitch() const { return need_to_switch; }
};
