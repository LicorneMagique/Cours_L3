#include "element.h"
#include "skiplist.h"
#include <cstdio>

using namespace std;

int main()
{
    printf("Création d'une liste vide\n");
    Skiplist lili;

    printf("\nAffichage de la liste vide\n");
    lili.affichage();

    printf("\nRemplissage de Lili avec 1, 2, 3, 4\n");
    for (int i = 1; i < 5; i++)
        lili.ajout(i);

    printf("\nAffichage de Lili avec 1, 2, 3, 4\n");
    lili.affichage();

    /*printf("\nAjout de 10, 11, 12, 13, 14 sur Lili\n");
    for (int i = 10; i < 15; i++)
        lili.ajout(i);

    printf("\nAffichage de Lili avec 1, 2, 3, 4, 10, 11, 12, 13, 14\n");
    lili.affichage();

    printf("\nCréation de la liste Lolo par copie de Lili\n");
    Skiplist lolo(lili);

    printf("\nAffichage de Lolo\n");
    lolo.affichage();

    printf("\nOn vide Lili\n");
    lili.vide();

    printf("\nAffichage de Lili vide\n");
    lili.affichage();

    printf("\nAffichage de Lolo avec Lili vide\n");
    lolo.affichage();

    printf("\nOn affecte Lili (vide) à Lolo\n");
    lolo = lili;

    printf("\nAffichage de Lolo (vide)\n");
    lolo.affichage();

    printf("\nRemplissage de Lili avec 7\n");
    lili.ajout(7);

    printf("\nAffichage de Lili avec 7\n");
    lili.affichage();*/

    return 0;
}
