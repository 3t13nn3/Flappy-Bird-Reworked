#include "head.h"

using namespace sf;
using namespace std;

string toString(Int64 integer)
{
    ostringstream os;
    os << integer;
    return os.str();
}

void trie(vector<Player>& joueurs){
	Player tmp("",0);
	size_t i,j;
	for (i = 0; i < joueurs.size(); ++i){
		for (j = i + 1; j < joueurs.size(); ++j){
			if(joueurs[i].getScore() < joueurs[j].getScore()){
				tmp = joueurs[i];
				joueurs[i] = joueurs[j];
				joueurs[j] = tmp;
			}
        }
    }
}

vector<Player> score(string nom, Player joueurActuel){
	vector<Player> joueurs;
	fstream fichier;
	fichier.open(nom, ios::in);
	if(!fichier){
		fichier.open(nom, ios::out);
		fichier.close();
		fichier.open(nom, ios::in);
	}
	if(fichier){
		if(joueurActuel.getNom() == ""){
			joueurActuel.setNom("Anon");		
		}
		string nomJ;
		string scoreJ;
		bool exist = false;
		bool recordPerso = false;
		/*On vérifie si il y a déjà un score avec le même nom*/      
		while (fichier >> nomJ >> scoreJ){
			if(joueurActuel.getNom() == nomJ){
				exist=true;
				if(joueurActuel.getScore() > stoi(scoreJ)){
					scoreJ = toString(joueurActuel.getScore());
					recordPerso = true;
					//cout << "Votre score a été enregistré!\n";
				}
			}
			joueurs.emplace_back(Player(nomJ,stoi(scoreJ)));
		}
		/*Si le joueur n'existe pas*/
		if(!exist || joueurs.size()==0){
			joueurs.emplace_back(joueurActuel);
			recordPerso = true;
		}
		if(!recordPerso){
			//cout << "Votre score n'a pas été enregistré.\n";
		}
		else{
			/*On vérifie si c'est le meilleur score parmis tout les joueurs*/
			Player tmp("",0);
			for(auto a : joueurs){
				if(tmp.getScore() <= a.getScore()){
					tmp = a;
				}
			}
			if(tmp.getScore() == joueurActuel.getScore()){
				//cout << "Vous êtes le meilleur joueur avec " << tmp.getScore() << " points. \n";
			}
			//else
				//cout << "Le meilleur joueur est " << tmp.getNom() << " avec " << tmp.getScore() << " points. \n";
		}
		fichier.close();
		/*On efface le fichier*/
		fstream fichier(nom, ios::in | ios::out);
		for(auto a : joueurs){
			fichier << a.getNom() << ' ' << a.getScore() << '\n';
			//cout << a.getNom() << ' ' << a.getScore() << '\n';
		}
		
		fichier.close();
	}

    return joueurs;
}