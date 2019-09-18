#ifndef _LISTE
#define _LISTE

#include "element.h" //offrant le type Elem

class Liste;

class Cellule
{
    friend class Liste;

private:
    Elem info;
    Cellule *suivant;
};

class Liste
{
public:
    //Constructeurs-------------------------------------------------------------
    Liste();
    //Postcondition : la liste initialisee est vide
    Liste(const Liste &l);
    //Postcondition : la liste initialisee et l correspondent a des listes identiques
    //                (mais elles sont totalement independantes l'une de l'autre)

    //Destructeur---------------------------------------------------------------
    ~Liste();

    //Affectation---------------------------------------------------------------
    Liste &operator=(const Liste &l);
    //Precondition : aucune
    //               (la liste a affecter et l initialisees et manipulees uniquement
    //               a travers les operations du module)
    //Postcondition : la liste affectee et l correspondent a des listes identiques
    //                (mais elles sont totalement independantes l'une de l'autre)

    bool testListeVide() const;
    //Precondition : aucune
    //               (*this initialisee et manipulee uniquement a travers les
    //                operations du module)
    //Resultat : true si *this est vide, false sinon

    Elem premierElement() const;
    //Precondition : testListeVide(l)==false
    //Resultat : valeur de l'Elem contenu dans la 1ere Cellule

    Cellule *premiereCellule() const;
    //Precondition : aucune
    //               (*this initialisee et manipulee uniquement a travers les
    //                operations du module)
    //Resultat : adresse de la premiere cellule de *this si this->testVide()==false
    //           O sinon
    //           Attention : la liste *this pourrait ensuite etre modifiee a travers
    //           la connaissance de l'adresse de sa premiere cellule

    Cellule *celluleSuivante(const Cellule *c) const;
    //Precondition : c adresse valide d'une Cellule de la Liste *this
    //Resultat : adresse de la cellule suivante si elle existe
    //           O sinon
    //           Attention : la liste *this pourrait ensuite etre modifiee a travers
    //           la connaissance de l'adresse d'une de ses cellules

    Elem elementCellule(const Cellule *c) const;
    //Precondition : c adresse valide d'une Cellule de la Liste *this
    //Resultat : valeur de l'Elem contenu dans la Cellule

    void affichage() const;
    //Precondition : aucune
    //               (*this initialisee et manipulee uniquement a travers les
    //                operations du module)
    //Postcondition : Affichage exhaustif de tous les elements de *this

    void ajoutEnTete(const Elem &e);
    //Precondition : aucune
    //               (*this et e initialises et manipules uniquement a travers les
    //                operations de leurs modules respectifs)
    //Postcondition : L'Elem e est ajoute en tete de *this

    void suppressionEnTete();
    //Precondition : this->testVide()==false
    //Postcondition : la liste *this perd son premier element

    void vide();
    //Precondition : aucune
    //               (*this initialisee et manipulee uniquement a travers les
    //                operations du module)
    //Postcondition : this->testVide()==true

    void ajoutEnQueue(const Elem &e);
    //Precondition : aucune
    //               (*this et e initialises et manipules uniquement a travers les
    //                operations de leurs modules respectifs)
    //Precondition : L'Elem e est ajoute en fin de la liste *this

    //OPERATIONS QUI POURRAIENT ETRE AJOUTEES AU MODULE

    Cellule *rechercheElement(const Elem &e) const;
    //Precondition : aucune
    //               (*this initialisee et manipulee uniquement a travers les
    //                operations du module)
    //Resultat : Adresse de la premiere Cellule de *this contenant e, 0 sinon
    //           Attention : la liste *this pourrait ensuite etre modifiee a travers
    //           la connaissance de l'adresse d'une de ses cellules

    void insereElementApresCellule(const Elem &e, Cellule *c);
    //Precondition : c adresse valide d'une Cellule de la Liste *this
    //               ou 0 si this->testVide()==true
    //Postcondition : l'element e est insere apres la Cellule pointee par c

    void modifieInfoCellule(const Elem &e, Cellule *c);
    //Precondition : *this non vide et c adresse valide d'une Cellule de *this
    //Postcondition : l'info contenue dans *c a pour valeur e
private:
    void ajoutEnQueueConnaissantUneCellule(const Elem &e, Cellule *c);
    void affichageDepuisCellule(const Cellule *c) const;
    //Donnees membres-----------------------------------------------------------
    Cellule *ad;
};

#endif
