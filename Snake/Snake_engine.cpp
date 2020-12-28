#include "Snake_engine.h"

Snake_engine::Snake_engine()
{
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	//RenderWindow e_window(sf::VideoMode(640, 480), "Snake");
	e_window.create(VideoMode(resolution.x, resolution.y), "Snake", Style::Fullscreen);
	num_cell = 1;
	speed_snake = 20;
	cell = new Snake1[num_cell];//конструктор по умолчанию
}

void Snake_engine::start()
{
	Clock clock;
	while (e_window.isOpen())
	{
		Time dt = clock.restart();
		float game_time = clock.getElapsedTime().asMicroseconds();
		game_time = game_time / 1000;
		Event event;
		while (e_window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				e_window.close();
		}
		input();
		//update(game_time);
		draw();
	}
}

void Snake_engine::draw()
{
	e_window.clear();
	for (int i = 0; i < num_cell; i++)
		e_window.draw(cell[i].get_sprite());
	e_window.display();
}

void Snake_engine::update(float time)
{

	for (int i = 0; i < num_cell; i++)
	{

		cell[i].update(time, speed_snake,i);
	}
	//cell[0].update(time, speed_snake);
}

void Snake_engine::input()
{
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		cell_inc();
		cout << num_cell << endl;
	}
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		cell[0].get_sprite().setPosition(100, 100);
		cout << "L\n";
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		cell[2].get_sprite().setPosition(200, 200);
		cout << "R\n";
		cout << cell[1].get_sprite().getPosition().x << endl;
	}
	/*if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		if (head.direction() == 2 || head.direction() == 0) { head.rotate(3); }
	}*/
}

void Snake_engine::cell_inc()
{
	num_cell=2;
}



