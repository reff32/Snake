#pragma once
#include"Snake1.h"

class Snake_engine
{
private:
	RenderWindow e_window;
	int num_cell;//кол-во €чеек
	Snake1* cell;
	float speed_snake;
protected:
	void draw();//рисуем все сеll
	void update(float time);
	void speed_snake_inc() {}//увеличиваем скорость
	void input();
	void cell_inc();//+€чейка
public:
	Snake_engine();//создаем окно, выдел€ем пам€ть дл€ cell
	void start();
	
	RenderWindow& get_window() { return e_window; }
	
};

