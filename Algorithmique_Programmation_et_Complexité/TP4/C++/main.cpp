//#include <cstdio>
//#include <cstdlib>
//#include <ctime>
//#include <chrono>
#include <iostream>
#include "table.h"

using namespace std;

// Fonctions de hashage
int hash_modulo_taille(Key k, int s)
{
    return k%s;
}

// Fonctions de ré-hashage (i:indice; o:occurence; s:size)
int pas_lineaire(int i, int o, int s)
{
    return (i+1)%s;
}

int pas_quadratique(int i, int o, int s);
int pas_double(int i, int o, int s);

int main()
{
    Table t = Table(hash_modulo_taille, pas_lineaire, 10);
    cout << "Affichage de test vide : " << endl;
    t.show();

    t.add(15, 3.5);
    t.add(22, 2.4);
    t.add(37, 8.3);
    t.add(98, 1);
    t.add(42, 0);
    t.add(42, 5);
    t.add(42, 10);
    t.add(42, 5);
    t.add(42, 5);
    t.add(42, 5);

    cout << endl << "Affichage de test après ajout de valeurs : " << endl;
    t.show();

    return 0;
}
