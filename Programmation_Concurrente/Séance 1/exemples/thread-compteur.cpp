// g++ -std=c++11 -pthread thread-compteur.cpp
#include <thread>
#include <iostream>
using namespace std;
#define NB 100000000

class Compteur {
public:
  void incr() {
    valeur++;
  }
  Compteur() {
    valeur = 0;
  }
  int valeur;
};

void compte (Compteur &c) {
  for (int i = 0; i < NB; ++i)
    c.incr();
}

int main() {
  Compteur c;
  thread t1(compte, ref(c));
  thread t2(compte, ref(c));
  t1.join();
  t2.join();
  cout << c.valeur << endl;
}
