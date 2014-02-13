#include "jeu.h"

Jeu::Jeu(Moteur * m_parent)
{
    parent = m_parent;

    forme_actuel = new Piece();
    forme_suivante = new Piece();
    plateau = new Plateau();
    interface = new Interface(forme_suivante);

    tempsActuel = SDL_GetTicks();
    tempsSuivant = SDL_GetTicks();

    touche_actuel = 0;
    bonus_point = 0;

    player = new Player;

    player->nombreLigne = 0;
    player->level = 1;
    player->score = 0;

    start = false;

    interface->setPlayer(player);

    TTF_Init();
    if (TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    police = TTF_OpenFont("police/arial.ttf", 26);
    SDL_Color couleurNoire = {0, 0, 0}, couleurBlanche = {255, 255, 255};
    sdl_start = TTF_RenderText_Shaded(police, "Appuyer sur \"s\" pour commencer.", couleurBlanche, couleurNoire);
}

Jeu::~Jeu()
{
    delete forme_actuel;
    delete forme_suivante;
    delete plateau;
    delete interface;
    delete player;
    parent = NULL;
    SDL_FreeSurface(sdl_start);
    TTF_CloseFont(police);
    TTF_Quit();
}

bool Jeu::init()
{
    //std::cerr << "L'initialisation du module de jeu a échoué." << std::endl;
    return true;
}

void Jeu::affiche(SDL_Surface * screen)
{
    plateau->affiche(screen);
    forme_actuel->affiche(screen);
    interface->affiche(screen);

    if (!start)
    {
        SDL_Rect position;
        position.x = LARGEUR_FENETRE/2 - sdl_start->w/2;
        position.y = screen->h/2 - sdl_start->h/2;
        SDL_BlitSurface(sdl_start, NULL, screen, &position);
    }

}

void Jeu::gereScene()
{
    if (start)
    {
        forme_actuel->descendre();
        if (forme_actuel->collision(plateau))
            forme_actuel->descendre(true);
        else
            tempsSuivant = tempsActuel + 200;


        if ((tempsSuivant - tempsActuel) <= 0)
        {
            if (player->score < 999999)
                player->score += compteCellScoring()*2*player->level;

            for (int i = 0;i<4;i++)
                plateau->addCube(forme_actuel->getCube(i));
            delete forme_actuel;
            forme_actuel = new Piece(*forme_suivante);
            forme_actuel->definirForme();
            delete forme_suivante;
            forme_suivante = new Piece();
            interface->update_piece(forme_suivante);

            int lignecomplete = plateau->ligneComplete();

            if (player->nombreLigne < 999)
                player->nombreLigne += lignecomplete;
            int bonusLigne = 0;
            if (lignecomplete == 1)
                bonusLigne = 40;
            else if (lignecomplete == 2)
                bonusLigne = 100;
            else if (lignecomplete == 3)
                bonusLigne = 300;
            else if (lignecomplete == 4)
                bonusLigne = 1200;
            else;


            player->score += bonusLigne*player->level;
        }

        if (plateau->game_over())
            parent->openGameOver();
        tempsActuel = SDL_GetTicks();

        int lvl = std::max(player->level,((player->nombreLigne-(2*player->level))/10)+1);

        if (lvl >= 20)
            lvl = 20;

        player->level = lvl;
    }
}

void Jeu::gereTouche(int touche)
{
    if (start)
    {
        if (touche == SDLK_LEFT)
        {
            forme_actuel->deplacer_gauche();
            if (forme_actuel->collision(plateau))
                forme_actuel->deplacer_droite();
            else
                tempsSuivant += 50;
        }
        else if (touche == SDLK_RIGHT)
        {
            forme_actuel->deplacer_droite();
            if (forme_actuel->collision(plateau))
                forme_actuel->deplacer_gauche();
            else
                tempsSuivant += 50;
        }
        else if (touche == SDLK_UP)
        {
            forme_actuel->rotation();

            if (forme_actuel->collision(plateau))
            {
                forme_actuel->rotation();
                forme_actuel->rotation();
                forme_actuel->rotation();

                collision_rot_gauche();
                collision_rot_droite();
            }
            else
                tempsSuivant += 50;
        }
        else if (touche == SDLK_SPACE)
            hardDrop();
        else if (touche == SDLK_p)
            parent->openMenu();
        else;
    }
    else
    {
        if (touche == SDLK_s)
            start = true;
    }

    touche_actuel = touche;
}

void Jeu::collision_rot_gauche()
{
    forme_actuel->deplacer_gauche();
    if (forme_actuel->collision(plateau))
        forme_actuel->deplacer_droite();
    else
    {
        forme_actuel->rotation();
        if (forme_actuel->collision(plateau))
        {
            forme_actuel->rotation();
            forme_actuel->rotation();
            forme_actuel->rotation();
            collision_rot_gauche();
        }
    }
}

void Jeu::collision_rot_droite()
{
    forme_actuel->deplacer_droite();
    if (forme_actuel->collision(plateau))
        forme_actuel->deplacer_gauche();
    else
    {
        forme_actuel->rotation();
        if (forme_actuel->collision(plateau))
        {
            forme_actuel->rotation();
            forme_actuel->rotation();
            forme_actuel->rotation();

            collision_rot_droite();
        }
    }
}

int Jeu::compteCellScoring()
{
    int scoring = 0;

    forme_actuel->deplacer_droite();
    scoring += forme_actuel->collision(plateau);
    forme_actuel->deplacer_gauche();

    forme_actuel->deplacer_gauche();
    scoring += forme_actuel->collision(plateau);
    forme_actuel->deplacer_droite();

    forme_actuel->descendre();
    scoring += forme_actuel->collision(plateau);
    forme_actuel->descendre(true);

    return scoring;

}

void Jeu::hardDrop()
{
    do
        forme_actuel->descendre();
    while (!forme_actuel->collision(plateau));
    forme_actuel->descendre(true);
    tempsSuivant = tempsActuel+50;
}
