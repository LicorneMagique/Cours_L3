/**
 * Réalisé par Julien GIRAUD - 2019
 */

#include <iostream>
#include "graphe.h"

using namespace std;

int main(int argc, char** argv)
{
    if (argc < 4)
    {
        cout << "Il manque des arguments, regarder le README.md" << endl;
        return 0;
    }
    if (argc > 5)
    {
        cout << "Il y a trop d'arguments, regarder le README.md" << endl;
        return 0;
    }

    string src = argv[1];
    string dest = argv[2];
    int alpha = stoi(argv[3]);

    // Sigma est de l'ordre de l'écart type de la dispersion des valeurs autour du noir et du blanc
    // noir -> [0-127], blanc -> [128-255], on peut partir sur sigma = 64 par défaut
    int sigma = 64;
    if (argc == 5)
        sigma = stoi(argv[4]);

    Graphe g = Graphe(src, sigma, alpha); // Utilisation du constructeur implicite string → image
    cout << "Image de taille ";
    g.show_info();
    cout << " chargée" << endl;
    cout << "Lancement de l'algorithme de Ford Fulkerson" << endl;
    g.ford_fulkerson();
    cout << "Fin de l'algorithme" << endl;
    cout << "Écriture dans le fichier " << dest << endl;
    g.save(dest);
    cout << "Exécution terminée" << endl;

    return 0;
}
