/*
 * Button.cpp
 *
 *  Created on: 3 juil. 2018
 *	  Author: Crabman
 */

#include "Button.hpp"


Button::Button(sf::Texture* texture, sf::Vector2f size, sf::Vector2f pixelPos, int callBack, sf::Vector2f pos)
{
	m_size = size;
	m_callBack = callBack;
	m_pos = pos;
	m_sprite.setTexture(*texture);
	for( int i = 0; i < 2; i++ )
	{
		m_anim.push_back(sf::IntRect(static_cast<int>(pixelPos.x+(m_size.x*i)), static_cast<int>(pixelPos.y), static_cast<int>(m_size.x), static_cast<int>(m_size.y)) );
	}
	m_sprite.setTextureRect(m_anim[0]);
	m_sprite.setOrigin(sf::Vector2f(m_size.x/2, m_size.y/2));
	//m_sprite.setScale(0.7, 0.7);
	m_sprite.setPosition(m_pos);
	m_active = false;
	m_pressed = false;
}


void Button::update(sf::Vector2f worldPos)
{
	sf::FloatRect box = m_sprite.getGlobalBounds();
	if (box.contains(worldPos))
	{
		if (!m_active)
		{
			m_sprite.setTextureRect(m_anim[1]);
			m_active = true;
		}
		bool clicked = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		if (clicked && !m_pressed)
		{
			m_pressed = true;
		}else if (!clicked)
		{
			m_pressed = false;
		}
	} else
	{
		if (m_active)
		{
			m_sprite.setTextureRect(m_anim[0]);
			m_active = false;
		}
		m_pressed = false;
	}
}


bool Button::isPressed()
{
	return (m_pressed);
}


int Button::getCallBack()
{
	return (m_callBack);
}


sf::Vector2f Button::getPosition()
{
	return (m_sprite.getPosition());
}


sf::Sprite Button::getSprite()
{
	return (m_sprite);
}
