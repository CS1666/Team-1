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



	int enemy_contr_count;
	int player_contr_count;
	bool inControl[7];
