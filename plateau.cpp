#include "plateau.h"

Plateau::Plateau()
{
}

Plateau::~Plateau()
{
    std::vector < Cube* >::iterator i_plat;
    for (i_plat = plateau.begin();i_plat != plateau.end();i_plat++)
    {
        delete (*i_plat);
    }
}

void Plateau::affiche(SDL_Surface * screen)
{
    std::vector < Cube* >::iterator i_plat;

    for (i_plat = plateau.begin();i_plat != plateau.end();i_plat++)
    {
        (*i_plat)->affiche(screen);
    }
}

void Plateau::addCube(const Cube* new_cube)
{
    plateau.push_back(new Cube(*new_cube));
}

bool Plateau::collision(Cube* cube_col)
{
    std::vector < Cube* >::iterator i_plat;
    for (i_plat = plateau.begin();i_plat != plateau.end();i_plat++)
    {
        if (cube_col->getCoord().y == (*i_plat)->getCoord().y && cube_col->getCoord().x == (*i_plat)->getCoord().x)
            return true;
    }

    return false;
}

int Plateau::ligneComplete()
{
    std::vector < Cube* >::iterator i_plat;

    int check = 0;
    int nb_ligne = 0;

    for (int i=0;i<NB_BLOCS_HAUTEUR;i++)
    {
        check = 0;
        for (i_plat = plateau.begin();i_plat != plateau.end();i_plat++)
        {
            if (((*i_plat)->getCoord().y/TAILLE_BLOC) == i)
                check++;
        }
        if (check == NB_BLOCS_LARGEUR)
        {
            videLigne(i);
            nb_ligne++;
        }
    }
    return nb_ligne;
}

void Plateau::videLigne(int ligneAEffacer)
{
    std::vector < Cube* >::iterator i_plat;

    while (itr.hasNext()) {
      Cube c = itr.next();
    }

    for (i_plat = plateau.begin();i_plat != plateau.end();)
    {
        if (((*i_plat)->getCoord().y/TAILLE_BLOC) == ligneAEffacer)
        {
            delete *i_plat;
            plateau.erase(i_plat);
        }
        else
            i_plat++;
    }
    replaceLigne(ligneAEffacer);
}

void Plateau::replaceLigne(int ligneEffacer)
{
    std::vector < Cube* >::iterator i_plat;

    for (i_plat = plateau.begin();i_plat != plateau.end();i_plat++)
    {
        if (((*i_plat)->getCoord().y/TAILLE_BLOC) < ligneEffacer)
        {
            (*i_plat)->setCoord(((*i_plat)->getCoord().y/TAILLE_BLOC)+1,(*i_plat)->getCoord().x/TAILLE_BLOC);
        }
    }
}

bool Plateau::game_over()
{
    std::vector < Cube* >::iterator i_plat;

    for (i_plat = plateau.begin();i_plat != plateau.end();i_plat++)
    {
        if (((*i_plat)->getCoord().y/TAILLE_BLOC) == 0)
        {
            return true;
        }
    }
    return false;
}
