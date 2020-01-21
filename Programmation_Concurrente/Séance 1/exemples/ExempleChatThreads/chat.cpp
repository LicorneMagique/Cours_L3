#include <unistd.h>
#include <stdlib.h>

#include <gtk/gtk.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <thread>
#include <mutex>
#include <condition_variable>

#define TAILLE_BUFF 100



// Fonctions du fichier interdit
extern GtkWindow *win;
void initialisation(int argc, char* argv[]);
void
affiche(const char *text, const char *prefix);
void terminaison(int);

// Les variables globales pour l'échange
int nouveau_message = FALSE;
char message[TAILLE_BUFF];
std::mutex m;
std::condition_variable cond;

char * ecoute() {
  // Cette fonction est appellée quand on clique sur le bouton ecoute
  // Elle lit sur la socket 
  //
  // On retrouve la socket
  int socket = GPOINTER_TO_INT(gtk_object_get_data(GTK_OBJECT(win), "socket"));

  char *buff = (char *) malloc(TAILLE_BUFF*sizeof(char));

  // On lit
  int retval = recv(socket, (char*)buff, TAILLE_BUFF, 0);
  if ( retval == -1 ) {
    perror("probleme de réception sur le client");

    terminaison(0);
  }

  buff[retval] = 0;
  
  return buff;
}

void producteur(const char *argument){
  fprintf(stdout, "Lancement du producteur avec l'argument %s\n", argument);
  char * mess;

  while (1) {
    mess = ecoute();


    //########################################################
    // part 3
    // Décomenter pour mettre en place les mutex
    // m.lock();
    //# Fin ##################################################
    //########################################################
    // part 3.ter
    // Décomenter pour mettre en place les mutex à libération automatique
    std::unique_lock<std::mutex> unlck(m);
    //# Fin ##################################################



    if (nouveau_message) { 
       // Il n'y a plus de place
      fprintf(stderr, "Il n'y a plus de place\n");
      //########################################################
      // part 4
      // Commenter ça pour mettre en place les variables de condition
      
      //      exit(1);
      // Décommenter pour mettre en place les variables de condition
      cond.wait(unlck);
      //# Fin ##################################################

    }
    
    nouveau_message = TRUE; // On signale la présence s'un nouveau message

    //########################################################
    // part 2
    // Décomenter pour tester la section critique
    usleep(50000);
    //# Fin ##################################################
    
    strncpy(message, mess, TAILLE_BUFF); // Copie le nouveau message dans la variable partagée
    
    //########################################################
    // part 3
    // Décommenter pour mettre en place les mutexes
    //    m.unlock();
    // part 3.ter
    fprintf(stderr, "suppression automatique du unique_lock\n");
    //# Fin ##################################################

    free(mess);
  }
}

gboolean consommateur(void *rien) {

  //########################################################
  // part 3
  // Décomenter pour mettre en place les mutex
  // m.lock();
  //########################################################
  // part 3.bis
  // Mettre à la place de lock pour une attente active
  if (!m.try_lock()) {
    fprintf(stdout, "section occupée !\n");
    return TRUE;
  }
  fprintf(stdout, "section libre !\n");
  //# Fin ##################################################
  
  if (!(nouveau_message)) {
    // il n'y a pas de nouveau message à lire
  } else {
    affiche(message, "# "); //On écrit le message sur la fenêtre précédé de # . 
    nouveau_message = FALSE; // On signale que le message à été lu

    //########################################################
    // part 4
    // Décomenter pour mettre en place les variables de condition
    cond.notify_one();
    //# Fin ##################################################
  }

  //########################################################
  // part 3
  // Décomenter pour mettre en place les mutex
  m.unlock();
  //# Fin ##################################################

  return TRUE; // On retourne TRUE parce que c'est comme ça.
}


int
main (int argc, char *argv[])
{
  std::thread *thr = NULL;

  initialisation(argc, argv);

  if (argc == 2) {
    fprintf(stdout, "Je suis le serveur, écoute sur le port %s\n", argv[1]);
  } else {
    fprintf(stdout, "Je suis le client, envoi à %s:%s\n", argv[1], argv[2]);

    //########################################################
    // part 1
    // Décomenter pour lancer les threads
    thr = new std::thread(producteur, "coucou");
    //# Fin ##################################################
  }
  

  //fonction qui permet d'appeler régulierement le consommateur
  g_timeout_add(5000, //nb de milliseconde entre les appel
		consommateur, // fonction à appeler
		NULL // Argument de la fonction si on en avait besoin
		);
  
  gtk_main ();

  if (argc == 2) {
    // je supprime le thread
    delete(thr);
  }

  return 0;
}

