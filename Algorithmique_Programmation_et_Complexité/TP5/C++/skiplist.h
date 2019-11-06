// LIFAP6 - Automne 2017 - R. Chaine
 
#ifndef _SKIPLIST
#define _SKIPLIST
 
#include "element.h" //offrant le type Elem
#include <vector>
 
class SkipList;
 
class Cellule
{
    friend class SkipList;
 
    private :
        Elem info;
        std::vector<Cellule*> suivants;
};
 
class SkipList
{
public :
    //Constructeurs-------------------------------------------------------------
    SkipList();
    //Postcondition : la liste initialisee est vide
    SkipList(const SkipList& l);
    //Postcondition : la liste initialisee et l correspondent a des listes identiques
    //                (mais elles sont totalement independantes l'une de l'autre)
     
    //Destructeur---------------------------------------------------------------
    ~SkipList();
     
    void ajout(const Elem& e);
 
    void affichage() const;
 
    bool testVide() const;
    //Precondition : aucune
    //               (*this initialisee et manipulee uniquement a travers les
    //                operations du module)
    //Resultat : true si *this est vide, false sinon
     
    void vide();
    //Precondition : aucune
    //               (*this initialisee et manipulee uniquement a travers les
    //                operations du module)
    //Postcondition : this->testVide()==true
     
    Cellule* rechercheElement(const Elem& e) const;
    //Precondition : aucune
    //               (*this initialisee et manipulee uniquement a travers les
    //                operations du module)
    //Resultat : Adresse de la premiere Cellule de *this contenant e, 0 sinon
    //           Attention : la liste *this pourrait ensuite etre modifiee a travers
    //           la connaissance de l'adresse d'une de ses cellules

    void supprimerElement(const Elem& e);
 
private :
    //Donnees membres-----------------------------------------------------------
    Cellule *ad;
};
 
 
#endif
