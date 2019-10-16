#include <math>
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
    // Give a 2D vector to represent the collision mesh, and an integer vision radius
    Pathfinder(Vector<Vector<bool>> &m, int v): mesh{m}, visionRange{v} {}
    
    // Takes 2 points and gives a queue representing a path of points to the destination
    queue<Point> pathfind(Point start, Point goal)
    {
        // gScore is our cost map for each point
        gScore = new map<Point, int>();
        gScore.insert(pair<Point, int>(start, 0));
        
        // Parent is used for backtracing in reconstruct_path()
        parent = new map<Point, Point>();
        parent.insert(pair<Point, Point>(start, start));
        
        // Open is the open set, aka a priority queue of points with their 'cost'
        // For now I'm using euclidean distance from the goal as my heuristic
        open = new priority_queue<pair<Point, int>, vector<pair<Point, int>, lessPriority>();
        open.push(pair<Point, int>>(start, gScore[start] + distance(start, goal));
        
        // Closed is the closed set unsurprisingly
        closed = new set<Point>;
        
        // This is basically A*
        while (!open.empty())
        {
            Point s = open.top()
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
        
        // Use this to update the mesh
        void update_mesh(Vector<Vector<bool>> &m) {mesh = m;}
    }
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
    }
    
    int distance(Point p1, Point p2)
    {
        return math::floor(math::sqrt(math::pow(math::abs(p1.x - p2.x)), 2) + math::pow(math::abs(p1.y - p2.y)));
    }
    
    boolean line_of_sight(Point p1, Point p2)
    {
        return (distance(p1, p2) < visionRange);
    }
    
    // Gets the immediate neighbors of s, this is also where we use the mesh for collisions
    // Right now this is a really naive implementation that doesn't account for the ship's collision box
    vector<Point> &neighborhood(Point s)
    {
        vector<Point> neighborhood{Point(s.x-1,s.y-1), Point(s.x, s.y-1), Point(s.x+1, s.y-1),
                                    Point(s.x-1, s.y),                 , Point(s.x+1, s.y),
                                    Point(s.x-1, s.y+1), Point(s.x, s.y+1), Point(s.x+1, s.y+1)};
                                    
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
    void update_vertex(Point s, Point neighbor)
    {
        if (line_of_sight(s, neighbor))
        {
            if (gScore[parent[s]] + distance(parent[s], neighbor) < gScore[neighbor])
            {
                gScore[neighbor] = gScore[parent[s] + distance(parent[s], neighbor);
                parent[neighbor] = parent[s];
                // Priority queues don't have search fuck my life
                if (inOpen(neighbor))
                {
                    //Priority queues also dont have random access holy shit why
                    removeOpen(neighbor);
                }
                open.push(pair<Point, int>(neighbor, gScore[neighbor] + distance(neighbor, goal)))
            }
        } else
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
                open.push(pair<Point, int>(neighbor, gScore[neighbor] + distance(neighbor, goal));
            }
        }
    }
    
    // Back traces to build a path
    queue<Point> reconstruct_path(Point s)
    {
        queue<Point> total_path;
        if (parent[s] == s)
        {
            total_path.push(s);
            return total_path;
        } else
        {
            total_path = reconstruct_path(parent[s]);
            total_path.push(s);
            return total_path;
        }
    }
}