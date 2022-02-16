#pragma once
#include <iostream>
#include <vector>

#include "../Cell/Cell.h"

class Snake : public Engine::BaseObject
{
private:
	std::vector<std::unique_ptr<Cell>> m_units;
	bool m_isAlive = true;

public:
	Snake(std::shared_ptr<RenderWindow>);
	~Snake();

	std::unique_ptr<Cell>& operator[](int);

	void processEvent() override;
	int processLogic(float time) override;
	void draw(RenderTarget& target, RenderStates states)const override;

	void addUnit(Vector2f, float);

	int getSize();
	bool getAlive();
};
