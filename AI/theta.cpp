#include "theta.h"


constexpr int MAX_DEPTH=5000; //max depth before we force backtrack rebuild
constexpr int ZONE_WIDTH = 3840; 
constexpr int ZONE_HEIGHT = 2160;
Pathfinder::Pathfinder(Mesh  m, int v) : visionRange(v), mesh(m){
    gScore = std::unordered_map<Point, double, CantorHash>();
    parent = std::unordered_map<Point, Point, CantorHash>();
    closed = std::unordered_set<Point, CantorHash>();
    open =  new p_queue(ZONE_WIDTH, ZONE_HEIGHT);
}
// Takes 2 points and gives a queue representing a path of points to the destination
Path Pathfinder::pathfind(Point start, Point goal, Sprite* currShip)
{


    gScore.clear();
    parent.clear();
    closed.clear();
    open->clear();
    
    ////std::cout << "Path finding" << std::endl;
    // gScore is our cost map for each point
    gScore.insert(std::pair<Point, double>(start, 0));
    //std::cout<<start.first<<std::endl;
    //std::cout<<start.second<<std::endl;
    // Parent is used for backtracing in reconstruct_path()
    parent.insert(std::pair<Point, Point>(start, start));
   
    // Open is the open set, aka a priority queue of points with their 'cost'
    // For now I'm using euclidean distance from the goal as my heuristic
   
    open->insert(start, 0);
    
    // Closed is the closed set unsurprisingly

    int i = 0;
    int counter=0;
    // This is basically A*
    while (!open->empty())
    {
        
        // Get the point with the LOWEST expected cost
        //std::cout << "Before pop" << std::endl;
        Point s = open->pop();

        if (s == goal||counter++==MAX_DEPTH)
        {   
            return reconstruct_path(s);
        }

        closed.insert(s);

      
        std::vector<Point> npath = neighborhood(s, currShip);
        //std::cout << "--------Begining Neigh--------"<< std::endl;
        for (std::pair<int,int> neighbor : npath)
        {
            

            i = i + 1;

            auto inClosed = closed.find(neighbor);

            if (inClosed == closed.end())
            {   

                if (!open->contains(neighbor))
                {
                    //setting cost to 'infinite'
                    gScore.insert(std::pair<Point, double>(neighbor, std::numeric_limits<double>::max()));
                    parent.insert(std::pair<Point, Point>(neighbor, start));
                }
                update_vertex(s, neighbor, goal);

            }
        }
    }

   std::cout<<"Stuck"<<std::endl;
    return new std::queue<Point>();
}

// Naive implementation of update_mesh. Will need to modify to not leak tons of memory
void Pathfinder::update_mesh(Mesh m) {mesh = m;}

// We're using Euclidean distance for our heuristic for now
int Pathfinder::heuristic(Point p1, Point p2)
{
    return distance(p1, p2);
}

// Euclidean Distance
int Pathfinder::distance(Point p1, Point p2)
{
    return std::floor(std::sqrt(std::pow(std::abs(p1.first - p2.first), 2) + std::pow(std::abs(p1.second - p2.second), 2)));
}

bool Pathfinder::line_of_sight(Point p1, Point p2)
{
    return (distance(p1, p2) < visionRange);
}

// Gets the immediate neighbors of s, this is also where we use the mesh for collisions
// Right now this is a really naive implementation that doesn't account for the ship's collision box
std::vector<Point> Pathfinder::neighborhood(Point s, Sprite* currShip)
{
    
    std::vector<Point> result = defineNeighbors(s);
    std::vector<Point> fresult;
               
    for(Point itr : result)
    {   
        
        if (isTraversable(itr, currShip))
        {    
            fresult.push_back(itr);
        }
    }
    return fresult;
}
bool Pathfinder::isTraversable(Point s, Sprite* currShips){
 
    SDL_Rect a = SDL_Rect({s.first, s.second, currShips->getW(), currShips->getH()});

    bool isCollision = false;
        
        for (Sprite* ent : *mesh) {
            if(currShips != ent){
                if (ent->isCircEnt()){
                    isCollision |= ent->check_collision(&a, ent->getCollisionCirc());
                }
                else
                    isCollision |= ent->check_collision(&a, ent->getDrawBox());
            }   
        }

    return !isCollision;
}
std::vector<Point> Pathfinder::defineNeighbors(Point s){

    std::vector<Point> neighbors;

    if(isOutofBound(s, -1, -1)){
        neighbors.push_back(Point({s.first-1,s.second-1}));
    }

    if(isOutofBound(s, 0, -1)){
        neighbors.push_back(Point({s.first, s.second-1}));

    }

    if(isOutofBound(s, 1, -1)){
        neighbors.push_back(Point({s.first + 1, s.second-1}));

    }

    if(isOutofBound(s,-1, 0)){
        neighbors.push_back(Point({s.first - 1, s.second}));

    }

    if(isOutofBound(s,1, 0)){
        neighbors.push_back(Point({s.first + 1, s.second}));

    }

    if(isOutofBound(s,-1, 1)){
        neighbors.push_back(Point({s.first - 1, s.second + 1}));

    }

    if(isOutofBound(s,0, 1)){
        neighbors.push_back(Point({s.first, s.second + 1}));

    }

     if(isOutofBound(s,1, 1)){
        neighbors.push_back(Point({s.first + 1, s.second + 1}));
    }

    return neighbors;

}

bool Pathfinder::isOutofBound(Point s, int xdif, int ydif){

    return (s.first + xdif) >= 0 && (s.first + xdif < ZONE_WIDTH) && (s.second + ydif) >= 0 && (s.second + ydif < ZONE_HEIGHT);
}

// Main difference between A* and Theta*. This checks for euclidean distance instead of just adjacency
void Pathfinder::update_vertex(Point s, Point neighbor, Point goal)
{       
    if(neighbor == goal){
        open->ndelete(neighbor);
        open->insert(neighbor, 0);
    }
    else{
  
        if (line_of_sight(parent[s], neighbor))
        {   

            if (gScore[parent[s]] + distance(parent[s], neighbor) < gScore[neighbor])
            {
                gScore[neighbor] = gScore[parent[s]] + distance(parent[s], neighbor);
                parent[neighbor] = parent[s];
                
                open->ndelete(neighbor);
               
                open->insert(neighbor, gScore[neighbor] + heuristic(neighbor, goal));
            }
        } 
        else
        {
            if (gScore[s] + distance(s, neighbor) < gScore[neighbor])
            {
                gScore[neighbor] = gScore[s] + distance(s, neighbor);
                parent[neighbor] = s;
                open->ndelete(neighbor); 
                open->insert(neighbor, gScore[neighbor] + heuristic(neighbor, goal));
            }
        }

    }   
}


// Back traces to build a path
Path Pathfinder::reconstruct_path(Point s)
{
    //std::cout << "Xq point: "<< s.first << " Yq point: " << s.second <<std::endl;
    std::queue<Point>* total_path = new std::queue<Point>();
    if (parent[s] == s)
    {
        total_path->push(s);
        return total_path;
    } 
    else
    {
        total_path = reconstruct_path(parent[s]);
        total_path->push(s);
        return total_path;
    }
}
