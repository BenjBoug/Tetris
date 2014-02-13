#ifndef MENU_H
#define MENU_H

#include "constantes.h"
#include "jeu.h"
#include "moteur.h"
#include <SDL/SDL_ttf.h>

class Jeu;
class Moteur;

class Menu
{
public:
    Menu(Moteur*);
    ~Menu();

    void affiche(SDL_Surface *);
    void gereTouche(int);

private:
    Moteur * parent;
    SDL_Surface *sdl_menu, *sdl_curseur;
    int positionCurseur;
    TTF_Font *police;
    SDL_Surface * sdl_reprendre, *sdl_recommencer,* sdl_quitter, *sdl_titre_menu;

};

#endif // MENU_H
