#include "p_queue.h"
#include <iostream>
#include <ctime>
#include <stdexcept>

p_queue::p_queue(){
    container = new std::vector<std::pair<Point,int>>();
    indirection = new std::map<Point, int>;
}

p_queue& p_queue::operator=(p_queue& a){

    std::vector<std::pair<Point,int>>* npq = new std::vector<std::pair<Point,int>>;
    std::map<Point, int>* nin = new std::map<Point, int>;

    npq = a.container;

    delete a.container;
    a.container = npq;

    nin = a.indirection;

    delete a.indirection;
    a.indirection = nin;

    return *this;
}
bool p_queue::lessPriority(std::pair<Point, int> &p1, std::pair<Point, int> &p2)
{
    return p1.second > p2.second;
}

void p_queue::push_up_heap(int index){
    //std::cout << "Push up heap" <<std::endl;

    if(index != 0){
        //std::cout << "A" <<std::endl;
        std::pair<Point, int> child = container->at(index);

        //std::cout << "B" <<std::endl;
        std::pair<Point, int> parent = container->at(getParent(index));
        while(!lessPriority(child,parent)){
            //std::cout << "C" <<std::endl;
            swap_nodes(index, getParent(index));

            //std::cout << "D" <<std::endl;
            index = getParent(index);
            //std::cout << "E" <<std::endl;
            child = container->at(index);

            //Stop if at top of heap
            if(index == 0){
                break;
            }
            //std::cout << "F" <<std::endl;
            parent = container->at(getParent(index));
            //std::cout << "G" <<std::endl;

        }
    }
    
}

void p_queue::push_down_heap(int index){
    
    int currindex = index;
    int rindex = getRightNode(currindex);
    int lindex = getRightNode(currindex);
    std::pair<Point, int> parent;
    std::pair<Point, int> lchild;
    std::pair<Point, int> rchild;

    parent = container->at(index);

    //Checks to make sure both left and right child exist before assigning them
    //To respective var
    //If they do not exist assign point, int pair where
    //Point = (-1,-1)
    //int = infinity
    if(lindex < container->size()){
        lchild = container->at(getLeftNode(index));
    }
    else{
        lchild = std::pair<Point, int>(std::pair<int, int>(-1,-1), std::numeric_limits<int>::max());
    }

    if(rindex < container->size()){
        rchild = container->at(getRightNode(index));
    }
    else{
        rchild = std::pair<Point, int>(std::pair<int, int>(-1,-1), std::numeric_limits<int>::max());
    }
     
     
    while(lessPriority(parent, lchild) || lessPriority(parent, rchild) ){

        //Go right
        if(lessPriority(lchild, rchild)){
            swap_nodes(index, getRightNode(index));
            index = getRightNode(index);
        }
        //Go left
        else{
            swap_nodes(index, getLeftNode(index));
            index = getLeftNode(index);
        }
        
      
        parent = container->at(index);
        
        if(lindex < container->size()){
            lchild = container->at(getLeftNode(index));
        }
        else{
            lchild = std::pair<Point, int>(std::pair<int, int>(-1,-1), std::numeric_limits<int>::max());
        }

        if(rindex < container->size()){
            rchild = container->at(getRightNode(index));
        }
        else{
            rchild = std::pair<Point, int>(std::pair<int, int>(-1,-1), std::numeric_limits<int>::max());
        }
    }
}

void p_queue::swap_nodes(int a, int b){

    swap(container->at(a),container->at(b) );
    
    //swap points in inderection

    //std::cout << "L" <<std::endl;
    indirection->at(container->begin()[a].first) = b;
    //std::cout << "M" <<std::endl;
    indirection->at(container->begin()[b].first) = a;
    //std::cout << "N" <<std::endl;

}
void p_queue::insert(Point& x, int p)
{   
    //std::cout << "Inserting point" <<std::endl;
    auto elem = std::pair<Point, int>(x,p);

    //Addes element to bottom of heap and adds to indirection
    container->push_back(elem);
    indirection->insert(std::pair<Point,int>(elem.first, (container->size() - 1)));

    //Begins heapify process
    push_up_heap(container->size() - 1); 
  
}

Point& p_queue::pop()
{
    std::pair<Point, int> result;
    if (!container->empty())
    {
      swap_nodes(0, container->size() - 1);
      result = container->at(container->size() - 1);
      container->pop_back();
      indirection->erase(result.first);


      //pop off last element from heap
      //push down from root element to heapify heap
    }

    return result.first;
}

void p_queue::ndelete(Point& P){

    if(contains(P)){
        //std::cout << "Deleting point" << std::endl;
        int index = indirection->at(P);
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
        auto pqiter = indirection->at(key);
    }catch(std::out_of_range& ex){
        return false;
    }
    
    return true;
   
}

std::vector<std::pair<Point,int>>* p_queue::getContainer(){
    return container;
}


int p_queue::getSize(){
    return container->size();
}


int p_queue::getLeftNode(int currpos){
    return 2*currpos + 1 ;
}

int p_queue::getRightNode(int currpos){
    return 2*currpos + 2;
}

int p_queue::getParent(int currpos){
    return (currpos - 1)/2;
}




