/**
 * Réalisé par Julien GIRAUD - 2019
 */

#include <iostream>
#include <iomanip>
#include "abrc.h"

using namespace std;

Node::Node(Elem e)
{
    elem = e;
    fd = nullptr;
    fg = nullptr;
    cousu = false;
}

Node::Node(const Node* n)
{
    elem = n->elem;
    fg = (n->fg != nullptr && !cousu) ? new Node(n->fg) : nullptr;
    fd = (n->fd != nullptr && !cousu) ? new Node(n->fd) : nullptr;
}

ABRC::ABRC()
{
    racine = nullptr;
    infixe = nullptr;
}

ABRC::ABRC(const ABRC& a)
{
    racine = new Node(a.racine->elem);
    racine->fg = new Node(a.racine->fg);
    racine->fd = new Node(a.racine->fd);
}

ABRC::~ABRC()
{
    if (racine != nullptr) racine->vide();
}

ABRC &ABRC::operator=(const ABRC &a)
{
    if (this == &a) return *this;

    ABRC abrc(a);

    return abrc;
}

bool Node::operator<(const Node &n)
{
    return (elem < n.elem);
}

void ABRC::add(const Elem e)
{
    if (racine == nullptr)
        racine = new Node(e);
    else
        racine->add(e);
}

void Node::add(Elem e)
{
    if (e < elem) // Si je dois mettre "e" à gauche
        if (fg == nullptr || cousu)
            fg = new Node(e);
        else
            fg->add(e);
    else
        if (fd == nullptr || cousu)
            fd = new Node(e);
        else
            fd->add(e);
}

void ABRC::show()
{
    if (racine != nullptr) racine->show(0);
    cout << endl;
}

void Node::show(int n)
{
    if (fd != nullptr && !cousu) fd->show(n+1);
    for (int i = 0; i < n; i++) cout << "   ";
    cout << elem << endl;
    if (fg != nullptr && !cousu) fg->show(n+1);
}

void ABRC::show_prefix()
{
    if (racine != nullptr) racine->show_prefix();
    cout << endl;
}

void Node::show_prefix()
{
    cout << elem << " ";
    if (fg != nullptr && !cousu) fg->show_prefix();
    if (fd != nullptr && !cousu) fd->show_prefix();
}

void ABRC::show_infix()
{
    if (racine != nullptr) racine->show_infix();
    cout << endl;
}

void Node::show_infix()
{
    if (fg != nullptr && !cousu) fg->show_infix();
    cout << elem << " ";
    if (fd != nullptr && !cousu) fd->show_infix();
}

void ABRC::show_postfix()
{
    if (racine != nullptr) racine->show_postfix();
    cout << endl;
}

void Node::show_postfix()
{
    if (fg != nullptr && !cousu) fg->show_postfix();
    if (fd != nullptr && !cousu) fd->show_postfix();
    cout << elem << " ";
}

void ABRC::vide()
{
    if (racine != nullptr) racine->vide();
    racine = nullptr;
}

void Node::vide()
{
    if (fg != nullptr && !cousu) fg->vide();
    if (fd != nullptr && !cousu) fd->vide();
    delete this;
}

void ABRC::transform_en_ABRC()
{
    racine->transform_en_ABRC(nullptr);
}

void Node::transform_en_ABRC(Node* prec)
{
    if (fg != nullptr) fg->transform_en_ABRC(this);
    if (fd == nullptr)
    {
        cout << elem << ", " << fd << ", " << prec << endl;
        //fd = prec; // fait planter le code...
        cousu = true;
    }
    if (fd != nullptr && !fd->cousu) fd->transform_en_ABRC(prec);
}

void ABRC::show_cousu()
{
    if (infixe == nullptr) cout << "L'arbre n'est pas cousu" << endl;
    else infixe->show_cousu();
    cout << endl;
}

void Node::show_cousu()
{
    cout << elem << " ";
    if (fd != nullptr) fd->show_cousu();
}
