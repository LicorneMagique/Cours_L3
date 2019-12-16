/**
 * Réalisé par Julien GIRAUD - 2019
 */

#include <cmath>
#include <fstream>
#include <limits>
#include <iomanip>
#include <iostream>
#include <vector>
#include "graphe.h"


using namespace std;

Image::Image(const string& adresse)
{
    ifstream ifs(adresse);
    string line;
    int i = -1;

    while(getline(ifs, line))
    {
        if (i == -1 && line[0] != '#' && line.find(' ') != -1)
        {
            largeur = stoi(line.substr(0, line.find(' ')));
            hauteur = stoi(line.substr(line.find(' ') + 1, line.length()));
            pixels = new int[largeur*hauteur];
            i = 0;
            getline(ifs, line); // line <- Intensité maximale
            max = stoi(line);
        }
        else if (i >= 0)
            pixels[i++] = stoi(line);
    }
}

Node::Node()
{
    poids = new float[6]();
    utilisable = new bool[6]();
}

Node::Node(int v, float a)
{
    val = v;
    alpha = a;
    sud = nullptr;
    nord = nullptr;
    est = nullptr;
    ouest = nullptr;
    poids = new float[6]();
    utilisable = new bool[6]{0, 0, 0, 0, 0, 0};
}

Graphe::Graphe(Image im, float s, float a)
{
    int indice, i2;
    image = new Image(im);
    sigma = s;
    alpha = a;
    pixels = new Node[im.hauteur*im.largeur];
    for (int i = 0; i < im.hauteur; i++)
        for (int j = 0; j < im.largeur; j++)
        {
            indice = i*im.largeur + j;
            pixels[indice].val = im.pixels[indice];
            i2 = get_sud(indice);
            pixels[indice].sud = (i2 != -1) ? new Node(im.pixels[i2], alpha) : nullptr;
            i2 = get_nord(indice);
            pixels[indice].nord = (i2 != -1) ? new Node(im.pixels[i2], alpha) : nullptr;
            i2 = get_est(indice);
            pixels[indice].est = (i2 != -1) ? new Node(im.pixels[i2], alpha) : nullptr;
            i2 = get_ouest(indice);
            pixels[indice].ouest = (i2 != -1) ? new Node(im.pixels[i2], alpha) : nullptr;
        }
}

Graphe::~Graphe()
{
    delete pixels;
}

int Graphe::get_nord(int i)
{
    if (i < image->largeur)
        return -1;
    return i - image->largeur;
}

int Graphe::get_sud(int i)
{
    if (i > image->largeur * (image->hauteur-1)-1)
        return -1;
    return i + image->largeur;
}

int Graphe::get_est(int i)
{
    if (((i+1) % image->largeur) == 0)
        return -1;
    return i + 1;
}

int Graphe::get_ouest(int i)
{
    if (((i+image->largeur) % image->largeur) == 0)
        return -1;
    return i - 1;
}

void Graphe::show()
{
    int indice;
    cout << image->hauteur << " " << image->largeur << endl;
    for (int i = 0; i < image->hauteur; i++)
        for (int j = 0; j < image->largeur; j++)
        {
            indice = i*image->largeur + j;
            cout << "Pixel : " << indice+1 << ", Val : " << pixels[indice].val;
            cout << ", Nord : ";
            if (pixels[indice].nord == nullptr)
                cout << "rien";
            else
                cout << pixels[indice].nord->val;
            cout << ", Sud : ";
            if (pixels[indice].sud == nullptr)
                cout << "rien";
            else
                cout << pixels[indice].sud->val;
            cout << ", Est : ";
            if (pixels[indice].est == nullptr)
                cout << "rien";
            else
                cout << pixels[indice].est->val;
            cout << ", Ouest : ";
            if (pixels[indice].ouest == nullptr)
                cout << "rien";
            else
                cout << pixels[indice].ouest->val;
            cout << endl;
        }
}

void Graphe::show_info()
{
    cout << "H : " << image->hauteur << ", L : " << image->largeur << endl;
}

float Graphe::get_valuation(Node* p, Node* q)
{
    float a, b;
    a = pow(p->val - q->val, 2); // a = (I(p) - I(q))²
    b = 2 * pow(sigma, 2); // b = 2 * sigma²
    return exp(-(a/b));
}

float Node::get_poids_S(int alpha)
{
    float a = (255 - (float)val) / 255;
    a = -(alpha * log(a));
    return a == -0 ? 0 : a; // -0 => 0
}

