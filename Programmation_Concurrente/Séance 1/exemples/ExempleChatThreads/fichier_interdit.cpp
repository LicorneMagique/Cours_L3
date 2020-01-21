// Le contenu de ce fichier est hors programme.
// Vous ne devez pas le lire


// Pour GTK

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "socklib.hpp"
#include <sys/types.h>
#include <sys/socket.h>


//Fonction de chat.c
char *ecoute();


#define GLADE_HOOKUP_OBJECT(component,widget,name) \
  g_object_set_data_full (G_OBJECT (component), name, \
    gtk_widget_ref (widget), (GDestroyNotify) gtk_widget_unref)

#define GLADE_HOOKUP_OBJECT_NO_REF(component,widget,name) \
  g_object_set_data (G_OBJECT (component), name, widget)

GtkWindow *win;


// Les fonctions support
GtkWidget*
lookup_widget                          (GtkWidget       *widget,
                                        const gchar     *widget_name)
{
  GtkWidget *parent, *found_widget;

  for (;;)
    {
      if (GTK_IS_MENU (widget))
        parent = gtk_menu_get_attach_widget (GTK_MENU (widget));
      else
        parent = widget->parent;
      if (!parent)
        parent = (GtkWidget*) g_object_get_data (G_OBJECT (widget), "GladeParentKey");
      if (parent == NULL)
        break;
      widget = parent;
    }

  found_widget = (GtkWidget*) g_object_get_data (G_OBJECT (widget),
                                                 widget_name);
  if (!found_widget)
    g_warning ("Widget not found: %s", widget_name);
  return found_widget;
}


// Les fonctions callbacks

void
affiche(const char *text, const char *prefix) {
  GtkTextView *fenaff;
  GtkTextBuffer *tb;
  GtkTextIter iter;
 
  fenaff = GTK_TEXT_VIEW(lookup_widget(GTK_WIDGET(win), "FenAffichage"));
  tb = gtk_text_view_get_buffer(fenaff);
  gtk_text_buffer_get_end_iter(tb, &iter);
  gtk_text_buffer_insert(tb, &iter, prefix, -1);
  gtk_text_buffer_insert(tb, &iter, text, -1);
  gtk_text_buffer_insert(tb, &iter, "\n", -1);
  
}

void
envoie(const char *text) {
  int sock_err;

  int sock = GPOINTER_TO_INT(gtk_object_get_data(GTK_OBJECT(win), "socket"));

  sock_err = send(sock, (char*)text, sizeof(char)*(strlen(text)+1), 0);

  

  if (sock_err < 0)
    perror("sock_err");
  
}

void
on_FenDeLecture_editing_done           (GtkEntry        *editable,
                                        gpointer         user_data)
{
  const gchar *text = gtk_entry_get_text(GTK_ENTRY(editable));

  //  win = gtk_widget_get_toplevel();
  affiche(text,"");
  envoie(text);
  gtk_entry_set_text(GTK_ENTRY(editable), "");
 
  
}

gboolean receive_data_from_client(GIOChannel *source,GIOCondition condition,void *user)
{

  int sock_recv;
  int fin = 0;
  char buff[100];
  GError *err=NULL;
  
  sock_recv = g_io_channel_unix_get_fd(source);
  printf("sock_recv=%d\n",sock_recv);
  int retval = recv(sock_recv, (char*)buff, 100, 0);
  if (retval == -1) {
    perror("recv/serveur");
    fin = 1;
  } else {
    buff[retval] = 0;
    fin = 0;
  }      
  
  if ((retval == 0)||(strcmp(buff, "_DISC_")==0)) {
    printf ("Fermeture de la socket\n");
    fin = 1;
  }

  if (fin) {
    if (shutdown(sock_recv, SHUT_RDWR) == -1) {
      perror("error pour la fermeture de la socket");
    }
    // close(sock_recv);
    printf ("fermeture de la iochanel\n");
    int r = g_io_channel_shutdown (source, FALSE, &err);
    if (r == G_IO_STATUS_ERROR) {
      fprintf(stderr, "Problème à la fermeture du io channel car %s\n", err->message);
    }
    //   printf ("fini\n", sock_recv, buff);
    return FALSE;
  } else {
    affiche(buff, "> ");
    printf ("%d : reçu %s\n", sock_recv, buff);

    return TRUE;
  }
}


