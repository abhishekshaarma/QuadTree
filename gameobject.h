#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Surface.h"
#include "Node.h"

class GameObject
{
public:
    GameObject(int x, int y, int r, int vspeed, int hspeed, int R, int G, int B, Surface &surface)
        : x_(x), y_(y), r_(r), vspeed_(vspeed), hspeed_(hspeed), R_(R), G_(G), B_(B), surface_(surface)
    {
        alive = true;
    }
    void change_speed_y(int factor) {
        vspeed_ *= factor;
        
    }
    void change_speed_x(int factor) {
        hspeed_ *= factor;
    }
    void move()
    {
        y_ += vspeed_;
        x_ += hspeed_;

        if (y_ >= H || y_ <= 0)
        {
            vspeed_ = -vspeed_;
        }
        if (x_ >= W || x_ <= 0)
        {
            hspeed_ = -hspeed_;
        }
    }
void bounceOffLines(int x1, int y1, int x2, int y2) {
    // Calculate distance between the object's center and the line
    double distance = abs((y2 - y1) * x_ - (x2 - x1) * y_ + x2 * y1 - y2 * x1) /
                      sqrt(pow(y2 - y1, 2) + pow(x2 - x1, 2));
    
    // If the distance is less than or equal to the object's radius, a collision occurred
    if (distance <= r_) {
        // Reverse the velocity
        vspeed_ = -vspeed_;
        hspeed_ = -hspeed_;
    }
}


    void change_speed()
    {
        vspeed_ = -vspeed_;
        hspeed_ = -hspeed_;
    }

    void change_color1()
    {
        R_ = std::rand() % 256;
        G_ = std::rand() % 256; 
        B_ = std::rand() % 256; 
    }

    double get_x() const
    {
        return x_;
    }

    double get_y() const
    {
        return y_;
    }

    void draw()
    {
        surface_.put_circle(x_, y_, r_, R_, G_, B_);
    }

    int x_, y_, r_, vspeed_, hspeed_;
    int R_, G_, B_;
    Surface &surface_;
    bool alive;
};

#endif
