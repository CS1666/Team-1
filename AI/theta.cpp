#include "theta.h"
#include "Queue.h"
#include <vector>
#include <math.h>

typedef vector<int> Point;
using namespace std;

bool inOpen(Point s) {return false}
void removeOpen(Point s) {

}
// Takes 2 points and gives a queue representing a path of points to the destination
queue<Point> Pathfinder::pathfind(Point start, Point goal){
    // gScore is our cost map for each point
    map<Point, int> gScore;
    gScore.insert(pair<Point, int>(start, 0));
    
    // Parent is used for backtracing in reconstruct_path()
    map<Point, Point> parent;
    parent.insert(pair<Point, Point>(start, start));
    
    // Open is the open set, aka a priority queue of points with their 'cost'
    // For now I'm using euclidean distance from the goal as my heuristic
    priority_queue<auto> * open = new priority_queue<pair<Point, int>, vector<pair<Point, int>, lessPriority>>();
    open.push(pair<Point, int>(start, gScore[start] + distance(start, goal)));
    
    // Closed is the closed set unsurprisingly
    closed = new set<Point>;
    
    // This is basically A*
    while (!open.empty())
    {
        Point s = open.top();
        open.pop();
        if (s = goal)
        {
            return reconstruct_path(s);
        }
        closed.insert(s);
        for (auto &neighbor : neighborhood(s))
        {
            auto inClosed = closed.find(neighbor);
            if (!inClosed)
            {
                // Priority queue doesn't have search functions dammit
                if (!inOpen(neighbor))
                {
                    //setting cost to 'infinite'
                    gScore.insert(pair<Point, int>(neighbor, INT_MAX));
                    parent.insert(pair<Point, Point>(neighbor, NULL));
                }
                update_vertex(s, neighbor);
            }
        }
    }
    return NULL;
}


// Use this to update the mesh
void Pathfinder::update_mesh(vector<vector<bool>> &m) {mesh = m;}

int Pathfinder::distance(Point p1, Point p2)
{
    return floor(sqrt(pow(abs(p1[0] - p2[0]), 2) + pow(abs(p1[1] - p2[1]),2)));
}

bool Pathfinder::line_of_sight(Point p1, Point p2)
{
    return (distance(p1, p2) < visionRange);
}

// Gets the immediate neighbors of s, this is also where we use the mesh for collisions
// Right now this is a really naive implementation that doesn't account for the ship's collision box
vector<Point> &Pathfinder::neighborhood(Point s)
{
    vector<Point> neighborhood{Point{s[0]-1,s[1]-1}, Point{s[0], s[1]-1}, Point{s[0]+1, s[1]-1},
                                Point{s[0]-1, s[1]},                    , Point{s[0]+1, s[1]},
                                Point{s[0]-1, s[1]+1}, Point{s[0], s[1]+1}, Point{s[0]+1, s[1]+1}};
                                
    for(auto itr = neighborhood.begin(); itr != neighborhood.end();)
    {
        if (mesh[itr->x][itr->y])
        {
            itr = neighborhood.erase(itr);
        } else
        {
            itr++;
        }
    }
    return neighborhood;
}

// Main difference between A* and Theta*. This checks for euclidean distance instead of just adjacency
void Pathfinder::update_vertex(Point s, Point neighbor)
{
    if (line_of_sight(s, neighbor))
    {
        if (gScore[parent[s]] + distance(parent[s], neighbor) < gScore[neighbor])
        {
            gScore[neighbor] = gScore[parent[s]] + distance(parent[s], neighbor);
            parent[neighbor] = parent[s];
            // Priority queues don't have search fuck my life
            if (inOpen(neighbor))
            {
                //Priority queues also dont have random access holy shit why
                removeOpen(neighbor);
            }
            open.push(pair<Point, int>(neighbor, gScore[neighbor] + distance(neighbor, goal)));
        }
    } 
    else
    {
        if (gScore[s] + distance(s, neighbor) < gScore[neighbor])
        {
            gScore[neighbor] = gScore[s] + distance(s, neighbor);
            parent[neighbor] = s;
            // I probably need to implement a custom data structure for open tbh
            if (inOpen(neighbor))
            {
                removeOpen(neighbor);
            }
            open.push(pair<Point, int>(neighbor, gScore[neighbor] + distance(neighbor, goal)));
        }
    }
}


// Back traces to build a path
queue<Point> Pathfinder::reconstruct_path(Point s)
{
    queue<Point> total_path;
    if (parent[s] == s)
    {
        total_path.push(s);
        return total_path;
    } 
    else
    {
        total_path = reconstruct_path(parent[s]);
        total_path.push(s);
        return total_path;
    }
}

