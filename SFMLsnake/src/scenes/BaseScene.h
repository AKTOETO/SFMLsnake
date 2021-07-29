#pragma once

struct RSceneData
{
	bool need_to_switch = false;
};

class BaseScene
{
protected:

public:
	BaseScene() {};
	virtual ~BaseScene() {};

	virtual void activate() = 0;
	virtual void deactivate() = 0;

	virtual void processEvent() = 0;
	virtual RSceneData processLogic(float) = 0;
	virtual void processDraw() = 0;
};
