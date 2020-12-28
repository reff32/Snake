#include "snake.h"

Snake::Snake(int l_blockSize, Textbox* l_textbox)
{
	m_textbox = l_textbox;
	m_size = l_blockSize;
	Reset();//создаем три ячейки, начальные параметры игры
}

Snake::~Snake()
{
}

void Snake::SetDirection(Direction dir)
{
	auto head = m_snakeBody.begin();
	AddPoint(head->position,m_dir,dir);
	m_dir = dir;
}

Direction Snake::GetDirection()
{
	return m_dir;
}



int Snake::GetSpeed()
{
	return m_speed;
}

sf::Vector2i Snake::GetPosition()
{
	return (!m_snakeBody.empty() ? m_snakeBody.front().position : sf::Vector2i(1, 1));
}

int Snake::GetLives()
{
	return m_lives;
}

int Snake::GetScore()
{
	return m_score;
}

int Snake::GetLength()
{
	return m_snakeBody.size();
}

void Snake::IncreaseScore()
{
	m_score += 10;
	m_textbox->GetScore(m_score);
	m_textbox->Add("+10", GetPosition());
}

bool Snake::HasLost()
{
	return m_lost;
}

void Snake::Lose()
{
	m_lost = true;
}

void Snake::ToggleLost()
{
	m_lost = !m_lost;
}

void Snake::Extend()
{
	if (m_snakeBody.empty())
		return;

	SnakeCell& tail_head = m_snakeBody[m_snakeBody.size() - 1];

	if (m_snakeBody.size() > 1)
	{
		SnakeCell& tail_bone = m_snakeBody[m_snakeBody.size() - 2];
		if (tail_head.position.x == tail_bone.position.x)
		{
			if (tail_head.position.y > tail_bone.position.y)
			{
				m_snakeBody.push_back(SnakeCell(tail_head.position.x, tail_head.position.y + 1));
				m_snakeBody[m_snakeBody.size()-1].Turn(Direction::Up);
			}
			else
			{
				m_snakeBody.push_back(SnakeCell(tail_head.position.x, tail_head.position.y - 1));
				m_snakeBody[m_snakeBody.size() - 1].Turn(Direction::Down);
			}
		}
		else if (tail_head.position.y == tail_bone.position.y)
		{
			if (tail_head.position.x > tail_bone.position.x)
			{
				m_snakeBody.push_back(SnakeCell(tail_head.position.x + 1, tail_head.position.y));
				m_snakeBody[m_snakeBody.size() - 1].Turn(Direction::Left);
			}
			else
			{
				m_snakeBody.push_back(SnakeCell(tail_head.position.x - 1, tail_head.position.y));
				m_snakeBody[m_snakeBody.size() - 1].Turn(Direction::Right);
			}
		}
	}
	else
	{
		switch (m_dir)
		{
		case Direction::Up:
			m_snakeBody.push_back(SnakeCell(tail_head.position.x, tail_head.position.y + 1));
			break;
		case Direction::Down:
			m_snakeBody.push_back(SnakeCell(tail_head.position.x, tail_head.position.y - 1));
			break;
		case Direction::Left:
			m_snakeBody.push_back(SnakeCell(tail_head.position.x - 1, tail_head.position.y));
			break;
		case Direction::Right:
			m_snakeBody.push_back(SnakeCell(tail_head.position.x + 1, tail_head.position.y));
			break;
		default:
			break;
		}
	}
}

void Snake::Reset()
{
	m_snakeBody.clear();
	m_snakeBody.push_back(SnakeCell(5, 9));
	m_snakeBody.push_back(SnakeCell(5, 8));
	m_snakeBody.push_back(SnakeCell(5, 7));
	m_snakeBody.push_back(SnakeCell(5, 6));
	m_snakeBody.push_back(SnakeCell(5, 5));

	SetDirection(Direction::None);

	m_turn_container.clear();

	m_textbox->Clear();

	m_speed = 6;
	m_lives = 3;
	m_score = 0;
	m_lost = false;
	m_turn = false;
}

