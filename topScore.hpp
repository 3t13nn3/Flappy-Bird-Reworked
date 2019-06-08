

class TopScore{
	public:
		TopScore(std::vector<Player> const& joueurs,sf::Font const& font, int const& largeur, int const& hauteur, std::string name){
				if(name == "")
					name ="Anon";
				std::string space = ": ";
				std::string tmp;

				J1_.setFont(font);
				J1_.setCharacterSize(50);
				J1_.setStyle(sf::Text::Bold);
				J2_.setFont(font);
				J2_.setCharacterSize(40);
				J2_.setStyle(sf::Text::Bold);
				J3_.setFont(font);
				J3_.setCharacterSize(30);
				J3_.setStyle(sf::Text::Bold);

				if(joueurs.size() > 0){
					if(name == joueurs[0].getNom()){
						J1_.setFillColor(sf::Color::Green);
					}
					tmp = joueurs[0].getNom();
					tmp.append(space);
					tmp.append(joueurs[0].getScoreString());
					J1_.setString(tmp);
					J1_.setOrigin({ J1_.getLocalBounds().width/2, J1_.getLocalBounds().height/2 });
					x1_= (largeur / 2);
					J1_.setPosition(x1_,hauteur/4);
				}

				if(joueurs.size() > 1){
					if(name == joueurs[1].getNom()){
						J2_.setFillColor(sf::Color::Red);
					}
					tmp = joueurs[1].getNom();
					tmp.append(space);
					tmp.append(joueurs[1].getScoreString());
					J2_.setString(tmp);
					J2_.setOrigin({ J2_.getLocalBounds().width/2, J2_.getLocalBounds().height/2 });
					x2_= (largeur / 2);
					J2_.setPosition(x2_,hauteur/3);
				}
				else{
					tmp = "Futur Player";
					J2_.setString(tmp);
					J2_.setOrigin({ J2_.getLocalBounds().width/2, J2_.getLocalBounds().height/2 });
					x2_= (largeur / 2);
					J2_.setPosition(x2_,hauteur/3);	
				}
				
				if(joueurs.size() > 2){
					if(name == joueurs[2].getNom()){
						J3_.setFillColor(sf::Color::Red);
					}
					tmp = joueurs[2].getNom();
					tmp.append(space);
					tmp.append(joueurs[2].getScoreString());	
					J3_.setString(tmp);
					J3_.setOrigin({ J3_.getLocalBounds().width/2, J3_.getLocalBounds().height/2 });
					x3_= (largeur / 2);
					J3_.setPosition(x3_,hauteur/2.45);
				}
				else{
					tmp = "Futur Player";
					J3_.setString(tmp);
					J3_.setOrigin({ J3_.getLocalBounds().width/2, J3_.getLocalBounds().height/2 });
					x3_= (largeur / 2);
					J3_.setPosition(x3_,hauteur/2.45);	
				}
				

				for(auto i : joueurs){
					//std::cout << i.getNom() << ' ' << i.getScore() << '\n';
				}
			//}
		}

		TopScore(){}

		sf::Text getJ1(){
			return J1_;
		}
		sf::Text getJ2(){
			return J2_;
		}
		sf::Text getJ3(){
			return J3_;
		}

	private:
		sf::Text J1_;
		sf::Text J2_;
		sf::Text J3_;

		float x1_;
		float x2_;
		float x3_;
};