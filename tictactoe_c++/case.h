#ifndef __CASE_H__
#define __CASE_H__

#include <gtk/gtk.h>

enum Case {
    EMPTY=0,
    CROSS=1,
    CERCLE=2
};

void initNstate();

void giveNstate(Case& cas, GtkWidget* label);

#endif