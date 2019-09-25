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

    // On part du pointeur de suivant le plus haut
    // Tant que son suivant n'est pas nul, est supérieur à 1 et est inférieur au nombre
        // Alors on va au suivant
    // Quand on ne peut plus on diminue d'un cran le pointeur de suivant
    
    int maxIndex = tempCel->suivant.size();
    
    while (tempCel->suivant.size() > 0 && tempCel->suivant[maxIndex].size())
    {
        tempCel = tempCel->suivant[0];
    }
    tempCel->suivant.push_back(new Cellule);
    tempCel->info = e;


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
