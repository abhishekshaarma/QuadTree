#include <iostream>
#include <cmath>
#include <vector>
#include "Includes.h"
#include "Constants.h"
#include "SDL_mouse.h"
#include "Surface.h"
#include "Event.h"
#include "Point.h"
#include "Node.h"
#include "QuadTree.h"
#include "gameobject.h"
#define A SDLK_a
#define D SDLK_d
#define W SDLK_w
#define S SDLK_s

void Quad(Node* node, Surface& surface, std::vector<GameObject*>& objects)
{
    if (node == NULL)
    {
        return;
    }

    if (node->HasChildren())
    {
        int x1 = (node->TopLeftPoint_.x_ + node->BottomRightPoint_.x_) / 2;
        int y1 = (node->TopLeftPoint_.y_ + node->BottomRightPoint_.y_) / 2;

        surface.put_line(x1, node->BottomRightPoint_.y_ - 1, x1, node->TopLeftPoint_.y_, 0, 255, 255);
        surface.put_line(node->TopLeftPoint_.x_, y1, node->BottomRightPoint_.x_ - 1, y1, 255, 255, 255);

        for (auto& obj : objects)
        {
            if (obj->get_x() >= node->TopLeftPoint_.x_ && obj->get_x() <= node->BottomRightPoint_.x_ &&
                obj->get_y() >= node->TopLeftPoint_.y_ && obj->get_y() <= node->BottomRightPoint_.y_)
            {
                obj->change_speed_x(-1); // Reverse horizontal velocity
                if (obj->get_y() == y1)
                {
                    obj->change_speed_y(-1); // Reverse vertical velocity
                }
            }
        }

        Quad(node->TopLeftNode, surface, objects);
        Quad(node->TopRightNode, surface, objects);
        Quad(node->BottomLeftNode, surface, objects);
        Quad(node->BottomRightNode, surface, objects);
    }
}
int main()
{
    srand((unsigned int)time(NULL));
    const int NUM_OBJECT = 1200;
    Event event;
    Surface surface;
    
    std::vector<GameObject*> object;
    
    
    for (int i = 0; i < NUM_OBJECT; ++i)
    {
        int x = rand() % W + 200 ;
        int y = rand() % H ;
        std::cout << "Object " << i << " at (" << x << ", " << y << ")\n";
        object.push_back(new GameObject(x, y, 2, rand() % 3 + 2, rand() % 3 + 2, 255, 0, 0, surface));
    }
    bool draw_lines = false;
    while (1)
    {
        KeyPressed keypressed = get_keypressed();
        QuadTree qtree;
        std::vector<GameObject*> CollidingPairs = qtree.get_colliding_pairs(object);
        
        if (event.poll())
        {
            if (event.type() == QUIT)
            {
                break;
            }
            
            else if (event.type() == KEYDOWN)
            {
                if (keypressed[SPACE])
                {
                    draw_lines = !draw_lines;
                }
                else if (mouse_left())
                {
                    object.push_back(new GameObject(mouse_x(), mouse_y(), 2, rand() % 3 + 2, rand() % 3 + 2, 255, 0, 0, surface));
                }
                else if (keypressed[W])
                {
                    for (auto& obj : object)
                    {
                        obj->r_++;
                    }
                }
                else if (keypressed[S])
                {
                    for (auto& obj : object)
                    {
                        obj->r_ = std::max(1, obj->r_ - 1);
                    }
                }
                else if (keypressed[A])
                {
                    for (auto& obj : object)
                    {
                        obj->vspeed_++;
                        obj->hspeed_++;
                    }
                }
                else if (keypressed[D])
                {
                    for (auto& obj : object)
                    {
                        obj->vspeed_ = std::max(1, obj->vspeed_ - 1);
                        obj->hspeed_ = std::max(1, obj->hspeed_ - 1);
                    }
                }
            }
            for (int i = 0; i < CollidingPairs.size(); ++i)
            {
                CollidingPairs[i]->change_color1();
                CollidingPairs[i]->change_speed();
                CollidingPairs[i]->move();
            }
            CollidingPairs.clear();
        }
        
        for (int i = 0; i < object.size(); ++i)
        {
            object[i]->move();
        }

        surface.lock();
        surface.fill(BLACK);
          
        for (int i = 0; i < object.size(); ++i)
        {
            object[i]->draw();
        }
    
        if (draw_lines)
        {
            Quad(qtree.root_, surface, object);
        }
        
        surface.unlock();
        surface.flip();
        delay(20);
    }
    
   
    
    return 0;
}
