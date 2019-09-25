#ifndef _SKIPLIST
#define _SKIPLIST

#include "element.h"
#include <vector>

class Skiplist;

class Cellule
{
    friend class Skiplist;

private:
    Elem info;
    std::vector<Cellule *> suivant;
};

class Skiplist
{
public:
    //Constructeurs-------------------------------------------------------------
    Skiplist();
    Skiplist(const Skiplist &l);

    //Destructeur---------------------------------------------------------------
    ~Skiplist();

    //Affectation---------------------------------------------------------------
    bool testSkiplistVide() const;
    Skiplist &operator=(const Skiplist &l);
    void affichage() const;
    void ajout(const Elem &e);
    void vide();

private:
    //Donnees membres-----------------------------------------------------------
    Cellule *ad;
};

#endif
