#pragma once
#include <vector>
#include <algorithm>

using namespace std;

// Priority queue with random access
template <class T>
class p_queue
{
    public:
    p_queue(): container{new vector<pair<T,int>>} {}
    void push(const T& x);
    T& top();
    T& pop();
    bool contains(const T& key);
    void remove(const T& key);
    private:
    vector<pair<T, int>> container;
};