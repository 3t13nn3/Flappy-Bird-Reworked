
class Player{

	public:
		Player(std::string const& nom, int const& score)
		: nom_(nom),score_(score){}

	std::string getNom() const{
		return nom_;
	}

	void setNom(std::string nom){
		nom_=nom;
	}

	int getScore() const{
		return score_;
	}

	std::string getScoreString() const{
    	return std::to_string(score_);
	}

	private:
		std::string nom_;
		int score_;
};