/**
 * Réalisé par Julien GIRAUD - 2019
 */

#ifndef _ABR
#define _ABR

#include "element.h"

class Node
{
    friend class ABR;
    public:
        Node(Elem);
        Node(const Node*);
        bool operator<(const Node &);
        void add(Elem);
        void vide();

        // Affichage
        void show(int);
        void show_infix();
        void show_prefix();
        void show_postfix();
        
    private :
        Elem elem;
        Node* fg;
        Node* fd;
};

class ABR
{
    public :
        // Constructeurs ---- Destructeur
        ABR(); // Constructeur par défaut
        ABR(const ABR&); // Constructeur par copie
        ~ABR();

        // Fonctions de manipulation de l'arbre
        bool search(Elem);
        void add(Elem);
        void vide();

        // Affichage
        void show();
        void show_infix();
        void show_prefix();
        void show_postfix();
        
        // Surcharge d'opérateur
        ABR& operator=(const ABR &);

    private :
        Node * racine;
};

#endif
