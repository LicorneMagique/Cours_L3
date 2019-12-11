/**
 * Réalisé par Julien GIRAUD - 2019
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include "graphe.h"

using namespace std;

Image::Image(const string& adresse)
{
    ifstream ifs(adresse);
    string line;
    int i = -1;

    while(getline(ifs, line))
    {
        if (i == -1 && line[0] != '#' && line.length() > 3 and line[3] == ' ')
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
    val = -1;
    sud = nullptr;
    nord = nullptr;
    est = nullptr;
    ouest = nullptr;
    flux = new int[6]{0, 0, 0, 0, 0, 0};
}

Node::Node(int v)
{
    val = v;
    sud = nullptr;
    nord = nullptr;
    est = nullptr;
    ouest = nullptr;
}

Graphe::Graphe(Image im)
{
    int indice, i2;
    image = new Image(im);
    S = new Node[im.hauteur*im.largeur];
    for (int i = 0; i < im.hauteur; i++)
        for (int j = 0; j < im.largeur; j++)
        {
            indice = i*im.largeur + j;
            S[indice].val = im.pixels[indice];
            i2 = get_sud(indice);
            S[indice].sud = (i2 != -1) ? new Node(im.pixels[i2]) : nullptr;
            i2 = get_nord(indice);
            S[indice].nord = (i2 != -1) ? new Node(im.pixels[i2]) : nullptr;
            i2 = get_est(indice);
            S[indice].est = (i2 != -1) ? new Node(im.pixels[i2]) : nullptr;
            i2 = get_ouest(indice);
            S[indice].ouest = (i2 != -1) ? new Node(im.pixels[i2]) : nullptr;
        }
}

Graphe::~Graphe()
{
    delete S;
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
            cout << "Pixel : " << indice+1 << ", Val : " << S[indice].val;
            cout << ", Nord : ";
            if (S[indice].nord == nullptr)
                cout << "vide";
            else
                cout << S[indice].nord->val;
            cout << ", Sud : ";
            if (S[indice].sud == nullptr)
                cout << "rien";
            else
                cout << S[indice].sud->val;
            cout << ", Est : ";
            if (S[indice].est == nullptr)
                cout << "rien";
            else
                cout << S[indice].est->val;
            cout << ", Ouest : ";
            if (S[indice].ouest == nullptr)
                cout << "rien";
            else
                cout << S[indice].ouest->val;
            cout << endl;
        }
}

void Graphe::show_info()
{
    cout << "H : " << image->hauteur << ", L : " << image->largeur << endl;
}
