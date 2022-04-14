#include "AnimatedPicture.h"
namespace Engine
{
	AnimatedPicture::AnimatedPicture()
		: m_currentFrame(0), m_isStart(true), m_isPause(false), m_isStop(false)
	{
		INFO("\t\tPicture constructor")
	}

	AnimatedPicture::AnimatedPicture(std::shared_ptr<Engine::Context> context, std::unique_ptr<AnimationData>& data)
		:BaseObject(context), m_currentFrame(0), m_isStart(true), m_isPause(false), m_isStop(false)
	{
		INFO("\t\tmoving data")
		m_data = move(data);
		m_frames.resize(m_data->numberOfFrame);

		for (int i = 0; i < m_data->numberOfFrame; i++)
		{
			INFO("\t\tcreating " + std::to_string(i) + " frame")
			std::unique_ptr<SpriteData> sData(new SpriteData(m_data->data));

#define DWIDTH sData->borders.width
#define DHEIGHT sData->borders.height
#define DTOP sData->borders.top
#define DLEFT sData->borders.left

			switch (m_data->offset)
			{
			case TextureOffset::RIGHT:
				sData->borders =
					IntRect(DLEFT + DWIDTH * i + i, DTOP, DWIDTH, DHEIGHT);
				break;

			case TextureOffset::LEFT:
				sData->borders =
					IntRect(DLEFT - DWIDTH * i - i, DTOP, DWIDTH, DHEIGHT);
				break;

			case TextureOffset::UP:
				sData->borders =
					IntRect(DLEFT, DTOP - DWIDTH * i - i, DWIDTH, DHEIGHT);
				break;

			case TextureOffset::DOWN:
				sData->borders =
					IntRect(DLEFT, DTOP + DWIDTH * i + i, DWIDTH, DHEIGHT);
				break;
			}
			m_frames.erase(m_frames.begin());
			m_frames.emplace_back(m_context, sData);
			INFO("added new frame")
		}
		INFO("frame vec. size:" + std::to_string(m_frames.size()));
	}

	AnimatedPicture::~AnimatedPicture()
	{
		m_frames.resize(0);
		m_data.reset(nullptr);
	}

	int AnimatedPicture::processLogic(float time)
	{
		if (m_isStart)
		{
			m_currentFrame += m_data->animSpeed * time;
			m_isPause = false;
			m_isStop = false;
		}

		else if (m_isPause)
		{
			//m_currentFrame += 0;
			m_isStart = false;
			m_isStop = false;
		}

		else if (m_isStop)
		{
			m_currentFrame = m_data->numberOfFrame - 1;
			m_isStart = false;
			m_isPause = false;
		}

		if (m_currentFrame >= m_data->numberOfFrame && m_data->type == AnimationType::LOOP)
			m_currentFrame = 0;
		else if (m_currentFrame >= m_data->numberOfFrame && m_data->type == AnimationType::ONCE)
		{
			stop();
			return 1;
		}
		return 0;
	}

#define ALLFR for (auto& sp : m_frames)sp.

	void AnimatedPicture::setPosition(Vector2f pos)
	{
		ALLFR setPosition(pos);
	}

	void AnimatedPicture::setRotation(float angle)
	{
		ALLFR setRotation(angle);
	}

	void AnimatedPicture::setScale(Vector2f scale)
	{
		ALLFR setScale(scale);
	}

	Vector2f AnimatedPicture::getPosition() const
	{
		return m_frames[0].getPosition();
	}

	float AnimatedPicture::getRotation() const
	{
		return m_frames[0].getRotation();
	}

	Vector2f AnimatedPicture::getScale() const
	{
		return m_frames[0].getScale();
	}

	RectangleShape& AnimatedPicture::getRectangleShape() const
	{
		return m_frames[0].getRectangleShape();
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

	void AnimatedPicture::restart()
	{
		stop();
		start();
	}

	void AnimatedPicture::draw(RenderTarget& target, RenderStates states) const
	{
		target.draw(m_frames[int(m_currentFrame)], states);
	}
}