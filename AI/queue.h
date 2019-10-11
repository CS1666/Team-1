#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;
//queue class
//used as a stream for our purposes (AI push to queue, ship pop

class queue
{
    private:
	int size;
	int head;
	int tail;
	vector<char> keys;
    public:
	queue();
	queue(int size);
	~queue();
	//need rest of 5
	bool isEmpty();
	void clear();
	bool push(char key);
	char pop();
	int getSize();
	int getHead();
	int getTail();
};
