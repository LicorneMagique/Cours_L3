//#include <cstdio>
//#include <cstdlib>
//#include <ctime>
//#include <chrono>
#include <iostream>
#include <iomanip>
#include "table.h"

using namespace std;

Node::Node()
{
    this->active = false;
    this->was_active = false;
    this->occurence_pas = 0;
}

Table::Table(int _hash(Key, int), int _pas(Key, int, int, int, int(Key, int)), const int _size)
{
    this->hash = _hash;
    this->pas = _pas;
    this->size = _size;
    this->tab = new Node[_size];
    this->echec = 0;
}

Table::~Table()
{
    delete this->tab;
}

void Table::show()
{
    Node n;
    cout << setfill(' ') << endl << "indice" << setw(12) << "clé" << setw(14)
         << "valeur" << setw(23) << "occurence(s) : " << this->getOccurence()
         << endl << setfill('-') << setw(55) << "-" << endl;
    for (int i = 0; i < size; i++)
    {
        n = tab[i];
        if (n.active)
            cout << setfill(' ') << setw(6) << i << setw(11) << n.key
                 << setw(14) << n.value << setw(24) << n.occurence_pas << endl;
    }
}

void Table::add(const Key cle, const Value val)
{
    int i = hash(cle, size); // indice d'insertion
    int o = 0; // occurence d'utilisation du ré-hashage
    while (tab[i].active && o < size)
        i = pas(cle, i, ++o, size, hash);
    if (o == size || tab[i].active)
        echec++;
    else
    {
        Node* n = &tab[i];
        n->active = true;
        n->was_active = true;
        n->key = cle;
        n->value = val;
        n->occurence_pas = o;
    }
}

int Table::getOccurence()
{
    int o = 0;
    for (int i = 0; i < size; i++)
    {
        if (tab[i].active)
            o = o + tab[i].occurence_pas;
    }
    return o;
}

int Table::getEchec()
{
    return echec;
}

string Table::getInfo()
{
    return "taille = " + to_string(this->getSize()) + ", " +
        to_string(this->getOccurence()) + " occurence(s), " +
        to_string(this->getEchec()) + " échec(s)";
}

void Table::remove(Key cle)
{
    int i = this->search(cle);
    if (i == -1)
        cout << "La clé " << cle << " n'existe pas" << endl;
    else
    {
        tab[i].active = false;
    }
}

int Table::search(Key cle)
/**
 * Retourne l'indice d'une clé si elle existe, sinon -1
 */
{
    int i = hash(cle, size); // indice d'insertion
    int o = 0; // occurence d'utilisation du ré-hashage
    while (tab[i].was_active && tab[i].key != cle && o < size)
        i = pas(cle, i, ++o, size, hash);
    if (tab[i].active && tab[i].key == cle)
        return i;
    return -1;
}

int Table::getSize()
/**
 * Retourne la taille occupée
 */
{
    int s = 0;
    for (int i = 0; i < size; i++)
    {
        if (tab[i].active)
            s++;
    }
    return s;
}
