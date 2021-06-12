#pragma once
class BaseScene
{
public:
	BaseScene() {};
	~BaseScene() {};

	virtual void activate() = 0;

	virtual void processEvent() = 0;
	virtual void processLogic(float) = 0;
	virtual void processDraw() = 0;
};

