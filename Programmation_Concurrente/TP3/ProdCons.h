/**
 * Réalisé par Julien GIRAUD - 2019
 */

#ifndef _ProdCons
#define _ProdCons

#include <queue>
#include <condition_variable>

using namespace std;

struct rect {
    int slice_number ;
    int y_start ;
    rect ( int sn , int y ) : slice_number ( sn ) , y_start ( y ) {};
};

class ProdCons {
    public :
        // Constructeurs ---- Destructeur
        ProdCons(int);
        ~ProdCons();

        // Fonctions
        void put(rect);
        rect get(); // Pop en même temps
        int get_size();
        bool is_empty();

        condition_variable& getVide();
        condition_variable& getPlein();

    private :
        queue<rect> file;
        unsigned int taille_max;
        condition_variable vide;
        condition_variable plein;
        mutex m;
};

#endif
