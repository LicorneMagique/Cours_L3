/**
 * Réalisé par Julien GIRAUD - 2019
 */

#include <iostream>
#include <iomanip>
#include "abr.h"

using namespace std;

Node::Node(Elem e)
{
    elem = e;
    fd = nullptr;
    fg = nullptr;
}

Node::Node(const Node* n)
{
    elem = n->elem;
    fg = nullptr;
    fd = nullptr;
    if (n->fg != nullptr) fg = new Node(n->fg);
    if (n->fd != nullptr) fd = new Node(n->fd);
}

ABR::ABR()
{
    racine = nullptr;
}

ABR::ABR(const ABR* a)
{
    racine = new Node(a->racine->elem);
    racine->fg = new Node(a->racine->fg);
    racine->fd = new Node(a->racine->fd);
}

ABR::~ABR()
{
    if (racine != nullptr) racine->vide();
}

ABR &ABR::operator=(const ABR &a)
{
    if (this == &a) return *this;

    racine = new Node(a.racine->elem);
    racine->fg = new Node(a.racine->fg);
    racine->fd = new Node(a.racine->fd);

    return *this;
}

/*Node &Node::operator=(const Node &n)
{
    if (this == &n) return *this;

    elem = n.elem;
    fg = n.fg;
    fd = n.fd;

    return *this;
}*/

bool Node::operator<(const Node &n)
{
    return (elem < n.elem);
}

void ABR::add(const Elem e)
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

void ABR::show()
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

void ABR::show_prefix()
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

void ABR::show_infix()
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

void ABR::show_postfix()
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

void ABR::vide()
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

Node* ABR::get(Elem e)
{
    if (racine != nullptr)
        return racine->get(e);
    return nullptr;
}

Node* Node::get(Elem e)
{
    if (this->elem == e) return this;
    Node* n;
    if (fg != nullptr)
    {
        n = fg->get(e);
        if (n != nullptr) return n;
    }
    if (fd != nullptr)
    {
        n = fd->get(e);
        if (n != nullptr) return n;
    }
    return nullptr;
}
