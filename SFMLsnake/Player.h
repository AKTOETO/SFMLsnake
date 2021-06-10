#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "Constans.h"

using namespace sf;

class Head {

private:
    std::shared_ptr<RenderWindow> m_window;
    enum class Direction
    {
        STOP = 0,
        UP,
        DOWN,
        LEFT,
        RIGHT,
    };
    Direction m_dir;

    std::vector<RectangleShape> m_rectangles;

public:
    Head(std::shared_ptr<RenderWindow>);
    
    ~Head() {};

    void event();
    void logic(float time);
    void draw();
};
