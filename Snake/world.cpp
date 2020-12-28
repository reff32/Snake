#include <cstdlib>
#include "world.h"

World::World(Textbox* l_textbox)
{
	
	m_textbox = l_textbox;
	m_blockSize = 16;
	m_windowSize.x = sf::VideoMode::getDesktopMode().width;
	m_windowSize.y = sf::VideoMode::getDesktopMode().height;
	m_gridx = m_windowSize.x / m_blockSize;
	m_gridy = m_windowSize.y / m_blockSize;

	RespawnApple();

	m_appleShape.setFillColor(sf::Color(122, 7, 39));
	m_appleShape.setRadius(static_cast<float>(m_blockSize / 2));

	for (int i = 0; i < 4; i++)
	{
		m_bounds[i].setFillColor(sf::Color(234, 91, 12, 255));

		if (!((i + 1) % 2))
			m_bounds[i].setSize(sf::Vector2f(static_cast<float>(m_windowSize.x), static_cast<float>(m_blockSize)));
		else
			m_bounds[i].setSize(sf::Vector2f(static_cast<float>(m_blockSize), static_cast<float>(m_windowSize.y)));

		if (i < 2)
			m_bounds[i].setPosition(0, 0);
		else
		{
			m_bounds[i].setOrigin(m_bounds[i].getSize());
			m_bounds[i].setPosition(sf::Vector2f(m_windowSize));
		}
	}
	m_image.loadFromFile("images/background.png");
	m_image.createMaskFromColor(sf::Color(63, 72, 204));
	m_texture.loadFromImage(m_image);
	m_sprite.setTexture(m_texture);

}

World::~World()
{
}

int World::GetBlockSize()
{
	return m_blockSize;
}

void World::SetLives(int live)
{
	m_snakeLive = live;
}



void World::RespawnApple()
{
	int maxX = (m_windowSize.x / m_blockSize) - 2;
	int maxY = (m_windowSize.y / m_blockSize) - 2;

	m_item = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);

	m_appleShape.setPosition(static_cast<float>(m_item.x * m_blockSize), static_cast<float>(m_item.y * m_blockSize));
}

void World::Update(Snake& l_player)
{
	if (l_player.GetPosition() == m_item)
	{
		l_player.Extend();
		l_player.IncreaseScore();
		RespawnApple();
	}

	int gridSize_x = m_windowSize.x / m_blockSize;
	int gridSize_y = m_windowSize.y / m_blockSize;

	if (l_player.GetPosition().x <= 0 ||
		l_player.GetPosition().y <= 0 ||
		l_player.GetPosition().x >= gridSize_x - 1 ||
		l_player.GetPosition().y >= gridSize_y - 1)
	{
		l_player.Lose();
	}
}

void World::Render(sf::RenderWindow& l_window)
{
	for (int i = 0; i < 4; ++i)
		l_window.draw(m_bounds[i]);
	for (int i = 1; i < m_gridx-1; i++)
	{
		for (int j = 1; j < m_gridy-1; j++)
		{
			m_sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
			m_sprite.setPosition(static_cast<float>(i * m_blockSize), static_cast<float>(j * m_blockSize));
			l_window.draw(m_sprite);
		}
	}
	for (int i = 0; i < m_snakeLive; i++)
	{
		m_sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));
		m_sprite.setPosition(static_cast<float>((3+i*2) * m_blockSize), 0);
		l_window.draw(m_sprite);
	}


	l_window.draw(m_appleShape);
}