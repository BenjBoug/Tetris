#ifndef PIECE_H
#define PIECE_H

#include "constantes.h"
#include "cube.h"
#include "plateau.h"
#include <vector>

class Piece
{
public:
    Piece();
    Piece(const Piece & );
    ~Piece();

    //deplace la piece
    void deplacer_gauche();
    void deplacer_droite();
    //affiche la piece
    void affiche(SDL_Surface * );
    //place les cubes pour qu'il prenne la bonne forme
    void definirForme();
    // graviter, fait descendre la piece d'un cran
    void descendre(bool annul = false);
    // choisi aléatoirement la piece
    int choixPieceAleatoire(int,int);
    // tourna la piece
    void rotation();
    // modifier la position de la piece
    void setPosition(int,int);
    // compte les collisions avec d'autres piece ou le bord de l'écran
    int collision(Plateau *);

    Cube * getCube(int i) const {return cube[i];}

private:
    std::vector < Cube* > cube;
    static std::vector<int> anti_doublons;
    int forme_piece;
};

#endif // PIECE_H
