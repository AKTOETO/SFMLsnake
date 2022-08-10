#include "Game.h"

namespace Engine
{
	Game::Game()
		:m_context(new Engine::Context)
	{
		// creating window object
		m_context->m_window = std::make_shared<RenderWindow>(VideoMode(W_WIDTH, W_HEIGHT), "Snake");

		// TODO creating logger object

		// creating scene manager object
		m_sceneManager = std::make_unique<SceneManager>(m_context);

		// setting the scene
		m_sceneManager->setScene(Scenes::Game, std::make_unique<GameScene>(m_context));
	}

	Game::~Game()
	{
		m_context.reset();
	}

	void Game::run()
	{
		Clock clock;
		while (m_context->m_window->isOpen())
		{
			float time = clock.getElapsedTime().asMicroseconds();
			clock.restart();
			time /= 800;

			//events
			Event event;
			while (m_context->m_window->pollEvent(event))
			{
				if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
				{
					m_context->m_window->close();
				}
			}
			m_sceneManager->processEvent();

			//logic
			m_sceneManager->processLogic(time);

			//draw
			m_context->m_window->clear();
			m_sceneManager->getCurScene().processDraw();
			m_context->m_window->display();
		}
	}
}

