/*
 * Engine.cpp
 *
 *  Created on: 30 juin 2018
 *      Author: Crabman
 */

#include "Engine.hpp"

enum callBackType { NONE, QUIT, GAME1, GAME2, GAME3, INFO };


bool Engine::init()
{
	difficulty difficulty1
	{
		9,
		3,
		301,
	};
	difficulty difficulty2
	{
		25,
		4,
		601,
	};
	difficulty difficulty3
	{
		64,
		5,
		1001,
	};

	m_difficultys.push_back(difficulty1);
	m_difficultys.push_back(difficulty2);
	m_difficultys.push_back(difficulty3);
	
	std::string gameName = "Jeu Du Taquin";
	m_windowSize.width = 1920;
	m_windowSize.height = 1280;
	
	// font
	if (!m_font.loadFromFile("font/default.ttf"))
	{
		std::cerr << "Error during import font/default.ttf" << std::endl;
		return (false);
	}
	
	//Title
	if(!m_spritesTexture.loadFromFile("textures/sprites.png"))
	{
		std::cerr << "Error during import textures/sprites.png" << std::endl;
		return (false);
	}
	
	//image
	if(!m_imageMenuTexture.loadFromFile("textures/image_menu.png"))
	{
		std::cerr << "Error during import textures/image_menu.png" << std::endl;
		return (false);
	}	
	
	
	
	if(!m_image1Texture.loadFromFile("textures/p1.png"))
	{
		std::cerr << "Error during import textures/p1.png" << std::endl;
		return (false);
	}
	
	if(!m_image2Texture.loadFromFile("textures/p2.png"))
	{
		std::cerr << "Error during import textures/p2.png" << std::endl;
		return (false);
	}	
	
	if(!m_image3Texture.loadFromFile("textures/p3.png"))
	{
		std::cerr << "Error during import textures/p3.png" << std::endl;
		return (false);
	}
		
	if(!m_image4Texture.loadFromFile("textures/p4.png"))
	{
		std::cerr << "Error during import textures/p4.png" << std::endl;
		return (false);
	}
	
	if(!m_image5Texture.loadFromFile("textures/p5.png"))
	{
		std::cerr << "Error during import textures/p5.png" << std::endl;
		return (false);
	}
	
	m_imagesTexture.push_back(&m_image1Texture);
	m_imagesTexture.push_back(&m_image2Texture);
	m_imagesTexture.push_back(&m_image3Texture);
	m_imagesTexture.push_back(&m_image4Texture);
	m_imagesTexture.push_back(&m_image5Texture);
	
	// sound move piece
	if (!m_moveBuffer.loadFromFile("sounds/move.ogg"))
	{
		std::cerr << "Error during import sounds/move.ogg" << std::endl;
		return (false);
	}
	m_moveSound.setBuffer(m_moveBuffer);

	// sound win
	if (!m_winBuffer.loadFromFile("sounds/win.ogg"))
	{
		std::cerr << "Error during import sounds/win.ogg" << std::endl;
		return (false);
	}
	m_winSound.setBuffer(m_winBuffer);

	// sound lost
	if (!m_lostBuffer.loadFromFile("sounds/lost.ogg"))
	{
		std::cerr << "Error during import sounds/lost.ogg" << std::endl;
		return (false);
	}
	m_lostSound.setBuffer(m_lostBuffer);

	srand(static_cast<unsigned int>(time(NULL)));
	
	m_hud = new Hud(m_font);
	m_hud->load();
	m_anim = new Anim();
	
	sf::VideoMode screen = sf::VideoMode::getDesktopMode();
	m_window.create(sf::VideoMode(static_cast<unsigned int>(m_windowSize.width), static_cast<unsigned int>(m_windowSize.height)), gameName);
	m_window.setFramerateLimit(60);
	
	sf::Image m_icon;

	if (m_icon.loadFromFile("textures/icon.png"))
		m_window.setIcon(m_icon.getSize().x, m_icon.getSize().y, m_icon.getPixelsPtr());

	m_render.create(static_cast<unsigned int>(m_windowSize.width), static_cast<unsigned int>(m_windowSize.height) );
	m_view.setSize(sf::Vector2f(static_cast<float>(m_windowSize.width), static_cast<float>(m_windowSize.height) ));
	m_view.setCenter(sf::Vector2f(static_cast<float>(m_windowSize.width / 2.f), static_cast<float>(m_windowSize.height / 2.f)));
	m_window.setView(m_view);

	m_window.setSize(sf::Vector2u(screen.width - 100, screen.height - 100));
	
	resize(screen.width - 100, screen.height - 100);
	m_window.setPosition(sf::Vector2i(0, 0));
	m_haveFocus = true;
	m_running = true;
	return (true);
}


