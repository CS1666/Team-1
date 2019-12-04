#include "GalaxyControl.h"

	GalaxyControl::GalaxyControl()
	{
		enemy_contr_count = 7;
		player_contr_count = 1;
		int i;
		for(i = 0; i < 9; i++)
		{
			inControl[i] = false;
		}
		inControl[7] = true;
		//inControl[4] = true;
	}

	int GalaxyControl::getEnemyCount()
	{
		return enemy_contr_count;
	}

	int GalaxyControl::getPlayerCount()
	{
		return player_contr_count;
	}

	bool GalaxyControl::getInControl(int zone)
	{
		return inControl[zone];
	}

	bool GalaxyControl::getWinGame()
	{
		
		if (enemy_contr_count <= 0)
		{
			return true;
		}
		return false;
	}

	bool GalaxyControl::getLoseGame()
	{
		if (player_contr_count <= 0)
		{
			return true;
		}
		return false;

	}

	void GalaxyControl::enemyWinZone(int zone)
	{
		enemy_contr_count++;
		player_contr_count--;
		inControl[zone] = false;
	}

	void GalaxyControl::playerWinZone(int zone)
	{
		enemy_contr_count--;
		player_contr_count++;
		inControl[zone] = true;
	}

	void GalaxyControl::setZone(int zone, bool contr)
	{
		inControl[zone] = contr;
	}
	int GalaxyControl::findNeighbor(int target)
	{
	    std::vector<int> possible;
	    std::vector<int> allowed;
	    //put in player or possible
	    for(int x=0;x<8;x++)
	    {
		if(!inControl[x])
		    possible.push_back(x);
	    }
	    //remove possible if not adjacent to player
	    for(auto x:possible)
	    {
		if(x+1==target||x-1==target||x+3==target||x-3==target)
		    allowed.push_back(x);
	    }
	    //randomly choose one from allowed
	    return allowed.at(std::rand()%allowed.size());
	}
	//rng choose one player sector to attack
	int GalaxyControl::findTarget()
	{
	    std::vector<int> possible;
	    //std::cout<<"?????"<<std::endl;
	    for(int x=0;x<8;x++)
	    {
		if(inControl[x])
		    possible.push_back(x);
	    }
	    return possible.at(std::rand()%possible.size());
	}
	int enemy_contr_count;
	int player_contr_count;
	bool inControl[8];
