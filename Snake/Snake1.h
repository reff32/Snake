#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;
#include<iostream>
using namespace std;

class Snake1//���� ����� ������ //������������� � Snake
{
private:
	Texture s_texture;
	Sprite s_sprite;
	float s_x;
	float s_y;
	float step_x;
public:
	Snake1(Image&image);//������� ��� �� �����
	Snake1();//������������ � ������������ Engine
	Sprite get_sprite()const;//������� sprite ��� ������ draw � engine
	void update(float time,float speed,int n);
	float get_x() { return s_x; }
	float get_y() { return s_y; }



};

