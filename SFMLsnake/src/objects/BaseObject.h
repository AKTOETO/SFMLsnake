#pragma once
#include "../../Support.h"

class BaseObject : public Drawable
{
protected:

public:
	BaseObject() {};
	~BaseObject() {};

	virtual void processEvent() = 0;
	virtual int processLogic(float time) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};
