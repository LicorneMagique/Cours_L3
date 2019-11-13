/**
 * Réalisé par Julien GIRAUD - 2019
 */

//#include <cstdio>
//#include <cstdlib>
#include <iostream>
#include "element.h"
#include "avl.h"

using namespace std;

int main()
{
    AVL a;
    cout << "Affichage de l'arbre vide" << endl;
    a.show_infix();

    a.add(25);
    a.add(12);
    a.add(32);
    a.add(4);
    a.add(23);
    a.add(27);

    a.show_prefix();
    a.show_infix();
    a.show_postfix();
    cout << endl;
    a.show();

    //cout << "Affichage du sous-arbre sur 12" << endl;
    //a.get(12)->show(0);

    cout << "Affichage de a2" << endl;
    AVL a2(a);
    a2.show();

    cout << "Affichage de a3" << endl;
    AVL a3 = a;
    a3.show();

    a.vide();
    cout << "Affichage de a après avoir vidé l'arbre" << endl;
    a.show_infix();
    cout << "Affichage de a2" << endl;
    a2.show();
    a2.vide();
    cout << "Affichage de a3" << endl;
    a3.show();
    a3.vide();

    for (int i = 0; i < 8; i++)
        a3.add(rand()%100);
    
    cout << "Affichage de a3 après insertions" << endl;
    a3.show();

    return 0;
}
