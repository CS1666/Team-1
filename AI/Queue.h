#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;
//Queue class
//used as a stream for our purposes (AI push to Queue, ship pop

class Queue
{
    private:
	int curSize;
	int head;
	int tail;
	vector<char> keys;
    public:
	//constructors
	Queue();
	Queue(int size);
	//copy constructor
	Queue(const Queue& other);
	//move constructor
	Queue(Queue&& other);
	//copy assignment
	Queue& operator=(const Queue& other);
	//move assignment
	Queue& operator=(Queue&& other);
	//deconstructor
	~Queue();
	bool isEmpty();
	void clear();
	bool push(char key);
	char pop();
	int getSize();
	int getHead();
	int getTail();
};
