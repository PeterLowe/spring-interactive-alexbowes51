/// <summary>
/// author Alex Bowes 2023
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

float VectorLength(sf::Vector2f);

const int Screen_Width = 1000;
const int Screen_Height  = 800;

using namespace sf;

enum class Direction
{
	None,
	Right,
	Left,
};


class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	
	void setupFontAndText();//sets up text and fonts 
	void setupSprite();//sets up sprites 
	void SetUpCoveyerBelt();//sets ups converyer belts 
	void SetUpMinecart();//sets up minecart 
	void MoveMinecart();//moves minecart 
	void AnimateMinecart();//animates minecart 
	void SetupCave();//sets up cave 
	void AnimateCave();//animates cave 
	void AnimateCoveryerBelt();//animates coveryer belt 



	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo

	sf::Sprite m_ConveryBelt_Sprite_1;
	sf::Sprite m_ConveryBelt_Sprite_2;
	sf::Sprite m_ConveryBelt_Sprite_3;//Convery belt sprite 
	sf::Texture m_ConveryBelt_Texture_1;
	sf::Texture m_ConveryBelt_Texture_2;
	sf::Texture m_ConveryBelt_Texture_3;//Convery belt Texture 
	sf::Vector2f m_ConveryBeltLocation_1;//Convery belt Location
	sf::Vector2f m_ConveryBeltLocation_2;
	sf::Vector2f m_ConveryBeltLocation_3;
	sf::RectangleShape m_ConveryBelt_Shape_1;//Convery belt rectangle shape 1
	sf::RectangleShape m_ConveryBelt_Shape_2;
	sf::RectangleShape m_ConveryBelt_Shape_3;



	sf::Sprite m_Minecart_Sprite;//Minecart Sprite 
	sf::Texture m_Minecart_Texture;//Minecart Texture
	sf::Vector2f m_MinecartLocation;//Minecart Location 
	sf::RectangleShape m_Minecart_Shape;//Minecart rectangle shape 
	sf::Vector2f m_Minecart_Shape_Location;
	int m_MinecartFrame{ -1 };//will start changing the sprite 
	const int m_MinecartFrames = 4;//the amount of frames 
	float m_FrameCount = 0.0f;//frame counter for minecart animation 
	float m_Minecart_FrameIncrement = 0.02f;//frame increament 
	Direction m_Direction = Direction::None;//Direction of the Minecart 
	float speed = 3.0f;// speed of minecart 

	sf::Sprite m_Minecart_Rail_Sprite;//Rail sprite 
	sf::Texture m_Minecart_Rail_Texture;//Rail texture
	sf::Vector2f m_Minecart_Rail_Location;//Rail location 
	sf::RectangleShape m_Rail_Shape;//Rail shape 

	sf::Sprite m_Cave_Sprite;//Cave sprite
	sf::Texture m_Cave_Texture;//Cave texture
	const int m_CaveFrames = 7;//Amount of frame 
	int m_CaveFrame{ -1 };//Will change sprite 
	float m_Cave_Frame_Increment = 0.005f;//frame increase 

	

	bool m_Graphics{ false };
	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

