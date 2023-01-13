#ifndef CARD_HPP_
#define CARD_HPP_


#include <SFML/Graphics.hpp>
#include <sstream> 
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>


class Card
{
	public:
		Card(sf::Texture* texture, sf::Vector2f pixelPos, int size, long unsigned int num);
		~Card();
		void setPos(sf::Vector2f pos);
		bool isVisible();
		sf::Sprite getSprite();
		sf::FloatRect getBounds();
		bool contain(sf::Vector2f worldPos);
		long unsigned int getNum();
		void setNum(long unsigned int num);
		long unsigned int getPosNum();
		void setPosNum(long unsigned int num);	
		
	private:
		sf::Sprite m_sprite;
		sf::Vector2f m_size;
		sf::Vector2f m_pos;
		long unsigned int m_num;
		long unsigned int m_posNum;
		sf::IntRect m_rect;
		std::vector<sf::IntRect> m_anim;
		bool m_visible;
};

#endif /* CARD_HPP_ */
