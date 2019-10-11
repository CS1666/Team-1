#include "Queue.h"

Queue::Queue()
{
    curSize=0;
    head=0;
    tail=0;
    keys=vector<char>(0);
};
Queue::Queue(int size)
{
    curSize=0;
    head=0;
    tail=0;
    keys=vector<char>(size);
}
//todo: actually assignment
Queue& Queue::operator = (const Queue& other)
{

}
//todo: copy?
Queue::Queue(const Queue& other)
{

}
Queue::~Queue()
{
    //probably don't need to manually destroy anything?
}
bool Queue::isEmpty()
{
    if(curSize==0)
	return true;
    return false;
}
void Queue::clear()
{
    curSize=0;
    head=0;
}

//true if added, false if not
//additionally moves tail
bool Queue::push(char key)
{
    if(curSize==keys.size())
    {
	cout << "Filled capacity" << endl;
	return false;
    }
    keys[tail]=key;
    if(tail==keys.size())
	tail=0;
    else
	tail++;
    curSize++;
    return true;
}
//returns head or null if size==0
//additionally, moves head (deletes the returned)
char Queue::pop()
{
    if(curSize==0)
	return 0;
    char val=keys[head];
    if(head==curSize)
	head=0;
    else
	head++;
    curSize--;
    return val;
}
int Queue::getSize()
{
    return curSize;
}
int Queue::getHead()
{
    return head;
}
int Queue::getTail()
{
    return tail;
}
int test()
{
    Queue test=Queue(5);
    test.push(1);
    test.push(2);
    test.push(3);
    cout <<test.getSize() <<endl;
    cout << test.pop() <<endl;
    cout<<test.getSize()<<endl;
    return 0;
}
