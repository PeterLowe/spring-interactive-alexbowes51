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
	
	
	void setupFontAndText();
	void setupSprite();
	void SetUpCoveyerBelt();
	void SetUpMinecart();
	void MoveMinecart();
	void AnimateMinecart();



	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo

	sf::Sprite m_ConveryBelt_Sprite;//Convery belt sprite 
	sf::Texture m_ConveryBelt_Texture;//Convery belt Texture 
	sf::Vector2f m_ConveryBeltLocation;//Convery belt Location
	sf::RectangleShape m_ConveryBelt_Shape;//Convery belt rectangle shape

	sf::Sprite m_Minecart_Sprite;//Minecart Sprite 
	sf::Texture m_Minecart_Texture;//Minecart Texture
	sf::Vector2f m_MinecartLocation;//Minecart Location 
	sf::RectangleShape m_Minecart_Shape;//Minecart rectangle shape 
	int m_MinecartFrame{ -1 };
	const int m_MinecartFrames = 3;
	float m_MinecartFrameCount = 0.0f;
	float m_MincecartFrameIncrement = 0.02f;
	Direction m_Direction = Direction::None;
	float speed = 3.0f;

	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