void Snake::Move()
{
	for (int i = m_snakeBody.size() - 1; i > 0; --i)
		m_snakeBody[i].position = m_snakeBody[i - 1].position;

	switch (m_dir)
	{
	case Direction::Up:
		--m_snakeBody[0].position.y;
		break;
	case Direction::Down:
		++m_snakeBody[0].position.y;
		break;
	case Direction::Left:
		--m_snakeBody[0].position.x;
		break;
	case Direction::Right:
		++m_snakeBody[0].position.x;
		break;
	default:
		break;
	}
}

void Snake::Tick()
{
	if (m_snakeBody.empty())
		return;

	if (m_dir == Direction::None)
		return;

	Move();
	CheckCollision();
}

bool Snake::IsTurnPoint()
{
	auto head = m_snakeBody.begin();
	if (m_turn_container.size() > 0)
	{
		if (head->position == m_turn_container[m_turn_container.size() - 1].position)
			return true;
		else
			return false;
	}
	else
		return false;
}

void Snake::Cut(int l_segments,int l_point)
{
	if (l_point > 0)	//удаляем лишние точки 
	{
		for (int j = 0; j != l_point; j++)
			DeletePoint();
	}

	for (int i = 0; i < l_segments; ++i)	//ампутируем snake
		m_snakeBody.pop_back();

	--m_lives;

	m_textbox->Add("You ate part of yourself. Remaining lives: " + std::to_string(m_lives));

	if (!m_lives)
	{
		Lose();
		return;
	}
}

void Snake::Render(sf::RenderWindow& l_window)
{
	if (m_snakeBody.empty())
		return;
	//рисуем head
	auto head = m_snakeBody.begin();
	m_texture.loadFromFile("images/head_s.png");
	m_sprite.setTexture(m_texture);
	if (m_turn_container.size() > 0)
	{
		if (head->position == m_turn_container[m_turn_container.size()-1].position)
			head->Turn(m_turn_container[m_turn_container.size() - 1].transit_direction);
		if (head->position == m_turn_container[m_turn_container.size() - 1].next_position)
			head->Turn(m_turn_container[m_turn_container.size()-1].next_direction);			
	}
	m_sprite.setTextureRect(sf::IntRect(head->offset_sprite, 0, 16, 16));
	m_sprite.setPosition(static_cast<float>(head->position.x * m_size), static_cast<float>(head->position.y * m_size));
	l_window.draw(m_sprite);

	//рисуем body
	m_texture.loadFromFile("images/body_s.png");
	m_sprite.setTexture(m_texture);
	for (auto itr_snake = m_snakeBody.begin() + 1; itr_snake != m_snakeBody.end()-1; ++itr_snake)
	{
		if (m_turn_container.size()>0)
		{
			for (auto itr_turn = m_turn_container.begin(); itr_turn != m_turn_container.end(); ++itr_turn)
			{
				if (itr_snake->position == itr_turn->position)
					itr_snake->Turn(itr_turn->transit_direction);
				if (itr_snake->position == itr_turn->next_position)
					itr_snake->Turn(itr_turn->next_direction);				
			}
		}
		m_sprite.setTextureRect(sf::IntRect(itr_snake->offset_sprite, 0, 16, 16));
		m_sprite.setPosition(static_cast<float>(itr_snake->position.x * m_size), static_cast<float>(itr_snake->position.y * m_size));
		l_window.draw(m_sprite);
	}
	//рисуем tail
	m_image.loadFromFile("images/tail.png");
	m_image.createMaskFromColor(sf::Color(255, 242, 0));
	m_texture.loadFromImage(m_image);
	m_sprite.setTexture(m_texture);
	if (m_turn_container.size() > 0)
	{
		TurnPoint& last_point = m_turn_container.front();
		if (m_snakeBody[m_snakeBody.size() - 1].position == last_point.position)
		{
			m_snakeBody[m_snakeBody.size() - 1].Turn(last_point.next_direction);
		}

		if (m_snakeBody[m_snakeBody.size() - 1].position == last_point.next_position)
		{
			m_snakeBody[m_snakeBody.size() - 1].Turn(last_point.next_direction);
			DeletePoint();//удаляем пройденную точку
		}
	}
	auto tail = m_snakeBody.back();
	m_sprite.setTextureRect(sf::IntRect(tail.offset_sprite, 0, 16, 16));
	m_sprite.setPosition(static_cast<float>(tail.position.x * m_size), static_cast<float>(tail.position.y * m_size));
	l_window.draw(m_sprite);
}

