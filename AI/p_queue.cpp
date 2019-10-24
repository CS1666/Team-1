#include "p_queue.h"
#include <iostream>


struct lessPriority
{
    const bool &operator()(const std::pair<Point, int> &p1, const std::pair<Point, int> &p2)
    {
        return p1.second > p2.second;
    }
};

p_queue::p_queue(){
    container = new std::vector<std::pair<Point,int>>;
}

p_queue& p_queue::operator=(p_queue& a){

    std::vector<std::pair<Point,int>>* npq = new std::vector<std::pair<Point,int>>();
    while(!a.getContainer()->empty()){
        npq->push_back(a.getContainer()->back());
        a.getContainer()->pop_back();
    }

    delete a.getContainer();
    a.container = npq;
    return *this;
}


void p_queue::push(Point& x, int p)
{
    auto elem = std::pair<Point, int>(x,p);
    container->push_back(elem);
    std::push_heap(container->begin(), container->end(), lessPriority());
}


Point& p_queue::top()
{
    if (!container->empty())
    {
        return container->begin()->first;
    }
}


Point& p_queue::pop()
{
    if (!container->empty())
    {
        std::pop_heap(container->begin(), container->end(), lessPriority());
        auto result = container->back();
        container->pop_back();
        return result.first;
    }
}


bool p_queue::empty()
{
    return container->empty();
}


bool p_queue::contains(Point& key)
{
    if(container->empty()){
        return false;
    }
    auto pqiter = find(key);
    return compPoints(pqiter->first, key);
   
}

std::vector<std::pair<Point,int>>* p_queue::getContainer(){
    return container;
}
void p_queue::remove(Point& key)
{   
      if(!container->empty()){
       
    
        auto pqiter = find(key);

    
        if(compPoints(pqiter->first, key)){
            //std::cout << "Removing points" <<  std::endl;
            container->erase(find(key));
        
        }
    }
    
    
}

int p_queue::getSize(){
    return container->size();
}

bool p_queue::compPoints(Point& a, Point& b){
    return a.first == b.first && a.second == b.second;
}

std::vector<std::pair<Point,int>>::iterator p_queue::find(Point& key){
   int i = 0;
   auto pq_iter = container->begin();
   
  for (auto iter = container->begin(); iter != std::prev(container->end()); ++iter) {
        if (compPoints((pq_iter->first), key)){
             return pq_iter;
        }

        advance(pq_iter, 1);
        i++;
    
    }


    return pq_iter;
}


