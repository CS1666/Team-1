class GalaxyControl
{
public:

	int getEnemyCount()
	{
		return enemy_contr_count;
	}

	int getPlayerCount()
	{
		return player_contr_count;
	}

	bool getInControl(int zone)
	{
		return inControl[zone];
	}

	bool getWinGame()
	{
		
		if (enemy_contr_count <= 0)
		{
			return true;
		}
	}

	bool getLoseGame()
	{
		if (player_contr_count <= 0)
		{
			return true;
		}

	}

	void enemyWinZone(int zone)
	{
		enemy_contr_count++;
		player_contr_count--;
		inControl[zone] = false;
	}

	void playerWinZone(int zone)
	{
		enemy_contr_count--;
		player_contr_count++;
		inControl[zone] = true;
	}

	void setZone(int zone, bool contr)
	{
		inControl[zone] = contr;
	}

private:

	int enemy_contr_count;
	int player_contr_count;
	bool inControl[7];

};