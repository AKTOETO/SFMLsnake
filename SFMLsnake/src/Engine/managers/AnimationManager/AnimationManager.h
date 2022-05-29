#pragma once
#include <map>
#include <memory>
#include "../../objects/AnimatedPicture/AnimatedPicture.h"
#include "../../Base.h"
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

		void useAnim(AnimType);
		void startAnim(AnimType = AnimType::NONE);
		inline void pauseAnim(AnimType = AnimType::NONE);
		inline void stopAnim(AnimType = AnimType::NONE);

		virtual void draw(RenderTarget& target, RenderStates states) const override;
	};
}
