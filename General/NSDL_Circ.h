
class NSDL_Circ{

	public:
		NSDL_Circ();
		NSDL_Circ(int x, int y,  int t);
		~NSDL_Circ();

		void RenderFillCirc(SDL_Renderer* rend);

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