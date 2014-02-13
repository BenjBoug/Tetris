#include <SDL/SDL_framerate.h>
#include "constantes.h"
#include "moteur.h"

int main ( int argc, char** argv )
{
    //initialisation de la SDL
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        std::cerr << "Unable to init SDL:" << SDL_GetError() << std::endl;
        return 1;
    }

    //Moteur du jeu
    Moteur moteur;
    if (!moteur.init())
    {
        std::cerr << "L'initialisation du moteur a échoué.";
        return 1;
    }

    //declaration variables
    bool avancement = false;
    int tempsPrecedent = 0, tempsActuel = 0;
    SDL_Surface* screen = SDL_SetVideoMode(LARGEUR_FENETRE+150, HAUTEUR_FENETRE, 16,SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Tetris", NULL);
    FPSmanager manager;
    SDL_initFramerate(&manager);
    SDL_setFramerate(&manager,30);
    SDL_Event event;
    SDL_EnableKeyRepeat(10, 50);


    //boucle principale tant que le jeu n'est pas fini
    while (!moteur.getQuitter())
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                moteur.setQuitter(true);
                break;

            case SDL_KEYUP:
            {
                moteur.gereTouche(0);
                break;
            }

            case SDL_KEYDOWN:
            {
                if (event.key.keysym.sym == SDLK_DOWN)
                    avancement = true;

                //envoi la touche pressée à Moteur
                moteur.gereTouche(event.key.keysym.sym);
                break;
            }
            }
        }

        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent > 600/moteur.getLvl())
        {
            avancement = true;
            tempsPrecedent = tempsActuel;
        }

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        if (avancement)
        {
            moteur.gereScene();
            avancement = false;
        }
        //affiche
        moteur.affiche(screen);
        SDL_Flip(screen);
        SDL_framerateDelay(&manager);
    }
    return 0;
}

