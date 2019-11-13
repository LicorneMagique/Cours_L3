/**
 * Réalisé par Julien GIRAUD - 2019
 */

#include <iostream>
#include <iomanip>
#include "avl.h"

using namespace std;

Node::Node(Elem e)
{
    elem = e;
    hauteur = 0;
    fd = nullptr;
    fg = nullptr;
}

Node::Node(const Node* n)
{
    elem = n->elem;
    hauteur = n->hauteur;
    fg = (n->fg != nullptr) ? new Node(n->fg) : nullptr;
    fd = (n->fd != nullptr) ? new Node(n->fd) : nullptr;
}

AVL::AVL()
{
    racine = nullptr;
}

AVL::AVL(const AVL& a)
{
    racine = new Node(a.racine->elem);
    racine->fg = new Node(a.racine->fg);
    racine->fd = new Node(a.racine->fd);
}

AVL::~AVL()
{
    if (racine != nullptr) racine->vide();
}

AVL &AVL::operator=(const AVL &a)
{
    if (this == &a) return *this;

    AVL avl(a);
    
    return avl;
}

bool Node::operator<(const Node &n)
{
    return (elem < n.elem);
}

void AVL::add(const Elem e)
{
    if (racine == nullptr)
        racine = new Node(e);
    else
        racine->add(e);
}

void Node::add(Elem e)
{
    if (e < elem) // Si je dois mettre "e" à gauche
    {
        if (fg == nullptr)
            fg = new Node(e);
        else
        {
            fg->add(e);
            fg->equilibre();
        }
    }
    else
    {
        if (fd == nullptr)
            fd = new Node(e);
        else
        {
            fd->add(e);
            fd->equilibre();
        }
    }
    hauteur = getHeight();
}

void AVL::show()
{
    if (racine != nullptr) racine->show(0);
    cout << endl;
}

void Node::show(int n)
{
    if (fd != nullptr) fd->show(n+1);
    for (int i = 0; i < n; i++) cout << "        ";
    cout << elem << "," << hauteur << endl;
    if (fg != nullptr) fg->show(n+1);
}

void AVL::show_prefix()
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

void AVL::show_infix()
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

void AVL::show_postfix()
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

void AVL::vide()
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

int Node::getHeight() {
    int h = 0;
    if (this != NULL)
        h = max(fg->getHeight() + 1, fd->getHeight() + 1);
    return h;
}

void Node::equilibre()
{
    int bal_factor = getDifference();
    if (bal_factor > 1) {
        if (fg->getDifference() > 0)
            rotationDoubleGauche();
        else
            rotationGauche();
    }
    else if (bal_factor < -1)
    {
        if (fd->getDifference() > 0)
            rotationDroite();
        else
            rotationDoubleDroite();
    }
}

void Node::rotationDroite()
{
    Node *n;
    n = fd;
    fd->rotationDoubleGauche();
    //cout<<"Right-Left Rotation";
    rotationDoubleDroite();
}

void Node::rotationGauche()
{
    Node *n;
    n = fg;
    fg->rotationDoubleDroite();
    //cout<<"Left-Right Rotation";
    rotationDoubleGauche();
}

void Node::rotationDoubleDroite()
{
    Node *n;
    n = fg;
    fd = n->fg;
    n->fg = this;
    //cout<<"Right-Right Rotation"; rr_rotat
}

void Node::rotationDoubleGauche()
{
    Node *n;
    n = fg;
    fg = n->fd;
    n->fd = this;
    //cout<<"Left-Left Rotation"; ll_rotat
}

int Node::getDifference()
{
    return fg->getHeight() - fd->getHeight();
}
