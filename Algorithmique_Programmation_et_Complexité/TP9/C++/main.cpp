/**
 * Réalisé par Julien GIRAUD - 2019
 */

//#include <cstdio>
//#include <cstdlib>
#include <iostream>
#include "graphe.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;

    string adresse = "image.pgm";
    Image im = Image(adresse);
    Graphe g = Graphe(im);
    //g.show();
    g.show_info();

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