Engine::~Engine()
{

}


bool Engine::running()
{
	return (m_running && m_window.isOpen());
}


void Engine::stop()
{
	m_running = false;
	m_window.close();
}


void Engine::resize(unsigned int width, unsigned int height)
{
	float nW = static_cast<float>(width) / static_cast<float>(m_windowSize.width);
	float nH = static_cast<float>(height) / static_cast<float>(m_windowSize.height);
	float scale = (nW < nH) ? nW : nH;
	m_view.setSize(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
	m_view.zoom(1.f/(scale));
	m_window.setView(m_view);
}


void Engine::launch(int callBack)
{
	switch (callBack)
	{
		case QUIT:
		{
			stop();
			break;
		}
		case GAME1:
		{
			menuLevel(0);
			break;
		}
		case GAME2:
		{
			menuLevel(1);
			break;
		}
		case GAME3:
		{
			menuLevel(2);
			break;
		}
		case INFO:
		{
			menuInfo();
			break;
		}
		default:
			break;
	}
}


void Engine::display()
{
	m_render.display();
	sf::Sprite renderSprite(m_render.getTexture());
	m_window.clear(sf::Color::Black);
	m_window.draw(renderSprite);
	m_window.display();
}


void Engine::menuInfo()
{
	sf::Text txt1Text;
	txt1Text.setFont(m_font);
	txt1Text.setCharacterSize(40);
	txt1Text.setString(L"Reconstituez l'image\nen faisant coulisser\nles pièces du puzzle.");
	txt1Text.setOrigin(sf::Vector2f(txt1Text.getLocalBounds().width/2 , 0.f));
	txt1Text.setPosition(sf::Vector2f(m_windowSize.width/2.f, 100.f));
	
	sf::Text txt2Text;
	txt2Text.setFont(m_font);
	txt2Text.setFillColor(sf::Color::Blue);
	txt2Text.setCharacterSize(50);
	txt2Text.setString(L"Déplacement des pièces:");
	txt2Text.setOrigin(sf::Vector2f(txt2Text.getLocalBounds().width/2.f , 0.f));
	txt2Text.setPosition(sf::Vector2f(m_windowSize.width/2.f, 350.f));
	
	sf::Sprite keysSprite;
	keysSprite.setTexture(m_spritesTexture);
	keysSprite.setTextureRect(sf::IntRect(744, 952, 280, 72));
	keysSprite.setOrigin(sf::Vector2f(140.f, 0.f));
	keysSprite.setPosition(sf::Vector2f(m_windowSize.width/2.f, 450.f));

	sf::Text txt3Text;
	txt3Text.setFont(m_font);
	txt3Text.setCharacterSize(40);
	txt3Text.setString(L"ou clic gauche");
	txt3Text.setOrigin(sf::Vector2f(txt3Text.getLocalBounds().width/2.f , 0.f));
	txt3Text.setPosition(sf::Vector2f(m_windowSize.width/2.f, 550.f));

	sf::Text txt4Text;
	txt4Text.setFont(m_font);
	txt4Text.setCharacterSize(50);
	txt4Text.setFillColor(sf::Color::Blue);
	txt4Text.setString(L"Afficher l'image d'aide:");
	txt4Text.setOrigin(sf::Vector2f(txt4Text.getLocalBounds().width/2.f , 0.f));
	txt4Text.setPosition(sf::Vector2f(m_windowSize.width/2.f, 660.f));

	sf::Text txt5Text;
	txt5Text.setFont(m_font);
	txt5Text.setCharacterSize(40);
	txt5Text.setString(L"Barre espace ou clic droit");
	txt5Text.setOrigin(sf::Vector2f(txt5Text.getLocalBounds().width/2.f , 0.f));
	txt5Text.setPosition(sf::Vector2f(m_windowSize.width/2.f, 760.f));


	sf::Text txt6Text;
	txt6Text.setFont(m_font);
	txt6Text.setCharacterSize(40);
	txt6Text.setString(L"Images créées sous blender.");
	txt6Text.setOrigin(sf::Vector2f(txt6Text.getLocalBounds().width/2.f , 0.f));
	txt6Text.setPosition(sf::Vector2f(m_windowSize.width/2.f, 980.f));


	std::vector<Button*> buttons;
	buttons.push_back(new Button(&m_spritesTexture, sf::Vector2f(280.f, 70.f), sf::Vector2f(0.f, 350.f), -1, sf::Vector2f(960.f, 1200.f))); //menu

	bool mouseReleased = false;
	sf::Event event;
	bool inMenuInfo = true;

	while (inMenuInfo && m_window.isOpen())
	{
		mouseReleased = false;
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
				{
					inMenuInfo = false;
					break;
				}
				case sf::Event::Resized:
				{
					resize(event.size.width, event.size.height);
					break;
				}
				case sf::Event::LostFocus:
				{
					m_haveFocus = false;
					break;
				}
				case sf::Event::GainedFocus:
				{
					m_haveFocus = true;
					break;
				}
				case sf::Event::KeyReleased:
				{
					switch (event.key.code)
					{
						case sf::Keyboard::Escape: //escape
						{
							if (m_haveFocus)
							{
								inMenuInfo = false;
							}
							break;
						}
						default: break;
					}
					break;
				}
				case sf::Event::MouseButtonReleased:
				{
					switch (event.mouseButton.button)
					{
						case sf::Mouse::Left:
							mouseReleased = true;
							break;
						default: break;
					}
					break;
				}
				default: break;
			}
		}

		m_render.clear(sf::Color::Black);
		m_render.draw(keysSprite);
		m_render.draw(txt1Text);
		m_render.draw(txt2Text);
		m_render.draw(txt3Text);
		m_render.draw(txt4Text);
		m_render.draw(txt5Text);
		m_render.draw(txt6Text);
		
		
		sf::Vector2i mPos = sf::Mouse::getPosition(m_window);
		sf::Vector2f worldPos = m_window.mapPixelToCoords(mPos);
		for (unsigned int i=0;i<buttons.size();i++)
		{
			if (buttons[i]->isPressed() && mouseReleased)
			{
				mouseReleased = false;
				int cb = buttons[i]->getCallBack();
				if (cb <= -1)
				{
					inMenuInfo = false;
					break;
				}
			}
			buttons[i]->update(worldPos);
			m_render.draw(buttons[i]->getSprite());
		}
		display();
	}
	for (size_t i = 0; i < buttons.size(); i++)
	{
		delete(buttons[i]);
	}
}


