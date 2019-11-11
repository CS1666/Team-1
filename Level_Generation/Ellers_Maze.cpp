#pragma once
#include <math.h>
#include <time.h>
#include <iostream>
#include "Ellers_Maze.h"


/*Definitions of Ellers Maze Header*/
/*Default constructor*/
Ellers_Maze::Ellers_Maze()
{
	//startCreate();	//Uncomment if you want recursive backtracking algorithm
	create_maze();		//Comment out, if you want recursive backtracking algorithm
	setEnd(0);
	
}

Ellers_Maze::Ellers_Maze(int side) : side{side}
{
	create_maze();
	setEnd(side);
	setStart(side);
}

int Ellers_Maze::getStartCol()
{
	return startCol;
}

int Ellers_Maze::getStartRow()
{
	return startRow;
}

int Ellers_Maze::getEndCol()
{
	return endCol;
}

int Ellers_Maze::getEndRow()
{
	return endRow;
}

void Ellers_Maze::setStart(int side)
{
	srand(time(NULL));
	switch(side)
	{
		case 0:
			startRow = 0;
			startCol = rand() % COL_SIZE;
			break;
		case 1:
			startRow = rand() % ROW_SIZE;
			startCol = COL_SIZE - 1;
			break;
		case 2:
			startRow = ROW_SIZE - 1;
			startCol = rand() % COL_SIZE;
			break;
		case 3:
			startRow = rand() % ROW_SIZE;
			startCol = 0;
			break;
	}
}

