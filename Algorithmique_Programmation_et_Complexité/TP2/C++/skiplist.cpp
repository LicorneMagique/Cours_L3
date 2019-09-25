#include <cstdio>
#include "skiplist.h"

Skiplist::Skiplist()
{
    ad = new Cellule;
}

/*Skiplist::Skiplist(const Skiplist &l)
{
    ad = new Cellule;
    Cellule *tempCel = l.ad;

    while (tempCel != NULL)
    {
        this->ajoutEnQueue(tempCel->info);
        tempCel = tempCel->suivant;
    }
}*/

Skiplist::~Skiplist()
{
    //this->vide();
}

void Skiplist::affichage() const
{
    Cellule *tempCel = ad;

    printf("Affichage liste :\n");
    while (tempCel->suivant.size() > 0)
    {
        std::printf("%d\n", tempCel->info);
        tempCel = tempCel->suivant[0];
    }
}

void Skiplist::ajout(const Elem &e)
{
    Cellule *tempCel = ad;

    int maxIndex = tempCel->suivant.size() - 1;

    // On va au bon endroit dans la liste
    while (tempCel->suivant.size() > 0) // Tant qu'il y a des éléments à parcourir
    {
        if (maxIndex > 1 && tempCel->suivant[maxIndex]->info >= e)
            maxIndex--;

        if (maxIndex <= 1 && tempCel->suivant[maxIndex]->info >= e)
            break;

        if (tempCel->suivant[maxIndex]->info < e)
            tempCel = tempCel->suivant[maxIndex];
    }

    // On insert la cellule
    if (tempCel->suivant.size() < 1) // Si on est au bout de la liste
    {
        tempCel->suivant.push_back(new Cellule);
        tempCel->info = e;
    }
    else
    {
        Cellule *tmp = tempCel->suivant[0];
        tempCel->suivant[0] = new Cellule;
        tempCel->suivant[0]->info = e;
        tempCel->suivant[0]->suivant.push_back(tmp);
    }
}

bool Skiplist::testSkiplistVide() const
{
    return ad->suivant.size() == 0;
}

/*void Skiplist::vide()
{
    Cellule *tempCel = this->ad;
    while (tempCel != NULL)
    {
        Cellule *toFree = tempCel;
        tempCel = tempCel->suivant;
        delete toFree;
    }
    this->ad = nullptr;
}*/

/*Skiplist &Skiplist::operator=(const Skiplist &l)
{
    if (this == &l)
        return *this;

    ad = nullptr;
    Cellule *tempCel = l.ad;

    while (tempCel != NULL)
    {
        this->ajoutEnQueue(tempCel->info);
        tempCel = tempCel->suivant;
    }

    return *this;
}*/
