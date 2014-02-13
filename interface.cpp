#include "interface.h"

Interface::Interface(Piece * piece_suivante_ctor)
{
    piece_suivante = piece_suivante_ctor;
    piece_suivante->setPosition(2,11);
    sdl_interface =  SDL_LoadBMP("images/interface.bmp");

    TTF_Init();
    if (TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    police = TTF_OpenFont("police/arial.ttf", 34);
}

Interface::~Interface()
{
    piece_suivante = NULL;
    SDL_FreeSurface(sdl_interface);
    TTF_CloseFont(police);
    TTF_Quit();
}

void Interface::update_piece(Piece* piece_suivante_fct)
{
    piece_suivante = piece_suivante_fct;
    piece_suivante->setPosition(2,11);
}

void Interface::affiche(SDL_Surface *screen)
{
    gereCalcul();

    SDL_Rect position;

    position.y = 0;

    position.x = LARGEUR_FENETRE;
    SDL_BlitSurface(sdl_interface, NULL, screen, &position);

    position.y = 210;
    position.x = LARGEUR_FENETRE+(150/2)-(sdl_score->w/2);
    SDL_BlitSurface(sdl_score, NULL, screen, &position);

    position.y = 300;
    position.x = LARGEUR_FENETRE+(150/2)-(sdl_ligne->w/2);
    SDL_BlitSurface(sdl_ligne, NULL, screen, &position);

    position.y = 390;
    position.x = LARGEUR_FENETRE+(150/2)-(sdl_lvl->w/2);
    SDL_BlitSurface(sdl_lvl, NULL, screen, &position);

    piece_suivante->affiche(screen);

    SDL_FreeSurface(sdl_score);
    SDL_FreeSurface(sdl_ligne);
    SDL_FreeSurface(sdl_lvl);

}

void Interface::gereCalcul()
{
    SDL_Color couleurNoire = {255, 255, 255};

    std::string std_ligne;
    std::ostringstream oss_ligne;
    oss_ligne << player->nombreLigne;
    std_ligne = oss_ligne.str();
    sdl_ligne = TTF_RenderText_Blended(police, std_ligne.c_str(), couleurNoire);

    std::string std_lvl;
    std::ostringstream oss_lvl;
    oss_lvl << player->level;
    std_lvl = oss_lvl.str();
    sdl_lvl = TTF_RenderText_Blended(police, std_lvl.c_str(), couleurNoire);

    std::string std_score;
    std::ostringstream oss_score;
    oss_score << player->score;
    std_score = oss_score.str();
    sdl_score = TTF_RenderText_Blended(police, std_score.c_str(), couleurNoire);

}