void Snake::AddPoint(sf::Vector2i pos,Direction l_dir,Direction n_dir)
{
	m_turn_container.push_back(TurnPoint(pos,l_dir,n_dir));
}

void Snake::DeletePoint()
{
	m_turn_container.erase(m_turn_container.begin());
}

// snake collides with itself
void Snake::CheckCollision()
{
	if (m_snakeBody.size() < 5)	// no need to check for collisions if there are four or less segments
		return;

	SnakeCell& head = m_snakeBody.front();

	for (auto itr = m_snakeBody.begin() + 1; itr != m_snakeBody.end(); ++itr)
	{
		if (itr->position == head.position)
		{
			int segments = m_snakeBody.end() - itr;
			int point = 0;
			if (segments > 0)
			{
				for (int i = 1; i <= segments; i++)
				{
					if (m_turn_container.size() > 0)
					{
						for (auto itr_turn = m_turn_container.begin(); itr_turn != m_turn_container.end(); ++itr_turn)
						{
							if (m_snakeBody[m_snakeBody.size() - i].position == itr_turn->position)
								point++;
						}
					}
				}
			}
			Cut(segments,point);
			break;
		}
	}
}

void SnakeCell::Turn(Direction dir)
{
	if (dir == Direction::Right)
		offset_sprite = 0;
	if (dir == Direction::Down)
		offset_sprite = 17;
	if (dir == Direction::Up)
		offset_sprite = 34;
	if (dir == Direction::Left)
		offset_sprite = 51;
	if (dir == Direction::Right_Up)
		offset_sprite = 68;
	if (dir == Direction::Right_Down)
		offset_sprite = 85;
	if (dir == Direction::Left_Up)
		offset_sprite = 102;
	if (dir == Direction::Left_Down)
		offset_sprite = 119;
	if (dir == Direction::Up_Left)
		offset_sprite = 136;
	if (dir == Direction::Up_Right)
		offset_sprite = 153;
	if (dir == Direction::Down_Left)
		offset_sprite = 170;
	if (dir == Direction::Down_Right)
		offset_sprite = 187;
}


TurnPoint::TurnPoint(sf::Vector2i pos, Direction l_dir, Direction n_dir)
{
	position = pos;
	last_direction = l_dir;
	next_direction = n_dir;
	if (n_dir == Direction::Down)
	{
		next_position.x = position.x;
		next_position.y = position.y+1;
	}
	if (n_dir == Direction::Left)
	{
		next_position.x = position.x-1;
		next_position.y = position.y;
	}
	if (n_dir == Direction::Right)
	{
		next_position.x = position.x+1;
		next_position.y = position.y;
	}
	if (n_dir == Direction::Up)
	{
		next_position.x = position.x;
		next_position.y = position.y-1;
	}
	if (last_direction == Direction::Up)
	{
		if (next_direction == Direction::Left)
			transit_direction = Direction::Up_Left;
		else
			transit_direction = Direction::Up_Right;
	}
	if (last_direction == Direction::Left)
	{
		if (next_direction == Direction::Up)
			transit_direction = Direction::Left_Up;
		else
			transit_direction = Direction::Left_Down;
	}
	if (last_direction == Direction::Right)
	{
		if (next_direction == Direction::Up)
			transit_direction = Direction::Right_Up;
		else
			transit_direction = Direction::Right_Down;
	}
	if (last_direction == Direction::Down)
	{
		if (next_direction == Direction::Left)
			transit_direction = Direction::Down_Left;
		else
			transit_direction = Direction::Down_Right;
	}
}
