/**
 * Réalisé par Julien GIRAUD - 2019
 */

#ifndef _ABR
#define _ABR

#include "element.h"

class Node
{
    friend class ABRC;
    public:
        Node(Elem);
        Node(const Node*);
        bool operator<(const Node&);
        void add(Elem);
        void vide();
        void transform_en_ABRC(Node*);

        // Affichage
        void show(int);
        void show_infix();
        void show_prefix();
        void show_postfix();
        void show_cousu();
        
    private :
        Elem elem;
        Node* fg;
        Node* fd;
        bool cousu;
};

class ABRC
{
    public :
        // Constructeurs ---- Destructeur
        ABRC(); // Constructeur par défaut
        ABRC(const ABRC&); // Constructeur par copie
        ~ABRC();

        // Fonctions de manipulation de l'arbre
        bool search(Elem);
        void add(Elem);
        void vide();
        void transform_en_ABRC();

        // Affichage
        void show();
        void show_infix();
        void show_prefix();
        void show_postfix();
        void show_cousu();
        
        // Surcharge d'opérateur
        ABRC& operator=(const ABRC &);

    private :
        Node * racine;
        Node * infixe;
};

#endif
