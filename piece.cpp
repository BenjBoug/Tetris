#include "piece.h"

std::vector<int> Piece::anti_doublons;

Piece::Piece()
{
    srand(time(NULL));
    forme_piece = choixPieceAleatoire(0, 6);

    anti_doublons.push_back(forme_piece);

    if (anti_doublons.size() > 4)
    {
        anti_doublons.erase(anti_doublons.begin());
    }

    for (int i=0;i<4;i++)
        cube.push_back(new Cube(forme_piece));
    definirForme();
}

Piece::Piece(const Piece & pieceACopier)
{
    forme_piece = pieceACopier.forme_piece;
    for (int i=0;i<4;i++)
        cube.push_back(new Cube(*(pieceACopier.cube[i])));
}

Piece::~Piece()
{
    std::vector < Cube* >::iterator i_cub;
    for (i_cub = cube.begin();i_cub != cube.end();i_cub++)
    {
        delete *i_cub;
    }
}

void Piece::affiche(SDL_Surface * screen)
{
    std::vector < Cube* >::iterator i_cub;
    for (i_cub = cube.begin();i_cub != cube.end();i_cub++)
        (*i_cub)->affiche(screen);
}

int Piece::choixPieceAleatoire(int min, int max)
{
    int nbr_alea = (int) (min + ((float) rand() / RAND_MAX * (max - min + 1)));

    std::vector <int>::iterator i_int;
    for (i_int = anti_doublons.begin();i_int != anti_doublons.end();i_int++)
    {
        if (*i_int == nbr_alea)
            return choixPieceAleatoire(min,max);
    }

    return nbr_alea;
}

void Piece::definirForme()
{
    if (forme_piece == L)
    {
        cube[0]->setCoord(0,NB_BLOCS_LARGEUR/2);
        cube[1]->setCoord(1,NB_BLOCS_LARGEUR/2);
        cube[2]->setCoord(2,NB_BLOCS_LARGEUR/2);
        cube[3]->setCoord(2,(NB_BLOCS_LARGEUR/2)+1);
    }
    else if (forme_piece == I)
    {
        cube[0]->setCoord(0,NB_BLOCS_LARGEUR/2);
        cube[1]->setCoord(1,NB_BLOCS_LARGEUR/2);
        cube[2]->setCoord(2,NB_BLOCS_LARGEUR/2);
        cube[3]->setCoord(3,NB_BLOCS_LARGEUR/2);
    }
    else if (forme_piece == O)
    {
        cube[0]->setCoord(0,NB_BLOCS_LARGEUR/2);
        cube[1]->setCoord(1,NB_BLOCS_LARGEUR/2);
        cube[2]->setCoord(0,(NB_BLOCS_LARGEUR/2)+1);
        cube[3]->setCoord(1,(NB_BLOCS_LARGEUR/2)+1);
    }
    else if (forme_piece == T)
    {
        cube[0]->setCoord(0,(NB_BLOCS_LARGEUR/2)-1);
        cube[1]->setCoord(0,NB_BLOCS_LARGEUR/2);
        cube[2]->setCoord(0,(NB_BLOCS_LARGEUR/2)+1);
        cube[3]->setCoord(1,NB_BLOCS_LARGEUR/2);
    }
    else if (forme_piece == J)
    {
        cube[0]->setCoord(0,NB_BLOCS_LARGEUR/2);
        cube[1]->setCoord(1,NB_BLOCS_LARGEUR/2);
        cube[2]->setCoord(2,NB_BLOCS_LARGEUR/2);
        cube[3]->setCoord(2,(NB_BLOCS_LARGEUR/2)-1);
    }
    else if (forme_piece == Z)
    {
        cube[0]->setCoord(0,(NB_BLOCS_LARGEUR/2)-1);
        cube[1]->setCoord(0,NB_BLOCS_LARGEUR/2);
        cube[2]->setCoord(1,NB_BLOCS_LARGEUR/2);
        cube[3]->setCoord(1,(NB_BLOCS_LARGEUR/2)+1);
    }
    else if (forme_piece == S)
    {
        cube[0]->setCoord(0,(NB_BLOCS_LARGEUR/2)+1);
        cube[1]->setCoord(0,NB_BLOCS_LARGEUR/2);
        cube[2]->setCoord(1,NB_BLOCS_LARGEUR/2);
        cube[3]->setCoord(1,(NB_BLOCS_LARGEUR/2)-1);
    }
}

