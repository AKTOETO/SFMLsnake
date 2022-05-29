#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#include "../managers/SceneManager/SceneManager.h"
#include "../Logger/Logger.h"

namespace Engine
{
	class Game
	{
	private:
		std::shared_ptr<Context> m_context;
		std::unique_ptr<SceneManager> m_sceneManager;

	public:
		Game();
		~Game();

		void run();
	};
}
