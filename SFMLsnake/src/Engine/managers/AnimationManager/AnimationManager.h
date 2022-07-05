#pragma once
#include <map>
#include <memory>
#include "../../objects/AnimatedPicture/AnimatedPicture.h"
#include "../../base/Base.h"

namespace Engine
{
	enum class AnimType
	{
		NONE = 0,
		STAY,
		MOVE,
		DIE,
	};

	class AnimationManager : public Base
	{
	private:
		std::map<AnimType, std::unique_ptr<AnimatedPicture>> m_animList;
		AnimType m_curAnim;

	public:
		AnimationManager(std::shared_ptr<Engine::Context> context);
		~AnimationManager();

		int addAnim(AnimType, std::unique_ptr<AnimatedPicture>&);
		std::unique_ptr<AnimatedPicture>& getAnimation(AnimType);

		int processLogic(float time);
		void processDraw();

		void useAnim(AnimType);
		void startAnim(AnimType = AnimType::NONE);
		void pauseAnim(AnimType = AnimType::NONE);
		void stopAnim(AnimType = AnimType::NONE);
	};
}
