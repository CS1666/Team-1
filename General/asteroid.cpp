#include <iostream>
#include <string>
#include <tuple>
using namespace std;

class Asteroid
{
	private:
		int radius;
		int velocity;
		float direction;
		tuple<int, int> position;
		string sprite;
		long mass;

	public:
		int getRadius()
		{
			return radius;
		}

		int getVelocity()
		{
			return velocity;
		}

		float getDirection()
		{
			return direction;
		}
	
		long getMass()
		{
			return mass;	
		}

		tuple<int, int> getPosition()
		{
			return position;
		}

		string getSprite()
		{
			return sprite;
		}

		void setRadius(int r)
		{
			radius = r;
		}

		void setVelocity(int v)
		{
			velocity = v;
		}

		void setDirection(float d)
		{
			direction = d;
		}

		void setPosition(tuple<int, int> newPos)
		{
			position = newPos;
		}

		void setSprite(string s)
		{
			sprite = s;
		}
	
		void setMass(long m)
		{
			mass = m;	
		}
		

};