float Node::get_poids_T(int alpha)
{
    float a = (float)val / 255;
    a = -(alpha * log(a));
    return a == -0 ? 0 : a;
}

void Graphe::ford_fulkerson_construction_graphe()
{
    float max = numeric_limits<float>::max();
    float inf = numeric_limits<float>::infinity();
    Node* p;
    for (int i = 0; i < image->hauteur*image->largeur; i++)
    {
        cout << "i=" << i << endl;
        p = &pixels[i];
        if (p->nord != nullptr)
        {
            p->poids[0] = get_valuation(p, p->nord); // Poids de l'arc (p, p->nord)
            p->utilisable[0] = true; // L'arc existe forcément
        }
        if (p->sud != nullptr)
        {
            p->poids[1] = get_valuation(p, p->sud);
            p->utilisable[1] = true;
        }
        if (p->est != nullptr)
        {
            p->poids[2] = get_valuation(p, p->est);
            p->utilisable[2] = true;
        }
        if (p->ouest != nullptr)
        {
            p->poids[3] = get_valuation(p, p->ouest);
            p->utilisable[3] = true;
        }
        p->poids[4] = p->get_poids_S(alpha); // Poids de l'arc (S, p)
        p->poids[5] = p->get_poids_T(alpha); // Poids de l'arc (T, p)
        p->utilisable[4] = (p->poids[4] < inf); // arc de taille infini <=> pas d'arc
        p->utilisable[5] = (p->poids[5] < inf);
        cout << p->poids[0] << " " << p->poids[1] << " " << p->poids[2]
             << " " << p->poids[3] << " " << p->poids[4] << " " << p->poids[5] << endl;
        cout << p->utilisable[0] << " " << p->utilisable[1] << " " << p->utilisable[2]
             << " " << p->utilisable[3] << " " << p->utilisable[4] << " " << p->utilisable[5] << endl;
    }
    cout << endl;
}

vector<int> Graphe::ford_fulkerson_get_chemin() // Version adaptée de l'algorithme de Bellman Ford
// Source : https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/
{
    int V = image->hauteur * image->largeur; // Nombre de sommets
    int E = 6; // Nombre de relations d'un sommet
    float dist[V+1]; // Tableau des distances
  
    // Étape 1 : Initialisation des distances de la source à tous les autres sommets sur INFINI
    float inf = numeric_limits<float>::infinity();
    for (int i = 0; i < V+2; i++)
        dist[i] = inf;
    dist[V] = 0; // S

    // Étape 2 : Pour chaque arc (A,B) on enregistre les sommets qui donnent les plus courts chemins
    int v;
    float weight;
    int parents[V+2];
    for (int i = 0; i < V+2; i++) 
            parents[i] = -1;
    bool changement = true;
    Node* p;
    while (changement) // Tant qu'on trouve des chemins plus courts
    {
        changement = false;
        for (int i = 0; i < V; i++) // Il aurait été plus pertinant d'utiliser un tableau pour cette partie...
        {
            p = &pixels[i];
            if (p->utilisable[0])
            {
                v = get_nord(i); // Indice de B dans dist[]
                weight = 1/p->poids[0]; // Poids de l'arc (A,B)
                if (dist[i] != inf && dist[i] + weight < dist[v])
                {
                    dist[v] = dist[i] + weight;
                    parents[v] = i;
                    changement = true;
                }
            }
            if (p->utilisable[1])
            {
                v = get_sud(i);
                weight = 1/p->poids[1];
                if (dist[i] != inf && dist[i] + weight < dist[v])
                {
                    dist[v] = dist[i] + weight;
                    parents[v] = i;
                    changement = true;
                }
            }
            if (p->utilisable[2])
            {
                v = get_est(i);
                weight = 1/p->poids[2];
                if (dist[i] != inf && dist[i] + weight < dist[v])
                {
                    dist[v] = dist[i] + weight;
                    parents[v] = i;
                    changement = true;
                }
            }
            if (p->utilisable[3])
            {
                v = get_ouest(i);
                weight = 1/p->poids[3];
                if (dist[i] != inf && dist[i] + weight < dist[v])
                {
                    dist[v] = dist[i] + weight;
                    parents[v] = i;
                    changement = true;
                }
            }
            if (p->utilisable[4])
            {
                v = V; // S
                weight = 1/p->poids[4];
                if (weight != inf && dist[i] > weight)
                {
                    dist[i] = weight;
                    parents[i] = v;
                    changement = true;
                }
            }
            if (p->utilisable[5])
            {
                v = V+1; // T
                weight = 1/p->poids[5];
                if (dist[i] != inf && dist[i] + weight < dist[v])
                {
                    //cout << "ancienne valeur : " << dist[v] << ", nouvelle : " << dist[i] + weight;
                    //if (dist[i] < 0) break;
                    dist[v] = dist[i] + weight;
                    parents[v] = i;
                    changement = true;
                }
            }
        }
    }

    // Affichage des distances
    /*for (int i = 0; i < V+2; i++)
    {
        cout << "dist[" << i << "] = " << dist[i] << ", parents[i] = " << parents[i] << endl;
    }*/

    // Enregistrement des noeuds du chemin dans le résultat de la fonction
    int parent = V+1; // Sommet de T
    vector<int> chemin;
    if (dist[V+1] < inf)
        while (parents[parent] != V)
        {
            chemin.push_back(parents[parent]);
            if (parent == V+1)
                cout << "[" << pixels[parents[parent]].poids[5] << "](T, " << parents[parent] << ")";
            else
            {
                float p = -1;
                if (get_nord(parents[parent]) == parent)
                    p = pixels[parents[parent]].poids[0];
                else if (get_sud(parents[parent]) == parent)
                    p = pixels[parents[parent]].poids[1];
                else if (get_est(parents[parent]) == parent)
                    p = pixels[parents[parent]].poids[2];
                else if (get_ouest(parents[parent]) == parent)
                    p = pixels[parents[parent]].poids[3];
                cout << " <- [" << p << "](" << parent << ", " << parents[parent] << ")";
               // if (p < 0) break;
            }
            parent = parents[parent];
            if (parents[parent] == V)
                cout << " <- [" << pixels[parent].poids[4] << "](" << parent << ", S)";
            
        }
        cout << endl;

    return chemin;
}

