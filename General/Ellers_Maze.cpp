#include <math.h>
#include <time.h>
#include <iostream>
#define ROW_SIZE 10
#define COL_SIZE 10



class Ellers_Maze
{

private:
	struct cell
	{
		//bool hasTop = false;
		bool hasBot = false;
		//bool hasLeft = false;
		bool hasRight = false;
		int setNum = 0;
		int setCount = 1;

	};

	struct cell mazeCells[ROW_SIZE][COL_SIZE];

	void create_maze()
	{
		
		using namespace std;
		srand(time(0));
		int row = 0;
		int col = 0;
		int set = 1;

		//Will need to initialize set count for each cell
		/*Create starting row*/
		int i;
		int j;
		for (i = 0; i < COL_SIZE; i++)
		{
			mazeCells[0][i].setNum = set;
			//mazeCells[0][i].hasTop = true;
			if (i == 0)
			{
				//mazeCells[0][i].hasLeft = true;
			}

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
				
				for (j = 0; j < COL_SIZE; j++)
				{
					if (j == 0)
					{
						//mazeCells[i][j].hasLeft = true;
					}

					if (j == COL_SIZE - 1)
					{
						mazeCells[i][j].hasRight = true;
					}

					if (mazeCells[i-1][j].hasBot)
					{
						//mazeCells[i][j].hasTop = true;
						mazeCells[i][j].setNum = set;
						set++;
						cout << "set: " << set << endl;
					}
					else
					{
						//mazeCells[i][j].hasTop = false;
						mazeCells[i][j].setNum = mazeCells[i - 1][j].setNum;
					}
				}
			}

			/*Random add left/right walls to each cell*/	
			for (j = 1; j < COL_SIZE; j++)
			{
				
				int random = rand() % 3; //fix
				
				if (random == 1 || mazeCells[i][j].setNum == mazeCells[i][j - 1].setNum)
				{
					if (mazeCells[i][j].setNum == mazeCells[i][j - 1].setNum)
					{
						cout << "I: " << i << "J: " << j << endl;
					}
					mazeCells[i][j - 1].hasRight = true;
					//mazeCells[i][j].hasLeft = true;
					//mazeCells[i][j].setCount = 0;
				}
				else
				{
					mazeCells[i][j].setNum = mazeCells[i][j - 1].setNum;
					mazeCells[i][j].setCount = mazeCells[i][j - 1].setCount;
					mazeCells[i][j].setCount++;
				}
			}
			

			/*Random add bottom wall to each set within the row*/
			int start_set = 0;
			//int curr_col = 0;
			int nextSet = 1;
			while (start_set < COL_SIZE)
			{
				
				while (nextSet < COL_SIZE && mazeCells[i][nextSet].setNum == mazeCells[i][start_set].setNum)
				{
					nextSet++;
				}


				int set_count = mazeCells[i][nextSet - 1].setCount;
				if (set_count > 1)
				{
					int rand_range = (int)pow(2, set_count);
					rand_range -= 1;
					int random = rand() % rand_range; //random range
					int x = set_count - 1;
					while (random > 0)
					{
						if (random - pow(2, x) >= 0)
						{
							mazeCells[i][start_set].hasBot = true;
							random -= (int)pow(2, x);
						}
						start_set++;
						x--;
					}
				}
				start_set = nextSet;
				nextSet++;
			}
			/*Last row*/
			if (i == ROW_SIZE - 1)
			{
				for (j = 0; j < COL_SIZE; j++)
				{
					mazeCells[i][j].hasBot = true;

				}
			}
		}
		cout << "i: " << i << endl;

		
	}

public:

	Ellers_Maze()
	{
		create_maze();
	}

	bool hasBottom(int row, int col)
	{
		return mazeCells[row][col].hasBot;
	}

	bool hasRight(int row, int col)
	{
		return mazeCells[row][col].hasRight;
	}


	void test_output()
	{
		using namespace std;
		int i;
		for (i = 0; i < COL_SIZE; i++)
		{
			cout << " _";
		}

		cout << endl;
		int j;
		for (i = 0; i < ROW_SIZE; i++)
		{
			
			for (j = 0; j < COL_SIZE; j++)
			{
				if (j == 0)
				{
					cout << "|";
				}

				if (mazeCells[i][j].hasBot)
				{
					cout << "_";
				}
				else
				{
					cout << " ";
				}

				if (mazeCells[i][j].hasRight)
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

		for (i = 0; i < ROW_SIZE; i++)
		{
			for (j = 0; j < COL_SIZE; j++)
			{
				cout << mazeCells[i][j].setNum << " ";
			}
			cout << endl;
		}
	}


};

//int main()
//{
//	Ellers_Maze a;
//	a.test_output();
//	return 0;
//
//}