// compiler avec g++ -std=c++11 -g -Wall sched.cpp -pthread -o sched.ex
// #define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <sched.h>
#include <unistd.h>

#include <mutex>
#include <thread>
#include <vector>
#include <sstream>
#include <iostream>

typedef struct {
  int num;
  int nbtours;
  struct timeval tv;
} param_t;


#define handle_error_en(en, msg) \
  if (en != 0) do { fprintf(stderr, "%s %d : %s %s\n", __FILE__, __LINE__, msg, strerror(en)); exit(EXIT_FAILURE); } while (0)

void timevalsub(struct timeval *tv1, const struct timeval *tv2) {
        tv1->tv_sec -= tv2->tv_sec;
        /* Add -1 or 0 to adjust with respect to the µs */
        tv1->tv_sec += (tv1->tv_usec - tv2->tv_usec - 1000000) / 1000000;

        tv1->tv_usec = (tv1->tv_usec - tv2->tv_usec + 1000000) % 1000000;
}

/**
 * Affiche les information d'ordonnancement du thread
 * Cette fonction est faite pour être utilisée en mode multithread
 *
 * @param prefix : un texte a mettre avant les écrits
 */
static void
affiche_attribu_thread(const char *prefix)
{  
  int s, i;
  size_t v;
  void *stkaddr;
  struct sched_param sp;

  pthread_attr_t attr;
  
  s = pthread_getattr_np(pthread_self(), &attr);
  handle_error_en(s, "pthread_getattr_np");

  // on utilise un mutex pour éviter que les affichage se mélange
  // c'est une variable statique pour le partage
  static std::mutex m;
  std::unique_lock<std::mutex> lck(m);

  printf("%sThread attributes:\n", prefix);
  
  s = pthread_attr_getdetachstate(&attr, &i);
  handle_error_en(s, "pthread_attr_getdetachstate");
  printf("%sDetach state        = %s\n", prefix,
	 (i == PTHREAD_CREATE_DETACHED) ? "PTHREAD_CREATE_DETACHED" :
	 (i == PTHREAD_CREATE_JOINABLE) ? "PTHREAD_CREATE_JOINABLE" :
	 "???");
  
  s = pthread_attr_getscope(&attr, &i);
  handle_error_en(s, "pthread_attr_getscope");
  printf("%sScope               = %s\n", prefix,
	 (i == PTHREAD_SCOPE_SYSTEM)  ? "PTHREAD_SCOPE_SYSTEM" :
	 (i == PTHREAD_SCOPE_PROCESS) ? "PTHREAD_SCOPE_PROCESS" :
	 "???");
  
  s = pthread_attr_getinheritsched(&attr, &i);
  handle_error_en(s, "pthread_attr_getinheritsched");
  printf("%sInherit scheduler   = %s\n", prefix,
	 (i == PTHREAD_INHERIT_SCHED)  ? "PTHREAD_INHERIT_SCHED" :
	 (i == PTHREAD_EXPLICIT_SCHED) ? "PTHREAD_EXPLICIT_SCHED" :
	 "???");
  
  s = pthread_attr_getschedpolicy(&attr, &i);
  handle_error_en(s, "pthread_attr_getschedpolicy");
  printf("%sScheduling policy   = %s\n", prefix,
	 (i == SCHED_OTHER) ? "SCHED_OTHER" :
	 (i == SCHED_FIFO)  ? "SCHED_FIFO" :
	 (i == SCHED_RR)    ? "SCHED_RR" :
	 "???");
  s = pthread_attr_getschedparam(&attr, &sp);
  handle_error_en(s, "pthread_attr_getschedparam");
  printf("%sScheduling priority = %d\n", prefix, sp.sched_priority);
  
  s = pthread_attr_getguardsize(&attr, &v);
  handle_error_en(s, "pthread_attr_getguardsize");
  printf("%sGuard size          = %d bytes\n", prefix, (int) v);
  
  s = pthread_attr_getstack(&attr, &stkaddr, &v);
  handle_error_en(s, "pthread_attr_getstack");
  printf("%sStack address       = %p\n", prefix, stkaddr);
  printf("%sStack size          = 0x%x bytes\n", prefix, (int)v);
}

/**
 * @brief Change la politique d'ordonnancement du thread et sa priorité
 *
 * @param policy : la politique à utiliser SHED_FIFO, SHED_RR ou SHED_OTHER
 * @param priorité : un nombre entre 0 (le minimum et 99 le max).
 *                   0 est la seule priorité valide pour les SHED_OTHER
 */
void change_ordonnancement(int policy, int priorite) {
  std::cerr << "###############################" << std::endl;
  std::cerr << "###############################" << std::endl;
  std::cerr << "###                         ###" << std::endl;
  std::cerr << "###                         ###" << std::endl;
  std::cerr << "###   Ce code est à faire   ###" << std::endl;
  std::cerr << "###                         ###" << std::endl;
  std::cerr << "###                         ###" << std::endl;
  std::cerr << "###############################" << std::endl;
  std::cerr << "###############################" << std::endl;

  int last_policy;
  sched_param param;
  int getParam = pthread_getschedparam(pthread_self(), &last_policy, &param);
  param.sched_priority = priorite;
  int setParam = pthread_setschedparam(pthread_self(), policy, &param);
}

void fonction(int num, int nb_tours, int policy, int priorite) {
  struct timeval tv2, tv;

  int i, err;

  
  change_ordonnancement(policy, priorite);

  std::ostringstream s;
  s << num << "\t";
  affiche_attribu_thread(s.str().c_str());

  sleep(1);

  err = gettimeofday(&tv, NULL);
  if (err != 0) {
    perror("gettimeofday");
    exit(EXIT_FAILURE);
  }
  for (i=0; i<nb_tours; i++) {
    int j;

    double sum = 0;
    for(j=0; j<5000000; j++) {
      sum += log(rand());
    }

    err = gettimeofday(&tv2, NULL);
    if (err != 0) {
      perror("gettimeofday");
      exit(EXIT_FAILURE);
    }
    timevalsub(&tv2, &tv);

    fprintf(stdout, "%d : je viens de faire un calcul dont le résultat est %g, il a fallu %ld.%06ld\n", num, sum, tv2.tv_sec, tv2.tv_usec);    
  }

  return;
}

int main(int argc, char* argv[]) {
  int nbtours = 10;

  if (argc == 2) {
    if ((nbtours = atoi(argv[1]))==0) {
      fprintf(stderr, "usage %s <nb tours>\n", argv[0]);
      exit(1);
    }
  }

  std::vector<std::thread> tab;
  
  tab.push_back(std::thread(fonction, tab.size(), nbtours, SCHED_RR, 5));
  tab.push_back(std::thread(fonction, tab.size(), nbtours, SCHED_RR, 5));
  tab.push_back(std::thread(fonction, tab.size(), nbtours, SCHED_FIFO, 5));

  
  for (auto &th : tab) {
    th.join();
  }

  return 0;
}
