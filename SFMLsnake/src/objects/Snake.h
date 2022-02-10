#pragma once
#include <iostream>
#include <vector>

#include "Cell.h"

class Snake : public BaseObject
{
private:
	std::vector<std::unique_ptr<Cell>> m_units;
	bool m_isAlive = true;

public:
	Snake(std::shared_ptr<RenderWindow>);
	~Snake();

	std::unique_ptr<Cell>& operator[](int);

	virtual void processEvent() override;
	virtual int processLogic(float time) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const override;

	void addUnit(Vector2f, float);

	int getSize();
	bool getAlive();
};