gboolean accepter(GIOChannel *source,GIOCondition condition, GtkWindow *window1)
{
  int sock = g_io_channel_unix_get_fd(source);

  printf("on accepte la connexion\n");

  // démarrage du listage (mode server)


  // Attente pendant laquelle le client se connecte
  printf ("Patientez pendant que le client se connecte...\n");

  int csock = socklib::AcceptConnexion(sock);

  GIOChannel* g_test2=g_io_channel_unix_new (csock);
  if (g_test2 == NULL)
    printf("error\n");
  g_io_add_watch_full(g_test2,0,G_IO_IN,(GIOFunc)receive_data_from_client,NULL,NULL);

  gtk_object_set_data(GTK_OBJECT(window1), "socket", GINT_TO_POINTER(csock));
  
  return TRUE;
}





void
on_quitter1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  envoie("_DISC_");
  /* socket = (int) gtk_object_get_data(GTK_OBJECT(win), "socket"); */
  /* close(socket); */
  

  gtk_main_quit();
}


void
on_ecoute1_activate                   (GtkMenuItem     *menuitem,
				       gpointer         user_data) {
  //  int socket = GPOINTER_TO_INT(gtk_object_get_data(GTK_OBJECT(win), "socket"));
  char *mes = ecoute();
  affiche(mes, " # ");
  free(mes);
}


// La creation de la fenetre
GtkWidget*
create_window1 (void)
{
  GtkWidget *window1;
  GtkWidget *vbox2;
  GtkWidget *menubar1;
  GtkWidget *menuitem1;
  GtkWidget *menuitem1_menu;
  GtkWidget *separatormenuitem1;
  GtkWidget *quitter1;
  GtkWidget *ecoute1;
  GtkWidget *image1;
  GtkWidget *scrolledwindow1;
  GtkWidget *FenAffichage;
  GtkWidget *FenDeLecture;
  GtkAccelGroup *accel_group;
  GtkTooltips *tooltips;

  tooltips = gtk_tooltips_new ();

  accel_group = gtk_accel_group_new ();

  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (window1, 500, 250);
  gtk_window_set_title (GTK_WINDOW (window1), "window1");

  vbox2 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox2);
  gtk_container_add (GTK_CONTAINER (window1), vbox2);

  menubar1 = gtk_menu_bar_new ();
  gtk_widget_show (menubar1);
  gtk_box_pack_start (GTK_BOX (vbox2), menubar1, FALSE, FALSE, 0);

  menuitem1 = gtk_menu_item_new_with_mnemonic (("_Fichier"));
  gtk_widget_show (menuitem1);
  gtk_container_add (GTK_CONTAINER (menubar1), menuitem1);

  menuitem1_menu = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem1), menuitem1_menu);

  separatormenuitem1 = gtk_separator_menu_item_new ();
  gtk_widget_show (separatormenuitem1);
  gtk_container_add (GTK_CONTAINER (menuitem1_menu), separatormenuitem1);
  gtk_widget_set_sensitive (separatormenuitem1, FALSE);

  quitter1 = gtk_image_menu_item_new_from_stock ("gtk-quit", accel_group);
  gtk_widget_show (quitter1);
  gtk_container_add (GTK_CONTAINER (menuitem1_menu), quitter1);

  ecoute1 = gtk_image_menu_item_new_with_mnemonic (("Ecoute"));
  gtk_widget_show (ecoute1);
  gtk_container_add (GTK_CONTAINER (menuitem1_menu), ecoute1);
  gtk_tooltips_set_tip (tooltips, ecoute1, ("Pour ecouter sur le reseau"), NULL);
  gtk_widget_add_accelerator (ecoute1, "activate", accel_group,
                              GDK_E, (GdkModifierType) GDK_MOD1_MASK,
                              GTK_ACCEL_VISIBLE);

  image1 = gtk_image_new_from_stock ("gtk-media-play", GTK_ICON_SIZE_MENU);
  gtk_widget_show (image1);
  gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (ecoute1), image1);

  scrolledwindow1 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow1);
  gtk_box_pack_start (GTK_BOX (vbox2), scrolledwindow1, TRUE, TRUE, 0);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolledwindow1), GTK_SHADOW_IN);

  FenAffichage = gtk_text_view_new ();
  gtk_widget_show (FenAffichage);
  gtk_container_add (GTK_CONTAINER (scrolledwindow1), FenAffichage);
  gtk_text_view_set_editable (GTK_TEXT_VIEW (FenAffichage), FALSE);

  FenDeLecture = gtk_entry_new ();
  gtk_widget_show (FenDeLecture);
  gtk_box_pack_start (GTK_BOX (vbox2), FenDeLecture, FALSE, FALSE, 0);
  gtk_entry_set_invisible_char (GTK_ENTRY (FenDeLecture), 8226);

  g_signal_connect ((gpointer) window1, "delete_event",
                    G_CALLBACK (on_quitter1_activate),
                    NULL);
  g_signal_connect ((gpointer) quitter1, "activate",
                    G_CALLBACK (on_quitter1_activate),
                    NULL);
  g_signal_connect ((gpointer) ecoute1, "activate",
                    G_CALLBACK (on_ecoute1_activate),
                    NULL);
  g_signal_connect ((gpointer) FenDeLecture, "activate",
                    G_CALLBACK (on_FenDeLecture_editing_done),
                    NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (window1, window1, "window1");
  GLADE_HOOKUP_OBJECT (window1, vbox2, "vbox2");
  GLADE_HOOKUP_OBJECT (window1, menubar1, "menubar1");
  GLADE_HOOKUP_OBJECT (window1, menuitem1, "menuitem1");
  GLADE_HOOKUP_OBJECT (window1, menuitem1_menu, "menuitem1_menu");
  GLADE_HOOKUP_OBJECT (window1, separatormenuitem1, "separatormenuitem1");
  GLADE_HOOKUP_OBJECT (window1, quitter1, "quitter1");
  GLADE_HOOKUP_OBJECT (window1, ecoute1, "ecoute1");
  GLADE_HOOKUP_OBJECT (window1, image1, "image1");
  GLADE_HOOKUP_OBJECT (window1, scrolledwindow1, "scrolledwindow1");
  GLADE_HOOKUP_OBJECT (window1, FenAffichage, "FenAffichage");
  GLADE_HOOKUP_OBJECT (window1, FenDeLecture, "FenDeLecture");
  GLADE_HOOKUP_OBJECT_NO_REF (window1, tooltips, "tooltips");

  gtk_window_add_accel_group (GTK_WINDOW (window1), accel_group);

  return window1;
}


