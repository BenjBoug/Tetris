#ifndef PLATEAU_H
#define PLATEAU_H

#include "constantes.h"
#include "cube.h"
#include <vector>

class Plateau
{
public:
    Plateau();
    ~Plateau();

    // ajoute les cube dans le plateau
    void addCube(const Cube*);
    // affiche le plateau
    void affiche(SDL_Surface *);
    // renvoi TRUE si le cube envoy� est sur un autre cube
    bool collision(Cube*);
    // renvoi le nombre de ligne compl�te
    int ligneComplete();
    // vide la ligne
    void videLigne(int);
    // deplace tout les cubes au dessus d'une ligne vide
    void replaceLigne(int);
    // si les cube sont pos�s en haut du tableau
    bool game_over();

private:
    std::vector < Cube* > plateau;
};

#endif // PLATEAU_H
