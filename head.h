#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>


#include "pipe.hpp"
#include "player.hpp"
#include "textzone.hpp"
#include "topScore.hpp"
#include "bird.hpp"


#define HAUTEUR 800
#define LARGEUR 600
#define LARGEUR_PIPE 100
#define VITESSE 2.75
#define VITESSE_FOND 2.f
#define GRAVITY 5
#define NB_LAYERS 8
#define SCORE "score.data"
