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





    if (nouveau_message) { 
       // Il n'y a plus de place
      fprintf(stderr, "Il n'y a plus de place\n");
      exit(1);
    }
    
    nouveau_message = TRUE; // On signale la présence s'un nouveau message

    
    strncpy(message, mess, TAILLE_BUFF); // Copie le nouveau message dans la variable partagée
    

    free(mess);
  }
}

gboolean consomateur(void *rien) {

  
  if (!(nouveau_message)) {
    // il n'y a pas de nouveau message à lire
  } else {
    affiche(message, "# "); //On écrit le message sur la fenêtre précédé de # . 
    nouveau_message = FALSE; // On signale que le message à été lu

  }


  return TRUE; // On retourne TRUE parce que c'est comme ça.
}


int
main (int argc, char *argv[])
{
  std::thread *thr = NULL;

  initialisation(argc, argv);

  if (argc == 2) {
    fprintf(stdout, "Je suis le serveur écoute sur le port %s\n", argv[1]);
  } else {
    fprintf(stdout, "Je suis le client envoie à %s:%s\n", argv[1], argv[2]);

  }
  

  //fonction qui permet d'appeler régulierement le consomateur
  g_timeout_add(5000, //nb de milliseconde entre les appel
		consomateur, // fonction à appeler
		NULL // Argument de la fonction si on en avait besoin
		);
  
  gtk_main ();

  if (argc == 2) {
    // je supprime le thread
    delete(thr);
  }

  return 0;
}

