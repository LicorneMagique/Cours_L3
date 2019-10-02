#include <cstdio>
#include <cstdlib>
#include "skiplist.h"

Skiplist::Skiplist()
{
    ad = new Cellule;
}

/*Skiplist::Skiplist(const Skiplist &l)
{
    ad = new Cellule;
    Cellule *curseur = l.ad;

    while (curseur != NULL)
    {
        this->ajoutEnQueue(curseur->info);
        curseur = curseur->suivant;
    }
}*/

Skiplist::~Skiplist()
{
    //this->vide();
}

void Skiplist::affichage() const
{
    Cellule *curseur = ad;

    while (curseur->suivant.size() > 0)
    {
        printf("Valeur : %d, taille : %d", curseur->info, (int)curseur->suivant.size());
        for (int i = 0; i < curseur->suivant.size() - 1; i++);
            printf("%d ", curseur->suivant[0]->info);
        printf("\n");
        curseur = curseur->suivant[0];
    }
}

void Skiplist::ajout(const Elem &e)
{
    Cellule *curseur = ad;
    int niveauCurseur = curseur->suivant.size() - 1;

    //std::vector<Cellule *> precedents;
    //for (int i = 0; i < niveauCurseur + 1; i++)
    //    precedents.push_back(nullptr);

    // On va au bon endroit dans la liste
    while (curseur->suivant.size() > 0 && niveauCurseur > 0) // Tant qu'il y a des éléments à parcourir
    {
        if (curseur->suivant[niveauCurseur] != nullptr)
            if (curseur->suivant[niveauCurseur]->info < e)
                curseur = curseur->suivant[niveauCurseur];
            else
                niveauCurseur--;
        else
            niveauCurseur--;
    }

    // On insert la cellule
    if (curseur->suivant.size() < 1) // Si on est au bout de la liste
    {
        // Cas liste vide
        if (curseur == ad)
        {
            curseur->suivant.push_back(new Cellule);
            curseur = curseur->suivant[0];
        }
        curseur->suivant.push_back(new Cellule);
        curseur->suivant[0]->info = e;
    }
    else
    {
        Cellule *tmp = curseur->suivant[0];
        curseur->suivant[0] = new Cellule;
        curseur->suivant[0]->info = e;
        curseur->suivant[0]->suivant.push_back(tmp);
        curseur = curseur->suivant[0];
    }

    // Ajout des niveaux
    while ((rand()%2))
    {
        printf("test %d, ", curseur->info);
        curseur->suivant.push_back(nullptr);
    }
    printf("\n");

}

bool Skiplist::testSkiplistVide() const
{
    return ad->suivant.size() == 0;
}

/*void Skiplist::vide()
{
    Cellule *curseur = this->ad;
    while (curseur != NULL)
    {
        Cellule *toFree = curseur;
        curseur = curseur->suivant;
        delete toFree;
    }
    this->ad = nullptr;
}*/

/*Skiplist &Skiplist::operator=(const Skiplist &l)
{
    if (this == &l)
        return *this;

    ad = nullptr;
    Cellule *curseur = l.ad;

    while (curseur != NULL)
    {
        this->ajoutEnQueue(curseur->info);
        curseur = curseur->suivant;
    }

    return *this;
}*/