void Piece::descendre( bool annul)
{
    std::vector < Cube* >::iterator i_cub;
    for (i_cub = cube.begin();i_cub != cube.end();i_cub++)
    {
        if (annul)
            (*i_cub)->setCoord(((*i_cub)->getCoord().y/TAILLE_BLOC)-1, (*i_cub)->getCoord().x/TAILLE_BLOC);
        else
            (*i_cub)->setCoord(((*i_cub)->getCoord().y/TAILLE_BLOC)+1, (*i_cub)->getCoord().x/TAILLE_BLOC);
    }
}

void Piece::deplacer_gauche()
{
    std::vector < Cube* >::iterator i_cub;
    for (i_cub = cube.begin();i_cub != cube.end();i_cub++)
    {
        (*i_cub)->setCoord((*i_cub)->getCoord().y/TAILLE_BLOC, ((*i_cub)->getCoord().x/TAILLE_BLOC)-1);
    }
}

void Piece::deplacer_droite()
{
    std::vector < Cube* >::iterator i_cub;
    for (i_cub = cube.begin();i_cub != cube.end();i_cub++)
    {
        (*i_cub)->setCoord((*i_cub)->getCoord().y/TAILLE_BLOC, ((*i_cub)->getCoord().x/TAILLE_BLOC)+1);
    }
}

int Piece::collision(Plateau * plateau)
{
    int nb_col = 0;
    std::vector < Cube* >::iterator i_cub;
    for (i_cub = cube.begin();i_cub != cube.end();i_cub++)
    {
        if (((*i_cub)->getCoord().y/TAILLE_BLOC) >= NB_BLOCS_HAUTEUR)
            return 1;
        else if (((*i_cub)->getCoord().x/TAILLE_BLOC) >= NB_BLOCS_LARGEUR)
            return 1;
        else if (((*i_cub)->getCoord().x/TAILLE_BLOC) < 0)
            return 1;
        else if (plateau->collision((*i_cub)))
            nb_col++;
    }
    return nb_col;
}

