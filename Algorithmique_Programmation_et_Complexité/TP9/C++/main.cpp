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

    return 0;
}
