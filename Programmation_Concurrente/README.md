# Programmation Concurrente

Cours de [Matthieu Moy](https://asr-lyon1.gitlabpages.inria.fr/prog-concurrente/)

## Séance 1

Pour l'exemple du cours il faut installer ```libgtk2.0-dev``` pour que ça compile

**La section critique** : une portion du code dans laquelle on interdit d'avoir plusieurs threads en même temps → Mutex

```C++
// Il faut utiliser la classe mutex
#include <mutex>

// Utilisation
std::mutex g_pages_mutex;
std::thread t1(nom_fonction, paramètres_fonction);
join();
lock();
unlock();
```
