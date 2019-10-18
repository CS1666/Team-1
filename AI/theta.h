#pragma once

#include <cmath>
#include <queue>
#include <vector>
#include <map>
#include <set>
using namespace std;

// The pathfinder needs to keep its own state so thought i'd make it a class
// I think the AI can just instantiate one of these and use it repeatedly
// To use the pathfinding just instantiate this object and call pathfind() as needed
// The collision mesh will change over time so modify it as needed with update_mesh()
class Pathfinder
{
    public:
    typedef vector<int> Point;
    // Give a 2D vector to represent the collision mesh, and an integer vision radius
    Pathfinder(Vector<Vector<bool>> &m, int v): mesh{m}, visionRange{v} {}
    queue<Point> pathfind(Point start, Point goal);
    void update_mesh(Vector<Vector<bool>> &m);
    
    private:
    int visionRange;
    vector<vector<bool>> &mesh;
    map<Point, int> gScore;
    map<Point, Point> parent;
    priority_queue<pair<Point, int>, vector<pair<Point, int>, lessPriority>() open;
    set<Point> closed;
    struct lessPriority
    {
        bool operator()(const pair<Point, int> p1, const pair<Point, int> p2) const
        {
            return p1.second < p2.second;
        }
    };
    int distance(Point p1, Point p2);
    bool line_of_sight(Point p1, Point p2);
    vector<Point> &neighborhood(Point s);
    void update_vertex(Point s, Point neighbor);
    queue<Point> reconstruct_path(Point s);
    
}