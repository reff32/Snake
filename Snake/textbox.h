#pragma once

#include <vector>
#include <string>
#include "SFML/Graphics.hpp"

class Message
{
public:
	std::string m_text;
	sf::Vector2i m_pos;
	int m_count;
	Message(std::string text, sf::Vector2i pos);
	void Move(float time);
};
using MessageContainer = std::vector<Message>;

class Textbox
{
public:
	Textbox();
	Textbox(sf::Vector2i center);
	~Textbox();

	void Setup(sf::Vector2i center);
	void Add(std::string l_message, sf::Vector2i pos);
	void GetScore(int score);
	void Clear();
	void Update(float time);
	void Render(sf::RenderWindow& l_wind);

private:
	MessageContainer m_messages;
	int m_numVisible;
	int m_snakeScore;
	std::string text_arr[2];
	//sf::RectangleShape m_backdrop;
	sf::Vector2i m_center;
	sf::Font m_font;
	sf::Text m_content;
	sf::Text m_popUpScore;
	sf::Text m_popUpInfo;
};

