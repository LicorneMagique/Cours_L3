/**
 * Réalisé par Julien GIRAUD - 2019
 */

#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iomanip>
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
int pas_lineaire(Key k, int i, int o, int s, int hash(Key, int))
{
    return (i+1)%s;
}

int pas_quadratique(Key k, int i, int o, int s, int hash(Key, int))
{
    return (int)(i + pow(o-1, 2))%s;
}

int pas_double(Key k, int i, int o, int s, int hash(Key, int))
{
    // Formule trouvée sur https://www.geeksforgeeks.org/double-hashing/
    // Double hashing -> hash1(key) + i * hash2(key)) % TABLE_SIZE
    // hash1(key) -> key%TABLE_SIZE
    // hash2(key) -> prime - (key%prime)
    // prime = TABLE_SIZE/2
    // i le premier indice testé pour l'insertion, incrémenté de 1 après chaque échec
    int h1 = k%s;
    int p = s/2;
    int h2 = p - (k%p);
    int _i = hash(k, s) + o-1;
    return (h1 + _i * h2)%s;
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
    cout << endl << "t : " << t.getInfo() << endl;
    t.show();
    
    t2.add(0, 0);
    t2.add(2, 1);
    t2.add(8, 2);
    t2.add(20, 3);
    t2.add(25, 4);
    t2.add(42, 5);
    cout << endl << "t2 : " << t2.getInfo() << endl;
    t2.show();
    
    t3.add(0, 0);
    t3.add(2, 1);
    t3.add(8, 2);
    t3.add(20, 3);
    t3.add(25, 4);
    t3.add(42, 5);
    cout << endl << "t3 : " << t3.getInfo() << endl;
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

    cout << endl << "Récupération de la valeur associée à la clé 25 dans t : " << t.getValue(25) << endl;
    cout << "Modification de la valeur associée à cette clé (nouvelle valeur = 42)" << endl;
    t.setValue(25, 42);
    cout << "Récupération de la nouvelle valeur associée à la clé 25 : " << t.getValue(25) << endl;

    string const fichier_resultats_1 = "./performance_lineaire.txt";
    string const fichier_resultats_2 = "./performance_quadratique.txt";
    string const fichier_resultats_3 = "./performance_double.txt";
    ofstream file_1(fichier_resultats_1.c_str());
    ofstream file_2(fichier_resultats_2.c_str());
    ofstream file_3(fichier_resultats_3.c_str());
    
    file_1 << "# \"nb\" \"temps\"" << endl;
    file_2 << "# \"nb\" \"temps\"" << endl;
    file_3 << "# \"nb\" \"temps\"" << endl;

    int global_size2 = 10007; // Nombre premier
    int global_size3 = 8192; // Puissance de 2
    int global_size4 = 10000; // Nombre quelconque
    
    Table t4 = Table(hash_modulo_taille, pas_lineaire, global_size2);
    Table t5 = Table(hash_modulo_taille, pas_quadratique, global_size2);
    Table t6 = Table(hash_modulo_taille, pas_double, global_size2);
    Key key, max_key = 20000;
    int perf;
    double value;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    for (int i = 0; i < global_size2; i++)
    {
        key = rand()%max_key;
        value = (double)rand() / 1000;
        if (t4.search(key) == -1) t4.add(key, value);
        if (t5.search(key) == -1) t5.add(key, value);
        if (t6.search(key) == -1) t6.add(key, value);
        if (i && i%1000 == 0)
        {
            start = std::chrono::system_clock::now();
            for (int j = 0; j < max_key; j++)
                t4.search(j);
            end = std::chrono::system_clock::now();
            perf = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            file_1 << perf << " " << i << endl;

            start = std::chrono::system_clock::now();
            for (int j = 0; j < max_key; j++)
                t5.search(j);
            end = std::chrono::system_clock::now();
            perf = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            file_2 << perf << " " << i << endl;

            start = std::chrono::system_clock::now();
            for (int j = 0; j < max_key; j++)
                t6.search(j);
            end = std::chrono::system_clock::now();
            perf = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            file_3 << perf << " " << i << endl;
        }
    }

    cout << endl << "Infos de t4, t5 et t6 après un grand nombre d'insertions avec un nombre premier en taille :" << endl;
    cout << endl << "t4 : " << t4.getInfo() << endl;
    cout << "t5 : " << t5.getInfo() << endl;
    cout << "t6 : " << t6.getInfo() << endl;
    cout << "-> Double hashage gagnant, globalement ils sont tous efficaces" << endl;

    Table t7 = Table(hash_modulo_taille, pas_lineaire, global_size3);
    Table t8 = Table(hash_modulo_taille, pas_quadratique, global_size3);
    Table t9 = Table(hash_modulo_taille, pas_double, global_size3);
    for (int i = 0; i < global_size3; i++)
    {
        key = rand()%max_key;
        value = (double)rand() / 1000;
        if (t7.search(key) == -1) t7.add(key, value);
        if (t8.search(key) == -1) t8.add(key, value);
        if (t9.search(key) == -1) t9.add(key, value);
    }
    cout << endl << "Infos de t7, t8 et t9 après un grand nombre d'insertions avec une puissance de 2 en taille :" << endl;
    cout << endl << "t7 : " << t7.getInfo() << endl;
    cout << "t8 : " << t8.getInfo() << endl;
    cout << "t9 : " << t9.getInfo() << endl;
    cout << "-> Re-hashage quadratique gagnant" << endl;
    cout << "-> Le double-hashage est presque aussi rapide que le quadratique mais il n'a pas pu insérer certains éléments" << endl;
    cout << "-> Le ré-hashage linéaire est très mauvais en vitesse" << endl;

    Table t10 = Table(hash_modulo_taille, pas_lineaire, global_size4);
    Table t11 = Table(hash_modulo_taille, pas_quadratique, global_size4);
    Table t12 = Table(hash_modulo_taille, pas_double, global_size4);
    for (int i = 0; i < global_size4; i++)
    {
        key = rand()%max_key;
        value = (double)rand() / 1000;
        if (t10.search(key) == -1) t10.add(key, value);
        if (t11.search(key) == -1) t11.add(key, value);
        if (t12.search(key) == -1) t12.add(key, value);
    }
    cout << endl << "Infos de t10, t11 et t12 après un grand nombre d'insertions avec un nombre quelconque comme taille :" << endl;
    cout << endl << "t10 : " << t10.getInfo() << endl;
    cout << "t11 : " << t11.getInfo() << endl;
    cout << "t12 : " << t12.getInfo() << endl;
    cout << "-> Re-hashage quadratique gagnant" << endl;
    cout << "-> Le hashage linéaire est presque aussi rapide le quadratique" << endl;
    cout << "-> Le double-hashage est très mauvais en vitesse en plus de n'avoir pas pu insérer certains éléments" << endl;

    return 0;
}
