#include "queue.h"

queue::queue()
{
    size=0;
    head=0;
    tail=0;
    keys=vector<char>(0);
};
queue::queue(int size)
{
    this->size=size;
    head=0;
    tail=0;
    keys=vector<char>(size);
}
queue::~queue()
{
    //probably don't need to manually destroy anything?
}
bool queue::isEmpty()
{
    if(size==0)
	return true;
    return false;
}
void queue::clear()
{
    size=0;
    head=0;
}

//true if added, false if not
//additionally moves tail
bool queue::push(char key)
{
    if(size==keys.size())
    {
	//cout << "Filled capacity" << endl;
	return false;
    }
    keys[tail]=key;
    if(tail+1==size)
	tail=0;
    else
	tail++;
    size++;
    return true;
}
//returns head or null if size==0
//additionally, moves head
char queue::pop()
{
    if(size==0)
	return 0;
    char val=keys[head];
    if(head+1==size)
	head=0;
    else
	head++;
    return val;
}
int queue::getSize()
{
    return size;
}
int queue::getHead()
{
    return head;
}
int queue::getTail()
{
    return tail;
}
