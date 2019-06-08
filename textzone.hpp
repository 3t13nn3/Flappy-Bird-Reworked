

class TextZone{
	public:
		TextZone(int const& largeur, int const& hauteur, sf::Font const& font)
		: largeur_(largeur), hauteur_(hauteur),on_(false), str_(""){
			nom_.setFont(font);
			nom_.setString(str_);
			nom_.setCharacterSize(40);
			nom_.setStyle(sf::Text::Bold | sf::Text::Underlined);
			
		}

		sf::Text getText(){
			return nom_;
		}

		void setStr(std::string str){
			str_ = str;
			nom_.setString(str_);
			x_= largeur_ - (nom_.getLocalBounds().width + (largeur_ / 20));
			y_= hauteur_/25;
			nom_.setPosition(x_,y_);
		}

		std::string getString(){
			return str_;
		}


	private:
		sf::Text nom_;

		int x_;
		int y_;
		int largeur_;
		int hauteur_; 

		bool on_;

		std::string str_;
};