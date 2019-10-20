#pragma once

#include <cmath>
#include <limits>
#include <queue>
#include <vector>
#include <map>
#include <set>
#include "p_queue.h"

// The pathfinder needs to keep its own state so thought i'd make it a class
// I think the AI can just instantiate one of these and use it repeatedly
// To use the pathfinding just instantiate this object and call pathfind() as needed
// The collision mesh will change over time so modify it as needed with update_mesh()
namespace Pathfinding
{
    class Pathfinder
    {
        public:
            typedef std::vector<int> Point;
            typedef std::queue<Point> Path;
            typedef std::vector<std::vector<bool> > Mesh;
            // Give a 2D vector to represent the collision mesh, and an integer vision radius
            Pathfinder(Mesh  &m, int v): visionRange(v), mesh(m) {}
            Path pathfind(Point start, Point goal);
            void update_mesh(Mesh &m);
    
        private:
            int visionRange;
            Mesh &mesh;
            std::map<Point, int> gScore;
            std::map<Point, Point> parent;
            p_queue<Point> open;
            std::set<Point> closed;
            int heuristic(Point p1, Point p2);
            int distance(Point p1, Point p2);
            bool line_of_sight(Point p1, Point p2);
            std::vector<Point> neighborhood(Point s);
            void update_vertex(Point s, Point neighbor, Point goal);
            Path reconstruct_path(Point s);
    };
}
