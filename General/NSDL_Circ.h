#pragma once
class NSDL_Circ{

	public:
		//Constructors
		NSDL_Circ();
		NSDL_Circ(int x, int y,  int t);

		//Destructors
		~NSDL_Circ();


		//Needs Mover and Copier
		void RenderFillCirc(SDL_Renderer* rend);

		//Setters and Getters
		int getX();
		void setX(int nx);
		int getY();
		void setY(int ny);
		int getR();
		void setR(int nr);

	private:
		int x;
		int y;
		int r;

};
