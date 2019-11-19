#include "p_queue.h"
#include <iostream>
#include <ctime>
#include <stdexcept>


p_queue::p_queue(int width, int heigth){
    container = new std::vector<std::pair<Point,double>>();
    indirection = std::unordered_map<Point, int, CantorHash>();
}

p_queue& p_queue::operator=(p_queue& a){

    std::vector<std::pair<Point,double>>* npq = new std::vector<std::pair<Point,double>>;

    std::unordered_map<Point, int, CantorHash> nin =  std::unordered_map<Point, int, CantorHash>();

    npq = a.container;

    delete a.container;
    a.container = npq;

    nin = a.indirection;


    return *this;
}
bool p_queue::lessPriority(std::pair<Point, double> &p1, std::pair<Point, double> &p2)
{   
    return std::abs(p1.second) > std::abs(p2.second);
}

void p_queue::clear(){
    container->clear();
    indirection.clear();
}
void p_queue::push_up_heap(int index){
    
    if(index != 0){
        
        std::pair<Point, double> child = container->at(index);

        std::pair<Point, double> parent = container->at(getParentIndex(index));
        while(!lessPriority(child,parent)){

            swap_nodes(index, getParentIndex(index));
            index = getParentIndex(index);
        
            child = container->at(index);

            //Stop if at top of heap
            if(index == 0){
                break;
            }
            parent = container->at(getParentIndex(index));
           

        }
    }
    
}

void p_queue::push_down_heap(int index){
    //std::cout << "Pushing Down" << std::endl;
    int currindex = index;
    std::pair<Point, double> parent;
    std::pair<Point, double> lchild;
    std::pair<Point, double> rchild;

    parent = container->at(index);
    lchild = getLeftNode(currindex);
    rchild = getRightNode(currindex);

     
    while(lessPriority(parent, lchild) || lessPriority(parent, rchild) ){

        //Go right
        if(lessPriority(lchild, rchild)){
            swap_nodes(index, getRightIndex(index));
            index = getRightIndex(index);
        }
        //Go left
        else{
            swap_nodes(index, getLeftIndex(index));
            index = getLeftIndex(index);
        }
        parent = container->at(index);
        lchild = getLeftNode(index);
        rchild = getRightNode(index);   
    }
}

void p_queue::swap_nodes(int a, int b){
    //std::cout << "Swapping " << a  << " with " << b << std::endl;
    swap(container->at(a),container->at(b));
    
    Point pa = container->begin()[a].first;
    Point pb = container->begin()[b].first;

    indirection[pa] = b;
    indirection[pb] = a;

}
void p_queue::insert(Point& x, double p)
{   
    auto elem = std::pair<Point, double>(x,p);

    //Addes element to bottom of heap and adds to indirection
    container->push_back(elem);
    indirection[x] = (container->size() - 1);

    //Begins heapify process
    push_up_heap(container->size() - 1); 
  
}

Point& p_queue::pop()
{   
    std::pair<Point, double> result;

    if (container->size() > 1)
    {
      swap_nodes(0, container->size() - 1);
      result = container->back();
      container->pop_back();
      indirection[result.first] = -1;

      push_down_heap(0);
      
    }
    else if(!container->empty()){

      result = container->back();
      container->pop_back();
      indirection[result.first] = -1;

    }

    return result.first;
}

void p_queue::ndelete(Point& P){
    //std::cout << "Deleting 1" << std::endl;
    if(contains(P)){
        //std::cout << "Deleting 2" << std::endl;
        int index = indirection[P];
        swap_nodes(index, container->size() - 1);
        pop();
        push_down_heap(index);
    }
    
}

Point& p_queue::top()
{
    if (!container->empty())
    {
        return container->begin()->first;
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

    try{
        indirection.at(key);
    }
    catch(const std::out_of_range& oor){
        return false;
    }
    
    if(indirection[key] == -1){
        return false;
    }

    return true;
   
}

std::vector<std::pair<Point,double>>* p_queue::getContainer(){
    return container;
}


int p_queue::getSize(){
    return container->size();
}


std::pair<Point, int> p_queue::getLeftNode(int currindex){

    int lindex = getLeftIndex(currindex);

    if(lindex < container->size()){
        return container->at(lindex);
    }
    else{
        return std::pair<Point, int>(std::pair<int, int>(-1,-1), std::numeric_limits<int>::max());
    }
}

int p_queue::getLeftIndex(int currpos){
    return 2*currpos + 1 ;
}

std::pair<Point, int> p_queue::getRightNode(int currindex){
    int rindex = getRightIndex(currindex);

    if(rindex < container->size()){
        return container->at(rindex);
    }
    else{
        return std::pair<Point, int>(std::pair<int, int>(-1,-1), std::numeric_limits<double>::max());
    }
}


int p_queue::getRightIndex(int currpos){
    return 2*currpos + 2;
}

std::pair<Point, int> p_queue::getParentNode(int currindex){
    
    if(currindex != 0){
        return container->at(getParentIndex(currindex));
    }

}

int p_queue::getParentIndex(int currpos){
    return (currpos - 1)/2;
}