// fonction pour quiter proprement
void terminaison(int signal) {
  //  int socket = (int) gtk_object_get_data(GTK_OBJECT(win), "socket");

  if (signal != 0) {
    fprintf(stderr, "Le programme se termine car il a recut le signal %d\n", signal);
  } else {
    fprintf(stderr, "Fin du programme\n");
  }

  if ((signal == SIGQUIT)||(signal == SIGTERM)) {
    on_quitter1_activate(NULL, NULL);
  } else {
    exit(1);
  }
}


// La partie initialisation du main
void initialisation(int argc, char* argv[]) {
  // la fonction magique qui fait tout
  GtkWidget *window1;
  int i;
  
  gtk_set_locale ();
  gtk_init (&argc, &argv);
  
  
  // ######################################
  // mise en place de la gestion de signal
  // ######################################
  for (i = 1; i<16; i++) {
    // pour tous les signaux en dessous du numéro 15.
    signal(i, terminaison);
  }

  window1 = create_window1 ();
  gtk_widget_show (window1);

  win = GTK_WINDOW(window1);
  

  if (argc == 2) {
    // C'est le serveur il faut lire le port
    int nport = atoi(argv[1]);
    if (!(nport >= 1024)) {
      fprintf(stderr, "Le port doit être supérieur à 1024\n");
      exit(1);
    }

    int sock = socklib::CreeSocketServeur(argv[1]);
    GIOChannel* channel_sock_serveur = g_io_channel_unix_new (sock);
    g_io_add_watch(channel_sock_serveur,G_IO_IN,(GIOFunc)accepter, window1);
    
  }
  else if (argc == 3) {
    // Création de la socket
    int sock = socklib::CreeSocketClient(argv[1], argv[2]);
    
    gtk_object_set_data(GTK_OBJECT(window1), "socket", GINT_TO_POINTER(sock));
  } 
  else {
    fprintf(stderr,"Usage %s <adresse> <port> : pour le client\n      %s           <port> : pour le serveur\n", argv[0], argv[0]);
    exit(1);
  }

}

