#pragma once
#include "Snake.h"
class Engine
{
private:
	bool count;
	float timer;
	int num_body;
	Snake_body* slaves[];
protected:
	void body_create();
public:
	Engine() { count = false; timer = 0; num_body = 0; body_create(); }
	void input();
	void counter(float time, float speed);
	bool get_counter()const;
	void inc_body();
	Snake_body* set_body(int cell);
	int get_num() const {return num_body; }
	//void create(Snake_base& sb,int num);
};

