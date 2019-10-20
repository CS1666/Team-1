#include "theta.h"
#include "Queue.h"
#include <vector>
#include <math.h>

using namespace Pathfinding;
typedef std::vector<int> Point;
typedef std::queue<Point> Path;
typedef std::vector<std::vector<bool> > Mesh;

// Takes 2 points and gives a queue representing a path of points to the destination
Path Pathfinder::pathfind(Point start, Point goal)
{
    // gScore is our cost map for each point
    gScore = std::map<Point, int>();
    gScore.insert(std::pair<Point, int>(start, 0));
    
    // Parent is used for backtracing in reconstruct_path()
    parent = std::map<Point, Point>();
    parent.insert(std::pair<Point, Point>(start, start));
    
    // Open is the open set, aka a priority queue of points with their 'cost'
    // For now I'm using euclidean distance from the goal as my heuristic
    open =  p_queue<Point>();
    open.push(start, gScore[start] + heuristic(start, goal));
    
    // Closed is the closed set unsurprisingly
    closed = std::set<Point>();
    
    // This is basically A*
    while (!open.empty())
    {
        // Get the point with the LOWEST expected cost
        Point s = open.pop();
        if (s == goal)
        {
            return reconstruct_path(s);
        }
        closed.insert(s);
        for (auto neighbor : neighborhood(s))
        {
            auto inClosed = closed.find(neighbor);
            if (inClosed == closed.end())
            {
                // Priority queue doesn't have search functions dammit
                if (!open.contains(neighbor))
                {
                    //setting cost to 'infinite'
                    gScore.insert(std::pair<Point, int>(neighbor, std::numeric_limits<int>::max()));
                    parent.insert(std::pair<Point, Point>(neighbor, Point{0,0}));
                }
                update_vertex(s, neighbor, goal);
            }
        }
    }
    return Path();
}

// Naive implementation of update_mesh. Will need to modify to not leak tons of memory
void Pathfinder::update_mesh(Mesh &m) {mesh = m;}

// We're using Euclidean distance for our heuristic for now
int Pathfinder::heuristic(Point p1, Point p2)
{
    return distance(p1, p2);
}

// Euclidean Distance
int Pathfinder::distance(Point p1, Point p2)
{
    return std::floor(std::sqrt(std::pow(std::abs(p1[0] - p2[0]), 2) + std::pow(std::abs(p1[1] - p2[1]), 2)));
}

bool Pathfinder::line_of_sight(Point p1, Point p2)
{
    return (distance(p1, p2) < visionRange);
}

// Gets the immediate neighbors of s, this is also where we use the mesh for collisions
// Right now this is a really naive implementation that doesn't account for the ship's collision box
std::vector<Point> Pathfinder::neighborhood(Point s)
{
    std::vector<Point> neighborhood{Point{s[0]-1,s[1]-1}, Point{s[0], s[1]-1}, Point{s[0]+1, s[1]-1},
                                    Point{s[0]-1, s[1]},                        Point{s[0]+1, s[1]},
                                    Point{s[0]-1, s[1]+1}, Point{s[0], s[1]+1}, Point{s[0]+1, s[1]+1}};
    std::vector<Point> result = std::vector<Point>();                           
    for(auto itr : neighborhood)
    {
        if (!mesh[itr[0]][itr[1]])
        {
            result.push_back(itr);
        }
    }
    return result;
}

// Main difference between A* and Theta*. This checks for euclidean distance instead of just adjacency
void Pathfinder::update_vertex(Point s, Point neighbor, Point goal)
{
    if (line_of_sight(s, neighbor))
    {
        if (gScore[parent[s]] + distance(parent[s], neighbor) < gScore[neighbor])
        {
            gScore[neighbor] = gScore[parent[s]] + distance(parent[s], neighbor);
            parent[neighbor] = parent[s];
            if (open.contains(neighbor))
            {
                open.remove(neighbor);
            }
            open.push(neighbor, gScore[neighbor] + heuristic(neighbor, goal));
        }
    } 
    else
    {
        if (gScore[s] + distance(s, neighbor) < gScore[neighbor])
        {
            gScore[neighbor] = gScore[s] + distance(s, neighbor);
            parent[neighbor] = s;
            if (open.contains(neighbor))
            {
                open.remove(neighbor);
            }
            open.push(neighbor, gScore[neighbor] + heuristic(neighbor, goal));
        }
    }
}


// Back traces to build a path
Path Pathfinder::reconstruct_path(Point s)
{
    std::queue<Point> total_path;
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

