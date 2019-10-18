#include "p_queue.h"

using namespace std;

template <class T>
struct lessPriority
{
    bool operator(const pair<T, int> &p1, const pair<T, int> &p2)
    {
        return p1.second < p2.second;
    }
}

template<class T>
void p_queue::push(const T& x, int p)
{
    auto elem = pair<T, int>(x,p);
    container.push_back(elem);
    push_heap(container.begin(), container.end(), lessPriority);
}

template<class T>
T& top()
{
    if (!container.empty()
    {
        return container[0].first;
    }
    return NULL;
}

template<class T>
T& pop()
{
    if (!container.empty())
    {
        pop_heap(container.begin(), container.end(), lessPriority);
        auto result = container.back();
        container.pop_back();
        return result;
    }
}

template<class T>
bool contains(const T& key)
{
    return find(container.begin(), container.end(), key); != container.end()
}

template<class T>
void remove(const T& key)
{
    auto found = find(container.begin(), container.end(), key);
    container.erase(found);
}