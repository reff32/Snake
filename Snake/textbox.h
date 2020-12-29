#pragma once

#include <vector>
#include <string>
#include<iostream>
#include "SFML/Graphics.hpp"

class  PopUpInfo
{
public:
	std::string m_text;
	sf::Vector2i m_pos;
	int m_count;
	PopUpInfo(std::string text="");
	virtual void Update(float time);
};
class PopUpScore:public PopUpInfo
{
public:
	PopUpScore(std::string text,sf::Vector2i pos);
	virtual void Update(float time);
};

using PopUpContainer = std::vector<PopUpInfo*>;

class Textbox
{
public:
	Textbox();
	~Textbox();
	void Setup();
	void Add(std::string l_message);
	void Add(std::string l_message, sf::Vector2i pos);
	void GetScore(int score);
	void Clear();
	void Update(float time);
	void Render(sf::RenderWindow& l_wind);

private:
	PopUpContainer m_PopUp;
	int m_numVisible;
	int m_snakeScore;
	int m_bestScore;
	sf::Font m_font;
	sf::Text m_content;
	sf::Text m_popUpText;
};

