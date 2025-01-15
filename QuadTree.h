#ifndef QUADTREE_H
#define QUADTREE_H

#include "gameobject.h"
#include "Node.h"
#include <cmath>
#include <cstdlib> // for rand()
#include <ctime>
#include <vector>

class QuadTree {
public:
    QuadTree() {
        std::srand(std::time(nullptr));
        root_ = new Node(Point(0, 0), Point(640, 480), nullptr, 0);
        Threshold_ = 5;
        MaxLevel_ = 10;
    }

    ~QuadTree() {
        delete root_;
    }

    void insert(std::vector<GameObject*>& objects);
    void insert(Node* node, std::vector<GameObject*>& objects);
    void CheckCollision(Node* node, std::vector<GameObject*>& collision_pairs);
    bool Collide(GameObject* object1, GameObject* object2);
    std::vector<GameObject*> get_colliding_pairs(std::vector<GameObject*>& objects);

    Node* root_;
    int Threshold_;
    int MaxLevel_;
};

void QuadTree::insert(std::vector<GameObject*>& objects) {
    insert(root_, objects);
}

void QuadTree::insert(Node* node, std::vector<GameObject*>& objects) {
    if (node == nullptr) {
        return;
    }

    if (node->level_ == MaxLevel_ + 1) {
        return;
    }

    for (GameObject* obj : objects) {
        if (node->InBound(obj)) {
            node->Objects.push_back(obj);
        }
    }

    if (node->NumOfObjects() > Threshold_) {
        node->TopLeftNode = new Node(node->TopLeftPoint_, Point((node->TopLeftPoint_.x_ + node->BottomRightPoint_.x_) / 2, (node->TopLeftPoint_.y_ + node->BottomRightPoint_.y_) / 2), node, node->level_ + 1);
        node->TopRightNode = new Node(Point((node->TopLeftPoint_.x_ + node->BottomRightPoint_.x_) / 2, node->TopLeftPoint_.y_), Point(node->BottomRightPoint_.x_, (node->TopLeftPoint_.y_ + node->BottomRightPoint_.y_) / 2), node, node->level_ + 1);
        node->BottomLeftNode = new Node(Point(node->TopLeftPoint_.x_, (node->TopLeftPoint_.y_ + node->BottomRightPoint_.y_) / 2), Point((node->TopLeftPoint_.x_ + node->BottomRightPoint_.x_) / 2, node->BottomRightPoint_.y_), node, node->level_ + 1);
        node->BottomRightNode = new Node(Point((node->TopLeftPoint_.x_ + node->BottomRightPoint_.x_) / 2, (node->TopLeftPoint_.y_ + node->BottomRightPoint_.y_) / 2), node->BottomRightPoint_, node, node->level_ + 1);

        insert(node->TopLeftNode, node->Objects);
        insert(node->TopRightNode, node->Objects);
        insert(node->BottomLeftNode, node->Objects);
        insert(node->BottomRightNode, node->Objects);

        node->Objects.clear();
    }
}
void QuadTree::CheckCollision(Node* node, std::vector<GameObject*>& collision_pairs) {
    if (!node->HasChildren()) {
        for (int i = 0; i < node->Objects.size(); ++i) {
            for (int j = i + 1; j < node->Objects.size(); ++j) {
                if (Collide(node->Objects[i], node->Objects[j])) {
                    collision_pairs.push_back(node->Objects[i]);
                    collision_pairs.push_back(node->Objects[j]);
                    
                    node->Objects[i]->change_color1();
                    node->Objects[i]->change_color1();
                        
              

                 
                    node->Objects[i]->hspeed_ = rand() % 11 - 5;;
                    node->Objects[i]->vspeed_ = rand() % 11 - 5;;
                    node->Objects[j]->hspeed_ = rand() % 11 - 5;;
                    node->Objects[j]->vspeed_ = rand() % 11 - 5;;
                }
            }
        }
    } else {
        // Recursively check collisions for child nodes
        CheckCollision(node->TopLeftNode, collision_pairs);
        CheckCollision(node->TopRightNode, collision_pairs);
        CheckCollision(node->BottomLeftNode, collision_pairs);
        CheckCollision(node->BottomRightNode, collision_pairs);
    }
}

std::vector<GameObject*> QuadTree::get_colliding_pairs(std::vector<GameObject*>& objects) {
    std::vector<GameObject*> collision_pairs;
    insert(objects);
    CheckCollision(root_, collision_pairs);
    return collision_pairs;
}

bool QuadTree::Collide(GameObject* object1, GameObject* object2) {
    double dx = object1->x_ - object2->x_;
    double dy = object1->y_ - object2->y_;
    double distance = sqrt(dx * dx + dy * dy);
    return distance <= (object1->r_ + object2->r_);
}

#endif