void Piece::rotation()
{
    std::vector < Cube* >::iterator i_cub;
    if (forme_piece != O)
        for (i_cub = cube.begin();i_cub != cube.end();i_cub++)
        {
            if (((*i_cub)->getCoord().x - cube[1]->getCoord().x) == -TAILLE_BLOC && ((*i_cub)->getCoord().y - cube[1]->getCoord().y) == 0)
                (*i_cub)->setCoord((cube[1]->getCoord().y/TAILLE_BLOC)-1, cube[1]->getCoord().x/TAILLE_BLOC);
            else if (((*i_cub)->getCoord().x - cube[1]->getCoord().x) == TAILLE_BLOC && ((*i_cub)->getCoord().y - cube[1]->getCoord().y) == 0)
                (*i_cub)->setCoord((cube[1]->getCoord().y/TAILLE_BLOC)+1, cube[1]->getCoord().x/TAILLE_BLOC);
            else if (((*i_cub)->getCoord().y - cube[1]->getCoord().y) == -TAILLE_BLOC && ((*i_cub)->getCoord().x - cube[1]->getCoord().x) == 0)
                (*i_cub)->setCoord((cube[1]->getCoord().y/TAILLE_BLOC), (cube[1]->getCoord().x/TAILLE_BLOC)+1);
            else if (((*i_cub)->getCoord().y - cube[1]->getCoord().y) == TAILLE_BLOC && ((*i_cub)->getCoord().x - cube[1]->getCoord().x) == 0)
                (*i_cub)->setCoord((cube[1]->getCoord().y/TAILLE_BLOC), (cube[1]->getCoord().x/TAILLE_BLOC)-1);
            else if (((*i_cub)->getCoord().y - cube[1]->getCoord().y) == 0 && ((*i_cub)->getCoord().x - cube[1]->getCoord().x) == 0)
                (*i_cub)->setCoord((cube[1]->getCoord().y/TAILLE_BLOC), cube[1]->getCoord().x/TAILLE_BLOC);

            if (((*i_cub)->getCoord().x - cube[1]->getCoord().x) == -TAILLE_BLOC && ((*i_cub)->getCoord().y - cube[1]->getCoord().y) == -TAILLE_BLOC)
                (*i_cub)->setCoord((*i_cub)->getCoord().y/TAILLE_BLOC, ((*i_cub)->getCoord().x/TAILLE_BLOC)+2);
            else if (((*i_cub)->getCoord().x - cube[1]->getCoord().x) == TAILLE_BLOC && ((*i_cub)->getCoord().y - cube[1]->getCoord().y) == -TAILLE_BLOC)
                (*i_cub)->setCoord(((*i_cub)->getCoord().y/TAILLE_BLOC)+2, (*i_cub)->getCoord().x/TAILLE_BLOC);
            else if (((*i_cub)->getCoord().y - cube[1]->getCoord().y) == TAILLE_BLOC && ((*i_cub)->getCoord().x - cube[1]->getCoord().x) == -TAILLE_BLOC)
                (*i_cub)->setCoord(((*i_cub)->getCoord().y/TAILLE_BLOC)-2, (*i_cub)->getCoord().x/TAILLE_BLOC);
            else if (((*i_cub)->getCoord().y - cube[1]->getCoord().y) == TAILLE_BLOC && ((*i_cub)->getCoord().x - cube[1]->getCoord().x) == TAILLE_BLOC)
                (*i_cub)->setCoord((*i_cub)->getCoord().y/TAILLE_BLOC, ((*i_cub)->getCoord().x/TAILLE_BLOC)-2);
            else if (((*i_cub)->getCoord().y - cube[1]->getCoord().y) == 0 && ((*i_cub)->getCoord().x - cube[1]->getCoord().x) == 0)
                (*i_cub)->setCoord((cube[1]->getCoord().y/TAILLE_BLOC), cube[1]->getCoord().x/TAILLE_BLOC);

            if (((*i_cub)->getCoord().x - cube[1]->getCoord().x) == -(2*TAILLE_BLOC) && ((*i_cub)->getCoord().y - cube[1]->getCoord().y) == 0)
                (*i_cub)->setCoord((cube[1]->getCoord().y/TAILLE_BLOC)-2, cube[1]->getCoord().x/TAILLE_BLOC);
            else if (((*i_cub)->getCoord().x - cube[1]->getCoord().x) == (2*TAILLE_BLOC) && ((*i_cub)->getCoord().y - cube[1]->getCoord().y) == 0)
                (*i_cub)->setCoord((cube[1]->getCoord().y/TAILLE_BLOC)+2, cube[1]->getCoord().x/TAILLE_BLOC);
            else if (((*i_cub)->getCoord().y - cube[1]->getCoord().y) == -(2*TAILLE_BLOC) && ((*i_cub)->getCoord().x - cube[1]->getCoord().x) == 0)
                (*i_cub)->setCoord((cube[1]->getCoord().y/TAILLE_BLOC), (cube[1]->getCoord().x/TAILLE_BLOC)+2);
            else if (((*i_cub)->getCoord().y - cube[1]->getCoord().y) == (2*TAILLE_BLOC) && ((*i_cub)->getCoord().x - cube[1]->getCoord().x) == 0)
                (*i_cub)->setCoord((cube[1]->getCoord().y/TAILLE_BLOC), (cube[1]->getCoord().x/TAILLE_BLOC)-2);
            else if (((*i_cub)->getCoord().y - cube[1]->getCoord().y) == 0 && ((*i_cub)->getCoord().x - cube[1]->getCoord().x) == 0)
                (*i_cub)->setCoord((cube[1]->getCoord().y/TAILLE_BLOC), cube[1]->getCoord().x/TAILLE_BLOC);
        }
}

void Piece::setPosition(int _y,int _x)
{
    std::vector < Cube* >::iterator i_cub;
    for (i_cub = cube.begin();i_cub != cube.end();i_cub++)
        (*i_cub)->setCoord(((*i_cub)->getCoord().y/TAILLE_BLOC)+_y,((*i_cub)->getCoord().x/TAILLE_BLOC)+_x);
}
