#include "Card.hpp"


Card::Card(sf::Texture* texture, sf::Vector2f pixelPos, int size, long unsigned int num)
{
	m_size = sf::Vector2f(static_cast<float>(size), static_cast<float>(size));
	m_pos = sf::Vector2f(0.f, 0.f);
	m_num = num;
	m_posNum = 0;
	
	m_sprite.setTexture(*texture);
	m_rect = sf::IntRect(static_cast<int>(pixelPos.x), static_cast<int>(pixelPos.y), size, size);
	m_sprite.setTextureRect(m_rect);
	//m_sprite.setOrigin(sf::Vector2f(m_size.x, m_size.y));
	m_sprite.setPosition(m_pos);
}


Card::~Card()
{

}


void Card::setPos(sf::Vector2f pos)
{
	m_pos = pos;
	m_sprite.setPosition(m_pos);
}


sf::Sprite Card::getSprite()
{
	return (m_sprite);
}


sf::FloatRect Card::getBounds()
{
	return (m_sprite.getGlobalBounds());
}


bool Card::contain(sf::Vector2f worldPos)
{
	sf::FloatRect box = m_sprite.getGlobalBounds();
	if (box.contains(worldPos))
	{
		return true;
	}
	return false;
}


long unsigned int Card::getNum()
{
	return (m_num);
}


void Card::setNum(long unsigned int num)
{
	m_num = num;
}


long unsigned int Card::getPosNum()
{
	return (m_posNum);
}


void Card::setPosNum(long unsigned int num)
{
	m_posNum = num;
}
