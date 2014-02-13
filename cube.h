#ifndef CUBE_H
#define CUBE_H

#include "constantes.h"

class Cube
{
public:
    Cube(int = 0);
    Cube(const Cube &);
    ~Cube();

    void affiche(SDL_Surface * );

    Coordonnees getCoord() const {return coord;}

    void setCoord(int _y, int _x) {coord.y = _y*TAILLE_BLOC; coord.x=_x*TAILLE_BLOC;}
    void setCoord2(int _y, int _x) {coord.y = _y; coord.x=_x;}

private:

    Coordonnees coord;
    SDL_Surface *cube;
    int m_couleur;
};

#endif // CUBE_H
