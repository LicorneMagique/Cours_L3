//#include <cstdio>
//#include <cstdlib>
//#include <ctime>
//#include <chrono>
#include <cmath>
#include <iostream>
#include "table.h"

using namespace std;

// Fonctions de hashage
int hash_modulo_taille(Key k, int s)
{
    return k%s;
}

// Fonctions de ré-hashage (i:indice; o:occurence; s:size)
int pas_lineaire(Key k, int i, int o, int s)
{
    return (i+1)%s;
}

int pas_quadratique(Key k, int i, int o, int s)
{
    //cout << i << " " << (i+1)%s << "  ";
    return (int)(i + pow(i-1, 2))%s;
}

int pas_double(Key k, int i, int o, int s)
{
    // Formule inspirée de <https://www.geeksforgeeks.org/double-hashing/>
    // Double hashing -> hash1(key) + i * hash2(key)) % TABLE_SIZE
    // hash1(key) -> key % TABLE_SIZE
    // hash2(key) -> PRIME – (key % PRIME), PRIME < TABLE_SIZE
    // Et pour PRIME j'ai pris TABLE_SIZE/2
    int h1 = k%s;
    int p = s/2;
    int h2 = p - (k%p);
    return (h1 + i * h2)%s;
}

int main()
{
    int global_size = 31;

    cout << endl << "t :" << endl;
    Table t = Table(hash_modulo_taille, pas_lineaire, global_size);
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
    t.add(8, 5);
    t.add(8, 5);
    t.add(8, 5);
    t.add(8, 5);
    t.add(0, 9);

    t.show();

    cout << endl << "t2 :" << endl;
    Table t2 = Table(hash_modulo_taille, pas_quadratique, global_size); // ici il faut un nombre premier
    t2.add(15, 3.5);
    t2.add(22, 2.4);
    t2.add(37, 8.3);
    t2.add(98, 1);
    t2.add(42, 0);
    t2.add(42, 5);
    t2.add(42, 10);
    t2.add(42, 5);
    t2.add(42, 5);
    t2.add(42, 5);
    t2.add(8, 5);
    t2.add(8, 5);
    t2.add(8, 5);
    t2.add(8, 5);
    t2.add(0, 9);

    t2.show();

    cout << endl << "t3 :" << endl;
    Table t3 = Table(hash_modulo_taille, pas_double, global_size); // ici il faut un nombre premier
    t3.add(15, 3.5);
    t3.add(22, 2.4);
    t3.add(37, 8.3);
    t3.add(98, 1);
    t3.add(42, 0);
    t3.add(42, 5);
    t3.add(42, 10);
    t3.add(42, 5);
    t3.add(42, 5);
    t3.add(42, 5);
    t3.add(8, 5);
    t3.add(8, 5);
    t3.add(8, 5);
    t3.add(8, 5);
    t3.add(0, 9);

    t3.show();

    return 0;
}
