#include "gridUI.h"
#include "case.h"
#include "tictactoe+.h"
#include "grid.h"
#include <iostream>

#define CROSS_DIV 8

static void dessinCarre(cairo_t *cr, int width, int height, int col, int ligne) {
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);

    cairo_set_line_width(cr, 3);
    cairo_move_to(cr, 0, 0);
    if (ligne) {
        cairo_line_to(cr, width, 0);
    } else {
        cairo_move_to(cr, width, 0);
    }
    if (col != 2) {
        cairo_line_to(cr, width, height); 
    } else {
        cairo_move_to(cr, width, height); 
    }
    if (ligne != 2) {
        cairo_line_to(cr, 0, height);  
    } else {
        cairo_move_to(cr, 0, height);  
    }
    if (col) {
        cairo_line_to(cr, 0, 0);
    } else {
        cairo_move_to(cr, 0, 0);
    }
    cairo_stroke(cr); 
}

static void dessinCase(GtkWidget *widget, cairo_t *cr, gpointer data) {
    Grid* gridCase = getGrid();
    // Récupère la taille de la zone de dessin
    GtkAllocation allocation;
    gtk_widget_get_allocation(widget, &allocation);
    int width = allocation.width;
    int height = allocation.height;
    int center_x, center_y, radius;
    switch (*gridCase->getCase((long)data/3, (long)data%3)) {
        case CROSS:
            // Définit la couleur bleue
            cairo_set_source_rgb(cr, 0.0, 0.0, 1.0); // Rouge = 0, Vert = 0, Bleu = 1
            // Dessine une ligne diagonale (haut gauche -> bas droit)
            cairo_set_line_width(cr, 5);
            cairo_move_to(cr, 0 + width / CROSS_DIV, 0 + height / CROSS_DIV);             // Point de départ
            cairo_line_to(cr, width - width / CROSS_DIV, height - height / CROSS_DIV);    // Point d'arrivée
            cairo_stroke(cr);

            // Dessine l'autre ligne diagonale (haut droit -> bas gauche)
            cairo_move_to(cr, width - width / CROSS_DIV, 0 + height / CROSS_DIV);         // Point de départ
            cairo_line_to(cr, 0 + width / CROSS_DIV, height - height / CROSS_DIV);        // Point d'arrivée
            cairo_stroke(cr);
            break;
        case CERCLE:
            // Calcul des coordonnées et du rayon pour un cercle centré
            center_x = width / 2;
            center_y = height / 2;
            radius = (width < height ? width : height) / 3; // Rayon basé sur la plus petite dimension

            // Définit la couleur rouge
            cairo_set_source_rgb(cr, 1.0, 0.0, 0.0); // Rouge = 1, Vert = 0, Bleu = 0

            // Dessine le cercle
            cairo_set_line_width(cr, 5);
            cairo_arc(cr, center_x, center_y, radius, 0, 2 * G_PI); // Cercle complet
            cairo_stroke(cr); // Remplit le cercle avec la couleur
            break;
        default:
            break;
    }
    dessinCarre(cr, width, height, (long)data/3, (long)data%3);
}

// Fonction appelée lorsqu'on clique sur une case
static gboolean on_case_clicked(GtkWidget *widget, GdkEventButton *event, gpointer data) {
    Grid* gridGame = getGrid();
    Case *caseData = gridGame->getCase((long)data/3, (long)data%3);

    // Change l'état de la case (par exemple, bascule entre vide, croix, et cercle)
    if (*caseData != EMPTY) {
        return TRUE;
    }

    GList* children = gtk_container_get_children(GTK_CONTAINER(gtk_widget_get_parent(gtk_widget_get_parent(gtk_widget_get_parent(widget)))));

    giveNstate(*caseData, GTK_WIDGET(children->data));

    g_list_free(children);

    // Force le redessin de la zone de dessin
    gtk_widget_queue_draw(widget);
    Case win = gridGame->checkWin();

    if (win || gridGame->getCoup() == 9) {
        changeMenu(NULL, (void*)&finGame);
    }

    return TRUE;
}

GridUI::GridUI(GtkWidget *grid, bool interract) {
    for (size_t lig{0}; lig < 3; lig++) {
        for(size_t col{0}; col < 3; col++) {
            this->gridDessins[lig][col] = gtk_drawing_area_new();
        
            // Connecte le signal "draw" pour dessiner la case
            g_signal_connect(G_OBJECT(this->gridDessins[lig][col]), "draw", G_CALLBACK(dessinCase), (void*)(lig*3 + col));
        
            if (interract) {
                // Crée l'EventBox pour capturer les clics
                this->gridEvents[lig][col] = gtk_event_box_new();
                g_signal_connect(G_OBJECT(this->gridEvents[lig][col]), "button-press-event", G_CALLBACK(on_case_clicked), (void*)(lig*3 + col));
            
                // Ajoute la zone de dessin dans l'EventBox
                gtk_container_add(GTK_CONTAINER(this->gridEvents[lig][col]), this->gridDessins[lig][col]);
            }

            // Permet à chaque zone de dessin de s'étendre
            gtk_widget_set_hexpand(this->gridDessins[lig][col], TRUE);
            gtk_widget_set_vexpand(this->gridDessins[lig][col], TRUE);
            gtk_widget_set_halign(this->gridDessins[lig][col], GTK_ALIGN_FILL);
            gtk_widget_set_valign(this->gridDessins[lig][col], GTK_ALIGN_FILL);
            
            // Ajoute la zone de dessin à la grille
            gtk_grid_attach(GTK_GRID(grid), interract ? this->gridEvents[lig][col] : this->gridDessins[lig][col], lig, col, 1, 1);
        }
    }
}
