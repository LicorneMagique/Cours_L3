// g++ -std=c++11 -pthread thread-compteur.cpp
#include <thread>
#include <iostream>
#include <assert.h>
using namespace std;
#define NB 100000000

#include <mutex>

class Compteur {
public:
  mutex m;
  int valeur = 0;
  void incr() {
    unique_lock<std::mutex> l(m);
    valeur++;
  }
  void decr() {
    unique_lock<std::mutex> l(m);
    valeur--;
    //assert(valeur >= 0); // Temporaire
  }
};

void compte (Compteur &c) {
  for (int i = 0; i < NB; ++i)
    c.incr();
}

void decompte (Compteur &c) {
  for (int i = 0; i < NB; ++i)
    c.decr();
}

int main() {
  Compteur c;
  thread t1(compte, ref(c));
  thread t2(decompte, ref(c));
  t1.join();
  t2.join();
  cout << c.valeur << endl;
}
