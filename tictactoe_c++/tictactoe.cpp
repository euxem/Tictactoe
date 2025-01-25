#include "tictactoe.h"
#include "window.h"
#include "button.h"
#include "grid.h"
#include "gridUI.h"

#include <iostream>
#include <string>

static GtkWidget* window;
static Grid* game;

Grid* getGrid(){
  return game;
}

void changeMenu(GtkWidget *widget, gpointer data) {
  gtk_container_foreach(GTK_CONTAINER(window), (GtkCallback)gtk_widget_destroy, NULL);
  ((void (*)())data)();
}

void mainMenu(){
  Bouton playButton("Play", &changeMenu, 200, 0, (void*)&gameMenu);
  Bouton exitButton("Exit", &on_destroy, 200, 0, NULL);
  GtkWidget *Title = gtk_label_new("TicTacToe");
  GtkWidget *spacerLabel = gtk_label_new("");

  // Utilisation de CSS pour modifier la police
  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_data(provider, 
      "label { font-size: 40px; font-weight: bold; }", 
      -1, NULL);

  GtkStyleContext *context = gtk_widget_get_style_context(Title);
  gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  
  GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget *buttonBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);;

  // Ajouter le label et la grille à la boîte
  gtk_box_pack_start(GTK_BOX(vbox), spacerLabel, FALSE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(vbox), Title, FALSE, FALSE, 20); // Le label est ajouté en haut, sans expansion
  gtk_box_pack_start(GTK_BOX(vbox), buttonBox, TRUE, TRUE, 0); // La grille occupe tout l'espace restant

  // Création de la grille
  gtk_widget_set_halign(buttonBox, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(buttonBox, GTK_ALIGN_CENTER);

  // Ajout des boutons à la grille
  gtk_box_pack_start(GTK_BOX(buttonBox), playButton.getButton(), FALSE, FALSE, 0); // Col 0, Ligne 0
  gtk_box_pack_start(GTK_BOX(buttonBox), exitButton.getButton(), FALSE, FALSE, 0); // Col 1, Ligne 0

  gtk_container_add(GTK_CONTAINER(window), vbox);

  // Création de la grille
  gtk_widget_set_halign(Title, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(Title, GTK_ALIGN_CENTER);

  // Affiche tous les widgets
  gtk_widget_show_all(window);
}

// Fonction principale du menu du jeu
void gameMenu() {
  initNstate();
  game->resetGrid();
  GtkWidget *label = gtk_label_new("Tour des croix");
  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_data(provider, 
      "label { font-size: 12px; font-weight: bold; }", 
      -1, NULL);
  GtkStyleContext *context = gtk_widget_get_style_context(label);
  gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  Bouton exit("Retour au menu principal", &changeMenu, 200, 0, (void*)&mainMenu);
  Bouton newGame("Nouvelle partie", &changeMenu, 200, 0, (void*)&gameMenu);
  GtkWidget *grid = gtk_grid_new();
  GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  GtkWidget *aspect_frame = gtk_aspect_frame_new(NULL, 0.5, 0.5, 1.0, TRUE);
  // Appliquer un style CSS pour enlever la bordure
  provider = gtk_css_provider_new();
  gtk_css_provider_load_from_data(provider, "* { border: none; }", -1, NULL);
  context = gtk_widget_get_style_context(aspect_frame);
  gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_container_add(GTK_CONTAINER(aspect_frame), grid);

  // Crée la grille avec le constructeur de la classe Grid
  GridUI gameUi(grid, true);

  // Configure l'expansion de la grille
  gtk_widget_set_hexpand(grid, TRUE);
  gtk_widget_set_vexpand(grid, TRUE);

  // Ajoute les widgets au layout vertical
  gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), aspect_frame, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
  gtk_box_pack_end(GTK_BOX(hbox), exit.getButton(), FALSE, FALSE, 0);
  gtk_box_pack_end(GTK_BOX(hbox), newGame.getButton(), FALSE, FALSE, 0);

  // Ajoute la boîte verticale à la fenêtre
  gtk_container_add(GTK_CONTAINER(window), vbox);
  gtk_widget_show_all(window);
}

void finGame(){
  GtkWidget *label;
  switch (game->checkWin()) {
  case CROSS:
    label = gtk_label_new("Victoire des croix");
    break;
  case CERCLE:
    label = gtk_label_new("Victoire des cercles");
    break;
  default:
    label = gtk_label_new("Égalité");
    break;
  }
  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_data(provider, 
      "label { font-size: 12px; font-weight: bold; }", 
      -1, NULL);

  GtkStyleContext *context = gtk_widget_get_style_context(label);
  gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  Bouton exit("Retour au menu principal", &changeMenu, 200, 0, (void*)&mainMenu);
  Bouton newGame("Nouvelle partie", &changeMenu, 200, 0, (void*)&gameMenu);
  GtkWidget *grid = gtk_grid_new();
  GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  GtkWidget *aspect_frame = gtk_aspect_frame_new(NULL, 0.5, 0.5, 1.0, TRUE);
  // Appliquer un style CSS pour enlever la bordure
  provider = gtk_css_provider_new();
  gtk_css_provider_load_from_data(provider, "* { border: none; }", -1, NULL);
  context = gtk_widget_get_style_context(aspect_frame);
  gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_container_add(GTK_CONTAINER(aspect_frame), grid);

  // Crée la grille avec le constructeur de la classe Grid
  GridUI gameUi(grid, false);

  // Configure l'expansion de la grille
  gtk_widget_set_hexpand(grid, TRUE);
  gtk_widget_set_vexpand(grid, TRUE);

  // Ajoute les widgets au layout vertical
  gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), aspect_frame, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
  gtk_box_pack_end(GTK_BOX(hbox), exit.getButton(), FALSE, FALSE, 0);
  gtk_box_pack_end(GTK_BOX(hbox), newGame.getButton(), FALSE, FALSE, 0);

  // Ajoute la boîte verticale à la fenêtre
  gtk_container_add(GTK_CONTAINER(window), vbox);
  gtk_widget_show_all(window);
}


int main(int argc, char* argv[])
{
    // Initialisation de GTK
    gtk_init(&argc, &argv);
    game = new Grid();

    initWindow(window);
    gtk_widget_show_all(window);

    mainMenu();
    
    // Lance l'applis
    gtk_main();

    delete game;

    return 0;
}
