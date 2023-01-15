/*
 * Hud.cpp
 *
 *  Created on: 30 juin 2018
 *      Author: Crabman
 */

#include "Hud.hpp"


Hud::Hud(sf::Font& font)
{
	for( long unsigned int i = 0; i < m_levelNumber*3; i++ )
	{
		score s
		{
			0,
			0,
		};
		m_highScores.push_back(s);
	}
	m_highScores[0].unlocked = 1; //unlocked firt level
	m_highScores[m_levelNumber].unlocked = 1; //unlocked firt level
	m_highScores[m_levelNumber*2].unlocked = 1; //unlocked firt level

	m_levelNumText.setFont(font);
	m_levelNumText.setCharacterSize(30);
	m_levelNumText.setString("Niveau:1");
	m_levelNumText.setPosition(sf::Vector2f(30, 10));
	
	//score
	m_score = 0;
	m_scoreText.setFont(font);
	m_scoreText.setCharacterSize(30);
	m_scoreText.setString("Score:1000");
	m_scoreText.setPosition(sf::Vector2f(440, 10));
	
	//time
	m_time = 1000;
	m_timeText.setFont(font);
	m_timeText.setCharacterSize(30);
	m_timeText.setString("Temps restant:1000");
	m_timeText.setPosition(sf::Vector2f(880, 10));
	
	//highScore
	m_highScore = 0;
	m_highScoreText.setFont(font);
	m_highScoreText.setCharacterSize(30);
	m_highScoreText.setString("Meilleur score:0");
	m_highScoreText.setPosition(sf::Vector2f(1310, 10));
}


Hud::~Hud()
{

}


void Hud::update()
{
	//score
	m_scoreText.setString("Score:" + std::to_string(static_cast<int>(m_score)));
	//bound = m_scoreText.getLocalBounds();
	//m_scoreText.setOrigin(sf::Vector2f(bound.width/2 , 0));
	//m_scoreText.setPosition(sf::Vector2f(530, 45));

	//time
	m_timeText.setString("Temps restant:" + std::to_string(static_cast<int>(m_time)));
	//bound = m_timeText.getLocalBounds();
	//m_timeText.setOrigin(sf::Vector2f(bound.width/2 , 0));
	//m_timeText.setPosition(sf::Vector2f(530, 45));
	
	//highScore
	m_highScoreText.setString("Meilleur score:" + std::to_string(m_highScore));
	//bound = m_highScoreText.getLocalBounds();
	//m_highScoreText.setOrigin(sf::Vector2f(bound.width/2 , 0));
	//m_highScoreText.setPosition(sf::Vector2f(1560, 45));
}


void Hud::draw(sf::RenderTexture& render)
{
	render.draw(m_levelNumText);
	render.draw(m_scoreText);
	render.draw(m_timeText);
	render.draw(m_highScoreText);
}


void Hud::updateTime(float elapsedTime)
{
	m_time -= elapsedTime;
}


void Hud::resetTime()
{
	m_time = 1001;
	m_score = 0;
}


float Hud::getTime()
{
	return (m_time);
}


void Hud::setTime(float t)
{
	m_time = t;
}


int Hud::getScore()
{
	return (m_score);
}


bool Hud::isUnlockedLevel(long unsigned int difficulty, long unsigned int levelNum)
{
	if (levelNum+(m_levelNumber*difficulty) < m_highScores.size())
	{
		return (m_highScores[levelNum+(m_levelNumber*difficulty)].unlocked == 1);
	}
	return (false);
}


void Hud::unlockLevel(long unsigned int difficulty, long unsigned int levelNum)
{
	
	if (levelNum+(m_levelNumber*difficulty) < m_highScores.size())
	{
		m_highScores[levelNum+(m_levelNumber*difficulty)].unlocked = 1;
	}
}


void Hud::reset(long unsigned int difficulty, long unsigned int levelNum)
{
	m_levelNumText.setString("Niveau:" + std::to_string(levelNum+1));
	m_time = 1001;
	m_score = 0;
	m_highScore = m_highScores[levelNum+(m_levelNumber*difficulty)].highScore;
}


void Hud::updateHighScore(long unsigned int difficulty, long unsigned int levelNum)
{
	m_score = static_cast<int>(m_time)*10;
	if (m_score > m_highScore)
	{
		m_highScore = m_score;
		m_highScores[levelNum+(m_levelNumber*difficulty)].highScore = m_highScore;
	}
}


void Hud::load()
{
	std::ifstream file(m_fileName.c_str(), std::ios::in);
	if(!file)
	{
		std::cerr << "Erreur, impossible d'ouvrir " << m_fileName << " !" << std::endl;
		return;
	}
	std::string line;
	while (getline(file, line))
	{
		std::istringstream iss( line );
		long unsigned int n = 50;
		long unsigned int u = 0;
		long unsigned int s = 0;
		iss >> n;
		iss >> u;
		iss >> s;
		if (n < m_levelNumber*3)
		{
			if (u == 1)
				m_highScores[n].unlocked = u;
			m_highScores[n].highScore = s;
		}
	}
	m_highScores[0].unlocked = 1; //unlocked firt level
	m_highScores[m_levelNumber].unlocked = 1; //unlocked firt level
	m_highScores[m_levelNumber*2].unlocked = 1; //unlocked firt level
	file.close();
}


void Hud::save()
{
	std::ofstream file(m_fileName.c_str(), std::ios::out | std::ios::trunc);
	if(!file)
	{
		std::cerr << "Erreur, impossible d'ouvrir le fichier" << m_fileName << "!" << std::endl;
		return;
	}

	for (unsigned int i = 0; i < m_highScores.size(); i++){ 
		score s = m_highScores[i];
		file << std::to_string(i) << " " << std::to_string(static_cast<int>(s.unlocked)) << " " << std::to_string(static_cast<int>(s.highScore)) << std::endl;
	}
	file.close();
}
