#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iostream>
#include "element.h"
#include "skiplist.h"
 
int main()
{
    int nbSkipList = 100, nbInsertion = 1000, i, j, perf1, perf2;

    std::vector<SkipList*> lists;

    for (i = 0; i < nbSkipList; i++)
    {
        lists.push_back(new SkipList);
    }

    std::chrono::time_point<std::chrono::system_clock> start, end;
    
    // perf1 : insertion des valeurs
    start = std::chrono::system_clock::now();
    for (std::vector<SkipList*>::iterator it = lists.begin() ; it != lists.end(); ++it)
        for (j = 0; j < nbInsertion; j++)
            (*it)->ajout(rand()%1000);
    end = std::chrono::system_clock::now();
    perf1 = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Temps d'insertion moyen : " << perf1 << "ms" << std::endl;

    return 0;
}
