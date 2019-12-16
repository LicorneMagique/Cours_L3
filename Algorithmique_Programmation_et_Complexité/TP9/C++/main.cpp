/**
 * Réalisé par Julien GIRAUD - 2019
 */

#include <iostream>
#include "graphe.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;

    // Sigma est de l'ordre de l'écart type de la dispersion des valeurs autour du noir et du blanc
    // noir -> [0-127], blanc -> [128-255], on peut partir sur sigma = 64
    int sigma = 64;

    int alpha = 4;

    string adresse = "image4.pgm";
    string sortie = "toto.pgm";
    Graphe g = Graphe(adresse, sigma, alpha); // Utilisation du constructeur implicite string → image
    g.show_info();
    g.ford_fulkerson();
    g.save(sortie);

    return 0;
}

/*
Binarisation(alpha)
getPoids(alpha, pixel){
    return -alpha * ln( (255-I(pixel)) / 255)
}
I(p){
    return S[p].val
}
*/
