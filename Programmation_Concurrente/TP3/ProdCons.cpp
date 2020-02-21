/**
 * Réalisé par Julien GIRAUD - 2019
 */

#include <iostream>
#include <condition_variable>

#include "ProdCons.h"

using namespace std;


ProdCons::ProdCons(int t) {
    file = queue<rect>();
    taille_max = t;
}

ProdCons::~ProdCons(){}

void ProdCons::put(rect i) {
    unique_lock<std::mutex> l(m);
    while (file.size() == taille_max) {
        plein.wait(l);
    }
    file.push(i);
    vide.notify_one();
}

rect ProdCons::get() {
    unique_lock<std::mutex> l(m);
    while (file.size() == 0) {
        vide.wait(l);
    }
    rect i = file.front();
    file.pop();
    plein.notify_one();
    return i;
}

int ProdCons::get_size() {
    return file.size();
}

bool ProdCons::is_empty() {
    return file.empty();
}

condition_variable& ProdCons::getVide() {
    return std::ref(vide);
}

condition_variable& ProdCons::getPlein() {
    return std::ref(plein);
}