void Engine::menu()
{
	sf::Sprite imageMenuSprite;
	imageMenuSprite.setTexture(m_imageMenuTexture);
	imageMenuSprite.setTextureRect(sf::IntRect(0, 0, 1024, 1024));
	imageMenuSprite.setOrigin(sf::Vector2f(512.f, 0.f));
	imageMenuSprite.setPosition(sf::Vector2f(m_windowSize.width/2.f, 100.f));

	sf::Sprite titleSprite;
	titleSprite.setTexture(m_spritesTexture);
	titleSprite.setTextureRect(sf::IntRect(0, 560, 1024, 256));
	titleSprite.setOrigin(sf::Vector2f(512.f, 0.f));
	titleSprite.setPosition(sf::Vector2f(m_windowSize.width/2.f, 80.f));
	
	sf::Text versionText;
	versionText.setFont(m_font);
	versionText.setCharacterSize(22);
	versionText.setString(L"Crabman 2018  V 1.2");
	versionText.setPosition(sf::Vector2f(1620.f, m_windowSize.height-40.f));
	
	std::vector<Button*> buttons;
	buttons.push_back(new Button(&m_spritesTexture, sf::Vector2f(280.f, 70.f), sf::Vector2f(0.f, 0.f), GAME1, sf::Vector2f(960.f, 550.f))); //3x3
	buttons.push_back(new Button(&m_spritesTexture, sf::Vector2f(280.f, 70.f), sf::Vector2f(0.f, 70.f), GAME2, sf::Vector2f(960.f, 640.f))); //4x4
	buttons.push_back(new Button(&m_spritesTexture, sf::Vector2f(280.f, 70.f), sf::Vector2f(0.f, 140.f), GAME3, sf::Vector2f(960.f, 730.f))); //5x5
	buttons.push_back(new Button(&m_spritesTexture, sf::Vector2f(280.f, 70.f), sf::Vector2f(0.f, 490.f), INFO, sf::Vector2f(960.f, 1110.f))); //info
	buttons.push_back(new Button(&m_spritesTexture, sf::Vector2f(280.f, 70.f), sf::Vector2f(0.f, 210.f), QUIT, sf::Vector2f(960.f, 1200.f))); //quit

	bool mouseReleased = false;
	sf::Event event;
	while (running())
	{
		mouseReleased = false;
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
				{
					stop();
					break;
				}
				case sf::Event::Resized:
				{
					resize(event.size.width, event.size.height);
					break;
				}
				case sf::Event::LostFocus:
				{
					m_haveFocus = false;
					break;
				}
				case sf::Event::GainedFocus:
				{
					m_haveFocus = true;
					break;
				}
				case sf::Event::KeyReleased:
				{
					switch (event.key.code)
					{
						case sf::Keyboard::Escape: //escape
						{
							stop();
							break;
						}
						default: break;
					}
					break;
				}
				case sf::Event::MouseButtonReleased:
				{
					switch (event.mouseButton.button)
					{
						case sf::Mouse::Left:
							mouseReleased = true;
							break;
						default: break;
					}
					break;
				}
				default: break;
			}
		}
		
		m_render.clear(sf::Color::Black);
		//m_render.draw(titleSprite);
		m_render.draw(imageMenuSprite);
		m_render.draw(titleSprite);
		sf::Vector2i mPos = sf::Mouse::getPosition(m_window);
		sf::Vector2f worldPos = m_window.mapPixelToCoords(mPos);
		for (unsigned int i=0;i<buttons.size();i++)
		{
			if (buttons[i]->isPressed() && mouseReleased)
			{
				mouseReleased = false;
				launch(buttons[i]->getCallBack());
			}
			buttons[i]->update(worldPos);
			m_render.draw(buttons[i]->getSprite());
		}
		m_render.draw(versionText);
		display();
	}

	for (size_t i = 0; i < buttons.size(); i++)
	{
		delete(buttons[i]);
	}
}


