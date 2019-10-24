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

int hash_modulo_taille_deux(Key k, int s)
{
    return k%(s/2);
}

// Fonctions de ré-hashage (i:indice; o:occurence; s:size)
int pas_lineaire(Key k, int i, int o, int s)
{
    return (i+1)%s;
}

int pas_quadratique(Key k, int i, int o, int s)
{
    return (int)(i + pow(o-1, 2))%s;
}

int pas_double(Key k, int i, int o, int s)
{
    // Formule inspirée de <https://www.geeksforgeeks.org/double-hashing/>
    // Double hashing -> hash1(key) + i * hash2(key)) % TABLE_SIZE
    int h1 = (k+1)%s;
    int p = s/2;
    int h2 = p - (k%p);
    return (h1 + i * h2)%s;
}

int main()
{
    int global_size = 13;

    Table t = Table(hash_modulo_taille_deux, pas_lineaire, global_size);
    Table t2 = Table(hash_modulo_taille_deux, pas_quadratique, global_size);
    Table t3 = Table(hash_modulo_taille_deux, pas_double, global_size);

    cout << endl << "Affichage de t vide" << endl;
    t.show();

    cout << endl << "Affichage de t, t2 et t3 après l'ajout de quelques valeurs :" << endl;
    t.add(0, 0);
    t.add(2, 1);
    t.add(8, 2);
    t.add(20, 3);
    t.add(25, 4);
    t.add(42, 5);
    cout << endl << "t a " << t.getInfo() << endl;
    t.show();
    
    t2.add(0, 0);
    t2.add(2, 1);
    t2.add(8, 2);
    t2.add(20, 3);
    t2.add(25, 4);
    t2.add(42, 5);
    cout << endl << "t2 a " << t2.getInfo() << endl;
    t2.show();
    
    t3.add(0, 0);
    t3.add(2, 1);
    t3.add(8, 2);
    t3.add(20, 3);
    t3.add(25, 4);
    t3.add(42, 5);
    cout << endl << "t3 a " << t3.getInfo() << endl;
    t3.show();

    cout << endl << "Affichage de t, t2 et t3 après deux tentatives de suppression de l'avant dernière valeur (clé 25) :" << endl << endl;
    t.remove(25);
    t.remove(25);
    t.show();
    cout << endl;
    t2.remove(25);
    t2.remove(25);
    t2.show();
    cout << endl;
    t3.remove(25);
    t3.remove(25);
    t3.show();
    cout << endl;

    cout << endl << "Affichage de t, t2 et t3 après deux tentatives de suppression de la dernière valeur (clé 42) :" << endl << endl;
    t.remove(42);
    t.remove(42);
    cout << "t :";
    t.show();
    cout << endl;
    t2.remove(42);
    t2.remove(42);
    cout << "t2 :";
    t2.show();
    cout << endl;
    t3.remove(42);
    t3.remove(42);
    cout << "t3 :";
    t3.show();

    cout << endl << "Affichage de t, t2 et t3 après avoir rajouté une valeur supprimée (clé 25) :" << endl;
    t.add(25, 8);
    cout << "t :";
    t.show();
    cout << endl;
    t2.add(25, 8);
    cout << "t2 :";
    t2.show();
    cout << endl;
    t3.add(25, 8);
    cout << "t3 :";
    t3.show();

    cout << endl << "Recherche de la clé 20 dans t3 : " << t3.search(20) << endl
         << "Il y a donc la clé 20 dans t3, son indice est " << t3.search(20) << endl;
    
    cout << endl << "Recherche de la clé 42 dans t3 : " << t3.search(42)
         << endl << "Il n'y a donc pas la clé 42 dans t3" << endl;

    int global_size2 = 500;
    Table t4 = Table(hash_modulo_taille_deux, pas_lineaire, global_size2);
    Table t5 = Table(hash_modulo_taille_deux, pas_quadratique, global_size2);
    Table t6 = Table(hash_modulo_taille_deux, pas_double, global_size2);
    int key;
    double value;
    for (int i = 0; i < 800; i++)
    {
        key = rand()%1000;
        value = (double)rand() / 1000;
        if (t4.search(key) == -1) t4.add(key, value);
        if (t5.search(key) == -1) t5.add(key, value);
        if (t6.search(key) == -1) t6.add(key, value);
    }
    // Il faut gérer les erreurs d'insertion double d'une clé et on pourrq virer les if ici
    
    cout << endl << "Infos de t4, t5 et t6 après un grand nombre d'insertions :" << endl;

    cout << endl << "t4 a " << t4.getInfo() << endl;
    cout << "t5 a " << t5.getInfo() << endl;
    cout << "t6 a " << t6.getInfo() << endl;

    return 0;
}
