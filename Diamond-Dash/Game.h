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

const int Screen_Width = 1000;//screen width 
const int Screen_Height  = 800;//screen height 

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
	void SetUpMinecart();//sets up minecart 
	void MoveMinecart();//moves minecart 
	void AnimateMinecart();//animates minecart 
	void SetupCave();//sets up cave 
	void AnimateCave();//animates cave 
	void SetUpCoveyerBelt();//sets ups converyer belts 
	void AnimateCoveryerBelt();//animates coveryer belt 
	void Setup_Objects();
	void Setup_Falling_Objects_1();
	void Setup_Falling_Objects_2();
	void Setup_Falling_Objects_3();
	void move_Falling_Objects();
	void check_Catch(sf::CircleShape m_Rock_1,sf::CircleShape m_Rock_2,sf::CircleShape m_Rock_3,sf::CircleShape m_Diamond_1, sf::CircleShape m_Diamond_2, sf::CircleShape m_Diamond_3,sf::CircleShape m_FakeDiamond_1, sf::CircleShape m_FakeDiamond_2, sf::CircleShape m_FakeDiamond_3, sf::RectangleShape& m_Minecart_Shape);


	sf::RenderWindow m_window; // main SFML window
	sf::Font m_CYBER_font; // font used by message
	sf::Text m_Title; //Game Title 
	sf::Text m_LIVES;//Lives counter 
	int m_Lives_count{ 5 };
	sf::Text m_SCORE;//Score counter 
	int m_Score_count{ 0 };

	sf::Sprite m_ConveryBelt_Sprite_1;//Convery belt sprite 1
	sf::Sprite m_ConveryBelt_Sprite_2;//Convery belt sprite 2
	sf::Sprite m_ConveryBelt_Sprite_3;//Convery belt sprite 3
	sf::Texture m_ConveryBelt_Texture_1;//Convery belt Texture 1
	sf::Texture m_ConveryBelt_Texture_2;//Convery belt Texture 2
	sf::Texture m_ConveryBelt_Texture_3;//Convery belt Texture 3
	sf::Vector2f m_ConveryBeltLocation_1;//Convery belt Location 1
	sf::Vector2f m_ConveryBeltLocation_2;//Convery belt Location 2
	sf::Vector2f m_ConveryBeltLocation_3;//Convery belt Location 3 
	sf::RectangleShape m_ConveryBelt_Shape_1;//Convery belt rectangle shape 1
	sf::RectangleShape m_ConveryBelt_Shape_2;//Convery belt rectangle shape 2
	sf::RectangleShape m_ConveryBelt_Shape_3;//Convery belt rectangle shape 3

	sf::Sprite m_Rock_Sprite_1;
	sf::Texture m_Rock_Texture_1;
	sf::Sprite m_Rock_Sprite_2;
	sf::Texture m_Rock_Texture_2;
	sf::Sprite m_Rock_Sprite_3;
	sf::Texture m_Rock_Texture_3;

	sf::Sprite m_Diamond_Sprite_1;
	sf::Texture m_Diamond_Texture_1;
	sf::Sprite m_Diamond_Sprite_2;
    sf::Texture m_Diamond_Texture_2;	
	sf::Sprite m_Diamond_Sprite_3;
	sf::Texture m_Diamond_Texture_3;

	sf::Sprite m_FakeDiamond_Sprite_1;
	sf::Texture m_FakeDiamond_Texture_1;
	sf::Sprite m_FakeDiamond_Sprite_2;
	sf::Texture m_FakeDiamond_Texture_2;
	sf::Sprite m_FakeDiamond_Sprite_3;
	sf::Texture m_FakeDiamond_Texture_3;
	

	sf::Sprite m_Minecart_Sprite;//Minecart Sprite 
	sf::Texture m_Minecart_Texture;//Minecart Texture
	sf::Vector2f m_MinecartLocation;//Minecart Location 
	sf::RectangleShape m_Minecart_Shape;//Minecart rectangle shape 
	sf::Vector2f m_Minecart_Shape_Location;
	Direction m_Direction = Direction::None;//Direction of the Minecart 
	float speed = 3.0f;// speed of minecart 

	sf::Sprite m_Minecart_Rail_Sprite;//Rail sprite 
	sf::Texture m_Minecart_Rail_Texture;//Rail texture
	sf::Vector2f m_Minecart_Rail_Location;//Rail location 
	sf::RectangleShape m_Rail_Shape;//Rail shape 

	sf::Sprite m_Cave_Sprite;//Cave sprite
	sf::Texture m_Cave_Texture;//Cave texture

	sf::CircleShape m_Rock_1;
	sf::Vector2f m_Rock_Location_1;
	sf::Vector2f m_Rock_Velocity_1;
	sf::CircleShape m_Rock_2;
	sf::Vector2f m_Rock_Location_2;
	sf::Vector2f m_Rock_Velocity_2;
	sf::CircleShape m_Rock_3;
	sf::Vector2f m_Rock_Location_3;
	sf::Vector2f m_Rock_Velocity_3;

	sf::CircleShape m_Diamond_1;
	sf::Vector2f m_Diamond_Location_1;
	sf::Vector2f m_Diamon_Velocity_1;
	sf::CircleShape m_Diamond_2;
	sf::Vector2f m_Diamond_Location_2;
	sf::Vector2f m_Diamon_Velocity_2;
	sf::CircleShape m_Diamond_3;
	sf::Vector2f m_Diamond_Location_3;
	sf::Vector2f m_Diamon_Velocity_3;

	sf::CircleShape m_FakeDiamond_1;
	sf::Vector2f m_FakeDiamond_Location_1; 
	sf::Vector2f m_FakeDiamond_Velocity_1;
	sf::CircleShape m_FakeDiamond_2;
	sf::Vector2f m_FakeDiamond_Location_2;
	sf::Vector2f m_FakeDiamond_Velocity_2;
	sf::CircleShape m_FakeDiamond_3;
	sf::Vector2f m_FakeDiamond_Location_3;
	sf::Vector2f m_FakeDiamond_Velocity_3;


    int m_ConveryerFrame{ -1 };//will change the converveyer belt sprite 
	float m_Converyer_Frame_Increment = 0.02f;//will increase the Converyer frame count 
	const int m_ConveryerFrames = 2;//the max amount frames
	float m_CB_FrameCount = 0.0f;//Converyer frame count 

    int m_MinecartFrame{ -1 };//will start changing the sprite 
	const int m_MinecartFrames = 4;//the max amount of frames 
    float m_MC_FrameCount = 0.0f;//Minecart count 
    float m_Minecart_FrameIncrement = 0.05f;//frame increament 

	float m_CV_FrameCount = 0.0f;//Converyer count 
    const int m_CaveFrames = 7;//max amount of frames of cave 
	int m_CaveFrame{ -1 };//Will change sprite straight away 
	float m_Cave_Frame_Increment = 0.025f;//frame increase

	bool m_Graphics{ false };
	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

