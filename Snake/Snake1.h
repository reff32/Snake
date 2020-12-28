#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;
#include<iostream>
using namespace std;

class Snake1//одно звено змейки //переименовать в Snake
{
private:
	Texture s_texture;
	Sprite s_sprite;
	float s_x;
	float s_y;
	float step_x;
public:
	Snake1(Image&image);//наверно нах не нужен
	Snake1();//используется в конструкторе Engine
	Sprite get_sprite()const;//возврат sprite для метода draw в engine
	void update(float time,float speed,int n);
	float get_x() { return s_x; }
	float get_y() { return s_y; }



};

