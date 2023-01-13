/*
 * Hud.hpp
 *
 *  Created on: 10 decembre 2018
 *      Author: Crabman
 */

#ifndef HUD_HPP_
#define HUD_HPP_

#include <SFML/Graphics.hpp>
#include <sstream> 
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>


struct score
{
	int unlocked;
	int highScore;
};

class Hud
{
public:
	Hud(sf::Font& font);
	~Hud();
	void update();
	void draw(sf::RenderTexture& render);
	void updateTime(float elapsedTime);
	void resetTime();
	float getTime();
	void setTime(float t);
	int getScore();
	bool isUnlockedLevel(long unsigned int difficulty, long unsigned int levelNum);
	void unlockLevel(long unsigned int difficulty, long unsigned int levelNum);
	void reset(long unsigned int difficulty, long unsigned int levelNb);
	void updateHighScore(long unsigned int difficulty, long unsigned int levelNb);
	void load();
	void save();
	
private:
	sf::Text m_levelNumText;
	sf::Text m_scoreText;
	sf::Text m_timeText;
	sf::Text m_highScoreText;
	
	int m_levelNumber = 5;
	int m_score;
	float m_time;
	int m_highScore;
	
	const std::string m_fileName = "score.txt";
	std::vector<struct score> m_highScores;
};

#endif /* HUD_HPP_ */
