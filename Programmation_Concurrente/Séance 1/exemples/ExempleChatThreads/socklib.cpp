#include "socklib.hpp"
#include <system_error>
#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include <string>

void
socklib::__error_(const char *file, const int ligne, const std::string &msg, bool cond, int errnum, bool exception) {
    
  if (cond) {
    // il y a bien une erreur
    std::ostringstream c;
    if (exception) {
      c <<  "\033[31;11mERREUR\033[00m";
    } else {
      c <<  "\033[34;11mWARNING\033[00m";
    }
    c << " fichier " << file << " ligne " <<  ligne << " : ";
    if (errnum != 0) {
      std::system_error err = std::system_error(errno, std::system_category(), msg);
      c << err.what() << std::endl;
      std::cerr << c.str();
      if (exception) {
	throw err;
      }
    } else {
      std::runtime_error err = std::runtime_error(msg);
      c << err.what() << std::endl;
      std::cerr << c.str();
      if (exception) {
	throw err;
      }
    }
  }
}


int
socklib::CreeSocketServeur(const std::string &port) {
  // la socket résultat
  int s = -1;
  // structure pour faire la demande de port
  struct addrinfo hints;
  // structure pour stocker et lire les résultats
  struct addrinfo *result, *rp;
  // variables pour tester si les fonctions donnent un résultats ou une erreur 
  int bon, res;
  // Des variables pour contenir des adresses de machines et des numeros de ports afin de les afficher
  char hname[NI_MAXHOST], sname[NI_MAXSERV];

  // ######################################
  // mise en place de la connexion
  // ######################################
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;     /* IPv4 ou IPv6 */
  hints.ai_socktype = SOCK_STREAM; /* socket flux connectée */
  hints.ai_flags = AI_PASSIVE;     /* Les signifie que toutes les addresses de la machine seront utilisées */
  hints.ai_protocol = 0;           /* Any protocol */

  // on effectue la demande pour le port demandé

  res = getaddrinfo(NULL, port.c_str(), &hints, &result);
  if (res != 0) { // c'est une erreur
    std::ostringstream c;
    c << "getaddrinfo sur le port '"<< port << "': " << gai_strerror(res);
    exit_error(c.str().c_str(), true, 0);
  }
  
  // si res = 0 le véritable résultat de la fontion est l'argument result
  // qui contient une liste d'addresses correspondant à la demande. On va les
  // tester jusqu'à en trouver une qui convient
  rp = result;
  bon = 0;
  while (rp != NULL) { // on parcourt la liste 
    int yes = 1;

    s = socket(rp->ai_family, rp->ai_socktype,rp->ai_protocol);
    // si le résultat est -1 cela n'a pas fonctionné on recommence avec la prochaine
    if (s == -1) {
      warning_error("Création de la socket", true, errno); 
      continue;
    }
    
    // partie optionnelle pour éviter d'être rejeté par le système si le précédant test a planté
    res = setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &yes,
		     sizeof(int));
    if (res == -1) {
      warning_error("setsockopt", true, errno); 
      continue;
    }
    // fin de la partie optionnelle

    // si la socket a été obtenue, on essaye de réserver le port
    res = bind(s, rp->ai_addr, rp->ai_addrlen);
    if (res == 0 ) {// cela a fonctionné on affiche l'information
      bon = 1;

      // on récupère des informations affichables
      res = getnameinfo(rp->ai_addr, rp->ai_addrlen,
			hname, NI_MAXHOST,
			sname, NI_MAXSERV,
			NI_NUMERICSERV|NI_NUMERICHOST);
      if (res != 0) {
	std::ostringstream c;
	c << "getnameinfo: " << gai_strerror(res);
	exit_error(c.str().c_str(), true, 0);
      }
      std::cerr << "La socket " << s
		<< " est maintenant en attente sur l'adresse "
		<< hname << ":" << sname << std::endl;
      break;
    }
    else { // sinon le bind a été impossible, il faut fermer la socket
      warning_error("Imposible de réserver l'adresse", true, errno);
      close (s);
    }
    
    rp = rp->ai_next;
  }

  if (bon == 0) { // Cela n'a jamais fonctionné
    exit_error("Impossible de faire un bind", true, 0);
  }
  
  // on libère la structure devenue inutile
  freeaddrinfo(result);
  
  res = listen (s, 42);
  exit_error("listen", res == -1, errno);

  return s;
}

