#pragma once

#include "SFML/Graphics.hpp"
#include "snake.h"
#include "textbox.h"
#include<iostream>


class World
{
public:
	World(Textbox* l_textbox);
	~World();

	int GetBlockSize();
	void SetLives(int live);
	void RespawnApple();

	void Update(Snake& l_player);
	void Render(sf::RenderWindow& l_window);

private:
	sf::Vector2u m_windowSize;
	sf::Vector2i m_item;
	int m_blockSize;
	int m_snakeLive;
	sf::CircleShape m_appleShape;//������
	sf::RectangleShape m_bounds[4];//�������
	sf::Image m_image;
	sf::Texture m_texture;//����� ��������
	sf::Sprite m_sprite;//���
	int m_gridx;
	int m_gridy;
	Textbox* m_textbox;

};

