#ifndef ANIM_HPP_
#define ANIM_HPP_


class Anim
{
	public:
		Anim();
		~Anim();
		void setTime(float t);
		bool isActive();	
		void updatetime(float elapsedTime);
	
	private:
		float m_time;
};

#endif /* ANIM_HPP_ */
