#include "Snake1.h"


Snake1::Snake1(Image& image)//возможно нах не нужен
{
	s_texture.loadFromImage(image);
	s_sprite.setTexture(s_texture);
	s_x = 0;
	s_y = 0;
	step_x = 0;
}

Snake1::Snake1()
{
	Image image;
	image.loadFromFile("images/body.png");
	s_texture.loadFromImage(image);
	s_sprite.setTexture(s_texture);
	s_x = 0;
	s_y = 200;
	step_x = 0;
}

Sprite Snake1::get_sprite() const
{
	return s_sprite;
}

void Snake1::update(float time,float speed,int n)
{
	/*step_x += time * speed;
	if (step_x >= 18)
	{
		s_x += 18;
		step_x = 0;
	}
	if (n == 0)
	{
		s_sprite.setPosition(s_x, s_y);
	}
	else
	{
		s_sprite.setPosition(100, 100);
	}*/

}



