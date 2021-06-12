#include "Cell.h"
#include <iostream>

Cell::Cell(std::shared_ptr<RenderWindow> window, std::unique_ptr<CellData> data)
    :m_window(window)
{
    m_data = move(data);
	m_rect.setSize({ m_data->size, m_data->size });
    m_rect.setOrigin(m_rect.getLocalBounds().width / 2,
        m_rect.getLocalBounds().height / 2);
    m_rect.setPosition(Vector2f{ m_data->pos });
    m_rect.setFillColor(m_data->color);
    m_head = m_data->head;
}

Cell::~Cell()
{
}

void Cell::event()
{
#define PRESS(par) Keyboard::isKeyPressed(Keyboard::par) 
    if (m_data->head == true && (PRESS(A) || PRESS(Left)) && m_dir != Direction::RIGHT)m_dir = Direction::LEFT;
    else if (m_data->head == true && (PRESS(W) || PRESS(Up)) && m_dir != Direction::DOWN)m_dir = Direction::UP;
    else if (m_data->head == true && (PRESS(D) || PRESS(Right)) && m_dir != Direction::LEFT)m_dir = Direction::RIGHT;
    else if (m_data->head == true && (PRESS(S) || PRESS(Down)) && m_dir != Direction::UP)m_dir = Direction::DOWN;
}

void Cell::logic(float time)
{
    if (m_head == true)
    {
#define POSG(para) m_rect.getPosition().para
#define BOUND(para) m_rect.getLocalBounds().para


        if (m_dir == Direction::LEFT)
        {
            if (POSG(x) - BOUND(width) / 2 > 0)
            {
                m_rect.setPosition(POSG(x) - SPEED * time, POSG(y));
            }
            else
            {
                //m_rect.setPosition(BOUND(width) / 2, POSG(y));
            }
        }
        else if (m_dir == Direction::RIGHT)
        {
            if (POSG(x) + BOUND(width) / 2 < WIDTH)
            {
                m_rect.setPosition(POSG(x) + SPEED * time, POSG(y));
            }
            else
            {
                //m_rect.setPosition(WIDTH - BOUND(width) / 2, POSG(y));
            }
        }
        else if (m_dir == Direction::UP)
        {
            if (POSG(y) - BOUND(width) / 2 > 0)
            {
                m_rect.setPosition(POSG(x), POSG(y) - SPEED * time);
            }
            else
            {
                //m_rect.setPosition(POSG(x), BOUND(width) / 2);
            }
        }
        else if (m_dir == Direction::DOWN)
        {
            if (POSG(y) + BOUND(width) / 2 < HEIGHT)
            {
                m_rect.setPosition(POSG(x), POSG(y) + SPEED * time);
            }
            else
            {
                //m_rect.setPosition(POSG(x), HEIGHT - BOUND(width) / 2);
            }
        }
    }
    else
    {
        float k = 0.1; // smoothness of movement
        m_rect.move(
            ((m_newPos.x - POSG(x)) * SPEED * time * k),
            ((m_newPos.y - POSG(y)) * SPEED * time * k)
        );
    }

    if (POSG(x) + m_rect.getSize().x / 2 > WIDTH)
    {
        m_rect.setPosition(m_rect.getSize().x / 2, POSG(y));
    }
    else if (POSG(y) + m_rect.getSize().y / 2 > HEIGHT)
    {
        m_rect.setPosition(POSG(x), m_rect.getSize().y / 2);
    }
    else if (POSG(x) - m_rect.getSize().x / 2 < 0)
    {
        m_rect.setPosition(WIDTH - m_rect.getSize().x / 2, POSG(y));
    }
    else if (POSG(y) - m_rect.getSize().y / 2 < 0)
    {
        m_rect.setPosition(POSG(x), HEIGHT - m_rect.getSize().y / 2);
    };

}

void Cell::draw()
{
    m_window->draw(m_rect);
}

void Cell::setDirection(Direction dir, Vector2f new_pos)
{

}

Direction Cell::getDirection()
{
    return m_dir;
}

Vector2f Cell::getSize()
{
    return m_rect.getSize();
}

Vector2f Cell::getPos()
{
    return m_rect.getPosition();
}

void Cell::setNewPos(Vector2f newPos)
{
    m_newPos = newPos;
}

void Cell::canRotate()
{
    m_dir = m_newDir;
}

RectangleShape& Cell::getRectangleShape()
{
    return m_rect;
}

