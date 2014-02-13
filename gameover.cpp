#include "gameover.h"

GameOver::GameOver(Moteur * _p)
{
    TTF_Init();
    if (TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    police = TTF_OpenFont("police/arial.ttf", 24);
    SDL_Color couleurNoire = {0, 0, 0}, couleurBlanche = {255, 255, 255}, couleurGrise = {120, 120, 120};

    sdl_game_o = TTF_RenderText_Shaded(police, "Game Over", couleurGrise, couleurNoire);
    sdl_quitter = TTF_RenderText_Shaded(police, "Quitter", couleurBlanche, couleurNoire);
    sdl_restart = TTF_RenderText_Shaded(police, "Recommencer", couleurBlanche, couleurNoire);
    sdl_menu =  SDL_LoadBMP("images/menu.bmp");
    sdl_curseur =  SDL_LoadBMP("images/curseur_menu.bmp");

    positionCurseur = 0;

    parent = _p;
}

GameOver::~GameOver()
{
    parent = NULL;
    SDL_FreeSurface(sdl_restart);
    SDL_FreeSurface(sdl_quitter);
    SDL_FreeSurface(sdl_menu);
    SDL_FreeSurface(sdl_game_o);
    SDL_FreeSurface(sdl_curseur);
    TTF_CloseFont(police);
    TTF_Quit();
}

void GameOver::affiche(SDL_Surface * screen)
{
    SDL_Rect position, positionRel;
    positionRel.w=20;
    positionRel.h=15;
    position.y = screen->h/2 - sdl_menu->h/2;
    position.x = LARGEUR_FENETRE/2-(sdl_menu->w/2);
    SDL_BlitSurface(sdl_menu, NULL, screen, &position);

    position.y += 20;
    position.x += 30;
    SDL_BlitSurface(sdl_game_o, NULL, screen, &position);

    position.y +=60;
    position.x = LARGEUR_FENETRE/2-(sdl_restart->w/2);
    SDL_BlitSurface(sdl_restart, NULL, screen, &position);
    SDL_SetClipRect(sdl_restart,&position);

    position.y +=30;
    position.x = LARGEUR_FENETRE/2-(sdl_quitter->w/2);
    SDL_BlitSurface(sdl_quitter, NULL, screen, &position);
    SDL_SetClipRect(sdl_quitter,&position);

    position.y = screen->h/2 - sdl_menu->h/2;
    if (positionCurseur == 0)
    {
        position.y = sdl_restart->clip_rect.y+(sdl_curseur->h/2);
        position.x = LARGEUR_FENETRE/2-(sdl_restart->w/2)-(sdl_curseur->w/2);
    }
    else if (positionCurseur == 1)
    {
        position.y = sdl_quitter->clip_rect.y+(sdl_curseur->h/2);
        position.x = LARGEUR_FENETRE/2-(sdl_quitter->w/2)-(sdl_curseur->w/2);
    }

    positionRel.x=0;
    positionRel.y=0;
    SDL_BlitSurface(sdl_curseur, &positionRel, screen, &position);

    if (positionCurseur == 0)
    {
        position.x += sdl_restart->w+sdl_curseur->w/2;
    }
    else if (positionCurseur == 1)
    {
        position.x += sdl_quitter->w+sdl_curseur->w/2;
    }

    positionRel.x=20;
    SDL_BlitSurface(sdl_curseur, &positionRel, screen, &position);


}

void GameOver::gereTouche(int touche)
{

    if (touche == SDLK_DOWN)
    {
        if (positionCurseur == 1)
            positionCurseur = 0;
        else
            positionCurseur++;
    }
    else if (touche == SDLK_UP)
    {
        if (positionCurseur == 0)
            positionCurseur = 1;
        else
            positionCurseur--;
    }
    else if (touche == SDLK_SPACE || touche == SDLK_RETURN)
    {
        if (positionCurseur == 0)
            parent->restartJeu();
        else if (positionCurseur == 1)
            parent->setQuitter(true);
        else;
    }

}
