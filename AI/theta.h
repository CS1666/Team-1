#pragma once

#include <cmath>
#include <limits>
#include <queue>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "CantorHash.h"
#include "p_queue.h"
#include <vector>
#include <math.h>
#include <iostream>
#include "../General/Sprite.h"
#include <SDL.h>


// The pathfinder needs to keep its own state so thought i'd make it a class
// I think the AI can just instantiate one of these and use it repeatedly
// To use the pathfinding just instantiate this object and call pathfind() as needed
// The collision mesh will change over time so modify it as needed with update_mesh()
typedef std::pair<int,int> Point;
typedef std::queue<Point>* Path;
typedef std::vector<Sprite *>* Mesh;

    class Pathfinder
    {
        public:
            
            // Give a 2D vector to represent the collision mesh, and an integer vision radius
            Pathfinder(Mesh  m, int v);
            Path pathfind(Point start, Point goal, Sprite* currShip);
            void update_mesh(Mesh m);
            bool isTraversable(Point s, Sprite* currShips);
            int distance(Point p1, Point p2);

    
        private:
            int visionRange;
            Mesh mesh;
            std::unordered_map<Point, double, CantorHash> gScore;
            std::unordered_map<Point, Point, CantorHash> parent;
            p_queue* open;
            std::unordered_set<Point, CantorHash> closed;
            int heuristic(Point p1, Point p2);
            
            bool line_of_sight(Point p1, Point p2);
            std::vector<Point> neighborhood(Point s, Sprite* currShip);

            void update_vertex(Point s, Point neighbor, Point goal);
            Path reconstruct_path(Point s);
            bool isOutofBound(Point s, int xdif, int ydif);
            std::vector<Point> defineNeighbors(Point s);
    };