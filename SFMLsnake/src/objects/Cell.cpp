#include "Cell.h"

Cell::Cell(std::shared_ptr<RenderWindow> window, std::unique_ptr<CellData> data)
    :m_window(window)
{
    m_collisionRectangle = nullptr;
    m_data = move(data);
	m_rect.setSize({ m_data->size, m_data->size });
    m_rect.setOrigin(m_rect.getLocalBounds().width / 2,
        m_rect.getLocalBounds().height / 2);
    m_rect.setPosition(Vector2f{ m_data->pos });
    m_rect.setFillColor(m_data->color);
    m_head = m_data->head;

    //temp
    // =====
    //texture;
    if (!m_texture.loadFromFile("assets/textures/snake.png"))
        std::cout << "failed to load snake.png (wrong path) <Cell.cpp>\n";

    //sprite
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(m_rect.getPosition());    
    // =====



    //collision shape
    if (m_head == true)
    {
        m_collisionRectangle = std::make_unique<RectangleShape>(
            Vector2f( m_rect.getSize().x / 4, 2 )
            );
        m_collisionRectangle->setOrigin(
            m_collisionRectangle->getLocalBounds().width / 2,
            m_collisionRectangle->getLocalBounds().height / 2
        );
        //m_collisionRectangle->setPosition(m_data->pos);
        m_collisionRectangle->setFillColor(Color::Magenta);
#define POSG(param) m_rect.getPosition().param
        m_collisionRectangle->setPosition(
            POSG(x), POSG(y) - m_rect.getSize().x / 2
        );

        //temp
        // =====
        //sprite
        m_sprite.setTextureRect(IntRect(1, 1, 20, 20));
        // =====
    }
    else
    {
        //temp
        // =====
        //sprite
        m_sprite.setTextureRect(IntRect(1, 22, 20, 20));
        // =====
    }
    m_sprite.setOrigin(
        m_sprite.getLocalBounds().width / 2,
        m_sprite.getLocalBounds().height / 2
    );
}

Cell::~Cell()
{
}

void Cell::event()
{
#define PRESS(param) Keyboard::isKeyPressed(Keyboard::param) 
    if (m_data->head == true && (PRESS(A) || PRESS(Left)) && m_dir != Direction::RIGHT)
        m_dir = Direction::LEFT;
    else if (m_data->head == true && (PRESS(W) || PRESS(Up)) && m_dir != Direction::DOWN)
        m_dir = Direction::UP;
    else if (m_data->head == true && (PRESS(D) || PRESS(Right)) && m_dir != Direction::LEFT)
        m_dir = Direction::RIGHT;
    else if (m_data->head == true && (PRESS(S) || PRESS(Down)) && m_dir != Direction::UP)
        m_dir = Direction::DOWN;
}

RCellData Cell::logic(float time)
{
    RCellData rdata;

    //==========HEAD==========
    if (m_head == true)
    {
#define POSG(param) m_rect.getPosition().param
#define BOUND(param) m_rect.getLocalBounds().param

        //collision with wall
        if (
            POSG(x) + m_rect.getSize().x / 2 > WIDTH ||
            POSG(y) + m_rect.getSize().y / 2 > HEIGHT ||
            POSG(x) - m_rect.getSize().x / 2 < 0 ||
            POSG(y) - m_rect.getSize().y / 2 < 0
            )
        {
            m_dir = Direction::STOP;
            rdata.wallCollision = true;
            std::cout << "game over (wall collision) <Cell.cpp>\n";
        }

        //head mooving
        if (m_dir == Direction::LEFT)
        {
            if (POSG(x) - BOUND(width) / 2 > 0)
            {
                m_rect.setPosition(POSG(x) - SPEED * time, POSG(y));
            }
            else
            {
                m_rect.setPosition(BOUND(width) / 2, POSG(y));
            }

            //temp
            m_sprite.setRotation(270);
        }
        else if (m_dir == Direction::RIGHT)
        {
            if (POSG(x) + BOUND(width) / 2 < WIDTH)
            {
                m_rect.setPosition(POSG(x) + SPEED * time, POSG(y));
            }
            else
            {
                m_rect.setPosition(WIDTH - BOUND(width) / 2, POSG(y));
            }

            //temp
            m_sprite.setRotation(90);
        }
        else if (m_dir == Direction::UP)
        {
            if (POSG(y) - BOUND(width) / 2 > 0)
            {
                m_rect.setPosition(POSG(x), POSG(y) - SPEED * time);
            }
            else
            {
                m_rect.setPosition(POSG(x), BOUND(width) / 2);
            }

            //temp
            m_sprite.setRotation(0);
        }
        else if (m_dir == Direction::DOWN)
        {
            if (POSG(y) + BOUND(width) / 2 < HEIGHT)
            {
                m_rect.setPosition(POSG(x), POSG(y) + SPEED * time);
            }
            else
            {
                m_rect.setPosition(POSG(x), HEIGHT - BOUND(width) / 2);
            }

            //temp
            m_sprite.setRotation(180);
        }

        //collision rectangle logic
        switch (m_dir)
        {
        case Direction::UP:
            m_collisionRectangle->setPosition(
                POSG(x), POSG(y) - m_rect.getSize().x / 2
            );
            m_collisionRectangle->setRotation(180);
            break;
        case Direction::DOWN:
            m_collisionRectangle->setPosition(
                POSG(x), POSG(y) + m_rect.getSize().x / 2
            );
            m_collisionRectangle->setRotation(180);
            break;
        case Direction::LEFT:
            m_collisionRectangle->setPosition(
                POSG(x) - m_rect.getSize().x / 2, POSG(y)
            );
            m_collisionRectangle->setRotation(270);
            break;
        case Direction::RIGHT:
            m_collisionRectangle->setPosition(
                POSG(x) + m_rect.getSize().x / 2, POSG(y)
            );
            m_collisionRectangle->setRotation(270);
            break;
        }

    }
    //==========BODY==========
    else
    {
        if (m_dir != Direction::STOP)
        {
            float k = 0.06; // smoothness of movement //0.1
            m_rect.move(
                ((m_newPos.x - POSG(x)) * SPEED * time * k),
                ((m_newPos.y - POSG(y)) * SPEED * time * k)
            );

            m_rect.setRotation(
                - std::atan((m_newPos.x - POSG(x)) / (m_newPos.y - POSG(y)))
                * 180 / PI
            );
        }
        //temp
        m_sprite.setRotation(m_rect.getRotation());
    }

    //temp
    m_sprite.setPosition(m_rect.getPosition());

   
    return rdata;
}

void Cell::draw()
{
    m_window->draw(m_rect);
    /*if (m_head == true)
        m_window->draw(*m_collisionRectangle);*/
    m_window->draw(m_sprite);
}

RectangleShape& Cell::getCollisionShape()
{
    return *m_collisionRectangle;
}

Vector2f Cell::getSize()
{
    return m_rect.getSize();
}

Vector2f Cell::getPos()
{
    return m_rect.getPosition();
}

void Cell::setDirection(Direction dir)
{
    m_dir = dir;
}

Direction Cell::getDirection()
{
    return m_dir;
}

void Cell::setPos(Vector2f newPos)
{
    m_newPos = newPos;
}

void Cell::setSize(Vector2f newSize)
{
    m_data->size = newSize.x;
    m_rect.setSize(newSize);
}

RectangleShape& Cell::getRectangleShape()
{
    return m_rect;
}

