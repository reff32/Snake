#include "textbox.h"


Textbox::Textbox()
{
	sf::Vector2i res;
	res.x = 400;
	res.y = 600;
	Setup(res);
}

Textbox::Textbox(sf::Vector2i center)
{
	Setup(center);
}

Textbox::~Textbox()
{
	Clear();
}

void Textbox::Setup(sf::Vector2i center)
{
	m_center = center;
	m_snakeScore = 0;
	m_font.loadFromFile("20051.ttf");
	m_content.setFont(m_font);
	//m_content.setString("");
	m_content.setCharacterSize(14);
	m_content.setFillColor(sf::Color::White);
	m_content.setOutlineColor(sf::Color(120, 120, 120, 255));
	m_popUpScore.setFont(m_font);
	m_popUpScore.setCharacterSize(16);
	m_popUpScore.setFillColor(sf::Color::Red);
	m_popUpScore.setOutlineColor(sf::Color(120, 120, 120, 255));
	m_popUpInfo.setFont(m_font);
	m_popUpInfo.setCharacterSize(30);
	m_popUpInfo.setFillColor(sf::Color::Red);
	m_popUpInfo.setOutlineColor(sf::Color(120, 120, 120, 255));
}

void Textbox::Add(std::string l_message,sf::Vector2i pos)
{
	m_messages.push_back(Message(l_message,pos));
	if (m_messages.size() < 6)
		return;
	else
		m_messages.erase(m_messages.begin());
}

void Textbox::GetScore(int score)
{
	m_snakeScore = score;
}

void Textbox::Clear()
{
	m_messages.clear();
}

void Textbox::Update(float time)
{
	if (m_messages.empty())
		return;
	else
	{
		for (auto itr_text = m_messages.begin(); itr_text != m_messages.end(); ++itr_text)
		{
			itr_text->Move(time);
		}
		if(m_messages.front().m_count>10)
			m_messages.erase(m_messages.begin());
	}
	
}

void Textbox::Render(sf::RenderWindow& l_wind)
{

	m_content.setString("Lives:");
	m_content.setPosition(10, 0);
	l_wind.draw(m_content);
	m_content.setString("Score: " + std::to_string(m_snakeScore));
	m_content.setPosition(400, 0);
	l_wind.draw(m_content);
	m_content.setString("Best score: ");//טח פאיכא
	m_content.setPosition(800, 0);
	l_wind.draw(m_content);


	if (m_messages.empty())
		return;
	else
	{
		for (auto itr_text = m_messages.begin(); itr_text != m_messages.end(); ++itr_text)
		{
			m_popUpScore.setString(itr_text->m_text);
			m_popUpScore.setPosition(itr_text->m_pos.x, itr_text->m_pos.y);
			l_wind.draw(m_popUpScore);
		}
	}
}
	
Message::Message(std::string text, sf::Vector2i pos)
	:m_text(text),m_pos(pos),m_count(0)
{
	m_pos.x = m_pos.x * 16;
	m_pos.y = m_pos.y * 16;
}

void Message::Move(float time)
{
	m_pos.y-=90*time;
	m_count++;
}
