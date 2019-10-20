#include "p_queue.h"

using namespace std;

template <class T>
struct lessPriority
{
    bool &operator()(const pair<T, int> &p1, const pair<T, int> &p2)
    {
        return p1.second < p2.second;
    }
};

template<class T>
void p_queue<T>::push(const T& x, int p)
{
    auto elem = pair<T, int>(x,p);
    p_queue::container.push_back(elem);
    push_heap(p_queue::container.begin(), p_queue::container.end(), lessPriority<T>());
}

template<class T>
T& p_queue<T>::top()
{
    if (!p_queue<T>::container.empty())
    {
        return p_queue<T>::container[0].first;
    }
    return NULL;
}

template<class T>
T& pop()
{
    if (!p_queue<T>::container.empty())
    {
        pop_heap(p_queue<T>::container.begin(), p_queue<T>::container.end(), lessPriority<T>());
        auto result = p_queue<T>::container.back();
        p_queue<T>::container.pop_back();
        return result;
    }
}

template<class T>
bool contains(const T& key)
{
    return find(p_queue<T>::container.begin(), p_queue<T>::container.end(), key) != p_queue<T>::container.end();
}

template<class T>
void remove(const T& key)
{
    auto found = find(p_queue<T>::container.begin(), p_queue<T>::container.end(), key);
    p_queue<T>::container.erase(found);
}