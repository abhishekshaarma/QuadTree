#ifndef NODE_H
#define NODE_H

#include <vector>
#include "gameobject.h"

class Node
{
public:
    Node(Point TopLeftPoint, Point BottomRightPoint, Node* parent, int level)
        : TopLeftPoint_(TopLeftPoint), BottomRightPoint_(BottomRightPoint), parent_(parent), level_(level)
    {
        TopLeftNode = NULL;
        TopRightNode = NULL;
        BottomLeftNode = NULL;
        BottomRightNode = NULL;
        parent_ = NULL;
    }

    bool HasChildren()
    {
        return (TopLeftNode != NULL);
    }

    bool InBound(GameObject* object)
    {
        return ((object->get_x()) + object->r_ <= BottomRightPoint_.x_
            && object->get_x() - object->r_ >= TopLeftPoint_.x_
            && object->get_y() - object->r_ >= TopLeftPoint_.y_
            && object->get_y() + object->r_ <= BottomRightPoint_.y_);
    }

    bool is_root() const
    {
        return (parent_ == NULL);
    }

    int NumOfObjects() const
    {
        return this->Objects.size();
    }

    const Node* const parent() const
    {
        return parent_;
    }

    int get_depth() const
    {
        if (this->is_root())
        {
            return 0;
        }
        else
        {
            return (this->parent()->get_depth() + 1);
        }
    }

    ~Node()
    {
        delete TopLeftNode;
        delete TopRightNode;
        delete BottomLeftNode;
        delete BottomRightNode;
    }

public:
    Point TopLeftPoint_;
    Point BottomRightPoint_;
    Node* parent_;
    Node* TopLeftNode;
    Node* TopRightNode;
    Node* BottomLeftNode;
    Node* BottomRightNode;
    int level_;
    std::vector<GameObject*> Objects;
    std::vector<GameObject*> RemainingObjects;
};

#endif
