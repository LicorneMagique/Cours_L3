// LIFAP6 - Automne 2017 - R. Chaine
 
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "element.h"
#include "skiplist.h"
 
int main()
{
  std::srand(std::time(nullptr));
 
  SkipList lili;
  std::printf("Lili\n");
  lili.affichage();
  for(int i = 0; i < 5; i++)
    lili.ajout(i);
  lili.affichage();
  SkipList lala(lili);
  std::printf("Lala\n");
  lala.affichage();
  lala.vide();
  lala.affichage();
  std::printf("Lili\n");
  lili.affichage();
  std::printf("Recherche 2 : %d\n", lili.rechercheElement(2));
  lili.supprimerElement(3);
  lili.affichage();
   
  return 0;
}
