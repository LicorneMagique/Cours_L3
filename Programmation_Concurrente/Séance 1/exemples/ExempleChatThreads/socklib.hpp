#pragma once
#include <cerrno>
#include <string>

namespace socklib {
  class ReaderWriter;
  class BufferedReaderWriter;
  
  /**
     @brief fonction générique de la gestion d'erreur
     @param file,ligne : le nom et la ligne du fichier où a lieu l'erreur
     @param msg : le message à afficher en cas d'erreur
     @param cond : la condition (l'erreure est déclanchée si elle est vraie)
     @param errnum : code d'erreur système
     @param exception : si vrai envoie une exception en cas d'erreur,
     sinon, c'est just un warning
  */
  void
  __error_(const char *file, const int ligne, const std::string &msg,
	   bool cond, int errnum, bool exception);
  
  /**
     @brief teste errnum et envoie une exception si errnum est un code d'erreur différent de 0
  */
#define exit_error(msg, cond, errnum) socklib::__error_(__FILE__, __LINE__, (msg), cond, errnum, true)
  /**
     @brief teste errnum et affiche une erreur si errnum est un code d'erreur différent de 0
  */
#define warning_error(msg, cond, errnum) socklib::__error_(__FILE__, __LINE__, (msg), cond, errnum, false)


  /**
   * @brief Cree une socket d'attente pour le serveur sur le port ''port''
   * @param port : le port utilisé
   * @return la socket d'attente
   * @throws une system_error s'il y a un soucis à la création ou une runtime_error
   * si le port est occupé ou ne peux pas être pris
   *
   * En cas d'erreur, un message explicatif est affiché sur la sortie d'erreur 
   * standart
   */
  int CreeSocketServeur(const std::string &port);
  
  /**
   * @brief Crée une socket de client en se connectant à un serveur
   * @param server, port : le serveur et le port à contacter.
   * @return la socket de discution
   * @throws une system_error s'il y a un souci à la création ou une runtime_error
   * si le serveur ne peut pas être contacté
   */
  int CreeSocketClient(const std::string &serveur, const std::string &port);

  
  /**
   * @brief Accepte un nouveau client
   * @param s : la socket d'attente du serveur
   * @return la socket de discution
   * @throws une système error s'il y a un problème
   */
  int AcceptConnexion(int s);

}