void Engine::menuLevel(long unsigned int difficultyNum)
{
	sf::Sprite levelSprite;
	levelSprite.setTexture(m_spritesTexture);
	levelSprite.setTextureRect(sf::IntRect(0, 816, 546, 162));
	levelSprite.setOrigin(sf::Vector2f(273.f, 0.f));
	levelSprite.setPosition(sf::Vector2f(m_windowSize.width/2.f, 300.f));

	sf::RectangleShape buttonShape;
	buttonShape.setSize(sf::Vector2f(70.f -12.f, 70.f -12.f));
	buttonShape.setFillColor(sf::Color(200, 200, 200));
	buttonShape.setOutlineColor(sf::Color(180, 180, 180));
	buttonShape.setOutlineThickness(6);
	buttonShape.setOrigin(sf::Vector2f(70.f/2.f, 70.f/2.f));

	std::vector<Button*> buttons;
	float posStart = 1000.f-(80.f*5/2);
	for (int i=0;i < 5;i++)
	{
		buttons.push_back(new Button(&m_spritesTexture, sf::Vector2f(70.f, 70.f), sf::Vector2f(560.f, 0.f +(70.f*i)), i, sf::Vector2f(posStart +(80.f*i), 600.f))); //level
	}
	
	buttons.push_back(new Button(&m_spritesTexture, sf::Vector2f(280.f, 70.f), sf::Vector2f(0.f, 350.f), -1, sf::Vector2f(960.f, 1200.f))); //menu
	bool mouseReleased = false;
	sf::Event event;
	m_inMenuLevel = true;
	
	while (m_inMenuLevel && m_window.isOpen())
	{
		mouseReleased = false;
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
				{
					m_inMenuLevel = false;
					break;
				}
				case sf::Event::Resized:
				{
					resize(event.size.width, event.size.height);
					break;
				}
				case sf::Event::LostFocus:
				{
					m_haveFocus = false;
					break;
				}
				case sf::Event::GainedFocus:
				{
					m_haveFocus = true;
					break;
				}
				case sf::Event::KeyReleased:
				{
					switch (event.key.code)
					{
						case sf::Keyboard::Escape: //escape
						{
							if (m_haveFocus)
							{
								m_inMenuLevel = false;
							}
							break;
						}
						default: break;
					}
					break;
				}
				case sf::Event::MouseButtonReleased:
				{
					switch (event.mouseButton.button)
					{
						case sf::Mouse::Left:
							mouseReleased = true;
							break;
						default: break;
					}
					break;
				}
				default: break;
			}
		}

		m_render.clear(sf::Color::Black);
		m_render.draw(levelSprite);
		sf::Vector2i mPos = sf::Mouse::getPosition(m_window);
		sf::Vector2f worldPos = m_window.mapPixelToCoords(mPos);
		for (unsigned int i=0;i<buttons.size();i++)
		{
			int cb = buttons[i]->getCallBack();
			if ( (cb < 0) || (m_hud->isUnlockedLevel(difficultyNum, static_cast<long unsigned int>(cb))) )
			{
				if (buttons[i]->isPressed() && mouseReleased)
				{
					mouseReleased = false;
					if (cb >= 0)
					{ 
						launchGame(difficultyNum, cb);
					} else
					{
						m_inMenuLevel = false;
						break;
					}
				}
				buttons[i]->update(worldPos);
				m_render.draw(buttons[i]->getSprite());
			} else
			{
				buttonShape.setPosition(buttons[i]->getPosition().x+6, buttons[i]->getPosition().y+6);
				m_render.draw(buttonShape);
			}
		}
		display();
	}
	for (size_t i = 0; i < buttons.size(); i++)
	{
		delete(buttons[i]);
	}
}


