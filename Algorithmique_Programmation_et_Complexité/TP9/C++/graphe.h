/**
 * Réalisé par Julien GIRAUD - 2019
 */

#ifndef _Graphe
#define _Graphe

using namespace std;

class Image
{
    friend class Graphe;
    public:
        Image(const string&);
    private:
        int* pixels;
        int largeur;
        int hauteur;
};

class Node
{
    friend class Graphe;
    public:
        Node();
        void add(int);
        void vide();

        // Affichage
        void show();
        
    private :
        int val;
        Node* sud;
        Node* nord;
        Node* est;
        Node* ouest;
};

class Graphe
{
    public :
        // Constructeurs ---- Destructeur
        Graphe(Image); // Constructeur par défaut
        ~Graphe();

        // Fonctions de manipulation
        int get_sud(int);
        int get_nord(int);
        int get_est(int);
        int get_ouest(int);

        // Affichage
        void show();
    private :
        Node * tous_les_noeuds;
        Image * image;
};

#endif
