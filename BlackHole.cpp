#include <vector>
using namespace std;

class BlackHole
{
	
public:
	vector<double> gravPull(int otherX, int otherY, int otherMass)
	{

	}

	bool isColliding(double distance)
	{

	}

	double calcDistance(int otherX, int otherY)
	{

	}

	vector<int> getPosition()
	{
		return position;
	}

	int getMass()
	{
		return mass;
	}

	double getRadius()
	{
		return schwarzschildRadius;
	}

	double getEventHorizon()
	{
		return eventHorizon;
	}


	void setPosition(vector<int> newPos)
	{
		position = newPos;
	}

	void setMass(int newMass)
	{
		mass = newMass;
	}

	void setRadius(double scRadius)
	{
		schwarzschildRadius = scRadius;
	}

private:
	vector<int> position;
	int mass;
	double schwarzschildRadius;
	const double eventHorizon = 1.5;

	/*Don't know where this is supposed to go (private or public)*/
	void updateMass(int addedMass)
	{

	}

};