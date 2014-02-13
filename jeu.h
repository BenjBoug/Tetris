#ifndef JEU_H
#define JEU_H

#include "constantes.h"
#include "plateau.h"
#include "piece.h"
#include "moteur.h"
#include "interface.h"
#include <SDL/SDL_ttf.h>

class Moteur;

class Jeu
{
public:
    Jeu(Moteur *);
    ~Jeu();
    //initialisation du jeu
    bool init();
    // affiche la scene
    void affiche(SDL_Surface *);
    // gere la scene
    void gereScene();
    //geres les touches envoyer par le moteur
    void gereTouche(int);

    // gere les collisions pour les rotations
    void collision_rot_gauche();
    void collision_rot_droite();

    int compteCellScoring();

    void hardDrop();

    int getLvl() {return player->level;}

private:
    // pointeur sur le moteur du jeu
    Moteur * parent;
    Piece * forme_actuel, *forme_suivante;
    Plateau * plateau;
    int tempsActuel, tempsSuivant;
    Interface * interface;
    // structure sur les données du joueur
    Player * player;
    int touche_actuel, bonus_point;
    SDL_Surface * sdl_start;
    TTF_Font *police;
    bool start;
};

#endif // JEU_H
