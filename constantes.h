#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES

#define TAILLE_BLOC         30
#define NB_BLOCS_LARGEUR    17
#define NB_BLOCS_HAUTEUR    23
#define LARGEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_LARGEUR
#define HAUTEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_HAUTEUR

#include <SDL/SDL.h>
#include <iostream>
#include <ctime>

enum
{
    I,O,T,L,J,Z,S
};

enum Direction
{
    droite,gauche,bas
};

struct Coordonnees
{
    int x,y;
};

struct Player
{
    int nombreLigne;
    int level;
    int score;
};


#endif

