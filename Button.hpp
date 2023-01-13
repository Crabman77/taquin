/*
 * Button.hpp
 *
 *  Created on: 3 juil. 2018
 *	  Author: Crabman
 */

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <SFML/Graphics.hpp>


class Button
{
	public:
		Button(sf::Texture* texture, sf::Vector2f size, sf::Vector2f pixelPos, int callBack, sf::Vector2f pos);
		void update(sf::Vector2f worldPos);
		bool isPressed();
		sf::Sprite getSprite();
		sf::Vector2f getPosition();
		int getCallBack();

	private:
		sf::Vector2f m_size;
		int m_callBack;
		sf::Vector2f m_pos;
		sf::Sprite m_sprite;
		std::vector<sf::IntRect> m_anim;
		bool m_active;
		bool m_pressed;
};

#endif /* BUTTON_HPP_ */
