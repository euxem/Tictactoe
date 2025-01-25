// File: helloworld.cc

#include "window.h"

void on_destroy(GtkWidget *widget, gpointer data) {
  gtk_main_quit();
}

void initWindow(GtkWidget*& window) {
  // Crée une fenêtre
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Exemple GTK+ en C++");
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
  gtk_widget_set_size_request(window, 400, 300);

  // Connecte l'événement "destroy" pour fermer l'application
  g_signal_connect(window, "destroy", G_CALLBACK(on_destroy), NULL);
}
