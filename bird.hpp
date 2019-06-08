#include <cmath>
#include <vector>
#include "main.h"
class Bird{

	public:
		Bird(std::string const& fichier, float const& gravite)
		: fichier_(fichier), vitesse_(1), gravite_(gravite), alive_(true){
			//std::cout<<fichier<<std::endl;
			if(!image_.loadFromFile(fichier)){
				std::cerr << "Error loading Bird" << fichier << std::endl;
				throw 1;
			}
			else{
				sprite_.setTexture(image_);
			}
		}

		Bird (const Bird& b):
            fichier_(b.fichier_), image_(b.image_), sprite_(b.sprite_), vitesse_(b.vitesse_), gravite_(b.gravite_), alive_(b.alive_)
        {}

		void move(){
			sprite_.move(0, gravite_ - vitesse_);
			vitesse_-=0.5;
			if(alive_ ==1){
				if(vitesse_ > -5){
					sprite_.setRotation(0);
				}		
				else{
					if(abs(vitesse_)/3 < 70)
						sprite_.rotate(abs(vitesse_)/3);
					else
						sprite_.rotate(abs(vitesse_)/2);
				}
			}
		}

		void setPosition(float const& x, float const& y){
			sprite_.setPosition(x, y);
		}

		float getX(){
			return sprite_.getPosition().x;
		}

		sf::Sprite& getSprite(){
			return sprite_;
		}

		float& getVitesse(){
			return vitesse_;
		}

		void setVitesse(float vit){
			if(!(gravite_ - vitesse_ < 0))
				vitesse_ = vit;
		}

		void setAlive(bool b){
			alive_ = b;
		}

		bool getAlive(){
			return alive_;
		}

		void collision(std::vector<Pipe>& mesPipes, std::vector<Bird>& birds, std::vector<Player>& joueurs, const std::string& SCORE, const std::string& name, const int& cpt, TopScore& TS, const sf::Font& font, bool& loose, sf::Music& music,sf::Sound& soundL){
			if(alive_ && (sprite_.getGlobalBounds().intersects(mesPipes[0].getShapeH().getGlobalBounds()) ||
	        	sprite_.getGlobalBounds().intersects(mesPipes[0].getShapeB().getGlobalBounds()))){
	        		mesPipes[0].getShapeH().setFillColor(sf::Color(149, 28, 28));
					mesPipes[0].getShapeB().setFillColor(sf::Color(149, 28, 28));
					alive_=false; 
					vitesse_ = 6;
					for(auto& e : birds){
						if(e.getAlive() == true)
							return;
					}

						joueurs = score(SCORE,Player(name,cpt));
						trie(joueurs);
						TS = TopScore(joueurs,font,LARGEUR,HAUTEUR,name);
						loose = true;
						music.stop();
						soundL.play();
					
	        }
	        else if((alive_ && sprite_.getPosition().y > HAUTEUR - sprite_.getLocalBounds().width/3) || (alive_ && sprite_.getPosition().y < 0)){
					alive_=false; 
					vitesse_ = 6; 
					for(auto& e : birds){
						if(e.getAlive() == true)
							return;
					}

						joueurs = score(SCORE,Player(name,cpt));
						trie(joueurs);
						TS = TopScore(joueurs,font,LARGEUR,HAUTEUR,name);
						loose = true;
						music.stop();
						soundL.play();
	        }
		}


	private:
		std::string fichier_;
		sf::Texture image_;
		sf::Sprite sprite_;

		float vitesse_;
		float gravite_;

		bool alive_;
};