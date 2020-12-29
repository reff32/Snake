#pragma once

#include "SFML/Graphics.hpp"
#include "textbox.h"

enum class Direction { None, Up, Down, Left, Right,Up_Left,Up_Right,Left_Up,Left_Down,Right_Up,Right_Down,Down_Left,Down_Right };

class SnakeCell
{
public:
	sf::Vector2i position;
	int offset_sprite;
	SnakeCell(int x, int y) :position(x, y), offset_sprite(17) { }
	~SnakeCell(){}
	void Turn(Direction dir);			//установка позиции спрайта
};


//точка поворота
class TurnPoint
{
public:
	sf::Vector2i position;				
	Direction last_direction;			//направление до поворота
	sf::Vector2i next_position;			//след. позиция с учетом нового направления 
	Direction next_direction;			//новое направление
	Direction transit_direction;		//направление в точке поворота last-next
	TurnPoint(sf::Vector2i pos, Direction l_dir, Direction n_dir);
	~TurnPoint() {}
};

using SnakeContainer = std::vector<SnakeCell>;
using TurnPointContainer = std::vector<TurnPoint>;

class Snake
{
public:
	Snake(int l_blockSize, Textbox* l_textbox);
	~Snake();
	void SetDirection(Direction dir);
	Direction GetDirection();
	int GetSpeed();
	sf::Vector2i GetPosition();
	int GetLives();
	int GetScore();
	int GetLength();
	void IncreaseScore();
	bool HasLost();
	void Lose();					// handle losing here
	void ToggleLost();
	void Extend();					// увеличение змейки
	void Reset();					// reset to starting position
	void Move();					// movement method
	void Tick();					// update method
	bool IsTurnPoint();
	void Render(sf::RenderWindow& l_window);
	void IncreaseSpeed();


	

private:
	void Cut(int l_segments, int l_point);		// method for cutting the snake
	void AddPoint(sf::Vector2i pos, Direction l_dir, Direction n_dir);
	void DeletePoint();
	void CheckCollision();			// checking for collisions with the snake
	SnakeContainer m_snakeBody;		// segment vector
	int m_size;						// size of the graphics
	Direction m_dir;				// current direction
	int m_speed;					// speed of the snake
	int m_lives;					// lives
	int m_score;					// score
	bool m_lost;					// losing state
	sf::RectangleShape m_bodyRect;	// shape used in rendering
	sf::Image m_image;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	Textbox* m_textbox;
	TurnPointContainer m_turn_container;
	bool m_turn;

};
