#ifndef INTERFACE_H
#define INTERFACE_H

#include "constantes.h"
#include "piece.h"
#include <SDL/SDL_ttf.h>
#include <sstream>

class Interface
{
public:
    Interface(Piece*);
    ~Interface();

    void update_piece(Piece*);
    // actualisa les données du joueur
    void setPlayer(Player* _p) {player = _p;}
    // affiche l'interface
    void affiche(SDL_Surface *);

    void gereCalcul();

private:
    Piece * piece_suivante;
    SDL_Surface * sdl_interface;
    SDL_Surface * sdl_ligne, * sdl_lvl, *sdl_score;
    Player * player;
    TTF_Font *police;
};

#endif
