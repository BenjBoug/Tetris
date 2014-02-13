#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "constantes.h"
#include "moteur.h"
#include <SDL/SDL_ttf.h>

class Moteur;

class GameOver
{
    public:
        GameOver(Moteur *);
        ~GameOver();

        void affiche(SDL_Surface*);
        void gereTouche(int);

    private:
    int positionCurseur;
    Moteur * parent;
    TTF_Font *police;
    SDL_Surface *sdl_game_o, *sdl_menu, *sdl_curseur;
    SDL_Surface *sdl_quitter, *sdl_restart;
};

#endif // GAMEOVER_H
