#include <iostream>
#include <string>
#include <tuple>
using namespace std;

class Planet
{
	private:
		int radius;
		int velocity;
		float direction;
		int gravity;
		tuple<int, int> position;
		sting sprite;

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

		int getGravity()
		{
			return gravity;
		}

		tuple getPosition()
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

		void setGravity(int g)
		{
			gravity = g;
		}

		void setPosition(tuple<int, int> newPos)
		{
			position = newPos;
		}

		void setSprite(string s)
		{
			sprite = s;
		}

}
