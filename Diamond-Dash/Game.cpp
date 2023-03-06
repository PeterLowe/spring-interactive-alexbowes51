/// <summary>
/// @author Alex Bowes
/// @date march 2023
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{Screen_Height, Screen_Width,32U }, "DIAMOND-DASH" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
	SetUpCoveyerBelt();//loads the Conveyer Belts
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_Direction = Direction::Left;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_Direction = Direction::Right;
	}
	MoveMinecart();
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	AnimateMinecart();
	AnimateCave();
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_Cave_Sprite);
    m_window.draw(m_Minecart_Shape);
    m_window.draw(m_Rail_Shape);
	m_window.draw(m_Minecart_Sprite);
	m_window.draw(m_Minecart_Rail_Sprite);
	m_window.draw(m_ConveryBelt_Shape_1);
	m_window.draw(m_ConveryBelt_Shape_2);
	m_window.draw(m_ConveryBelt_Shape_3);
	m_window.draw(m_ConveryBelt_Sprite_1);
	m_window.draw(m_ConveryBelt_Sprite_2);
	m_window.draw(m_ConveryBelt_Sprite_3);
	m_window.draw(m_welcomeMessage);
	m_window.draw(m_logoSprite);
	
	m_window.display();
	
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("Diamond-Dash");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(200.0f, 900.0f);
	m_welcomeMessage.setCharacterSize(60U);
	m_welcomeMessage.setOutlineColor(sf::Color::White);
	m_welcomeMessage.setFillColor(sf::Color::Blue);
	m_welcomeMessage.setOutlineThickness(3.0f);

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	SetUpMinecart();
	SetupCave();
}

void Game::SetupCave()
{
	if (!m_Cave_Texture.loadFromFile("ASSETS\\IMAGES\\Cave_Animation.png"))
	{
		std::cout << "ERROR with Cave" << std::endl;
	}
	m_Cave_Sprite.setTexture(m_Cave_Texture);
	m_Cave_Sprite.setTextureRect(sf::IntRect{ 0,0,100,100 });
	m_Cave_Sprite.setScale(8.0f, 10.0f);
}

void Game::AnimateMinecart()
{
	int frame;
	const int Frame_Width = 45;
	const int Frame_Height = 23;

	m_FrameCount += m_Minecart_FrameIncrement;
	frame = static_cast<int>(m_FrameCount);
	if (frame >= m_MinecartFrames)
	{
		frame = 0;
		m_FrameCount = 0;
	}
	if (frame != m_MinecartFrame)
	{
		m_MinecartFrame = frame;
		m_Minecart_Sprite.setTextureRect(sf::IntRect{ frame * 100,0,Frame_Width,Frame_Height });
	}
}

void Game::AnimateCave()
{
	int frame;
	const int Frame_Width = 100;
	const int Frame_Height = 100;

	m_FrameCount += m_Cave_Frame_Increment;
	frame = static_cast<int>(m_FrameCount);
	if (frame >= m_CaveFrames)
	{
		frame = 0;
		m_FrameCount = 0;
	}
	if (frame != m_CaveFrame)
	{
		m_CaveFrame = frame;
		m_Cave_Sprite.setTextureRect(sf::IntRect{ frame * 100,0,Frame_Width,Frame_Height });
	}
}

void Game::AnimateCoveryerBelt()
{

}

