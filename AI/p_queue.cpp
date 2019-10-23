#include "p_queue.h"
#include <iterator>


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
    auto pqiter = find(key);
    return compPoints(pqiter->first, key);
   
}


void p_queue::remove(Point& key)
{   auto pqiter = find(key);
    if(compPoints(pqiter->first, key)){
        container.erase(find(key));
    }
    
}

bool p_queue::compPoints(Point& a, Point& b){
    return a.first == b.first && a.second == b.second;
}

std::vector<std::pair<Point,int>>::iterator p_queue::find(Point& key){

   auto pq_iter = container.begin();
   do{

        if ((pq_iter->first).first == key.first && (pq_iter->first).second == key.second){
            break;
        }

    }
    while(pq_iter != container.end());

    return pq_iter;
}


