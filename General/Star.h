#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Star
{
	private:
		int radius;
		int gravity;
		string type;
		vector<int> position;
		string sprite;
		long mass;
		vector<int> size;

	public:
		int getRadius();
		int getGravity();
		string getType();
		vector<int> getPosition();
		string getSprite();
		void setRadius(int r);
		void setGravity(int g);
		void setType(string t);
		void setPosition(vector<int> newPos);
		void setSprite(string s);
		long getMass();
		void setMass(long newMass);
		vector<int> getSize();
		void setSize(vector<int> newSize);
};