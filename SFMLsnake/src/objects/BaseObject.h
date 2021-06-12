#pragma once

class BaseObject
{
protected:

public:
	BaseObject() {};
	~BaseObject() {};

	virtual void processEvent() = 0;
	virtual void processLogic(float time) = 0;
	virtual void processDraw() = 0;
};