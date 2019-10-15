#include <vector>
using namespace std;

class BlackHole
{
	vector<double> gravPull(int otherX, int otherY, int otherMass);

	bool isColliding(double distance);

	double calcDistance(int otherX, int otherY);

	vector<int> getPosition();

	int getMass();

	double getRadius();

	double getEventHorizon();

	void setPosition(vector<int> newPos);

	void setMass(int newMass);

	void setRadius(double scRadius);

private:
	vector<int> position;
	int mass;
	double schwarzschildRadius;
	const double eventHorizon = 1.5;

	/*Don't know where this is supposed to go (private or public)*/
	void updateMass(int addedMass);
};
