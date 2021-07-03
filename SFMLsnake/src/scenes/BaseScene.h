#pragma once

struct SceneData
{
	bool need_to_switch = false;
};

class BaseScene
{
protected:

public:
	BaseScene() {};
	~BaseScene() {};

	virtual void activate() = 0;

	virtual void processEvent() = 0;
	virtual SceneData processLogic(float) = 0;
	virtual void processDraw() = 0;
};

