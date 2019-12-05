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
        }
        else if (i >= 0 && line[0] != '#')
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
}


Graphe::Graphe(Image im)
{
    int indice, i2;
    image = im;
    tous_les_noeuds = new Node[im.hauteur*im.largeur];
    for (int i = 0; i < im.hauteur; i++)
        for (int j = 0; j < im.largeur; j++)
        {
            indice = i*im.largeur + j;
            tous_les_noeuds[indice].val = im.pixels[indice];
            i2 = get_sud(indice);
            if (i2 != -1) tous_les_noeuds[indice].sud = i2;
            i2 = get_nord(indice);
            if (i2 == -1) tous_les_noeuds[indice].nord = i2;
            i2 = get_est(indice);
            if (i2 == -1) tous_les_noeuds[indice].est = i2;
            i2 = get_ouest(indice);
            if (i2 == -1) tous_les_noeuds[indice].ouest = i2;
        }
}

Graphe::~Graphe()
{
    delete tous_les_noeuds;
}

int Graphe::get_sud(int i)
{
    if (i < image->largeur)
        return -1;
    return i - image->largeur;
}

int Graphe::get_nord(int i)
{
    if (i < image->largeur * (image->hauteur-1))
        return -1;
    return i + image->largeur;
}

int Graphe::get_est(int i)
{
    ;
}

int Graphe::get_ouest(int i)
{
    ;
}

/*
Graphe &Graphe::operator=(const Graphe &a)
{
    if (this == &a) return *this;

    Graphe graphe(a);
    
    return graphe;
}

bool Node::operator<(const Node &n)
{
    return (elem < n.elem);
}

void Graphe::add(const Elem e)
{
    if (racine == nullptr)
        racine = new Node(e);
    else
        racine->add(e);
}

void Node::add(Elem e)
{
    if (e < elem) // Si je dois mettre "e" à gauche
        if (fg == nullptr)
            fg = new Node(e);
        else
            fg->add(e);
    else
        if (fd == nullptr)
            fd = new Node(e);
        else
            fd->add(e);
}

void Graphe::show()
{
    if (racine != nullptr) racine->show(0);
    cout << endl;
}

void Node::show(int n)
{
    if (fg != nullptr) fg->show(n+1);
    for (int i = 0; i < n; i++) cout << "   ";
    cout << elem << endl;
    if (fd != nullptr) fd->show(n+1);
}

void Graphe::show_prefix()
{
    if (racine != nullptr) racine->show_prefix();
    cout << endl;
}

void Node::show_prefix()
{
    cout << elem << " ";
    if (fg != nullptr) fg->show_prefix();
    if (fd != nullptr) fd->show_prefix();
}

void Graphe::show_infix()
{
    if (racine != nullptr) racine->show_infix();
    cout << endl;
}

void Node::show_infix()
{
    if (fg != nullptr) fg->show_infix();
    cout << elem << " ";
    if (fd != nullptr) fd->show_infix();
}

void Graphe::show_postfix()
{
    if (racine != nullptr) racine->show_postfix();
    cout << endl;
}

void Node::show_postfix()
{
    if (fg != nullptr) fg->show_postfix();
    if (fd != nullptr) fd->show_postfix();
    cout << elem << " ";
}

void Graphe::vide()
{
    if (racine != nullptr) racine->vide();
    racine = nullptr;
}

void Node::vide()
{
    if (fg != nullptr) fg->vide();
    if (fd != nullptr) fd->vide();
    delete this;
}
*/
