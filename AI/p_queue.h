#pragma once
#include <vector>
#include <algorithm>
#include <iterator>


// Priority queue with random access

typedef std::pair<int,int> Point;



class p_queue
{
    public:
        p_queue();
        p_queue& operator=(p_queue& a);
        void push(Point& x, int p);
        Point& top();
        Point& pop();
        bool empty();
        bool contains(Point& key);
        bool compPoints(Point& a, Point& b);
        void remove(Point& key);
        int getSize();
        std::vector<std::pair<Point,int>>::iterator find(Point& key);
        std::vector<std::pair<Point,int>>* getContainer();

    private:
        std::vector<std::pair<Point, int>>* container;
};
