/**
 * Réalisé par Julien GIRAUD - 2019
 */

//#include <cstdio>
//#include <cstdlib>
#include <iostream>
#include "element.h"
#include "abrc.h"

using namespace std;

int main()
{
    ABRC a;
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
    ABRC a2(a);
    a2.show();

    cout << "Affichage de a3" << endl;
    ABRC a3 = a;
    a3.show();

    a.vide();
    cout << "Affichage de a après avoir vidé l'arbre" << endl;
    a.show_infix();
    cout << "Affichage de a2" << endl;
    a2.show();
    a2.vide();
    cout << "Affichage de a3" << endl;
    a3.show();

    a.add(2);
    a.add(1);
    a.add(3);
    a.show();
    cout << "test non sousu" << endl;
    a.show_cousu();
    cout << "test cousu" << endl;
    a.transform_en_ABRC();
    //a2.show_cousu();

    return 0;
}