void Game::SetUpCoveyerBelt()
{

	m_ConveryBelt_Shape_1.setPosition(100.0f, 00.0f);
	m_ConveryBelt_Shape_1.setFillColor(sf::Color::Blue);
	m_ConveryBelt_Shape_1.setSize(sf::Vector2f{ 100.0f,100.0f });
	m_ConveryBeltLocation_1 = sf::Vector2f{ 70.0f,0.0f };

	m_ConveryBelt_Shape_2.setPosition(350.0f, 00.0f);
	m_ConveryBelt_Shape_2.setFillColor(sf::Color::Blue);
	m_ConveryBelt_Shape_2.setSize(sf::Vector2f{ 100.0f,100.0f });
	m_ConveryBeltLocation_2 = sf::Vector2f{ 320.0f,0.0f };

	m_ConveryBelt_Shape_3.setPosition(600.0f, 00.0f);
	m_ConveryBelt_Shape_3.setFillColor(sf::Color::Blue);
	m_ConveryBelt_Shape_3.setSize(sf::Vector2f{ 100.0f,100.0f });
	m_ConveryBeltLocation_3 = sf::Vector2f{ 570.0f,0.0f };

	if (!m_ConveryBelt_Texture_1.loadFromFile("ASSETS\\IMAGES\\ConveryBelt_Animation.png"))
	{
		std::cout << "ERROR with ConveryerBelt" << std::endl;
	}
	m_ConveryBelt_Sprite_1.setTexture(m_ConveryBelt_Texture_1);
	m_ConveryBelt_Sprite_1.setTextureRect(sf::IntRect{ 0,0,38,24 });
	m_ConveryBelt_Sprite_1.setScale(4.5f, 4.5f);
	m_ConveryBelt_Sprite_1.setPosition(m_ConveryBeltLocation_1);

	if (!m_ConveryBelt_Texture_2.loadFromFile("ASSETS\\IMAGES\\ConveryBelt_Animation.png"))
	{
		std::cout << "ERROR with ConveryerBelt" << std::endl;
	}
	m_ConveryBelt_Sprite_2.setTexture(m_ConveryBelt_Texture_2);
	m_ConveryBelt_Sprite_2.setTextureRect(sf::IntRect{ 0,0,38,24 });
	m_ConveryBelt_Sprite_2.setScale(4.5f, 4.5f);
    
	m_ConveryBelt_Sprite_2.setPosition(m_ConveryBeltLocation_2);
	if (!m_ConveryBelt_Texture_3.loadFromFile("ASSETS\\IMAGES\\ConveryBelt_Animation.png"))
	{
		std::cout << "ERROR with ConveryerBelt" << std::endl;
	}
	m_ConveryBelt_Sprite_3.setTexture(m_ConveryBelt_Texture_3);
	m_ConveryBelt_Sprite_3.setTextureRect(sf::IntRect{ 0,0,38,24 });
	m_ConveryBelt_Sprite_3.setScale(4.5f, 4.5f);
	m_ConveryBelt_Sprite_3.setPosition(m_ConveryBeltLocation_3);

}

void Game::SetUpMinecart()
{
	m_Minecart_Shape.setPosition(450.0f, 800.0f);
	m_Minecart_Shape_Location = sf::Vector2f{ 450.0f,800.0f };
	m_Minecart_Shape.setSize(sf::Vector2f{ 170.0f,50.0f });
	m_Minecart_Shape.setFillColor(sf::Color::Green);

	if (!m_Minecart_Texture.loadFromFile("ASSETS\\IMAGES\\Minecart.png"))
	{
		std::cout << "ERROR with Minecart" << std::endl;
	}
	m_Minecart_Sprite.setTexture(m_Minecart_Texture);
    m_MinecartLocation = sf::Vector2f{ 450.0f,710.0f };
	m_Minecart_Sprite.setPosition(m_MinecartLocation);
	m_Minecart_Sprite.setTextureRect(sf::IntRect{ 0,0,46,26 });
	m_Minecart_Sprite.setScale(4.0f, 4.0f);
	

	
	if (!m_Minecart_Rail_Texture.loadFromFile("ASSETS\\IMAGES\\Minecart_Rail.png"))
	{
		std::cout << "ERROR with Rail" << std::endl;
	}

	m_Minecart_Rail_Sprite.setTexture(m_Minecart_Rail_Texture);
	m_Minecart_Rail_Location = sf::Vector2f{0.0f, 733.0f};
    m_Minecart_Rail_Sprite.setPosition(m_Minecart_Rail_Location);
	m_Minecart_Rail_Sprite.setScale(4.5f, 4.5f);
	m_Minecart_Rail_Texture.setRepeated(true);
	m_Minecart_Rail_Sprite.setTextureRect(sf::IntRect{ 0,0,200,30});
    
	
	m_Rail_Shape.setFillColor(sf::Color::Blue);
	m_Rail_Shape.setSize(sf::Vector2f{ 1000.0f,30.0f });
	m_Rail_Shape.setPosition(0.0f,800.0f);

	
	
	

}

void Game::MoveMinecart()
{
	sf::Vector2f Moving{ 0.0f,0.0f };

	switch (m_Direction)
	{
	case Direction::None:
		break;
	case Direction::Right:
		Moving.x = speed;
		break;
	case Direction::Left:
		Moving.x = -speed;
		break;
	}

	m_MinecartLocation += Moving;
	m_Minecart_Shape_Location += Moving;
	m_Minecart_Sprite.setPosition(m_MinecartLocation);
	m_Minecart_Shape.setPosition(m_Minecart_Shape_Location);
	
	if (m_MinecartLocation.x < 0.0f||m_Minecart_Shape_Location.x < 0.0f)
	{
		m_MinecartLocation.x = 1.0f;
		m_Minecart_Shape_Location.x = 1.0f;
		m_Direction = Direction::Right;
  
	}
	if (m_MinecartLocation.x > 618.0f || m_Minecart_Shape_Location.x > 618.0f)
	{
		m_MinecartLocation.x = 618.0f;
		m_Minecart_Shape_Location.x = 618.0f;
		m_Direction = Direction::Left;

	}

}



