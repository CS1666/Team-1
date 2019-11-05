#pragma once
#include <math.h>
#include <time.h>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#define ROW_SIZE 35
#define COL_SIZE 19


class Ellers_Maze
{
public:
	/*Default Constructor*/
	Ellers_Maze();

	/*Get if current cell has bottom wall*/
	bool hasBottom(int row, int col);

	/*Get if current cell has right wall*/
	bool hasRight(int row, int col);

	/*Get maze seed*/
	unsigned int getSeed();

	/*Test output of maze*/
	void test_output();
	void drawMaze(SDL_Texture *maze_wall, SDL_Renderer *mRender);

	int getRowSize();
	int getColSize();
	
	bool isEnd(int row, int col);

private:

	/*Structure for each cell*/
	struct cell
	{
		//bool hasTop = false;
		//bool hasLeft = false;
		bool hasBot = false;	//If there is a bottom wall	
		bool hasRight = false;	//If there is a right wall
		int setNum = 0;			//The set that the cell currently belongs to
		//int oldSet = 0;
		bool handled = false;	//Necessary for assessing possible bottom walls
		bool visited = false;	//Used for recursive backtracking maze algorithm

	};

	struct cell mazeCells[ROW_SIZE][COL_SIZE];	//Maze structure
	unsigned int seed;							//Seed for reusing mazes or testing

	/*Start of Recursive Backtracking algorithm*/
	void startCreate();

	/*Recursive Backtracking algorithm, fallback*/
	void recMaze(int i, int j, int prevDir);

	void setEnd(int side);

	int rowEnd;
	int colEnd;


	/*Eller's Maze*/
	void create_maze();
};
