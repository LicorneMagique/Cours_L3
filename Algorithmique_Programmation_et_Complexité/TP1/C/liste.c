#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

void initialiseListeDefaut(Liste *l)
{
    l->ad = NULL;
    l->nb_elem = 0;
}

void initialiseListeCopie(Liste *l1, Liste l2)
{
    initialiseListeDefaut(l1);
    affectationListe(l1, l2);
}

void testamentListe(Liste *l)
{
    videListe(l);
    l = NULL;
}

void affectationListe(Liste *l1, Liste l2)
{
    Cellule *tempCel = l2.ad;
    while (tempCel != NULL)
    {
        ajoutEnQueueListe(tempCel->info, l1);
        tempCel = tempCel->suivant;
    }
}

int testListeVide(Liste l)
{
    return l.ad == NULL;
}

Elem premierElementListe(Liste l)
{
    return l.ad->info;
}

Cellule *premiereCelluleListe(Liste l)
{
    return l.ad;
}

Cellule *celluleSuivanteListe(const Cellule *c, Liste l)
{
    return c->suivant;
}

Elem elementCelluleListe(const Cellule *c)
{
    return c->info;
}

void affichageListe(Liste l)
{
    Cellule *tempCel = l.ad;

    printf("Affichage liste :\n");
    while (tempCel != NULL)
    {
        printf("%d\n", tempCel->info);
        tempCel = tempCel->suivant;
    }
}

void ajoutEnTeteListe(Elem e, Liste *l)
{
    Cellule *newCel = malloc(sizeof(Cellule));
    newCel->info = e;
    newCel->suivant = l->ad;
    l->ad = newCel;
    l->nb_elem++;
}

void suppressionEnTeteListe(Liste *l)
{
    Cellule *tempCel = l->ad->suivant;
    free(l->ad);
    l->ad = tempCel;
    l->nb_elem--;
}

void videListe(Liste *l)
{
    Cellule *tempCel = l->ad;
    while (tempCel != NULL)
    {
        Cellule *toFree = tempCel;
        tempCel = tempCel->suivant;
        free(toFree);
    }
    l->ad = NULL;
    l->nb_elem = 0;
}

void ajoutEnQueueListe(Elem e, Liste *l)
{
    if (testListeVide(*l) == 1)
        ajoutEnTeteListe(e, l);
    else
    {
        Cellule *tempCel = l->ad;
        while (tempCel->suivant != NULL)
        {
            tempCel = tempCel->suivant;
        }
        tempCel->suivant = malloc(sizeof(Cellule));
        tempCel->suivant->info = e;
        tempCel->suivant->suivant = NULL;
    }
}
