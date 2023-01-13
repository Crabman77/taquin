#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Hud.hpp"
#include "Button.hpp"
#include "Card.hpp"
#include "Anim.hpp"


struct difficulty
{
	int nbPieces;
	int size;
	float timeMax;
};


class Engine
{
	public:
		~Engine();
		void cleanup()
		{
			delete m_hud;
			delete m_anim;
			m_imagesTexture.clear();
		};
		
		bool init();
		bool running();
		void stop();
		void resize(unsigned int width, unsigned int height);
		void launch(int callBack);
		void display();
		void menuInfo();
		void menu();
		void menuLevel(long unsigned int levelNum);
		void launchGame(long unsigned int difficultyNum, int callBack);
		int game(long unsigned int levelNb, long unsigned  int levelNum);
	
	private:
		sf::IntRect m_windowSize;
		bool m_running;
		bool m_haveFocus;
		bool m_inMenuLevel;
	
		std::vector<struct difficulty>  m_difficultys;
		sf::Font m_font;
		sf::RenderWindow m_window;
		sf::RenderTexture m_render;
		sf::View m_view;
		Hud* m_hud;
	
		//sprites
		sf::Texture m_imageMenuTexture;
		sf::Texture m_spritesTexture;
		
		//Cartes
		std::vector<sf::Texture*> m_imagesTexture;
		sf::Texture m_image1Texture;
		sf::Texture m_image2Texture;
		sf::Texture m_image3Texture;
		sf::Texture m_image4Texture;
		sf::Texture m_image5Texture;
		
		Anim *m_anim;

		// sound
		sf::SoundBuffer m_winBuffer;
		sf::Sound m_winSound;
		
		sf::SoundBuffer m_lostBuffer;
		sf::Sound m_lostSound;
		
		sf::SoundBuffer m_moveBuffer;
		sf::Sound m_moveSound;
};

#endif /* ENGINE_HPP_ */