float Graphe::ford_fulkerson_get_poids_min(vector<int> chemin)
{
    float min, poids;
    float min2, poids2;
    for (int i = 0; i < chemin.size(); i++)
    {
        //cout << "Index actuel : " << chemin[i];
        if (i == 0) // T
        {
            min2 = pixels[chemin[i]].poids[5];
            //cout << ", Je commence à : " << min2;
            if (chemin.size() == 1)
            {
                poids2 = pixels[chemin[i]].poids[4];
                if (poids2 < min2)
                    min2 = poids2;
            }
        }
        else // Tous les arcs sauf T
        {
            //cout << ", index du précédent : " << chemin[i-1];
            if (chemin[i-1] == get_nord(chemin[i]))
            {
                //cout << " [" << pixels[chemin[i]].poids[0] << "]NORD";
                poids2 = pixels[chemin[i]].poids[0];
            }
            else if (chemin[i-1] == get_sud(chemin[i]))
            {
                //cout << " [" << pixels[chemin[i]].poids[1] << "]SUD";
                poids2 = pixels[chemin[i]].poids[1];
            }
            else if (chemin[i-1] == get_est(chemin[i]))
            {
                //cout << " [" << pixels[chemin[i]].poids[2] << "]EST";
                poids2 = pixels[chemin[i]].poids[2];
            }
            else if (chemin[i-1] == get_ouest(chemin[i]))
            {
                //cout << " [" << pixels[chemin[i]].poids[3] << "]OUEST";
                poids2 = pixels[chemin[i]].poids[3];
            }
            if (poids2 < min2)
                min2 = poids2;
            if (i == chemin.size() - 1) // S
            {
                //cout << ", C'est la fin";
                poids2 = pixels[chemin[i]].poids[4];
            }
            if (poids2 < min2)
                min2 = poids2;
        }

        //cout << endl;

    }

    return min2;
}

bool Graphe::is_in_vect(int n, vector<int> v)
{
    for (int i = 0; i < v.size(); i++)
        if (v[i] == n)
            return true;
    return false;
}

