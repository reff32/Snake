#pragma once
#include"Snake1.h"

class Snake_engine
{
private:
	RenderWindow e_window;
	int num_cell;//���-�� �����
	Snake1* cell;
	float speed_snake;
protected:
	void draw();//������ ��� ��ll
	void update(float time);
	void speed_snake_inc() {}//����������� ��������
	void input();
	void cell_inc();//+������
public:
	Snake_engine();//������� ����, �������� ������ ��� cell
	void start();
	
	RenderWindow& get_window() { return e_window; }
	
};

