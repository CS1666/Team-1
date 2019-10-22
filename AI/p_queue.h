#pragma once
#include <vector>
#include <algorithm>


// Priority queue with random access

typedef std::vector<int> Point;

class p_queue
{
    public:
        p_queue() : container(std::vector<std::pair<Point,int>>()) {}
        void push(Point& x, int p);
        Point& top();
        Point& pop();
        bool empty();
        bool contains(Point& key);
        
        void remove(const Point& key);

    private:
        std::vector<std::pair<Point, int> > container;
    };