void Graphe::ford_fulkerson_coloration()
{    
    int V = image->hauteur * image->largeur; // Nombre de sommets
    vector<int> S;
    Node* p;
    float inf = numeric_limits<float>::infinity();
    bool changement;

    for (int i = 0; i < V; i++)
    {
        p = &pixels[i];
        p->val = 128;
        if (p->poids[4] > 0 && p->poids[4] < inf)
            S.push_back(i);
    }
    changement = true;
    while (changement)
    {
        changement = false;
        for (int i = 0; i < S.size(); i++)
        {
            p = &pixels[S[i]];
            if (p->val == 128)
            {
                changement = true;
                p->val = 255;
                if (p->utilisable[0] && p->poids[0] > 0 && p->poids[0] < inf
                    && !is_in_vect(get_nord(S[i]), S)) // Exploration branche Nord
                    S.push_back(get_nord(S[i]));
                if (p->utilisable[1] && p->poids[1] > 0 && p->poids[1] < inf
                    && !is_in_vect(get_sud(S[i]), S)) // Exploration branche Sud
                    S.push_back(get_sud(S[i]));
                if (p->utilisable[2] && p->poids[2] > 0 && p->poids[2] < inf
                    && !is_in_vect(get_est(S[i]), S)) // Exploration branche Est
                    S.push_back(get_est(S[i]));
                if (p->utilisable[3] && p->poids[3] > 0 && p->poids[3] < inf
                    && !is_in_vect(get_ouest(S[i]), S)) // Exploration branche Ouest
                    S.push_back(get_ouest(S[i]));
            }
        }
    }
    for (int i = 0; i < V; i++)
    {
        p = &pixels[i];
        if (p->val == 128)
            p->val = 0;
    }
}

void Graphe::ford_fulkerson()
{
    // Construction du graphe orienté (écriture des valeurs dans poids[] et utilisable[])
    ford_fulkerson_construction_graphe();

    /*cout << "Toto" << endl;
    for (int i = 171; i < 201; i++)
        if (i == 171 || i > 197)
        cout << "Pixel : " << i << ", poids[0] : " << pixels[i].poids[0] << ", poids[1] : "
                << pixels[i].poids[1] << ", poids[2] : " << pixels[i].poids[2] << ", poids[3] : "
                << pixels[i].poids[3] << ", poids[4] : " << pixels[i].poids[4] << ", poids[5] : "
                << pixels[i].poids[5] << endl;
    cout << endl;*/

    // Tant qu'il existe un chemin de S à T ne passant pas par un arc de poids nul
    vector<int> chemin;
    float min;
    while ((chemin = ford_fulkerson_get_chemin()).size() > 0)
    {
        /*cout << "Voici le chemin :";
        for (int i = 0; i < chemin.size(); i++)
            cout << " " << chemin[i];
        cout << endl;*/
        // On récupère le poids de l'arc le plus faible du chemin
        min = ford_fulkerson_get_poids_min(chemin);
        cout << "Le min : " << min << endl;

        // Pour chaque arc (A, B) du chemin, enlever min de l'arc et ajouter min sur l'arc (B, A)
        for (int i = 0; i < chemin.size(); i++) // ATTENTION le chemin est à l'envers
        {
            if (i == 0) // Cas du traitement de T
                pixels[chemin[i]].poids[5] -= min;
            if (i == chemin.size() -1) // Cas du traitement de S
                pixels[chemin[i]].poids[4] -= min;
            else if (chemin[i+1] == get_nord(chemin[i])) // Tous les autres cas
            {
                pixels[chemin[i+1]].poids[1] -= min;
                pixels[chemin[i]].poids[0] += min;
            }
            else if (chemin[i+1] == get_sud(chemin[i]))
            {
                pixels[chemin[i+1]].poids[0] -= min;
                pixels[chemin[i]].poids[1] += min;
            }
            else if (chemin[i+1] == get_est(chemin[i]))
            {
                pixels[chemin[i+1]].poids[3] -= min;
                pixels[chemin[i]].poids[2] += min;
            }
            else if (chemin[i+1] == get_ouest(chemin[i]))
            {
                pixels[chemin[i+1]].poids[2] -= min;
                pixels[chemin[i]].poids[3] += min;
            }
        }
        cout << "Toto2" << endl;
        for (int i = 0; i < 16; i++)
            cout << "Pixel : " << i << ", poids[0] : " << pixels[i].poids[0] << ", poids[1] : "
                    << pixels[i].poids[1] << ", poids[2] : " << pixels[i].poids[2] << ", poids[3] : "
                    << pixels[i].poids[3] << ", poids[4] : " << pixels[i].poids[4] << ", poids[5] : "
                    << pixels[i].poids[5] << endl;
        cout << endl;
    }

    ford_fulkerson_coloration();
    
    cout << "C'est fini !" << endl;

}

void Graphe::save(string s)
{
    ofstream file;
    file.open (s);
    file << "P2" << endl
         << image->largeur << " " << image->hauteur << endl
         << image->max << endl;
    for (int i = 0; i < image->largeur*image->hauteur; i++)
        file << pixels[i].val << endl;
    file.close();
}
