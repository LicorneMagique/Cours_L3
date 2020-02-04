/**
 * Réalisé par Julien GIRAUD - 2019
 */

#ifndef _ProdCons
#define _ProdCons

#include <queue>

using namespace std;

class ProdCons {
    public :
        // Constructeurs ---- Destructeur
        ProdCons();
        ~ProdCons();

        // Fonctions
        void put(int);
        int get();
        int get_size();
    private :
        queue<int> file;
};

#endif
