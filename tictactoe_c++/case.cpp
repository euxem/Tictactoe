#include "case.h"

static Case nstate;
#include <gtk/gtk.h>

void initNstate() {
    nstate = CROSS;
}

void giveNstate(Case& cas, GtkWidget* label){
    cas = nstate;
    if (nstate == CROSS) {
        gtk_label_set_text(GTK_LABEL(label), "Tour des cercles");
        nstate = CERCLE;
    } else {
        gtk_label_set_text(GTK_LABEL(label), "Tour des croix");
        nstate = CROSS;
    }
    gtk_widget_queue_draw(label);
}
