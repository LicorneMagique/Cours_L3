/**
 * Réalisé par Julien GIRAUD - 2019
 */

#include <queue>
#include "ProdCons.h"

using namespace std;


ProdCons::ProdCons() {
    file = queue<ind>();
}

ProdCons::~ProdCons() {
    delete file;
}

void ProdCons::put(int i) {
    file.push_back(i);
}

int ProdCons::get() {
    return file.pop_front();
}

int ProdCons::getSize() {
    return list.size();
}
