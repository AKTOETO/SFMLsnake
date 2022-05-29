#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include "Logger/Logger.h"

using namespace sf;

#define W_WIDTH 800  // 800 1920
#define W_HEIGHT 600 // 600 1080

#define CENTER W_WIDTH / 2 , W_HEIGHT / 2

#define SPEED 0.2 // 0.2
#define SOCHX 28 
#define SOCHY 33 

#define SOCBX 12 
#define SOCBY 40 
#define OBC 10 // offset between cells

#define PI 3.14159265

#define SHB false //show hit boxes

#define INFO(msg) m_context->m_logger->info(FINFO(msg));
#define ERROR(msg) m_context->m_logger->crit(FINFO(msg));

namespace Engine
{
	struct Context
	{
		std::shared_ptr<RenderWindow> m_window;
		std::shared_ptr<Logger> m_logger;

		Context() {
			m_logger = std::make_shared<Logger>();
		};
		Context(std::shared_ptr<RenderWindow> window)
		{
			m_window = std::move(window);
			m_logger = std::make_shared<Logger>();
		}

		~Context()
		{
			m_window.reset();
			m_logger.reset();
		}
	};

	namespace SupportFunc
	{
		static bool intersectRectShapes(RectangleShape f, RectangleShape s)
		{
			return f.getGlobalBounds().intersects(s.getGlobalBounds());
		}
		static bool intersectRectShapePoint(Vector2f f, RectangleShape s)
		{
			return s.getGlobalBounds().contains(f);
		}
		// =====PICTURE====

		static void loadTexture(std::shared_ptr<Texture> texture, std::string file)
		{
			if (!texture->loadFromFile("assets/textures/" + file))
				// ERROR("failed to load " + file)
				std::cout << "cringe 70str in support.h\n";
		}

		// ================
	}

	// ===== CELL =====


	enum class Direction
	{
		STOP = 0,
		UP,
		DOWN,
		LEFT,
		RIGHT,
	};

	// ================
}


