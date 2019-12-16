/**
 * Réalisé par Julien GIRAUD - 2019
 */

#ifndef _Graphe
#define _Graphe

#include <vector>

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
        int max;
};

class Node
{
    friend class Graphe;
    public:
        Node();
        Node(int, float);
        void add(int);
        void vide();
        float get_poids_S(int);
        float get_poids_T(int);

        // Affichage
        void show();
        
    private :
        int val;
        Node* nord;
        Node* sud;
        Node* est;
        Node* ouest;
        float alpha; // C'est juste plus pratique...
        float* poids; // Valeurs des arcs [0]=nord, [1]=sud, [2]=est, [3]=ouest, [4]=S et [5]=T
        bool* utilisable; // Indique si l'arc est utilisable (false = supprimé)
};

class Graphe
{
    public :
        // Constructeurs ---- Destructeur
        Graphe(Image, float, float);
        ~Graphe();

        // Fonctions de calcul
        float get_valuation(Node*, Node*);
        int get_sud(int);
        int get_nord(int);
        int get_est(int);
        int get_ouest(int);
        bool is_in_vect(int, vector<int>);

        // Ford Fulkerson
        void ford_fulkerson(); // Fonction générale
        void ford_fulkerson_construction_graphe(); // Initialisation graphe orienté
        vector<int> ford_fulkerson_get_chemin(); // Bellman Ford global + traitement des arcs
        float ford_fulkerson_get_poids_min(vector<int>); // Avant le traitement des arcs
        void ford_fulkerson_coloration(); // Coloration des pixels suite à Ford Fulkerson

        // Affichage
        void show();
        void show_info();
        void save(string); // Affichage dans un fichier en soit...

    private :
        Image* image;
        Node* pixels;
        float sigma;
        float alpha;
};

#endif
