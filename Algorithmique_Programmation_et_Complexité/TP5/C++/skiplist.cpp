#include <cstdio>
#include <cstdlib>
#include <vector>
#include "skiplist.h"
 
SkipList::SkipList()
{
    this->ad = new Cellule;
    this->ad->suivants.push_back(nullptr);
}
 
SkipList::SkipList(const SkipList& l)
{
    this->ad = new Cellule;
    this->ad->suivants.push_back(nullptr);
    Cellule* tempCel = l.ad->suivants[0];
    while(tempCel != nullptr)
    {
        this->ajout(tempCel->info);
        tempCel = tempCel->suivants[0];
    }
}
 
SkipList::~SkipList()
{
    this->vide();
}
 
void SkipList::ajout(const Elem& e)
{
    std::vector<Cellule*> savedCels;
    Cellule* tempCel = this->ad;
    for(int i = this->ad->suivants.size()-1; i >= 0; i--)
    {
        while(tempCel->suivants[i] != nullptr && tempCel->suivants[i]->info < e)
        { tempCel = tempCel->suivants[i]; }
        savedCels.push_back(tempCel);
    }
 
    Cellule* newCel = new Cellule;
    newCel->info = e;
    newCel->suivants.push_back(tempCel->suivants[0]);
    tempCel->suivants[0] = newCel;
 
    for(int i = 1; rand()%2 == 1; i++)
    {
        if(i >= this->ad->suivants.size())
        {
            this->ad->suivants.push_back(newCel);
            newCel->suivants.push_back(nullptr);
        }
        else
        {
            newCel->suivants.push_back(savedCels[savedCels.size()-i-1]->suivants[i]);
            savedCels[savedCels.size()-i-1]->suivants[i] = newCel;
        }
    }
}
 
void SkipList::affichage() const
{
    Cellule* tempCel = this->ad;
 
    printf("Affichage liste :\n");
    while(tempCel->suivants[0] != nullptr)
    {
        tempCel = tempCel->suivants[0];
        printf("%d -> ", tempCel->info);
    }
    printf("nullptr\n\n");
}
 
bool SkipList::testVide() const
{
    return this->ad->suivants[0] == nullptr;
}
 
void SkipList::vide()
{
    Cellule* tempCel = this->ad->suivants[0];
    while(tempCel != nullptr)
    {
        Cellule* toFree = tempCel;
        tempCel = tempCel->suivants[0];
        delete toFree;
    }
    this->ad->suivants.clear();
    this->ad->suivants.push_back(nullptr);
}
 
Cellule* SkipList::rechercheElement(const Elem& e) const
{
    Cellule* tempCel = this->ad;
    for(int i = this->ad->suivants.size()-1; i >= 0; i--)
    {
        while(tempCel->suivants[i] != nullptr && tempCel->suivants[i]->info <= e)
        { tempCel = tempCel->suivants[i]; }
    }
    return tempCel;
}
 
void SkipList::supprimerElement(const Elem& e)
{
    std::vector<Cellule*> savedCels;
    Cellule* tempCel = this->ad;
    for(int i = this->ad->suivants.size()-1; i >= 0; i--)
    {
        while(tempCel->suivants[i] != nullptr && tempCel->suivants[i]->info < e)
        { tempCel = tempCel->suivants[i]; }
        savedCels.push_back(tempCel);
    }
 
    if(tempCel->suivants[0] != nullptr && tempCel->suivants[0]->info == e)
        tempCel = tempCel->suivants[0];
    else
        return;
 
    for(int i = 0; i < tempCel->suivants.size(); i++)
    {
        savedCels[savedCels.size() - 1 - i]->suivants[i] = tempCel->suivants[i];
    }
    delete tempCel;
}
