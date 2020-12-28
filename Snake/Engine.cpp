#include "Engine.h"

void Engine::body_create()
{
    Image body_img;
    body_img.loadFromFile("images/body.png");
    Snake_body b4(body_img, 3);
    Snake_body* slaves = new Snake_body[num_body];
    //Snake_body slaves[3];
    for (int i = 0; i < num_body; i++)
    {
        slaves[i] = b4; //Snake_body(body_img, i);
    }
}

void Engine::input()
{
}

void Engine::counter(float time, float speed)
{
    timer += time;
    if (timer > speed)
    {
        count = true;
        timer = 0;
    }
    else
        count = false;
    
}

bool Engine::get_counter() const
{
    return count;
}

void Engine::inc_body()
{
    num_body++;
}

Snake_body* Engine::set_body(int cell)
{
    
    return slaves[cell];
}

/*void Engine::create(Snake_base& sb,int num)
{
    Snake_body* slave = new Snake_body[num];
    sl = slave;
    for (int i = 0; i < num; i++)
    {
        sl[i] = Snake_body(, i);
    }
   
}*/



