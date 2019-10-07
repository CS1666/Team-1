#include <iostream>
#include <string>
#include <tuple>
using namespace std;

class Star
{
	private:
		int radius;
		int gravity
		string type;
		tuple<int, int> position;
		string sprite;

	public:
		int getRadius()
		{
			return radius;
		}

		int getGravity()
		{
			return gravity;
		}

		string getType()
		{
			return type;
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

		void setGravity(int g)
		{
			gravity = g;
		}

		void setType(string t)
		{
			type = t;
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