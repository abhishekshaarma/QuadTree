#ifndef POINT_H
#define POINT_H

class Point
{
public:
    Point(int x, int y)
        : x_(x), y_(y)
    {
    }
    Point()
    {
        x_ = 0;
        y_ = 0;
    }
    Point(const Point& p2)
        : x_(p2.x_), y_(p2.y_)
    {
    }

public:
    int x_;
    int y_;
};

#endif
