#pragma once
#include "Player.h"

Head::Head(std::shared_ptr<RenderWindow> window) {
    m_window = window;

    m_rectangles.resize(2);
    m_rectangles[0].setSize({ SOC, SOC });
    m_rectangles[0].setOrigin(m_rectangles[0].getLocalBounds().width / 2,
        m_rectangles[0].getLocalBounds().height / 2);
    m_rectangles[0].setPosition(WIDTH / 2, HEIGHT / 2);
    m_rectangles[0].setFillColor(Color::Green);

    //test
    m_rectangles[1].setSize({ SOC / 2, SOC / 2 });
    m_rectangles[1].setOrigin(m_rectangles[1].getLocalBounds().width / 2,
        m_rectangles[1].getLocalBounds().height / 2);
    m_rectangles[1].setPosition(WIDTH / 2, HEIGHT / 2);
    m_rectangles[1].setFillColor(Color::Red);

};

void Head::event()
{
#define PRESS(par) Keyboard::isKeyPressed(Keyboard::par) 
    if (PRESS(A))m_dir = Direction::LEFT;
    else if (PRESS(W))m_dir = Direction::UP;
    else if (PRESS(D))m_dir = Direction::RIGHT;
    else if (PRESS(S))m_dir = Direction::DOWN;
}

void Head::logic(float time)
{
    /*
    *               HEAD
    */


#define POSG(ind,para) m_rectangles[ind].getPosition().para
#define BOUND(para) m_rectangles[0].getLocalBounds().para

    if (m_dir == Direction::LEFT)
    {
        if (POSG(0,x) - BOUND(width) / 2 > 0)
        {
            m_rectangles[0].setPosition(POSG(0, x) - SPEED * time, POSG(0, y));
        }
        else
        {
            m_rectangles[0].setPosition(BOUND(width) / 2, POSG(0, y));
        }
    }
    else if (m_dir == Direction::RIGHT)
    {
        if (POSG(0, x) + BOUND(width) / 2 < WIDTH)
        {
            m_rectangles[0].setPosition(POSG(0, x) + SPEED * time, POSG(0, y));
        }
        else
        {
            m_rectangles[0].setPosition(WIDTH - BOUND(width) / 2, POSG(0, y));
        }
    }
    else if (m_dir == Direction::UP)
    {
        if (POSG(0, y) - BOUND(width) / 2 > 0)
        {
            m_rectangles[0].setPosition(POSG(0, x), POSG(0, y) - SPEED * time);
        }
        else
        {
            m_rectangles[0].setPosition(POSG(0, x), BOUND(width) / 2);
        }
    }
    else if (m_dir == Direction::DOWN)
    {
        if (POSG(0, y) + BOUND(width) / 2 < HEIGHT)
        {
            m_rectangles[0].setPosition(POSG(0, x), POSG(0, y) + SPEED * time);
        }
        else
        {
            m_rectangles[0].setPosition(POSG(0, x), HEIGHT - BOUND(width) / 2);
        }
    }

    /*
    *                              BODY
    */
    for (int i = m_rectangles.size() - 1; i > 0; i--)
    {
        m_rectangles[i].setPosition(POSG(i - 1, x), POSG(i - 1, y));
    }

}

void Head::draw()
{
    for (RectangleShape rect : m_rectangles)
    {
        m_window->draw(rect);
    }
}
