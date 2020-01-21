// g++ -std=c++11 -pthread thread-compteur.cpp
#include <thread>
#include <iostream>
using namespace std;
#define NB 100000000
#include <mutex>

#include <condition_variable>
struct Compteur {
  mutex m;
  condition_variable c; // Déclaration
  int valeur = 0;
  void incr() {
    unique_lock<std::mutex> l(m);
    valeur++;
    c.notify_one(); // Réveiller decr()
  }
  void decr() {
    unique_lock<std::mutex> l(m);
    while (!(valeur > 0)) {
      c.wait(l); // Attendre incr()
    }
    valeur--;
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
