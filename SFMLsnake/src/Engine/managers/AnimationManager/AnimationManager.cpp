#include "AnimationManager.h"
namespace Engine
{
	AnimationManager::AnimationManager(std::shared_ptr<Engine::Context> context)
		:m_curAnim(AnimType::STAY), Base(context)
	{
		INFO("AnimationManager constructor")
		//m_context->m_logger->info(FINFO("AnimationManager constructor"));
	}

	AnimationManager::~AnimationManager()
	{
	}

	int AnimationManager::addAnim(AnimType type, std::unique_ptr<AnimatedPicture>& anim)
	{
		m_animList[type] = std::move(anim);
		m_curAnim = type;
		return 0;
	}

	std::unique_ptr<AnimatedPicture>& AnimationManager::getAnimation(AnimType type)
	{
		return m_animList[type];
	}

	int AnimationManager::processLogic(float time)
	{
		return m_animList[m_curAnim]->processLogic(time);
	}

	void AnimationManager::useAnim(AnimType type)
	{
		m_animList[type]->setPosition(m_animList[m_curAnim]->getPosition());
		m_animList[type]->setRotation(m_animList[m_curAnim]->getRotation());
		m_curAnim = type;
		startAnim(m_curAnim);
	}

#define IFNONE if(type == AnimType::NONE) m_animList[type]-> //checking for none animation
#define ENONE m_animList[m_curAnim]->

	inline void AnimationManager::startAnim(AnimType type)
	{
		IFNONE start();
		ENONE start();
	}

	inline void AnimationManager::pauseAnim(AnimType type)
	{
		IFNONE pause();
		ENONE pause();
	}

	inline void AnimationManager::stopAnim(AnimType type)
	{
		IFNONE stop();
		ENONE stop();
	}

	void AnimationManager::draw(RenderTarget& target, RenderStates states) const
	{
		target.draw(*m_animList.find(m_curAnim)->second, states);
	}
}