void Engine::launchGame(long unsigned int difficultyNum, int callBack)
{
	while (callBack >= 0)
	{
		callBack = game(difficultyNum, static_cast<long unsigned int>(callBack));
	}
}


int Engine::game(long unsigned int difficultyNum, long unsigned int levelNum)
{
	int ret = -1;
	long unsigned int imageNum = levelNum;
	if (imageNum >= m_imagesTexture.size())
	{
		imageNum = 0;
	}
	
	if (difficultyNum >= (m_difficultys.size()))
	{
		difficultyNum = 0;
	}
	difficulty diff = m_difficultys[difficultyNum];
	
	int size = diff.size;
	long unsigned int nbPieces = static_cast<long unsigned int>(size*size);
	int sizePieces = 1080/diff.size;
	
	std::vector<sf::Vector2i> nmap;
	std::vector<sf::Vector2f> pos;
	int nbX = 0;
	int nbY = 0;
	for (size_t i = 0; i < nbPieces; i++)
	{
		float x = static_cast<float>(sizePieces)*nbX;
		float y = static_cast<float>(sizePieces)*nbY;
		pos.push_back(sf::Vector2f(x,  y));
		nmap.push_back(sf::Vector2i(nbX, nbY));
		nbX++;
		if (nbX >= size)
		{
			nbX = 0;
			nbY++;
		}
	}

	std::vector<Card*> pieces;
	for (size_t i = 0; i < nbPieces-1; i++)
	{
		pieces.push_back(new Card(m_imagesTexture[imageNum], pos[i], sizePieces, i));
	}
	
	std::vector<long unsigned int> randomPos;
	for (size_t i = 0; i < pos.size(); i++)
	{
		randomPos.push_back(i);
	}
	
	for (size_t i = 0; i < pieces.size(); i++)
	{
		int n = rand()%(static_cast<int>(randomPos.size()));
		pieces[i]->setPosNum(randomPos[static_cast<size_t>(n)]);
		randomPos.erase(randomPos.begin()+n);
	}
	
	struct emptyStruct
	{
		long unsigned int posNum;
		sf::Vector2f pos;
		sf::RectangleShape shape;
	};
	
	sf::Color color(220, 220, 220);
	emptyStruct empty;
	empty.posNum = randomPos[0];
	empty.shape.setSize(sf::Vector2f(sizePieces-4.f, sizePieces-4.f));
	empty.shape.setFillColor(color);
	empty.shape.setOutlineColor(color);
	empty.shape.setOutlineThickness(2);
	
	randomPos.erase(randomPos.begin());
	randomPos.clear();
	
	//m_hud->resetTime();
	m_hud->reset(difficultyNum, levelNum);
	m_hud->setTime(diff.timeMax);

	// menu
	std::vector<Button*> buttons;
	buttons.push_back(new Button(&m_spritesTexture, sf::Vector2f(280.f, 70.f), sf::Vector2f(0.f, 280.f), static_cast<int>(levelNum), sf::Vector2f(660.f, 1200.f))); //retry
	buttons.push_back(new Button(&m_spritesTexture, sf::Vector2f(280.f, 70.f), sf::Vector2f(0.f, 350.f), -1, sf::Vector2f(960.f, 1200.f))); //menu
	buttons.push_back(new Button(&m_spritesTexture, sf::Vector2f(280.f, 70.f), sf::Vector2f(0.f, 420.f), static_cast<int>(levelNum+1), sf::Vector2f(1260.f, 1200.f))); //next

	sf::Sprite image;
	image.setTexture(*m_imagesTexture[imageNum]);
	image.setPosition(sf::Vector2f(420.f, 60.f));
	sf::Text lostText;
	lostText.setFont(m_font);
	lostText.setCharacterSize(140);
	lostText.setString(L"Perdu");
	lostText.setOrigin(sf::Vector2f(lostText.getLocalBounds().width/2.f , 0.f));
	lostText.setPosition(sf::Vector2f(m_windowSize.width/2.f, (m_windowSize.height/2.f)-40.f));
	
	sf::Text winText;
	winText.setFont(m_font);
	winText.setCharacterSize(140);
	winText.setString(L"Gagné");
	winText.setOrigin(sf::Vector2f(winText.getLocalBounds().width/2.f , 0.f));
	winText.setPosition(sf::Vector2f(m_windowSize.width/2.f, (m_windowSize.height/2.f)-40.f));
		
	
	
	bool ingame = true;
	bool mouseReleased = false;
	sf::Event event;
	sf::Clock time;
	m_anim->setTime(0);
	
	bool isWin = false;
	bool isLost = false;
	bool isHelp = false;
	sf::Vector2i mPos = sf::Mouse::getPosition(m_window);
	sf::Vector2f worldPos = m_window.mapPixelToCoords(mPos);	
	
	while (ingame && m_window.isOpen())
	{
		mouseReleased = false;
		mPos = sf::Mouse::getPosition(m_window);
		worldPos = m_window.mapPixelToCoords(mPos);
		float elapsedTime = time.restart().asSeconds();
		m_anim->updatetime(elapsedTime);
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
				{
					ingame = false;
					break;
				}
				case sf::Event::Resized:
				{
					resize(event.size.width, event.size.height);
					break;
				}
				case sf::Event::LostFocus:
				{
					m_haveFocus = false;
					break;
				}
				case sf::Event::GainedFocus:
				{
					m_haveFocus = true;
					break;
				}
				case sf::Event::KeyReleased:
				{
					switch (event.key.code)
					{
						case sf::Keyboard::Escape: //return
						{
							if (m_haveFocus)
							{
								ingame = false;
							}
							break;
						}
						default: break;
					}
					break;
				}
				case sf::Event::MouseButtonReleased:
				{
					switch (event.mouseButton.button)
					{
						case sf::Mouse::Left:
							mouseReleased = true;
							break;
						default: break;
					}
					break;
				}
				default: break;
			}
		}

		if (m_haveFocus && !isWin && !isLost)
		{
			m_hud->updateTime(elapsedTime);
			if (!m_anim->isActive())
			{
				if (!isHelp)
				{
					long unsigned int numE = empty.posNum;
					int numEX = nmap[numE].x;
					int numEY = nmap[numE].y;
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					{
						for (size_t i = 0; i < pieces.size(); i++)
						{
							long unsigned int numP = pieces[i]->getPosNum();
							int numPX = nmap[numP].x;
							int numPY = nmap[numP].y;
							if (numPX == numEX && numPY-1 == numEY)
							{
								m_anim->setTime(0.3f);
								empty.posNum = numP;
								pieces[i]->setPosNum(numE);
								m_moveSound.play();
								break;
							}
						}
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					{
						for (size_t i = 0; i < pieces.size(); i++)
						{
							long unsigned int numP = pieces[i]->getPosNum();
							int numPX = nmap[numP].x;
							int numPY = nmap[numP].y;
							if (numPX == numEX && numPY+1 == numEY)
							{
								m_anim->setTime(0.3f);
								empty.posNum = numP;
								pieces[i]->setPosNum(numE);
								m_moveSound.play();
								break;
							}
						}
					} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					{
						for (size_t i = 0; i < pieces.size(); i++)
						{
							long unsigned int numP = pieces[i]->getPosNum();
							int numPX = nmap[numP].x;
							int numPY = nmap[numP].y;
							
							if (numPY == numEY && numPX-1 == numEX)
							{
								m_anim->setTime(0.3f);
								empty.posNum = numP;
								pieces[i]->setPosNum(numE);
								m_moveSound.play();
								break;
							}
						}
					} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					{
						for (size_t i = 0; i < pieces.size(); i++)
						{
							long unsigned int numP = pieces[i]->getPosNum();
							int numPX = nmap[numP].x;
							int numPY = nmap[numP].y;
							
							if (numPY == numEY && numPX+1 == numEX)
							{
								m_anim->setTime(0.3f);
								empty.posNum = numP;
								pieces[i]->setPosNum(numE);
								m_moveSound.play();
								break;
							}
						}
					}
					
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						for (size_t i = 0; i < pieces.size(); i++)
						{
							if (pieces[i]->contain(worldPos))
							{
								long unsigned int numP = pieces[i]->getPosNum();	
								int numPX = nmap[numP].x;
								int numPY = nmap[numP].y;								
								if (numPX == numEX && numPY-1 == numEY)
								{
									m_anim->setTime(0.3f);
									empty.posNum = numP;
									pieces[i]->setPosNum(numE);
									m_moveSound.play();
								} else if (numPX == numEX && numPY+1 == numEY)
								{
									m_anim->setTime(0.3f);
									empty.posNum = numP;
									pieces[i]->setPosNum(numE);
									m_moveSound.play();
								}
								else if (numPY == numEY && numPX-1 == numEX)
								{
									m_anim->setTime(0.3f);
									empty.posNum = numP;
									pieces[i]->setPosNum(numE);
									m_moveSound.play();
								}
								else if (numPY == numEY && numPX+1 == numEX)
								{
									m_anim->setTime(0.3f);
									empty.posNum = numP;
									pieces[i]->setPosNum(numE);
									m_moveSound.play();
								}
								break;
							}
						}
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{
					isHelp = true;
				} else
				{
					isHelp = false;
				}
			}
			long unsigned int ok = 0;
			for (size_t i = 0; i < pieces.size(); i++)
			{
				long unsigned int num = pieces[i]->getNum();
				long unsigned int posNum = pieces[i]->getPosNum();
				if (num == posNum)
				{
					ok++;
				}
			}
			if (ok == nbPieces-1)
			{
				isWin = true;
				m_winSound.play();
				m_hud->unlockLevel(difficultyNum, levelNum+1);
				m_hud->updateHighScore(difficultyNum, levelNum);
				m_hud->save();
			}
		}
		
		//drawing
		m_render.clear(sf::Color::Black);
		//hud drawing
		m_hud->update();
		m_hud->draw(m_render);
		
		if (!isLost && m_hud->getTime() <= 0)
		{
			isLost = true;
			m_lostSound.play();
		}
		
		for (size_t i = 0; i < pieces.size(); i++)
		{
			size_t p = static_cast<size_t>(pieces[i]->getPosNum());
			pieces[i]->setPos(sf::Vector2f(pos[p].x+420.f, pos[p].y+60.f));
			m_render.draw(pieces[i]->getSprite());
		}
		
		empty.shape.setPosition(sf::Vector2f(pos[static_cast<long unsigned int>(empty.posNum)].x+422.f, pos[static_cast<long unsigned int>(empty.posNum)].y+62.f));
		m_render.draw(empty.shape);
		
		if (isWin || isHelp)
		{
			m_render.draw(image);
		}
		
		if (isLost)
		{
			m_render.draw(lostText);
		}
		if (isWin)
		{
			m_render.draw(winText);
		}
		
		for (size_t i=0;i<buttons.size();i++)
		{
			if ((!isWin && i < 2) || (isWin && buttons[i]->getCallBack() < static_cast<int>(m_imagesTexture.size())))
			{
				if (buttons[i]->isPressed() && mouseReleased)
				{
					mouseReleased = false;
					ingame = false;
					ret = buttons[i]->getCallBack();
					break;
				}
				buttons[i]->update(worldPos);
				m_render.draw(buttons[i]->getSprite());
			}
		}
		display();
	}

	for (size_t i = 0; i < buttons.size(); i++)
	{
		delete(buttons[i]);
	}
	buttons.clear();
	
	for (size_t i = 0; i < pieces.size(); i++)
	{
		delete(pieces[i]);
	}
	pieces.clear();
	return (ret);
}
