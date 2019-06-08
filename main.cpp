/*TODO - NEED COMMENTS*/
#include "head.h"

using namespace sf;
using namespace std;

int main (int argc, char* argv[]){
	int NB_BIRDS = 1;
	if(argc == 2){
		if (atoi(argv[1]) > 3 || atoi(argv[1]) <= 0){
			cout << "Enter a valid number of players (beetween 1 & 3)." << "\n";
			return 0;
		}
		NB_BIRDS = atoi(argv[1]);
	}
	else if(argc > 2){
		cout << "usage: " << argv[0] << " Players.";
	}
    RenderWindow window(VideoMode(LARGEUR, HAUTEUR, 32), "Flappy");
    Event event;
    window.setVerticalSyncEnabled(true);

    vector<Bird> birds;
    birds.reserve(NB_BIRDS);
    for(int i=0; i<NB_BIRDS; i++){
    	birds.emplace_back(("Media/Sprite/" + toString(i+1) + ".png"), GRAVITY);
    }

    srand(time(NULL));
    int nb = rand()%(500-100 + 1) + 100;
    /*On peut utiliser uniquement deux couples de tuyaux*/
    Pipe pipe1(600,nb,((HAUTEUR/4)*3)-nb,LARGEUR_PIPE);
    nb = rand()%(500-100 + 1) + 100;
    Pipe pipe2(1000,nb,((HAUTEUR/4)*3)-nb,LARGEUR_PIPE);
    vector<Pipe> mesPipes;
    mesPipes.emplace_back(pipe1);
    mesPipes.emplace_back(pipe2);

    bool loose = false;
    int cpt = 0;
    bool etatc = 0;

    for(int i=0; i<NB_BIRDS; i++){
    	birds[i].setPosition(200,275 + (i +1) * 25);    	   
    	birds[i].getSprite().setOrigin({ birds[i].getSprite().getLocalBounds().width/2, birds[i].getSprite().getLocalBounds().height/2 });
	}
    sf::Font font;
	if (!font.loadFromFile("Media/Font/stocky.ttf")){
    	cout << "Error loading police\n";
	}
	sf::Text compteur;

	compteur.setFont(font);
	compteur.setString(toString(cpt));
	compteur.setCharacterSize(60); // exprimée en pixels, pas en points !
	compteur.setPosition(25,10);
	compteur.setStyle(sf::Text::Bold | sf::Text::Underlined);

	sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("Media/Audio/pipe.ogg"))
        return -1;
    sf::Sound sound;
	sound.setBuffer(buffer);

	sf::SoundBuffer bufferL;
    if (!bufferL.loadFromFile("Media/Audio/loose.ogg"))
        return -1;
    sf::Sound soundL;
	soundL.setBuffer(bufferL);

	sf::SoundBuffer bufferS;
    if (!bufferS.loadFromFile("Media/Audio/start.ogg"))
        return -1;
    sf::Sound soundStart;
	soundStart.setBuffer(bufferS);
	soundStart.play();

	float pitch = 0.95;

	Texture fond_;

	std::vector<Texture> textures;
	for(int i=0; i<NB_LAYERS; i++){
		if(!fond_.loadFromFile("Media/Layers/" + toString((i+1)) + ".png")){
			return -1;
		}
		textures.emplace_back(fond_);
	}
	vector<Sprite> layers;

	for(int i=NB_LAYERS-1; i>=0; i--){
			layers.emplace_back(textures[i]);
			layers.back().setScale(1, 1);
			layers.emplace_back(textures[i]);
			layers.back().setScale(1, 1);
			layers.back().setPosition(layers.back().getGlobalBounds().width,0);
	}

	sf::Music music;
	if (!music.openFromFile("Media/Audio/loop.ogg"))
    	return -1; // erreur
	

	bool start = 0;
	bool etatMusic = 0;
	music.setLoop(true);

	TextZone TZ(LARGEUR,HAUTEUR,font);
	string name;

	vector<Player> joueurs;
 	TopScore TS = TopScore();

 	sf::Clock time_;
 	float time;

    // on fait tourner le programme jusqu'à ce que la fenêtre soit fermée
    while(window.isOpen()){
  		time = time_.restart().asSeconds();
        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        while(window.pollEvent(event))
        {
            
            // évènement "fermeture demandée" : on ferme la fenêtre
            if (event.type == Event::Closed)
                window.close();

            if(event.type == sf::Event::TextEntered && start ==0){
    			if(event.text.unicode < 256){
    				if(static_cast<char>(event.text.unicode) == 8 && name.size() > 0){ //8 == del
    					name.pop_back();
    				}
    				else if((static_cast<char>(event.text.unicode) == 8 && name.size() <= 0) || static_cast<char>(event.text.unicode) == 32){ //8 == del
    					continue;
    				}
    				else{
    					if(name.size() < 16)
    					name += static_cast<char>(event.text.unicode);
    				}
    				TZ.setStr(name);   				
                }
			}
        }

        if(soundStart.getStatus() == 0 && etatMusic == 0){
        	music.play();
        	etatMusic = 1;
	    }
        if(loose == false){
        	for(int i = 0; i< NB_BIRDS; i++)
        		birds[i].collision(mesPipes, birds, joueurs,SCORE,name,cpt,TS,font,loose,music,soundL);

        	for(int i = 0; i< NB_LAYERS*2; i++){
			    if(layers[i].getPosition().x <= -layers[i].getGlobalBounds().width){
			        layers[i].setPosition(layers[i].getGlobalBounds().width,0);
			    }
			}
        	
	        if ((Keyboard::isKeyPressed(Keyboard::Space)) && soundStart.getStatus() == 0 && birds[0].getAlive()){
	        	 	birds[0].setVitesse(14);
	        	 	start = 1;
	        	 	
	        }
	        if (Keyboard::isKeyPressed(Keyboard::Up) && soundStart.getStatus() == 0 && birds[1].getAlive()){
	        	 	birds[1].setVitesse(14);
	        	 	start = 1;
	        }
	        if (Keyboard::isKeyPressed(Keyboard::LShift) && soundStart.getStatus() == 0 && birds[2].getAlive()){
	        	 	birds[2].setVitesse(14);
	        	 	start = 1;
	        }

	        if(!start || soundStart.getStatus() == 2){
		    	float v = NB_LAYERS*2;
		        for(int i = 0; i< NB_LAYERS*2; i++, v-=2.f){
		    		layers[i].move(time * 100 * (-VITESSE_FOND/(float)v), 0);
		    		i++;
		    		layers[i].move(time * 100 * (-VITESSE_FOND/(float)v), 0);
	    		}
	        }
        	
	        if(start && soundStart.getStatus() != 2){
	        	for(int i=0; i< NB_BIRDS; i++)
		        	birds[i].move();
		        float v = NB_LAYERS;
		        for(int i = 0; i< NB_LAYERS*2; i++, v-=1.f){
			    	layers[i].move(time * 100 * (-VITESSE_FOND/(float)v), 0);
			    	i++;
			    	layers[i].move(time * 100 * (-VITESSE_FOND/(float)v), 0);
		    	}

				for(int i=0; i<2; i++){
		            mesPipes[i].getShapeH().move(time * 100 * (-VITESSE),0);
		            mesPipes[i].getShapeB().move(time * 100 * (-VITESSE),0);
		            mesPipes[i].setY(mesPipes[i].getY()-VITESSE * time * 100);
		        }

		        if(mesPipes[0].getY() < -LARGEUR_PIPE){
		            mesPipes[0]=mesPipes[1];
		            nb = rand()%(475-125 + 1) + 125;
		            Pipe tmp(800-LARGEUR_PIPE,nb,((HAUTEUR/4)*3)-nb,LARGEUR_PIPE);
		            mesPipes[1]=tmp;
		            etatc = 0;
		        }
		        for(int i = 0; i< NB_BIRDS; i++){
			        if((mesPipes[0].getShapeH().getPosition().x + mesPipes[0].getShapeH().getLocalBounds().width < birds[i].getX()&& etatc == 0)){
			        	mesPipes[0].getShapeH().setFillColor(sf::Color(68, 99, 54));
						mesPipes[0].getShapeB().setFillColor(sf::Color(68, 99, 54));
			        	cpt++;
			        	compteur.setString(toString(cpt));
			        	etatc = 1;
			        	sound.play();
			        	pitch+=0.02;
			        	sound.setPitch(pitch); 
			        }
			    }
	        }      
	    }

        else{        	
    		if ((Keyboard::isKeyPressed(Keyboard::Space) || Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::LShift)) && soundL.getStatus() == 0){
    			    sound.setPitch(0);
    				joueurs.clear();
    				TS = TopScore();
    				etatMusic = 0;
    				soundStart.play();
    				start = 0;
    				etatc = 0;
    				for(int i = 0; i< NB_BIRDS; i++){
	    				birds[i].setAlive(true);
	    				birds[i].getSprite().setRotation(0);
	    				birds[i].setPosition(200,275 + (i + 1) * 25);
	    				birds[i].setVitesse(1);
	    			}
		        	nb = rand()%(500-100 + 1) + 100;
		        	mesPipes[0] = Pipe(600,nb,((HAUTEUR/4)*3)-nb,LARGEUR_PIPE);
		    		nb = rand()%(500-100 + 1) + 100;
		    		mesPipes[1] = Pipe(1000,nb,((HAUTEUR/4)*3)-nb,LARGEUR_PIPE);
    				pitch = 0.95;
	                loose = false;
	                cpt = 0;
	                compteur.setString(toString(cpt));
	            }
        }
        for(int i = 0; i< NB_BIRDS; i++){
	        if(birds[i].getAlive() == false){
		       	birds[i].getSprite().rotate(-10);
	        	birds[i].getSprite().move(time * 100 * (-VITESSE/2),0);
	        	birds[i].move();
		    }
		}
		for(int i = 0; i< NB_LAYERS*2; i++){
			window.draw(layers[i]);
			i++;
			window.draw(layers[i]);     
    	}

        for(int i=0; i<2; i++){
	        window.draw(mesPipes[i].getShapeH());
	        window.draw(mesPipes[i].getShapeB());
		}

		window.draw(compteur);

		for(auto& b : birds)
			window.draw(b.getSprite());
		
		window.draw(TZ.getText());
		window.draw(TS.getJ1());
		window.draw(TS.getJ2());
		window.draw(TS.getJ3());
        window.display();
        
    }

    return 0;
}