#ifndef MOTEUR_H
#define MOTEUR_H

#include "constantes.h"
#include "jeu.h"
#include "gameover.h"
#include "menu.h"

class Jeu;
class Menu;
class GameOver;

enum STATE
{
    IN_GAME, IN_MENU, IN_GAMEOVER
};


class Moteur
{
public:
    Moteur();
    ~Moteur();
    //initialisation du moteur
    bool init();
    // gère la scène
    void gereScene();
    // gere les touches préssés
    void gereTouche(int);
    //gère l'affichage
    void affiche(SDL_Surface *);


    //ouvre le menu Game Over
    void openGameOver();
    // ouvre le menu
    void openMenu();
    // quitte le menu
    void quitMenu();
    // recommence une partie
    void restartJeu();

    // ACESSEURS

    int getLvl();

    inline bool getQuitter()
    {
        return quitter;
    }
    inline void setQuitter(bool q)
    {
        quitter = q;
    }

private:
    Jeu *jeu;
    GameOver * game_over;
    Menu * menu;
    bool quitter;
    STATE state;
};

#endif // MOTEUR_H
