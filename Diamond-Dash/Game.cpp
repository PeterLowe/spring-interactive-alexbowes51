/// <summary>
/// @author Alex Bowes
/// @date march 2023
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>
#include <ctime>
#include <cstdlib>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{Screen_Height, Screen_Width,32U }, "DIAMOND-DASH" },//will create a window the size of 1000 x 800
	m_exitGame{false} //when true game will exit
{ 
	setupSprite(); // load texture
	setupFontAndText(); // load font 
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))//if tab is pressed 
	{
		m_Graphics = !m_Graphics;//m_graphics is set to false 
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))//if tab is pressed 
	{
		Game_Mode = 2;//m_graphics is set to false 
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
	if (Game_Mode == 2)
	{
    move_Falling_Objects();
    check_Catch(m_Rock_1, m_Rock_2, m_Rock_3, m_Diamond_1, m_Diamond_2, m_Diamond_3, m_FakeDiamond_1, m_FakeDiamond_2, m_FakeDiamond_3,	m_Minecart_Shape);
	AnimateDiamond();
	AnimateRocks();
	AnimateFakeDiamond();
	AnimateCoveryerBelt();
	AnimateCave();
	AnimateMinecart();
	}
	
 
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
   
	m_window.clear(sf::Color::White);
    
	if (Game_Mode == 1)//Intro
	{
		m_window.draw(m_Title_screen_Sprite);
		m_window.draw(m_Intro);
	}

	if (Game_Mode == 2)//Gameplay
	{
		if (m_Graphics == true)//if graphics is = true draw all thats in the if statement 
		{
			m_window.draw(m_Cave_Sprite);
			m_window.draw(m_Rock_Sprite_1);
			m_window.draw(m_Rock_Sprite_2);
			m_window.draw(m_Rock_Sprite_3);
			m_window.draw(m_Diamond_Sprite_1);
			m_window.draw(m_Diamond_Sprite_2);
			m_window.draw(m_Diamond_Sprite_3);
			m_window.draw(m_FakeDiamond_Sprite_1);
			m_window.draw(m_FakeDiamond_Sprite_2);
			m_window.draw(m_FakeDiamond_Sprite_3);
			m_window.draw(m_Minecart_Rail_Sprite);
			m_window.draw(m_Minecart_Sprite);
			m_window.draw(m_ConveryBelt_Sprite_1);
			m_window.draw(m_ConveryBelt_Sprite_2);
			m_window.draw(m_ConveryBelt_Sprite_3);
		}
		else//if graphics is = false draw the rest 
		{
			m_window.draw(m_Minecart_Shape);
			m_window.draw(m_Rail_Shape);
			m_window.draw(m_Rock_1);
			m_window.draw(m_Rock_2);
			m_window.draw(m_Rock_3);
			m_window.draw(m_Diamond_1);
			m_window.draw(m_Diamond_2);
			m_window.draw(m_Diamond_3);
			m_window.draw(m_FakeDiamond_1);
			m_window.draw(m_FakeDiamond_2);
			m_window.draw(m_FakeDiamond_3);
			m_window.draw(m_ConveryBelt_Shape_1);
			m_window.draw(m_ConveryBelt_Shape_2);
			m_window.draw(m_ConveryBelt_Shape_3);

		}
		m_window.draw(m_Title);
		m_window.draw(m_LIVES);
		m_window.draw(m_SCORE);
		
		if (m_Lives_count <= 0 || m_Score_count < 0)// if lives
		{
			m_window.clear();
			Game_Mode = 3;
		}
	}
	if (Game_Mode == 3)//Ending
	{
        m_window.draw(m_Game_over_Sprite);
		m_window.draw(m_Exit);
		
	}
	m_window.display();
	
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_CYBER_font.loadFromFile("ASSETS\\FONTS\\Bazer-K7vpp.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_Title.setFont(m_CYBER_font);
	m_Title.setString("Diamond-Dash");
	m_Title.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_Title.setPosition(150.0f, 810.0f);
	m_Title.setCharacterSize(40U);
	m_Title.setOutlineColor(sf::Color::Black);
	m_Title.setFillColor(sf::Color::Blue);
	m_Title.setOutlineThickness(3.5f);

	m_LIVES.setFont(m_CYBER_font);
	m_LIVES.setString("Diamond-Dash");
	m_LIVES.setCharacterSize(25U);//the size of the texted
	m_LIVES.setPosition(40.0f, 950.0f);// the position of the text
	m_LIVES.setFillColor(sf::Color::Yellow);// the color of the text 
	m_LIVES.setFont(m_CYBER_font);// the type of font for text
	m_LIVES.setString("LIVES = 5");// the message displayed for the text 
	m_LIVES.setOutlineColor(sf::Color::Black);//the outline color of the text 
	m_LIVES.setOutlineThickness(3.0f);//the size of the outline for text 

	m_SCORE.setCharacterSize(25U);//the size of the texted
	m_SCORE.setPosition(40.0f, 900.0f);// the position of the text
	m_SCORE.setFillColor(sf::Color::Yellow);// the color of the text 
	m_SCORE.setFont(m_CYBER_font);// the type of font 
	m_SCORE.setString("SCORE = 000");// the message displayed for the text
	m_SCORE.setOutlineColor(sf::Color::Black);//the outline color of the text 
	m_SCORE.setOutlineThickness(3.0f);//the outline size of the text

	m_Intro.setCharacterSize(25U);//the size of the texted
	m_Intro.setPosition(200.0f, 600.0f);// the position of the text
	m_Intro.setFillColor(sf::Color::Blue);// the color of the text 
	m_Intro.setFont(m_CYBER_font);// the type of font 
	m_Intro.setString("Press enter to begin");// the message displayed for the text
	m_Intro.setOutlineColor(sf::Color::Black);//the outline color of the text 
	m_Intro.setOutlineThickness(3.0f);//the outline size of the text

	m_Exit.setCharacterSize(25U);//the size of the texted
	m_Exit.setPosition(200.0f, 600.0f);// the position of the text
	m_Exit.setFillColor(sf::Color::Red);// the color of the text 
	m_Exit.setFont(m_CYBER_font);// the type of font 
	m_Exit.setString("Press ESC to escape");// the message displayed for the text
	m_Exit.setOutlineColor(sf::Color::Black);//the outline color of the text 
	m_Exit.setOutlineThickness(3.0f);//the outline size of the text
}


/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	SetUpMinecart();
	SetupCave();
    Setup_Objects();
	Setup_Falling_Objects_1();
	Setup_Falling_Objects_2();
	Setup_Falling_Objects_3();

	if (!m_Game_over_Texture.loadFromFile("ASSETS\\IMAGES\\game-over.png"))
	{
		std::cout << "ERROR with Game over" << std::endl;
	}
	m_Game_over_Sprite.setTexture(m_Game_over_Texture);
	m_Game_over_Sprite.setScale(16.0f, 20.0f);

	if (!m_Title_screen_Texture.loadFromFile("ASSETS\\IMAGES\\TitleScreen.png"))
	{
		std::cout << "ERROR with Title-Screen" << std::endl;
	}
	 m_Title_screen_Sprite.setTexture(m_Title_screen_Texture);
	 m_Title_screen_Sprite.setScale(16.0f, 20.0f);
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

//Animates cave
void Game::AnimateCave()
{
	int frame;
	const int Frame_Width = 100;
	const int Frame_Height = 100;

	m_CV_FrameCount += m_Cave_Frame_Increment;
	frame = static_cast<int>(m_CV_FrameCount);
	if (frame >= m_CaveFrames)
	{
		frame = 0;
		m_CV_FrameCount = 0;
	}
	if (frame != m_CaveFrame)
	{
		m_CaveFrame = frame;
		m_Cave_Sprite.setTextureRect(sf::IntRect{ frame * 100,0,Frame_Width,Frame_Height });
	}
}

//Animate Minecart
void Game::AnimateMinecart()
{
	int frame;
	const int Frame_Width = 45;
	const int Frame_Height = 23;

	m_MC_FrameCount += m_Minecart_FrameIncrement;
	frame = static_cast<int>(m_MC_FrameCount);
	if (frame >= m_MinecartFrames)
	{
		frame = 0;
		m_MC_FrameCount = 0;
	}
	if (frame != m_MinecartFrame)
	{
		m_MinecartFrame = frame;
		m_Minecart_Sprite.setTextureRect(sf::IntRect{ frame * 100,0,Frame_Width,Frame_Height });
	}
}


//Animates Converyer 
void Game::AnimateCoveryerBelt()
{
	int frame;
	const int Frame_Width = 44;
	const int Frame_Height = 24;
	m_CB_FrameCount += m_Converyer_Frame_Increment;
	frame = static_cast<int>(m_CB_FrameCount);
	if (frame >= m_ConveryerFrames)
	{
		frame = 0;
		m_CB_FrameCount = 0;
	}
	if (frame != m_ConveryerFrame)
	{
		m_ConveryerFrame = frame;
	    m_ConveryBelt_Sprite_1.setTextureRect(sf::IntRect{ frame * 44,0,Frame_Width,Frame_Height });
		m_ConveryBelt_Sprite_2.setTextureRect(sf::IntRect{ frame * 44,0,Frame_Width,Frame_Height });
		m_ConveryBelt_Sprite_3.setTextureRect(sf::IntRect{ frame * 44,0,Frame_Width,Frame_Height });
		
	}

}

//Animtes Rock
void Game::AnimateRocks()
{
	int frame;
	const int Frame_Width = 26;
	const int Frame_Height = 30;
	m_R_FrameCount += m_Rock_FrameIncrement;
	frame = static_cast<int>(m_R_FrameCount);
	if (frame >= m_RockFrames)
	{
		frame = 0;
		m_R_FrameCount = 0;
	}
	if (frame != m_RockFrame)
	{
		m_RockFrame = frame;
		m_Rock_Sprite_1.setTextureRect(sf::IntRect{ frame * 30,0,Frame_Width,Frame_Height });
		m_Rock_Sprite_2.setTextureRect(sf::IntRect{ frame * 30,0,Frame_Width,Frame_Height });
		m_Rock_Sprite_3.setTextureRect(sf::IntRect{ frame * 30,0,Frame_Width,Frame_Height });

	}
}

//Animates Diamonds
void Game::AnimateDiamond()
{
	int frame;
	const int Frame_Width = 11;
	const int Frame_Height = 26;
	m_D_FrameCount += m_Diamond_FrameIncrement;
	frame = static_cast<int>(m_D_FrameCount);
	if (frame >= m_DiamondFrames)
	{
		frame = 0;
		m_D_FrameCount = 0;
	}
	if (frame != m_DiamondFrame)
	{
		m_DiamondFrame = frame;
		m_Diamond_Sprite_1.setTextureRect(sf::IntRect{ frame * 30,0,Frame_Width,Frame_Height });
		m_Diamond_Sprite_2.setTextureRect(sf::IntRect{ frame * 30,0,Frame_Width,Frame_Height });
		m_Diamond_Sprite_3.setTextureRect(sf::IntRect{ frame * 30,0,Frame_Width,Frame_Height });

	}

}

//Animates Fake Diamonds 
void Game::AnimateFakeDiamond()
{
	int frame;
	const int Frame_Width = 10;
	const int Frame_Height = 30;
	m_F_FrameCount += m_FAKE_FrameIncrement;
	frame = static_cast<int>(m_F_FrameCount);
	if (frame >= m_FAKEFrames)
	{
		frame = 0;
		m_F_FrameCount = 0;
	}
	if (frame != m_FAKEFrame)
	{
		m_FAKEFrame = frame;
		m_FakeDiamond_Sprite_1.setTextureRect(sf::IntRect{ frame * 30,0,Frame_Width,Frame_Height });
		m_FakeDiamond_Sprite_2.setTextureRect(sf::IntRect{ frame * 30,0,Frame_Width,Frame_Height });
		m_FakeDiamond_Sprite_3.setTextureRect(sf::IntRect{ frame * 30,0,Frame_Width,Frame_Height });
	}

}

void Game::Setup_Objects()
{
	
}

//Randomly picks a object from 1-3 
void Game::Setup_Falling_Objects_1()
{

	srand((unsigned)time(0));
	int Number_1;
	Number_1 = (rand() % 3) + 1;

	if (Number_1 == 3)
	{
		if (!m_Rock_Texture_1.loadFromFile("ASSETS\\IMAGES\\Rock.png"))
		{
			std::cout << "ERROR with rock" << std::endl;
		}
		m_Rock_Sprite_1.setTexture(m_Rock_Texture_1);
		m_Rock_Sprite_1.setTextureRect(sf::IntRect(0, 0, 26, 30));
		m_Rock_Location_1 = sf::Vector2f{ 150.0f,100.0f };
		m_Rock_Sprite_1.setScale(2.0f, 2.0f);

		m_Rock_1.setFillColor(sf::Color::Magenta);
		m_Rock_1.setRadius(15.0f);
		m_Rock_1.setOrigin(15.0f, 15.0f);
		m_Rock_1.setPosition(m_Rock_Location_1);
		m_Rock_Sprite_1.setPosition(m_Rock_Location_1);

	}
	if (Number_1 == 2)
	{

		if (!m_Diamond_Texture_1.loadFromFile("ASSETS\\IMAGES\\Diamond.png"))
		{
			std::cout << "ERROR with Diamond" << std::endl;
		}
		m_Diamond_Sprite_1.setTexture(m_Diamond_Texture_1);
		m_Diamond_Sprite_1.setTextureRect(sf::IntRect(0, 0, 11, 26));
		m_Diamond_Location_1 = sf::Vector2f{ 150.0f,100.0f };
		m_Diamond_Sprite_1.setScale(4.0f, 4.0f);

		m_Diamond_1.setFillColor(sf::Color::Blue);
		m_Diamond_1.setRadius(15.0f);
		m_Diamond_1.setOrigin(15.0f, 15.0f);
		m_Diamond_1.setPosition(m_Diamond_Location_1);
		m_Diamond_Sprite_1.setPosition(m_Diamond_Location_1);
	}
	if (Number_1 == 1)
	{
		if (!m_FakeDiamond_Texture_1.loadFromFile("ASSETS\\IMAGES\\FakeDiamond.png"))
		{
			std::cout << "ERROR with fake diamond" << std::endl;
		}
		m_FakeDiamond_Sprite_1.setTexture(m_FakeDiamond_Texture_1);
		m_FakeDiamond_Sprite_1.setTextureRect(sf::IntRect(0, 0, 10, 30));
		m_FakeDiamond_Location_1 = sf::Vector2f{ 150.0f,100.0f };
		m_FakeDiamond_Sprite_1.setScale(4.5f, 4.5f);


		m_FakeDiamond_1.setFillColor(sf::Color::Red);
		m_FakeDiamond_1.setRadius(15.0f);
		m_FakeDiamond_1.setOrigin(15.0f, 15.0f);
		m_FakeDiamond_1.setPosition(m_FakeDiamond_Location_1);
		m_FakeDiamond_Sprite_1.setPosition(m_FakeDiamond_Location_1);
	}

}

//Randomly picks a object from 1-3 
void Game::Setup_Falling_Objects_2()
{
	srand((unsigned)time(0));
	int Number_2;
	Number_2 = (rand() % 3) + 1;

	if (Number_2 == 2)
	{
		if (!m_Rock_Texture_2.loadFromFile("ASSETS\\IMAGES\\Rock.png"))
		{
			std::cout << "ERROR with rock" << std::endl;
		}
		m_Rock_Sprite_2.setTexture(m_Rock_Texture_2);
		m_Rock_Sprite_2.setTextureRect(sf::IntRect(0, 0, 26, 30));
		m_Rock_Location_2 = sf::Vector2f{ 400.0f,100.0f };
		m_Rock_Sprite_2.setScale(2.0f, 2.0f);

		m_Rock_2.setFillColor(sf::Color::Magenta);
		m_Rock_2.setRadius(15.0f);
		m_Rock_2.setOrigin(15.0f, 15.0f);
		m_Rock_2.setPosition(m_Rock_Location_2);
		m_Rock_Sprite_2.setPosition(m_Rock_Location_2);
	}
	if (Number_2 == 1)
	{

		if (!m_Diamond_Texture_2.loadFromFile("ASSETS\\IMAGES\\Diamond.png"))
		{
			std::cout << "ERROR with Diamond" << std::endl;
		}
		m_Diamond_Sprite_2.setTexture(m_Diamond_Texture_2);
		m_Diamond_Sprite_2.setTextureRect(sf::IntRect(0, 0, 11, 26));
		m_Diamond_Location_2 = sf::Vector2f{ 400.0f,100.0f };
		m_Diamond_Sprite_2.setScale(4.0f, 4.0f);

		m_Diamond_2.setFillColor(sf::Color::Blue);
		m_Diamond_2.setRadius(15.0f);
		m_Diamond_2.setOrigin(15.0f, 15.0f);
		m_Diamond_2.setPosition(m_Diamond_Location_2);
		m_Diamond_Sprite_2.setPosition(m_Diamond_Location_2);
	}
	if (Number_2 == 3)
	{
		if (!m_FakeDiamond_Texture_2.loadFromFile("ASSETS\\IMAGES\\FakeDiamond.png"))
		{
			std::cout << "ERROR with fake diamond" << std::endl;
		}
		m_FakeDiamond_Sprite_2.setTexture(m_FakeDiamond_Texture_2);
		m_FakeDiamond_Sprite_2.setTextureRect(sf::IntRect(0, 0, 10, 30));
		m_FakeDiamond_Location_2 = sf::Vector2f{ 400.0f,100.0f };
		m_FakeDiamond_Sprite_2.setScale(4.5f, 4.5f);

		m_FakeDiamond_2.setFillColor(sf::Color::Red);
		m_FakeDiamond_2.setRadius(15.0f);
		m_FakeDiamond_2.setOrigin(15.0f, 15.0f);
		m_FakeDiamond_Sprite_2.setPosition(m_FakeDiamond_Location_2);

	}

}

//Randomly picks a object from 1-3 
void Game::Setup_Falling_Objects_3()
{

		srand((unsigned)time(0));
		int Number_3;
		Number_3 = (rand() % 3) + 1;

		if (Number_3 == 1)
		{
			if (!m_Rock_Texture_3.loadFromFile("ASSETS\\IMAGES\\Rock.png"))
			{
				std::cout << "ERROR with rock" << std::endl;
			}
			m_Rock_Sprite_3.setTexture(m_Rock_Texture_3);
			m_Rock_Sprite_3.setTextureRect(sf::IntRect(0, 0, 26, 30));
			m_Rock_Location_3 = sf::Vector2f{ 650.0f,100.0f };
			m_Rock_Sprite_3.setScale(2.0f, 2.0f);

			m_Rock_3.setFillColor(sf::Color::Magenta);
			m_Rock_3.setRadius(15.0f);
			m_Rock_3.setOrigin(15.0f, 15.0f);
			m_Rock_3.setPosition(m_Rock_Location_3);
			m_Rock_Sprite_3.setPosition(m_Rock_Location_3);
		}
		if (Number_3 == 3)
		{
			if (!m_Diamond_Texture_3.loadFromFile("ASSETS\\IMAGES\\Diamond.png"))
			{
				std::cout << "ERROR with Diamond" << std::endl;
			}
			m_Diamond_Sprite_3.setTexture(m_Diamond_Texture_3);
			m_Diamond_Sprite_3.setTextureRect(sf::IntRect(0, 0, 11, 26));
			m_Diamond_Location_3 = sf::Vector2f{ 650.0f,100.0f };
			m_Diamond_Sprite_3.setScale(4.0f, 4.0f);

			m_Diamond_3.setFillColor(sf::Color::Blue);
			m_Diamond_3.setRadius(15.0f);
			m_Diamond_3.setOrigin(15.0f, 15.0f);
			m_Diamond_3.setPosition(m_Diamond_Location_3);
			m_Diamond_Sprite_3.setPosition(m_Diamond_Location_3);
		}
		if (Number_3 == 2)
		{
			if (!m_FakeDiamond_Texture_3.loadFromFile("ASSETS\\IMAGES\\FakeDiamond.png"))
			{
				std::cout << "ERROR with fake diamond" << std::endl;
			}
			m_FakeDiamond_Sprite_3.setTexture(m_FakeDiamond_Texture_3);
			m_FakeDiamond_Sprite_3.setTextureRect(sf::IntRect(0, 0, 10, 30));
			m_FakeDiamond_Location_3 = sf::Vector2f{ 650.0f,100.0f };
			m_FakeDiamond_Sprite_3.setScale(4.5f, 4.5f);


			m_FakeDiamond_3.setFillColor(sf::Color::Red);
			m_FakeDiamond_3.setRadius(15.0f);
			m_FakeDiamond_3.setOrigin(15.0f, 15.0f);
			m_FakeDiamond_3.setPosition(m_FakeDiamond_Location_3);
			m_FakeDiamond_Sprite_3.setPosition(m_FakeDiamond_Location_3);
		}


}

//Moves the Falling Objects 
void Game::move_Falling_Objects() 
{
	const float speed_1 = 2.0f;
	const float speed_2 = 2.0f;
	const float speed_3 = 2.0f;



	if (m_Rock_Location_1.y < 10000 && m_Rock_Location_2.y < 10000 && m_Rock_Location_3.y < 10000)
	{
		m_Rock_Velocity_1.y = speed_1;
		m_Rock_Velocity_2.y = speed_1;
		m_Rock_Velocity_3.y = speed_1;	

     m_Rock_Location_1 += m_Rock_Velocity_1;
     m_Rock_1.setPosition(m_Rock_Location_1);
	 m_Rock_Sprite_1.setPosition(m_Rock_Location_1);

     m_Rock_Location_2 += m_Rock_Velocity_2;
     m_Rock_2.setPosition(m_Rock_Location_2);
	  m_Rock_Sprite_2.setPosition(m_Rock_Location_2);

	 m_Rock_Location_3 += m_Rock_Velocity_3;
	 m_Rock_3.setPosition(m_Rock_Location_3);
	 m_Rock_Sprite_3.setPosition(m_Rock_Location_3);

	}

	if (m_Diamond_Location_1.y < 10000 && m_Diamond_Location_2.y < 10000 && m_Diamond_Location_3.y <10000)
	{
		m_Diamon_Velocity_1.y = speed_2;
		m_Diamon_Velocity_2.y = speed_2;
		m_Diamon_Velocity_3.y = speed_2;


   
	m_Diamond_Location_1 += m_Diamon_Velocity_1;
     m_Diamond_1.setPosition(m_Diamond_Location_1);
	m_Diamond_Sprite_1.setPosition(m_Diamond_Location_1);

    m_Diamond_Location_2 += m_Diamon_Velocity_2;
	m_Diamond_2.setPosition(m_Diamond_Location_2);
	m_Diamond_Sprite_2.setPosition(m_Diamond_Location_2);

	m_Diamond_Location_3 += m_Diamon_Velocity_3;
	m_Diamond_3.setPosition(m_Diamond_Location_3);
	m_Diamond_Sprite_3.setPosition(m_Diamond_Location_3);
	
	
	}

	if (m_FakeDiamond_Location_1.y < 10000 && m_FakeDiamond_Location_2.y < 10000 && m_FakeDiamond_Location_3.y < 10000)
	{
		m_FakeDiamond_Velocity_1.y = speed_3;
		m_FakeDiamond_Velocity_2.y = speed_3;
		m_FakeDiamond_Velocity_3.y = speed_3;

        m_FakeDiamond_1.setPosition(m_FakeDiamond_Location_1);
	    m_FakeDiamond_Location_1 += m_FakeDiamond_Velocity_1;
	    m_FakeDiamond_Sprite_1.setPosition(m_FakeDiamond_Location_1);

	    m_FakeDiamond_2.setPosition(m_FakeDiamond_Location_2);
	    m_FakeDiamond_Location_2 += m_FakeDiamond_Velocity_2;
	    m_FakeDiamond_Sprite_2.setPosition(m_FakeDiamond_Location_2);

	    m_FakeDiamond_3.setPosition(m_FakeDiamond_Location_3);
	    m_FakeDiamond_Location_3 += m_FakeDiamond_Velocity_3;
	    m_FakeDiamond_Sprite_3.setPosition(m_FakeDiamond_Location_3);

		
	}
	

}

//Checks if Falling Objects hit the minecart and boundry checks + Moves the Objects to each row.
void Game::check_Catch(sf::CircleShape m_Rock_1, sf::CircleShape m_Rock_2, sf::CircleShape m_Rock_3, sf::CircleShape m_Diamond_1, sf::CircleShape m_Diamond_2, sf::CircleShape m_Diamond_3, sf::CircleShape m_FakeDiamond_1, sf::CircleShape m_FakeDiamond_2, sf::CircleShape m_FakeDiamond_3, sf::RectangleShape& m_Minecart_Shape)
{
	bool result = true;

	sf::FloatRect Minecart = m_Minecart_Shape.getGlobalBounds();

	sf::FloatRect Rock_1 = m_Rock_1.getGlobalBounds();
	sf::FloatRect Rock_2 = m_Rock_2.getGlobalBounds();
	sf::FloatRect Rock_3 = m_Rock_3.getGlobalBounds();

	sf::FloatRect Diamond_1 = m_Diamond_1.getGlobalBounds();
	sf::FloatRect Diamond_2 = m_Diamond_2.getGlobalBounds();
	sf::FloatRect Diamond_3 = m_Diamond_3.getGlobalBounds();

	sf::FloatRect FakeDiamond_1 = m_FakeDiamond_1.getGlobalBounds();
	sf::FloatRect FakeDiamond_2 = m_FakeDiamond_2.getGlobalBounds();
	sf::FloatRect FakeDiamond_3 = m_FakeDiamond_3.getGlobalBounds();

	if (Diamond_1.intersects(Minecart) || Diamond_2.intersects(Minecart) || Diamond_3.intersects(Minecart))
	{

		m_Score_count = m_Score_count + 100;
		m_SCORE.setString("SCORE = " + std::to_string(m_Score_count));
		

	}
	if (FakeDiamond_1.intersects(Minecart) || FakeDiamond_2.intersects(Minecart) || FakeDiamond_3.intersects(Minecart))
	{
		m_Lives_count--;
		m_LIVES.setString("LIVES = " + std::to_string(m_Lives_count));
	
	}
	if (Rock_1.intersects(Minecart) || Rock_2.intersects(Minecart) || Rock_3.intersects(Minecart))
	{
		m_Score_count = m_Score_count - 50;
		m_SCORE.setString("SCORE = " + std::to_string(m_Score_count));
		
	}
	if (Rock_1.intersects(Minecart) || Diamond_1.intersects(Minecart) || FakeDiamond_1.intersects(Minecart))
	{

		m_Rock_Location_1.x += 250;
		m_Rock_1.setPosition(m_Rock_Location_1);
		m_Rock_Sprite_1.setPosition(m_Rock_Location_1);

		
		m_Diamond_Location_1.x += 250;
		m_Diamond_1.setPosition(m_Diamond_Location_1);
		m_Diamond_Sprite_1.setPosition(m_Diamond_Location_1);

	
		m_FakeDiamond_Location_1.x += 250;
		m_FakeDiamond_1.setPosition(m_FakeDiamond_Location_1);
		m_FakeDiamond_Sprite_1.setPosition(m_FakeDiamond_Location_1);

		if (m_Rock_Location_1.x > 650.0f || m_Diamond_Location_1.x > 650.0f || m_FakeDiamond_Location_1.x > 650.0f)
		{
			m_Rock_Location_1.x = 150.0f;
			m_Diamond_Location_1.x = 150.0f;
			m_FakeDiamond_Location_1.x = 150.0f;
		}

		
	}
	if (Rock_2.intersects(Minecart) || Diamond_2.intersects(Minecart) || FakeDiamond_2.intersects(Minecart))
	{
		
		m_Rock_Location_2.x += 250.0f;
		m_Rock_2.setPosition(m_Rock_Location_2);
		m_Rock_Sprite_2.setPosition(m_Rock_Location_2);

	
		m_Diamond_Location_2.x += 250;
		m_Diamond_2.setPosition(m_Diamond_Location_2);
		m_Diamond_Sprite_2.setPosition(m_Diamond_Location_2);

		
		m_FakeDiamond_Location_2.x += 250;
		m_FakeDiamond_2.setPosition(m_FakeDiamond_Location_2);
		m_FakeDiamond_Sprite_2.setPosition(m_FakeDiamond_Location_2);

		if (m_Rock_Location_2.x > 650.0f || m_Diamond_Location_2.x > 650.0f || m_FakeDiamond_Location_2.x > 650.0f)
		{
			m_Rock_Location_2.x = 150.0f;
			m_Diamond_Location_2.x = 150.0f;
			m_FakeDiamond_Location_2.x = 150.0f;
		}


	}
	if (Rock_3.intersects(Minecart) || Diamond_3.intersects(Minecart) || FakeDiamond_3.intersects(Minecart))
	{
		
		m_Rock_Location_3.x += 250.0f;
		m_Rock_3.setPosition(m_Rock_Location_3);
		m_Rock_Sprite_3.setPosition(m_Rock_Location_3);


		
		m_Diamond_Location_3.x += 250;
		m_Diamond_3.setPosition(m_Diamond_Location_3);
		m_Diamond_Sprite_3.setPosition(m_Diamond_Location_3);

		
		m_FakeDiamond_Location_3.x += 250;
		m_FakeDiamond_3.setPosition(m_FakeDiamond_Location_3);
		m_FakeDiamond_Sprite_3.setPosition(m_FakeDiamond_Location_3);

		if (m_Rock_Location_3.x > 650.0f || m_Diamond_Location_3.x > 650.0f || m_FakeDiamond_Location_3.x > 650.0f)
		{
			m_Rock_Location_3.x = 150.0f;
			m_Diamond_Location_3.x = 150.0f;
			m_FakeDiamond_Location_3.x = 150.0f;
		}

		
	}
	if (m_Rock_Location_1.y > Screen_Width || m_Diamond_Location_1.y > Screen_Width || m_FakeDiamond_Location_1.y > Screen_Width)
	{
		m_Rock_Location_1.y = (150.0f, 100.0f);
		m_Rock_Location_1.x += 250;
		m_Diamond_Location_1.y = (150.0f, 100.0f);
		m_Diamond_Location_1.x += 250;
	    m_FakeDiamond_Location_1.y = (150.0f, 100.0f); 
		m_FakeDiamond_Location_1.x += 250;

		if (m_Rock_Location_1.x > 650.0f || m_Diamond_Location_1.x > 650.0f || m_FakeDiamond_Location_1.x > 650.0f)
		{
			m_Rock_Location_1.x = 150.0f;
			m_Diamond_Location_1.x = 150.0f;
			m_FakeDiamond_Location_1.x = 150.0f;
		}

		
    }
	if (m_Rock_Location_2.y > Screen_Width || m_Diamond_Location_2.y > Screen_Width || m_FakeDiamond_Location_2.y > Screen_Width)
	{
		m_Rock_Location_2.y = ( 400.0f,100.0f );
		m_Rock_Location_2.x += 250;
		m_Diamond_Location_2.y = ( 400.0f,100.0f );
		m_Diamond_Location_2.x += 250;
		m_FakeDiamond_Location_2.y = (400.0f, 100.0f);
		m_FakeDiamond_Location_2.x += 250;

		if (m_Rock_Location_2.x > 650.0f || m_Diamond_Location_2.x > 650.0f || m_FakeDiamond_Location_2.x > 650.0f)
		{
			m_Rock_Location_2.x = 150.0f;
			m_Diamond_Location_2.x = 150.0f;
			m_FakeDiamond_Location_2.x = 150.0f;
		}

		
	}
	if (m_Rock_Location_3.y > Screen_Width || m_Diamond_Location_3.y > Screen_Width || m_FakeDiamond_Location_3.y > Screen_Width)
	{
		m_Rock_Location_3.y = ( 650.0f,100.0f );
		m_Rock_Location_3.x += 250;
        m_Diamond_Location_3.y = (650.0f,100.0f );
		m_Diamond_Location_3.x += 250;
		m_FakeDiamond_Location_3.y = ( 650.0f,100.0f );
		m_FakeDiamond_Location_3.x += 250;

		if (m_Rock_Location_3.x > 650.0f || m_Diamond_Location_3.x > 650.0f || m_FakeDiamond_Location_3.x > 650.0f)
		{
			m_Rock_Location_3.x = 150.0f;
			m_Diamond_Location_3.x = 150.0f;
			m_FakeDiamond_Location_3.x = 150.0f;
		}
		
	}
	
}

//Sets up Converyer Belt sprite
void Game::SetUpCoveyerBelt()
{

	m_ConveryBelt_Shape_1.setPosition(100.0f, 00.0f);
	m_ConveryBelt_Shape_1.setFillColor(sf::Color::Black);
	m_ConveryBelt_Shape_1.setSize(sf::Vector2f{ 100.0f,100.0f });
	m_ConveryBeltLocation_1 = sf::Vector2f{ 70.0f,0.0f };

	m_ConveryBelt_Shape_2.setPosition(350.0f, 00.0f);
	m_ConveryBelt_Shape_2.setFillColor(sf::Color::Black);
	m_ConveryBelt_Shape_2.setSize(sf::Vector2f{ 100.0f,100.0f });
	m_ConveryBeltLocation_2 = sf::Vector2f{ 320.0f,0.0f };

	m_ConveryBelt_Shape_3.setPosition(600.0f, 00.0f);
	m_ConveryBelt_Shape_3.setFillColor(sf::Color::Black);
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

//Sets up Minecart + Rail Sprite 
void Game::SetUpMinecart()
{
	m_Minecart_Shape.setPosition(450.0f, 710.0f);
	m_Minecart_Shape_Location = sf::Vector2f{ 450.0f,710.0f };
	m_Minecart_Shape.setSize(sf::Vector2f{ 170.0f,100.0f });
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
	m_Minecart_Rail_Location = sf::Vector2f{0.0f, 650.0f};
    m_Minecart_Rail_Sprite.setPosition(m_Minecart_Rail_Location);
	m_Minecart_Rail_Sprite.setScale(4.5f, 9.5f);
	m_Minecart_Rail_Texture.setRepeated(true);
	m_Minecart_Rail_Sprite.setTextureRect(sf::IntRect{ 0,0,200,30});
    

	m_Rail_Shape.setFillColor(sf::Color::Blue);
	m_Rail_Shape.setSize(sf::Vector2f{ 1000.0f,30.0f });
	m_Rail_Shape.setPosition(0.0f,800.0f);
}

//Moves Minecart + Boundary checking 
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
 
	}
	if (m_MinecartLocation.x > 618.0f || m_Minecart_Shape_Location.x > 618.0f)
	{
		m_MinecartLocation.x = 618.0f;
		m_Minecart_Shape_Location.x = 618.0f;

	}

}