int
socklib::CreeSocketClient(const std::string &host, const std::string &port) {
  // structure pour faire la demande
  struct addrinfo hints;
  // structure pour stocker et lire les résultats
  struct addrinfo *result, *rp;
  // socket  (s)
  int s=-1;
  // variables pour tester si les fonctions donnent un résultats ou une erreur
  int res;
  int bon;
  // Des variable pour contenir de adresse de machine et des numero de port afin de les afficher
  char hname[NI_MAXHOST], sname[NI_MAXSERV];


  // on rempli la structure hints de demande d'adresse
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;    /* IPv4 ou IPv6 */
  hints.ai_socktype = SOCK_STREAM; /* socket flux connectée */
  hints.ai_flags = 0;  
  hints.ai_protocol = 0;          /* Any protocol */
  hints.ai_addrlen = 0; 
  hints.ai_addr = NULL;           
  hints.ai_canonname = NULL;
  hints.ai_next = NULL;
 
  res = getaddrinfo(host.c_str(), port.c_str(), &hints, &result);
  if (res != 0) { // c'est une erreur
    std::ostringstream c;
    c << "getaddrinfo: pour le client sur " << host << ":" << port << " " << gai_strerror(res);
    exit_error(c.str().c_str(), true, 0);
  }
  
  // si res = 0 le véritable résultat de la fontion est l'argument result
  // qui contient une liste d'addresses correspondant à la demande. On va les
  // tester jusqu'a trouver une qui convient
  rp = result;
  bon = 0;
  while (rp != NULL) {
    // on parcourt la liste

    // on récupère des informations affichables
    res = getnameinfo(rp->ai_addr, rp->ai_addrlen,
		      hname, NI_MAXHOST,
		      sname, NI_MAXSERV,
		      NI_NUMERICSERV|NI_NUMERICHOST);
    if (res != 0) {
      std::ostringstream c;
      c << "getnameinfo: " << gai_strerror(res);
      exit_error(c.str().c_str(), true, 0);
    }
    std::cerr << "On tente l'adresse " << hname
	      << " sur le port " << sname << "..." << std::endl;
    
    // on essaye
    s = socket(rp->ai_family, rp->ai_socktype,rp->ai_protocol);
    // si le résultat est -1 cela n'a pas fonctionné on recommence avec la prochaine
    if (s == -1) {
      warning_error("Création de la socket", true, errno);
      continue;
    }    
   
    // si la socket a été obtenue, on essaye de se connecter
    res = connect(s, rp->ai_addr, rp->ai_addrlen);
    if (res == 0 ) {// cela a fonctionné on est connecté
      bon = 1;
      std::cerr <<  "OK" << std::endl;
      break; 
    }
    else { // sinon le bind a été impossible, il faut fermer la socket
      warning_error("Connection impossible" , true, errno);
      close (s);
    }

    rp = rp->ai_next;
  }

  if (bon == 0) { // Cela n'a jamais fonctionné
    exit_error("Aucune connexion possible", true, 0);
  }
  
  freeaddrinfo(result);           /* No longer needed */

  return s;
}

int
socklib::AcceptConnexion(int s){
  int sClient;
  int res;
  char host[NI_MAXHOST], service[NI_MAXSERV];
  struct sockaddr_storage tadr;
  socklen_t tadr_len = sizeof(struct sockaddr_storage);

  sClient = accept(s, (struct sockaddr*) &tadr, &tadr_len);
  if (sClient == -1) {
    exit_error("Problème avec le accept", true, 0);
  }

  res = getnameinfo((struct sockaddr*) &tadr, tadr_len, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICSERV);
  if(res!=0){
    std::ostringstream c;
    c << "getnameinfo: " << gai_strerror(res);
    exit_error(c.str().c_str(), true, res);
  }
  
  std::cerr << "log : connexion depuis " << host << ":" << service << std::endl;

  return sClient;
}

