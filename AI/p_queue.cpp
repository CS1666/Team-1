#include "p_queue.h"
#include <iostream>
#include <ctime>
#include <stdexcept>

p_queue::p_queue(int width, int heigth){
    container = new std::vector<std::pair<Point,int>>();
    std::vector<int> x(heigth, -1);
    indirection = std::vector<std::vector<int>>(width, x);
}

p_queue& p_queue::operator=(p_queue& a){
;
    std::vector<std::pair<Point,int>>* npq = new std::vector<std::pair<Point,int>>;
    std::vector<int> x(indirection[0].size(), -1);
    std::vector<std::vector<int>> nin =  std::vector<std::vector<int>>(indirection.size(), x);

    npq = a.container;

    delete a.container;
    a.container = npq;

    nin = a.indirection;


    return *this;
}
bool p_queue::lessPriority(std::pair<Point, int> &p1, std::pair<Point, int> &p2)
{
    return p1.second > p2.second;
}


void p_queue::push_up_heap(int index){
    

    //std::cout << "\nPushing up: " << container->at(index).second << std::endl;
    if(index != 0){
        
        std::pair<Point, int> child = container->at(index);

        ////std::cout << "B" <<std::endl;
        std::pair<Point, int> parent = container->at(getParent(index));
        while(!lessPriority(child,parent)){
            ////std::cout << "C" <<std::endl;
            ////std::cout << "Parent p  " << getParent(index) << ": " << parent.second <<" child p "<< index << ": " << child.second << std::endl;
            swap_nodes(index, getParent(index));

            ////std::cout << "D" <<std::endl;
            index = getParent(index);
            ////std::cout << "E" <<std::endl;
            child = container->at(index);

            //Stop if at top of heap
            if(index == 0){
                break;
            }
            ////std::cout << "F" <<std::endl;
            parent = container->at(getParent(index));
            ////std::cout << "Parent p  " << getParent(index) << ": " << parent.second <<" child p "<< index << ": " << child.second << std::endl;
            ////std::cout << "G" <<std::endl;

        }
    }
    
}

void p_queue::push_down_heap(int index){
    
    int currindex = index;
    int rindex = getRightNode(currindex);
    int lindex = getLeftNode(currindex);
    std::pair<Point, int> parent;
    std::pair<Point, int> lchild;
    std::pair<Point, int> rchild;

    //std::cout << "A" << std::endl;
    parent = container->at(index);

    //Checks to make sure both left and right child exist before assigning them
    //To respective var
    //If they do not exist assign point, int pair where
    //Point = (-1,-1)
    //int = infinity
    //std::cout << "B" << std::endl;
    if(lindex < container->size()){
        //std::cout << "c" << std::endl;
        lchild = container->at(getLeftNode(index));
    }
    else{
        //std::cout << "D" << std::endl;
        lchild = std::pair<Point, int>(std::pair<int, int>(-1,-1), std::numeric_limits<int>::max());
    }

    //std::cout << "E" << std::endl;
    if(rindex < container->size()){
        //std::cout << "F" << std::endl;
        rchild = container->at(getRightNode(index));
    }
    else{
        //std::cout << "G" << std::endl;
        rchild = std::pair<Point, int>(std::pair<int, int>(-1,-1), std::numeric_limits<int>::max());
    }
     
    //std::cout << "H" << std::endl;
    while(lessPriority(parent, lchild) || lessPriority(parent, rchild) ){

        //Go right
        //std::cout << "Parent p: " << parent.second <<" lchild p: "<< lchild.second <<"rchild p: "<<rchild.second<< std::endl;
        //std::cout << "I" << std::endl;
        if(lessPriority(lchild, rchild)){
            //std::cout << "J" << std::endl;
            swap_nodes(index, getRightNode(index));
            //std::cout << "K" << std::endl;
            index = getRightNode(index);
        }
        //Go left
        else{
            //std::cout << "L" << std::endl;
            swap_nodes(index, getLeftNode(index));
            //std::cout << "M" << std::endl;
            index = getLeftNode(index);
        }
        
        //std::cout << "O" << std::endl;
        parent = container->at(index);
        //std::cout << "P" << std::endl;
        
        lindex = getLeftNode(index);
        rindex = getRightNode(index);
        if(lindex < container->size()){
            //std::cout << "Q" << std::endl;
            lchild = container->at(getLeftNode(index));

        }
        else{
            //std::cout << "R" << std::endl;
            lchild = std::pair<Point, int>(std::pair<int, int>(-1,-1), std::numeric_limits<int>::max());
        }

        if(rindex < container->size()){
            //std::cout << "S" << std::endl;
            rchild = container->at(getRightNode(index));
        }
        else{
            //std::cout << "T" << std::endl;
            rchild = std::pair<Point, int>(std::pair<int, int>(-1,-1), std::numeric_limits<int>::max());
        }

        //std::cout << "Parent p: " << parent.second <<" lchild p: "<< lchild.second <<"rchild p: "<<rchild.second<< "\n" << std::endl;
    }
}

void p_queue::swap_nodes(int a, int b){

    swap(container->at(a),container->at(b));
    
    //swap points in inderection

    Point pa = container->begin()[a].first;
    Point pb = container->begin()[b].first;

    ////std::cout << "L" <<std::endl;
    indirection[pa.first][pa.second] = b;
    ////std::cout << "M" <<std::endl;
    indirection[pb.first][pb.second] = a;
    ////std::cout << "N" <<std::endl;

}
void p_queue::insert(Point& x, int p)
{   
    ////std::cout << "Inserting point" <<std::endl;
    auto elem = std::pair<Point, int>(x,p);

    //Addes element to bottom of heap and adds to indirection
    container->push_back(elem);
    indirection[x.first][x.second] = (container->size() - 1);

    //Begins heapify process
    push_up_heap(container->size() - 1); 
  
}

Point& p_queue::pop()
{   
    //std::cout << "\nPopping: " << container->size() << std::endl;
    std::pair<Point, int> result;

    if (container->size() > 1)
    {
      swap_nodes(0, container->size() - 1);
      result = container->back();
      container->pop_back();
      indirection[result.first.first][result.first.second] = -1;

      push_down_heap(0);
      //pop off last element from heap
      //push down from root element to heapify heap
    }
    else if(!container->empty()){

      result = container->back();
      container->pop_back();
      indirection[result.first.first][result.first.second] = -1;

    }

    return result.first;
}

void p_queue::ndelete(Point& P){

    if(contains(P)){
        ////std::cout << "Deleting point" << std::endl;
        int index = indirection[P.first][P.second];
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
    
    else if(indirection[key.first][key.second] == -1){
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




