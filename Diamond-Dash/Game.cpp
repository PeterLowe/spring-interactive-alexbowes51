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
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
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
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
    m_window.draw(m_Minecart_Shape);
	m_window.draw(m_Minecart_Sprite);
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
	m_welcomeMessage.setPosition(200.0f, 530.0f);
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
}

void Game::SetUpCoveyerBelt()
{
	
}

void Game::SetUpMinecart()
{
	if (!m_Minecart_Texture.loadFromFile("ASSETS\\IMAGES\\Minecart.png"))
	{
		std::cout << "ERROR with Minecart" << std::endl;
	}
	m_Minecart_Sprite.setTexture(m_Minecart_Texture);
    m_MinecartLocation = sf::Vector2f{ 375.0f,400.0f };
	m_Minecart_Sprite.setPosition(m_MinecartLocation);
	m_Minecart_Sprite.setTextureRect(sf::IntRect{ 0,0,46,26 });
	m_Minecart_Sprite.setScale(4.0f, 4.0f);
	

	m_Minecart_Shape.setPosition(385.0f, 500.0f);
	m_Minecart_Shape_Location = sf::Vector2f{ 385.0f,500.0f };
	m_Minecart_Shape.setSize(sf::Vector2f{ 170.0f,50.0f });
	m_Minecart_Shape.setFillColor(sf::Color::Green);




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
		speed = speed * -1;

	}
	if (m_MinecartLocation.x > 630.0f || m_Minecart_Shape_Location.x > 630.0f)
	{
		m_MinecartLocation.x = 629.0f;
		m_Minecart_Shape_Location.x = 629.0f;
		speed = speed * -1;
	}

}

void Game::AnimateMinecart()
{
	int frame;
	const int Frame_Width = 45;
	const int Frame_Height = 26;

	m_MinecartFrameCount += m_MincecartFrameIncrement;
	frame = static_cast<int>(m_MinecartFrameCount);
	if(frame >= m_MinecartFrames)
	{ 
		frame = 0;
		m_MinecartFrameCount = 0;
	}
	if (frame != m_MinecartFrame)
	{
		m_MinecartFrame = frame;
		m_Minecart_Sprite.setTextureRect(sf::IntRect{ frame * 100,0,Frame_Width,Frame_Height });
	}
}