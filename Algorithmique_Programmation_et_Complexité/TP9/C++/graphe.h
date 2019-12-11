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
        Node(int);
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
        int* flux; // [0] = nord, [1] = sud, [2] = est, [3] = ouest, [4] = S, [5] = T
};

class Graphe
{
    public :
        // Constructeurs ---- Destructeur
        Graphe(Image);
        ~Graphe();

        // Fonctions de manipulation
        int get_sud(int);
        int get_nord(int);
        int get_est(int);
        int get_ouest(int);

        // Affichage
        void show();
        void show_info();

    private :
        Image* image;
        Node* S;
};

#endif
