#include "p_queue.h"

struct lessPriority
{
    const bool &operator()(const std::pair<Point, int> &p1, const std::pair<Point, int> &p2)
    {
        return p1.second < p2.second;
    }
};


void p_queue::push(Point& x, int p)
{
    auto elem = std::pair<Point, int>(x,p);
    container.push_back(elem);
    std::push_heap(container.begin(), container.end(), lessPriority());
}


Point& p_queue::top()
{
    if (!container.empty())
    {
        return container[0].first;
    }
}


Point& p_queue::pop()
{
    if (!container.empty())
    {
        std::pop_heap(container.begin(), container.end(), lessPriority());
        auto result = container.back();
        container.pop_back();
        return result.first;
    }
}


bool p_queue::empty()
{
    return container.empty();
}


bool p_queue::contains(Point& key)
{
    //return std::find(container.begin(), container.end(), key) != container.end();
    return false;
}


void p_queue::remove(const Point& key)
{
    //auto found = std::find(container.begin(), container.end(), key);
    //container.erase(found);
}


