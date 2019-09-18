#include <cstdio>
#include "liste.h"

Liste::Liste()
{
    ad = nullptr;
}

Liste::Liste(const Liste &l)
{
    ad = nullptr;
    Cellule *tempCel = l.ad;

    while (tempCel != NULL)
    {
        this->ajoutEnQueue(tempCel->info);
        tempCel = tempCel->suivant;
    }
}

Liste::~Liste()
{
    this->vide();
    //delete this;
}

void Liste::affichage() const
{
    Cellule *tempCel = ad;

    printf("Affichage liste :\n");
    while (tempCel != NULL)
    {
        std::printf("%d\n", tempCel->info);
        tempCel = tempCel->suivant;
    }
}

void Liste::ajoutEnTete(const Elem &e)
{
    Cellule *newCel = new Cellule();
    newCel->info = e;
    newCel->suivant = ad;
    ad = newCel;
}

void Liste::ajoutEnQueue(const Elem &e)
{
    if (this->testListeVide())
        ajoutEnTete(e);
    else
    {
        Cellule *tempCel = ad;
        while (tempCel->suivant != NULL)
        {
            tempCel = tempCel->suivant;
        }
        tempCel->suivant = new Cellule();
        tempCel->suivant->info = e;
        tempCel->suivant->suivant = NULL;
    }
}

bool Liste::testListeVide() const
{
    return ad == nullptr;
}

void Liste::vide()
{
    Cellule *tempCel = this->ad;
    this->ad = nullptr;
    while (tempCel != NULL)
    {
        Cellule *toFree = tempCel;
        tempCel = tempCel->suivant;
        delete toFree;
    }
}

Liste &Liste::operator=(const Liste &l)
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
}
