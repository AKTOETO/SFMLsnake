#include "AnimatedPicture.h"

AnimatedPicture::AnimatedPicture()
{
	INFO("Picture constructor")
}

AnimatedPicture::AnimatedPicture(std::unique_ptr<AnimationData>& data)
	:m_currentFrame(0), m_isStart(true), m_isPause(false), m_isStop(false)
{
	m_data = move(data);
	m_frames.resize(0);

	for (int i = 0; i < m_data->numberOfFrame; i++)
	{
		std::unique_ptr<SpriteData> sData(new SpriteData(m_data->data));

		switch (m_data->offset)
		{

		case TextureOffset::RIGHT:
			sData->borders = IntRect( /*sData->borders.left + (sData->borders.width + 1)*i*/
				1+(sData->borders.left + sData->borders.width) * i,
				sData->borders.top, sData->borders.width, sData->borders.height);
			INFO("border: " + std::to_string(sData->borders.left))
			break;

		case TextureOffset::LEFT:
			break;

		case TextureOffset::UP:
			break;

		case TextureOffset::DOWN:
			break;
		}
		m_frames.push_back(StaticPicture(sData));
		INFO("added new frame")
	}
}

AnimatedPicture::~AnimatedPicture()
{
	m_frames.resize(0);
	m_data.reset(nullptr);
}

void AnimatedPicture::processLogic(float time)
{
	if (m_isStart)
	{
		m_currentFrame += ANIMSPEED * time;
		//INFO("m_currentFrame: "+std::to_string(m_currentFrame)+" "+std::to_string(ANIMSPEED * time));
		m_isPause = false;
		m_isStop = false;
	}

	else if (m_isPause)
	{
		m_currentFrame += 0;
		m_isStart = false;
		m_isStop = false;
	}

	else if (m_isStop)
	{
		m_currentFrame = 0;
		m_isStart = false;
		m_isPause = false;
	}

	if (m_currentFrame >= m_data->numberOfFrame)
		m_currentFrame = 0;
}

void AnimatedPicture::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_frames[int(m_currentFrame)], states);
}

void AnimatedPicture::start()
{
	m_isStop = false;
	m_isPause = false;
	m_isStart = true;
}

void AnimatedPicture::pause()
{
	m_isStop = false;
	m_isPause = true;
	m_isStart = false;
}

void AnimatedPicture::stop()
{
	m_isStop = true;
	m_isPause = false;
	m_isStart = false;
}
