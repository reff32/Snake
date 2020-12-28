#include "textbox.h"


Textbox::Textbox()
{
	sf::Vector2i res;
	res.x = 400;
	res.y = 600;
	Setup();
}



Textbox::~Textbox()
{
	Clear();
}

void Textbox::Setup()
{
	m_snakeScore = 0;
	m_font.loadFromFile("20051.ttf");
	m_content.setFont(m_font);
	m_content.setCharacterSize(14);
	m_content.setFillColor(sf::Color::White);
	m_content.setOutlineColor(sf::Color(120, 120, 120, 255));
	//pop-up score
	m_popUpScore.setFont(m_font);
	m_popUpScore.setCharacterSize(16);
	m_popUpScore.setFillColor(sf::Color::Red);
	m_popUpScore.setOutlineColor(sf::Color(120, 120, 120, 255));
	//info
	m_popUpInfo.setFont(m_font);
	m_popUpInfo.setCharacterSize(30);
	m_popUpInfo.setFillColor(sf::Color::Red);
	m_popUpInfo.setOutlineColor(sf::Color(120, 120, 120, 255));
}

void Textbox::Add(std::string l_message)
{
	m_PopUp.push_back(new PopUpInfo(l_message));
	if (m_PopUp.size() < 6)
		return;
	else
		m_PopUp.erase(m_PopUp.begin());
}

void Textbox::Add(std::string l_message,sf::Vector2i pos)
{
	m_PopUp.push_back(new PopUpScore(l_message, pos));
	if (m_PopUp.size() < 6)
		return;
	else
		m_PopUp.erase(m_PopUp.begin());
}

void Textbox::GetScore(int score)
{
	m_snakeScore = score;
}

void Textbox::Clear()
{
	m_PopUp.clear();
}

void Textbox::Update(float time)
{
	if (m_PopUp.empty())
		return;
	else
	{
		for (int i = 0; i < m_PopUp.size(); i++)
		{
		m_PopUp[i]->Update(time);
		}
		if(m_PopUp.front()->m_count>10)
			m_PopUp.erase(m_PopUp.begin());
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


	if (m_PopUp.empty())
		return;
	else
	{
		for (int i=0; i< m_PopUp.size(); i++)
		{
			m_popUpScore.setString(m_PopUp[i]->m_text);
			m_popUpScore.setOrigin(m_popUpScore.getGlobalBounds().width/2, m_popUpScore.getGlobalBounds().height/2);
			m_popUpScore.setPosition(m_PopUp[i]->m_pos.x, m_PopUp[i]->m_pos.y);
			l_wind.draw(m_popUpScore);
		}
	}
}
	




PopUpInfo::PopUpInfo(std::string text)
	:m_text(text),m_count(0)
{
	m_pos.x = sf::VideoMode::getDesktopMode().width / 2;
	m_pos.y = sf::VideoMode::getDesktopMode().height / 2;
}

void PopUpInfo::Update(float time)
{
	std::cout << "fix\n";
	m_count++;
}

PopUpScore::PopUpScore(std::string text, sf::Vector2i pos):PopUpInfo(text)
{
	m_pos.x = pos.x * 16;
	m_pos.y = pos.y * 16;
}

void PopUpScore::Update(float time)
{
	std::cout << "move\n";
	PopUpInfo::Update(time);
	m_pos.y -= 90 * time;
}
