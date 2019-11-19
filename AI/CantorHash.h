#pragma once
#import <iostream>
 typedef std::pair<int,int> Point;
 class CantorHash {

        public:
            size_t operator() (const Point& p) const{
                //std::cout << "Point: " << p.first << " " << p.second <<" Hash: " <<(((int(p.first) + int(p.second))*(int(p.first) + int(p.second) + 1))/2) + p.second  << std::endl;
                return (((int(p.first) + int(p.second))*(int(p.first) + int(p.second) + 1))/2) + p.second ;
        }
    };