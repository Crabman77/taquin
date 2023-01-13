#include "Anim.hpp"


Anim::Anim()
{
	m_time = 0;
}


Anim::~Anim()
{

}


void Anim::setTime(float t)
{
	m_time = t;
}


bool Anim::isActive()
{	
	return (m_time > 0);
}


void Anim::updatetime(float elapsedTime)
{
	m_time -= elapsedTime;
}
