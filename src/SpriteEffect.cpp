#include "pch.h"
#include "SpriteEffect.h"


constexpr Seconds SpriteEffect::defaultFramesPerSec;

void SpriteEffect::initialize()
{
	m_isActive = false;
	m_frameDelay = defaultFramesPerSec;
	
	try {
		m_texture = std::make_unique<sf::Texture>();
		m_sprite = std::make_unique<sf::Sprite>();
	}
	catch (std::bad_alloc& err) {
		printException(err, "SpriteEffect::initialize", true);
	}

}

SpriteEffect::SpriteEffect() noexcept
{
	initialize();
}


SpriteEffect::SpriteEffect(const char* spriteSheetFile, 
	const sf::Vector2i& spriteSize, const sf::Vector2i& maxLeftAndTop) : 
	m_textureRect({0,0}, spriteSize),
	m_maxLeftAndTop(maxLeftAndTop)
{
	initialize();

	if (!m_texture->loadFromFile(spriteSheetFile))
		throw FileNotFoundException(std::string("file not found: ") + spriteSheetFile);

	m_sprite->setTexture(*m_texture);
	m_sprite->setTextureRect(m_textureRect);
	m_sprite->setOrigin(spriteSize.x * 0.5f, spriteSize.y * 0.5f);
}

void SpriteEffect::loadSpriteSheet(const char * spriteSheetFile, 
	const sf::Vector2i & spriteSize, const sf::Vector2i & leftAndTopMax)
{
	if (!m_texture->loadFromFile(spriteSheetFile))
		throw FileNotFoundException(std::string("file not found: ") + spriteSheetFile);
	
	m_textureRect.width = spriteSize.x;
	m_textureRect.height = spriteSize.y;
	
	m_maxLeftAndTop.x = leftAndTopMax.x;
	m_maxLeftAndTop.y = leftAndTopMax.y;

	m_sprite->setTexture(*m_texture);
	m_sprite->setTextureRect(m_textureRect);
	m_sprite->setOrigin(spriteSize.x * 0.5f, spriteSize.y * 0.5f);
}



void SpriteEffect::update() noexcept
{
	if ( m_isActive && m_frameDelay.finished() )
	{
		Chrono::ChronoGuard cGuard(m_frameDelay);
		if (m_textureRect.left == m_maxLeftAndTop.x)
		{
			if (m_textureRect.top == m_maxLeftAndTop.y) {
				m_textureRect.left = m_textureRect.top = 0;
				m_isActive = false;
			}

			else {
				m_textureRect.left = 0;
				m_textureRect.top += m_textureRect.height;
			}
		}

		else
			m_textureRect.left += m_textureRect.width;
		
		m_sprite->setTextureRect(m_textureRect);
	}

}
