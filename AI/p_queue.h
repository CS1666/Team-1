#pragma once
#include <vector>
#include <algorithm>


// Priority queue with random access
namespace Pathfinding
{
    template <class T>
    class p_queue
    {
        public:
            p_queue() : container(std::vector<std::pair<T,int> >()) {}
            void push(const T& x, int p);
            const T& top();
            const T& pop();
            bool empty();
            bool contains(const T& key);
            void remove(const T& key);
        private:
            std::vector<std::pair<T, int> > container;
    };
}
