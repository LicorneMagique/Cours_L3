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
    this->occurence_pas = 0;
}

Table::Table(int _hash(Key, int), int _pas(Key, int, int, int), const int _size)
{
    this->hash = _hash;
    this->pas = _pas;
    this->size = _size;
    this->tab = new Node[_size];
}

Table::~Table()
{
    delete this->tab;
}

void Table::show()
{
    Node n;
    cout << setfill(' ') << endl << "indice" << setw(12) << "clé" << setw(14)
         << "valeur" << setw(20) << "occurence(s) : " << this->getOccurence()
         << endl << setfill('-') << setw(51) << "-" << endl;
    for (int i = 0; i < size; i++)
    {
        n = tab[i];
        if (n.active)
            cout << setfill(' ') << setw(6) << i << setw(11) << n.key
                 << setw(14) << n.value << setw(15) << n.occurence_pas << endl;
    }
}

void Table::add(const Key cle, const Value val)
{
    int i = hash(cle, size); // indice d'insertion
    int o = 0; // occurence d'utilisation du ré-hashage
    while (tab[i].active && o < size)
    {
        i = pas(cle, i, ++o, size);
    }
    if (o == size)
        cout << "Plus de place : " << cle << "/" << val << endl;
    else
    {
        Node* n = &tab[i];
        n->active = true;
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
            o++;
    }
    return o;
}