/* The maze only looks for right walls, so when drawing the left edge, be sure to add the left walls as necessary, see testoutput for further clarification.
    No start/end openings have been added yet.  These can be added anywhere on any of the edges, fixed or random.
	The size of the maze is fixed, but can be adjusted if we want to have varying size.
*/

	/*Recursive backtracking maze, implemented as a fallback, but does not look nearly as good as Eller's, not enough randomness*/
	/*Initial creation function for recursive backtracking maze*/
	void Ellers_Maze::startCreate()
	{
		//srand(time(NULL));
		/*Randomize start location*/
		int j = rand() % COL_SIZE;	
		int i = rand() % ROW_SIZE;
		recMaze(i, j, 0);	//Start recursive function

	}

	/*Recursive function for recursive backtracking maze*/
	void Ellers_Maze::recMaze(int i, int j, int prevDir)
	{
		using namespace std;
		int test = 0;
		//cout << "test" << endl;
		//srand(time(NULL));
		while (true)
		{
			
			int dirs = 1;
			int random;
			mazeCells[i][j].visited = true;
			if (i > 0)
			{
				if (!(mazeCells[i - 1][j].visited))
				{
					dirs *= 2;
				}
			}

			if (j < COL_SIZE - 1)
			{
				if (!(mazeCells[i][j + 1].visited))
				{
					dirs *= 3;
				}
			}

			if (i < ROW_SIZE - 1)
			{
				if (!(mazeCells[i + 1][j].visited))
				{
					dirs *= 5;
				}
			}

			if (j > 0)
			{
				if (!(mazeCells[i][j - 1].visited))
				{
					dirs *= 7;
				}
			}

			switch (dirs)
			{
			case 1:
				return;

			case 2:
				mazeCells[i - 1][j].hasBot = false;
				recMaze(i - 1, j, 2);
				break;

			case 3:
				mazeCells[i][j].hasRight = false;
				recMaze(i, j + 1, 3);
				break;

			case 5:
				mazeCells[i][j].hasBot = false;
				recMaze(i + 1, j, 5);
				break;

			case 7:
				mazeCells[i][j - 1].hasRight = false;
				recMaze(i, j - 1, 7);
				break;

			case 6: //2 or 3
				
				if (prevDir == 2)
				{
					random = rand() % 3;
					if (random == 1)
					{
						mazeCells[i - 1][j].hasBot = false;
						recMaze(i - 1, j, 2);
					}
					else
					{
						mazeCells[i][j].hasRight = false;
						recMaze(i, j + 1, 3);
					}
				}
				else if (prevDir == 3)
				{
					random = rand() % 3;
					if (random == 1)
					{
						mazeCells[i][j].hasRight = false;
						recMaze(i, j + 1, 3);
					}
					else
					{
						mazeCells[i - 1][j].hasBot = false;
						recMaze(i - 1, j, 2);	
					}
				}
				else
				{
					random = rand() % 2;
					if (random)
					{
						mazeCells[i - 1][j].hasBot = false;
						recMaze(i - 1, j, 2);
					}
					else
					{
						mazeCells[i][j].hasRight = false;
						recMaze(i, j + 1, 3);
					}
				}
				
				break;

			case 10: //2 or 5
				
					random = rand() % 2;
					if (random)
					{
						mazeCells[i - 1][j].hasBot = false;
						recMaze(i - 1, j, 2);
					}
					else
					{
						mazeCells[i][j].hasBot = false;
						recMaze(i + 1, j, 5);
					}
				
				break;

			case 14: //2 or 7
				if (prevDir == 2)
				{
					random = rand() % 3;
					if (random == 1)
					{
						mazeCells[i - 1][j].hasBot = false;
						recMaze(i - 1, j, 2);
					}
					else
					{
						mazeCells[i][j - 1].hasRight = false;
						recMaze(i, j - 1, 7);
					}
				}
				else if (prevDir == 7)
				{
					random = rand() % 3;
					if (random == 1)
					{
						mazeCells[i][j - 1].hasRight = false;
						recMaze(i, j - 1, 7);
					}
					else
					{
						mazeCells[i - 1][j].hasBot = false;
						recMaze(i - 1, j, 2);
						
					}
				}
				else
				{
					random = rand() % 2;
					if (random)
					{
						mazeCells[i - 1][j].hasBot = false;
						recMaze(i - 1, j, 2);
					}
					else
					{
						mazeCells[i][j - 1].hasRight = false;
						recMaze(i, j - 1, 7);
					}
				}
				
				break;

			case 15: // 3 or 5
				if (prevDir == 3)
				{
					random = rand() % 3;
					if (random == 1)
					{
						mazeCells[i][j].hasRight = false;
						recMaze(i, j + 1, 3);
					}
					else
					{
						mazeCells[i][j].hasBot = false;
						recMaze(i + 1, j, 5);
					}
				}
				else if (prevDir == 5)
				{
					random = rand() % 3;
					if (random == 1)
					{
						mazeCells[i][j].hasBot = false;
						recMaze(i + 1, j, 5);
					}
					else
					{
						mazeCells[i][j].hasRight = false;
						recMaze(i, j + 1, 3);	
					}
				}
				else
				{
					random = rand() % 2;
					if (random)
					{
						mazeCells[i][j].hasRight = false;
						recMaze(i, j + 1, 3);
					}
					else
					{
						mazeCells[i][j].hasBot = false;
						recMaze(i + 1, j, 5);
					}
				}
				
				
				break;

			case 21: //3 or 7
				random = rand() % 2;
				if (random)
				{
					mazeCells[i][j].hasRight = false;
					recMaze(i, j + 1, 3);
				}
				else
				{
					mazeCells[i][j - 1].hasRight = false;
					recMaze(i, j - 1, 7);
				}
				break;

			case 35: //5 or 7
				if (prevDir == 5)
				{
					random = rand() % 3;
					if (random == 1)
					{
						mazeCells[i][j].hasBot = false;
						recMaze(i + 1, j, 5);
					}
					else
					{
						mazeCells[i][j - 1].hasRight = false;
						recMaze(i, j - 1, 7);
					}
					
				}
				else if (prevDir == 7)
				{
					random = rand() % 3;
					if (random == 1)
					{
						mazeCells[i][j - 1].hasRight = false;
						recMaze(i, j - 1, 7);
					}
					else
					{
						mazeCells[i][j].hasBot = false;
						recMaze(i + 1, j, 5);	
					}
					
				}
				else
				{
					random = rand() % 2;
					if (random)
					{
						mazeCells[i][j].hasBot = false;
						recMaze(i + 1, j, 5);
					}
					else
					{
						mazeCells[i][j - 1].hasRight = false;
						recMaze(i, j - 1, 7);
					}
					
				}
				break;
				

			case 30: //2 or 3 or 5
				random = rand() % 3;
				if (random == 1)
				{
					mazeCells[i][j].hasRight = false;
					recMaze(i, j + 1, 3);
					
				}
				else
				{
					random = rand() % 2;
					if (random)
					{
						mazeCells[i - 1][j].hasBot = false;
						recMaze(i - 1, j, 2);
					}
					else
					{
						mazeCells[i][j].hasBot = false;
						recMaze(i + 1, j, 5);
					}
				}
				break;

			case 42: //2 or 3 or 7
				random = rand() % 3;
				if (random == 1)
				{
					mazeCells[i - 1][j].hasBot = false;
					recMaze(i - 1, j, 2);
				}
				else
				{
					random = rand() % 2;
					if (random)
					{
						mazeCells[i][j].hasRight = false;
						recMaze(i, j + 1, 3);
					}
					else
					{
						mazeCells[i][j - 1].hasRight = false;
						recMaze(i, j - 1, 7);
					}
				}
				break;

			case 70: //2 or 5 or 7
				random = rand() % 3;
				if (random == 1)
				{
					mazeCells[i][j - 1].hasRight = false;
					recMaze(i, j - 1, 7);
					
				}
				else if (random == 2)
				{
					
				}
				else
				{
					random = rand() % 2;
					if (random)
					{
						mazeCells[i - 1][j].hasBot = false;
						recMaze(i - 1, j, 2);
					}
					else
					{
						mazeCells[i][j].hasBot = false;
						recMaze(i + 1, j, 5);
					}	
					
				}
				break;

			case 105: //3 or 5 or 7
				random = rand() % 3;
				if (random == 1)
				{
					mazeCells[i][j].hasBot = false;
					recMaze(i + 1, j, 5);
					
				}
				else
				{
					random = rand() % 2;
					if (random)
					{
						mazeCells[i][j].hasRight = false;
						recMaze(i, j + 1, 3);
					}
					else
					{
						mazeCells[i][j - 1].hasRight = false;
						recMaze(i, j - 1, 7);
					}
								
				}
				break;
			case 210: //2 or 3 or 5 or 7
				random = rand() % 4;
				if (random == 1)
				{
					mazeCells[i][j].hasRight = false;
					recMaze(i, j + 1, 3);
				}
				else if (random == 2)
				{
					mazeCells[i][j].hasBot = false;
					recMaze(i + 1, j, 5);
				}
				else if (random == 3)
				{
					mazeCells[i][j - 1].hasRight = false;
					recMaze(i, j - 1, 7);
				}
				else
				{
					mazeCells[i - 1][j].hasBot = false;
					recMaze(i - 1, j, 2);
				}
				break;
			}
		}
	}
	/*End of Recursive function for recursive backtracking maze*/

	/*Eller's Maze algorithm
	* Note: The set operations lack a complex structure to minimize performance impact.
	*       However, unless the size of the maze is obscenely large, 
	*       there is little actual impact on performance.  I note where performance could be impacted*/
	void Ellers_Maze::create_maze()
	{
		
		using namespace std;
		seed = (unsigned int)time(NULL);	//Save seed
		srand(seed);
		int set = 1;						//Initialize set value

		/*Create starting row*/
		int i;
		int j;
		for (i = 0; i < COL_SIZE; i++)
		{
			mazeCells[0][i].setNum = set;
			
			/*If cell is at right edge, add right wall*/
			if (i == (COL_SIZE - 1))
			{
				mazeCells[0][i].hasRight = true;
			}

			set++;
			
		}

		/*Loop through each row*/
		for (i = 0; i < ROW_SIZE; i++)
		{
			
			/*Copy for rows after first*/
			if (i > 0)
			{
				/*Loop through cells*/
				for (j = 0; j < COL_SIZE; j++)
				{
					/*If cell is at right edge, add right wall*/
					if (j == COL_SIZE - 1)
					{
						mazeCells[i][j].hasRight = true;
					}

					
					if (mazeCells[i-1][j].hasBot) //If above cell has bottom, set current cell to new set
					{
						mazeCells[i][j].setNum = set;
						set++;
						
					}
					else //Otherwise, set current cell to above cell's set
					{
						mazeCells[i][j].setNum = mazeCells[i - 1][j].setNum;
					}

					/*Starting from second cell*/
					if (j > 0)
					{
						/*Reverse loop: check each cell for matching sets after copying down, to prevent maze loops*/
						/*Performance impacted*/
						int k;
						for (k = j-1; k >= 0; k--)
						{
							
							if (mazeCells[i][j].setNum == mazeCells[i][k].setNum)	//If match found
							{
								
								//mazeCells[i][j - 1].hasRight = true;	//This line is currently not necessary, may change if a loop is discovered
								mazeCells[i][k].hasRight = true;	   //Set only the checked cell to have right wall
								break;								   //If match is found, end reverse loop for current cell check
							}
						}
					}

				}
			}

			/*Random add left/right walls to each cell*/	
			for (j = 1; j < COL_SIZE; j++)
			{
				
				int random = rand() % 2; //Random is set to 50%, can be adjusted for weight

				/*If previous cell does not already have right wall*/
				if (!mazeCells[i][j - 1].hasRight)
				{
					if (random)	//if don't add wall
					{
						/*If current cell is of a newer set than previous cell*/
						if (mazeCells[i][j].setNum > mazeCells[i][j - 1].setNum)
						{
							/*Scan through row for matches to newer set*/
							/*Performance impacted*/
							int tempSet = mazeCells[i][j].setNum;
							int k;
							for (k = 0; k < COL_SIZE; k++)
							{
								if (mazeCells[i][k].setNum == tempSet)	//If match is found
								{
									mazeCells[i][k].setNum = mazeCells[i][j - 1].setNum;	//Update each matched cell to older set
								}
								
							}
							
						}
						else //If don't add wall and otherwise current cell is of older set than previous cell
						{
							/*Scan through row for matches to newer set*/
							/*Performance impacted*/
							int tempSet = mazeCells[i][j - 1].setNum;
							int k;
							for (k = 0; k < COL_SIZE; k++)
							{
								if (mazeCells[i][k].setNum == tempSet)		//If match is found
								{
									mazeCells[i][k].setNum = mazeCells[i][j].setNum;	//Update each matched cell to older set
								}		
							}
						}
					}
					else //Otherwise, add wall
					{
						mazeCells[i][j - 1].hasRight = true;
					}
				}
			}

			
			/*If not at last row*/
			if (i < ROW_SIZE - 1)
			{
				/*Random add bottom wall to each set within the row*/
				int start_set = 0;	//Start cell of each set, start at first set
				int curr_cel = 1;	//Current cell being evaluated
				int nextSet = -1;	//Next set to be evaluated
				int setCount = 1;	//Count of set

				/*Loop through cells*/
				while (start_set < COL_SIZE)
				{
					/*If no next set to be evaluated*/
					if (start_set == -1)
					{
						break;	//end loop
					}

					
					nextSet = -1;	//Initialize next set to no set
					setCount = 1;	//Initalize current set count to 1

					/*Loop through row, starting from next cell over from start of set*/
					/*Performance impacted*/
					for (curr_cel = start_set + 1; curr_cel < COL_SIZE; curr_cel++)
					{
						if (mazeCells[i][curr_cel].setNum == mazeCells[i][start_set].setNum)	//If match is found 
						{
							setCount++;															//Increment set counter
							mazeCells[i][curr_cel].handled = true;								//Prevent cell from being re-evaluated
						}

						/*If match is not found, next set has not already been set, and current cell has not already been evaluated*/
						else if (nextSet < 0  && !mazeCells[i][curr_cel].handled)				
						{
							nextSet = curr_cel;								//Set current cell to next set to be evaluated
						}
					}

					

					curr_cel = start_set;	//Reset current cell to start of set

					/*Lazy bottom wall implementation*/
					/*While there is more than one cell in set, randomly evaluate 
					 *each cell in set for random 50% chance to add bottom wall.
					 *In this implementation the chance for adding bottom walls 
					 *to the last cell in a set is conditional on if walls were 
					 *already added to previous cells in the set*/
					/*Performance impacted*/
					while (setCount > 1)
					{
						if (curr_cel >= COL_SIZE)	//If current cell has reached end of row
						{	
							break;					//End loop
						}

						int random = rand() % 2;


						if (random > 0)	//If, add wall
						{
							mazeCells[i][curr_cel].hasBot = true;	//add wall
							setCount--;								//Decrement set counter
						}
						curr_cel++;									//Increment to next cell over

						
						/*While next cell is not next in set*/
						while (curr_cel < COL_SIZE && mazeCells[i][curr_cel].setNum != mazeCells[i][start_set].setNum)
						{
							curr_cel++;	//Increment current cell
						}

						/*More complex implementation, may be uneccessary, but it eliminates the conditional randomness and has all cells of equal chance*/
						//int rand_range = (int)pow(2, setCount);
						//rand_range -= 1;
						//int random = rand() % rand_range; //random range
						//int x = setCount - 1;
						//curr_col = start_set;
						//while (random > 0 && curr_col < COL_SIZE)
						//{
						//	
						//	while (curr_col < COL_SIZE && mazeCells[i][curr_col].setNum != mazeCells[i][start_set].setNum)
						//	{
						//		curr_col++;
						//	}

						//	if (random - pow(2, x) >= 0)
						//	{
						//		mazeCells[i][start_set].hasBot = true;
						//		random -= (int)pow(2, x);
						//	}
						//	curr_col++;
						//	x--;
						//}
					}
					start_set = nextSet;	//Set start of set to next set to be evaluated
				}
			}
			/*End of bottom wall adding*/

			/*Last row*/
			if (i == ROW_SIZE - 1)
			{
				int final = mazeCells[i][0].setNum; //Set final set evaluation to be first cell's set
				int tempSet = 0;					//Initialize temporary set evaluation to no set

				/*Loop through row*/
				for (j = 0; j < COL_SIZE; j++)
				{
					mazeCells[i][j].hasBot = true;	//Set each cell to have bottom wall

					/*Starting from second cell*/
					if (j > 0)
					{
						if (mazeCells[i][j].setNum != final)	//If current cell does not match final set
						{
							if (mazeCells[i][j].setNum != tempSet)	//If current cell's set does not match current temporary set
							{
								tempSet = mazeCells[i][j].setNum;		//Set temporary set to current cell's set
								mazeCells[i][j - 1].hasRight = false;	//Remove right wall
								mazeCells[i][j].setNum = final;			//Set current cell to final set

								/*Starting from cell after current cell, check remaining cells for match to current temporary set*/
								/*Performance impacted*/
								int k;
								for (k = j + 1; k < COL_SIZE; k++)
								{
									if (mazeCells[i][k].setNum == tempSet)	//If a match is found
									{
										mazeCells[i][k].setNum = final;		//Update current cell to final set, don't remove wall
									}
								}
							}
							else //Otherwise, current cell, matches current set, might be unnecessary
							{
								mazeCells[i][j].setNum = final;		//Update current cell to final set, don't remove wall
							}
							
						}
					}

				}
			}
		}
	}
	/*End of create Eller's Maze*/

	bool Ellers_Maze::isEnd(int row, int col)
	{
		
		if(endRow == row && endCol == col)
		{
			return true;
		}
		return false;
	}

	void Ellers_Maze::setEnd(int side)
	{
		switch(side)
		{
			case 0: //top, set end to bottom
				endRow = ROW_SIZE - 1;
				endCol = rand() % COL_SIZE;
				break;

			case 1: //right, set end to left
				endCol = 0;
				endRow = rand() % ROW_SIZE;
				break;

			case 2: //bottom, set end to top
				endRow = 0;
				endCol = rand() % COL_SIZE;
				break;

			case 3: //left, set end to right
				endCol = COL_SIZE - 1;
				endRow = rand() % ROW_SIZE;
				break;
		}
	}



	

	/*Get if current cell has bottom*/
	bool Ellers_Maze::hasBottom(int row, int col)
	{
		return mazeCells[row][col].hasBot;
	}
	
	bool Ellers_Maze::hasRight(int row, int col)
	{
		return mazeCells[row][col].hasRight;
	}

	/*Get current seed being used*/
	void Ellers_Maze::setSeed(){
		this->seed = seed + 100;
	}

	unsigned int Ellers_Maze::getSeed()
	{
		return seed;
	}

	/*Testing output function
	 *Outputs current maze to console as basic ascii*/
	void Ellers_Maze::test_output()
	{
		using namespace std;
		cout << endl;
		int i;
		for (i = 0; i < COL_SIZE; i++) //Initialize top edge cells to have top walls
		{
			cout << " __";
		}

		cout << endl;

		/*Loop through rows*/
		int j;
		for (i = 0; i < ROW_SIZE; i++)
		{
			/*Loop through cols*/
			for (j = 0; j < COL_SIZE; j++)
			{
				if (j == 0)	//If cell is at left edge, add left wall
				{
					cout << "|";
				}

				if (hasBottom(i, j))	//If cell has bottom wall
				{
					cout << "__";
				}
				else
				{
					cout << "  ";
				}

				if (hasRight(i, j))		//If cell has right wall
				{
					cout << "|";
				}
				else
				{
					cout << " ";
				}

			}
		   cout << endl;
		}

		cout << "Seed: " << getSeed() << endl;	//Output seed

		/*Testing for set evaluation */
		/*for (i = 0; i < ROW_SIZE; i++)
		{
			for (j = 0; j < COL_SIZE; j++)
			{
				if (mazeCells[i][j].setNum < 10)
				{
					cout << "0";
				}
				cout << mazeCells[i][j].setNum << " ";
			}
			cout << "\ti: " << i << endl;
		}*/
	}
	/*End of test output*/

	int Ellers_Maze::getRowSize()
	{
		return ROW_SIZE;
	}

	int Ellers_Maze::getColSize()
	{
		return COL_SIZE;
	}

	void Ellers_Maze::drawMaze(SDL_Texture *maze_wall, SDL_Renderer *mRender)
	{
   		int x = 8;
    		int y = 4;
	    	int width = 36;
	    	int height = 4;
	    	int row = 0;
	    	int col = 0;
		SDL_Point h;
		h.x = 0;
		h.y = 0;
		for(row = 0; row < getRowSize(); row++)
		{
			for(col = 0; col < getColSize(); col++)
			{
			   
			    if(row == 0)
			    {
				if(!(side == 2 && endCol == col))
				{
					SDL_Rect section = {x, y, width, height};
					SDL_RenderCopyEx(mRender, maze_wall, NULL, &section,  90, &h, SDL_FLIP_NONE);
				}
				
			    }

				if(col == 0)
				{
				    if(!(side == 1 && endRow == row))
				    {
				    	SDL_Rect section = {x, y, width, height};
				    	SDL_RenderCopyEx(mRender, maze_wall, NULL, &section, 0, &h, SDL_FLIP_NONE);
				    }
				}

			    if(hasRight(row, col) && !(side == 3 && endRow == row && endCol == col))
			    {
				SDL_Rect section = {x, y+width, width, height};
				SDL_RenderCopyEx(mRender, maze_wall, NULL, &section,  0, &h, SDL_FLIP_NONE);
			    }
			    else
			    {
				SDL_Rect section = {x, y, height, height};
				SDL_RenderCopyEx(mRender, maze_wall, NULL, &section,  0, &h, SDL_FLIP_NONE);
			    }

			    if(hasBottom(row, col) && !(side == 0 && endRow == row && endCol == col))
			    {
				SDL_Rect section = {x+width, y, width, height};
				SDL_RenderCopyEx(mRender, maze_wall, NULL, &section,  90, &h, SDL_FLIP_NONE);
			    }
		 	    
			    y += width;

			}
			y = 4;
			x += width;
    		}
	}

//int main()
//{
//
//	Ellers_Maze a;
//	a.test_output();
//	return 0;
//}
