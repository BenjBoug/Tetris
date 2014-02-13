#include "cube.h"

Cube::Cube(int _couleur)
{
    cube = SDL_LoadBMP("images/cube.bmp");
    m_couleur = _couleur;
}

Cube::Cube(const Cube & cubeACopier)
{
    coord = cubeACopier.coord;
    m_couleur = cubeACopier.m_couleur;
    cube = SDL_LoadBMP("images/cube.bmp");
}

Cube::~Cube()
{
    SDL_FreeSurface(cube);
}

void Cube::affiche(SDL_Surface* screen)
{
    SDL_Rect position, positionRel;

    position.x = coord.x;
    position.y = coord.y;

    positionRel.w=30;
    positionRel.h=30;
    positionRel.y=0;
    positionRel.x=m_couleur*TAILLE_BLOC;

    SDL_BlitSurface(cube, &positionRel, screen, &position);
}
