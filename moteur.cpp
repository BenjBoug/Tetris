#include "moteur.h"

Moteur::Moteur()
{
    jeu = new Jeu(this);
    quitter = false;
    state = IN_GAME;
    game_over = NULL;
    menu = NULL;
}

Moteur::~Moteur()
{
    if (game_over != NULL)
        delete game_over;
    if (menu != NULL)
        delete menu;
    delete jeu;
}

bool Moteur::init()
{
    if (!jeu->init())
        return false;

    return true;
}

void Moteur::affiche(SDL_Surface * screen)
{
    jeu->affiche(screen);

    if (state == IN_MENU)
        menu->affiche(screen);
    else if (state == IN_GAMEOVER)
        game_over->affiche(screen);
    else;
}

void Moteur::gereScene()
{
    if (state == IN_GAME)
        jeu->gereScene();
    else;
}

void Moteur::gereTouche(int touche)
{
    if (state == IN_GAME)
        jeu->gereTouche(touche);
    else if (state == IN_MENU)
        menu->gereTouche(touche);
    else if (state == IN_GAMEOVER)
        game_over->gereTouche(touche);
    else;
}

int Moteur::getLvl()
{
    return jeu->getLvl();
}

void Moteur::openGameOver()
{
    state = IN_GAMEOVER;
    game_over = new GameOver(this);
}

void Moteur::openMenu()
{
    state = IN_MENU;
    menu = new Menu(this);
}

void Moteur::quitMenu()
{
    state = IN_GAME;
    if (menu != NULL)
    {
        delete menu;
        menu = NULL;
    }
}

void Moteur::restartJeu()
{
    if (game_over != NULL)
    {
        delete game_over;
        game_over = NULL;
    }
    if (menu != NULL)
    {
        delete menu;
        menu = NULL;
    }

    delete jeu;
    jeu = new Jeu(this);
    state = IN_GAME;
}
