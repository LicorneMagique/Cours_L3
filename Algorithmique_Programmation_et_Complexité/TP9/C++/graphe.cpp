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
            getline(ifs, line); // On vire l'intensité maximale
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

vector<Node*> Graphe::ford_fulkerson_get_chemin() // Version adaptée de l'algorithme de Bellman Ford
// Source : https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/
{
    // Étape 0 : Recherche de la "source du graphe", autrement dit min(S)
    Node* p;
    Node* source = nullptr;
    int src = -1;
    float min = -1;
    for (int i = 0; i < image->hauteur*image->largeur; i++)
    {
        p = &pixels[i];
        if (p->utilisable[4]) // Si le sommet est relié à la source S
            if (min == -1 || min > p->poids[4])
            {
                min = p->poids[4];
                source = &pixels[i];
                src = i;
            }
    }
    cout << "val : " << source->val << ", indice : " << src << endl;

    int V = image->hauteur * image->largeur; // Nombre de sommets
    int E = 6; // Nombre de relations d'un sommet
    float dist[V+1]; // Tableau des distances
  
    // Étape 1 : Initialisation des distances de la source à tous les autres sommets sur INFINI
    float inf = numeric_limits<float>::infinity();
    for (int i = 0; i < V+1; i++)
        dist[i] = inf;
    dist[src] = 0;

    // Étape 2 : Pour chaque arc (A,B) on enregistre les sommets qui donnent les plus courts chemins
    int v;
    float weight;
    int parents[V+1];
    for (int i = 0; i < V - 1; i++) // Il aurait été plus pertinant d'utiliser un tableau pour cette partie...
    {
        p = &pixels[i];
        parents[i] = -1;
        if (p->utilisable[0])
        {
            v = get_nord(i); // Indice de B dans dist[]
            weight = 1/p->poids[0]; // Poids de l'arc (A,B)
            if (dist[i] != inf && dist[i] + weight < dist[v])
            {
                dist[v] = dist[i] + weight;
                parents[v] = i;
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
            }
        }
        // Cas de 4 : Impossible car rien ne va sur S
        if (p->utilisable[5])
        {
            v = V; // Fin du tableau
            weight = 1/p->poids[5]; // Poids de l'arc (A,B)
            if (dist[i] != inf && dist[i] + weight < dist[v])
            {
                dist[v] = dist[i] + weight;
                parents[v] = i;
            }
        }
    }

    int parent = V;
    if (dist[V] < inf)
        while (parents[parent] != -1)
        {
            cout << parents[parent] << " ";
            parent = parents[parent];
        }
    cout << endl;

    vector<Node*> chemin;
    return chemin;
}

void Graphe::ford_fulkerson()
{
    // Construction du graphe orienté (écriture des valeurs dans poids[] et utilisable[])
    ford_fulkerson_construction_graphe();

    // Tant qu'il existe un chemin de S à T ne passant pas par un arc de poids nul
    vector<Node*> chemin;
    int min;
    while ((chemin = ford_fulkerson_get_chemin()).size() > 0)
    {
        // On récupère le poids de l'arc le plus faible
        /*min = ford_fulkerson_get_poids_min(chemin);

        // Pour chaque arc du chemin
        for (int i = 0; i < chemin.size()-1; i++)
            ford_fulkerson_traitement_arc(chemin[i], chemin[i+1]);*/
    }

}

void Graphe::test()
{
    cout << pixels[0].get_poids_S(alpha) << " " << pixels[0].get_poids_T(alpha) << endl;
}
