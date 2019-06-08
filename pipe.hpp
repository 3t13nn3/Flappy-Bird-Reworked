#define HAUTEUR 800
#define LARGEUR 600	

class Pipe{

	public:
		Pipe(int const& y, int const& hauteurH, int const& hauteurB, int const& largeur) : y_(y),hauteurH_(hauteurH),hauteurB_(hauteurB),largeur_(largeur){
			pipeH.setSize(sf::Vector2f(largeur,hauteurH));
			pipeH.setPosition(y,0);
			pipeB.setSize(sf::Vector2f(largeur,hauteurB));
			pipeB.setPosition(y,HAUTEUR-hauteurB);
			pipeH.setFillColor(sf::Color(99, 36, 80));
			pipeB.setFillColor(sf::Color(99, 36, 80));
		}

		sf::RectangleShape& getShapeH(){
			return pipeH;
		}

		sf::RectangleShape& getShapeB(){
			return pipeB;
		}

		float getY(){
			return y_;
		}

		void setY(float nb){
			y_=nb;
		}

	private:
		float y_;
		int hauteurH_;
		int hauteurB_;
		int largeur_;

		sf::RectangleShape pipeH;
		sf::RectangleShape pipeB;
};