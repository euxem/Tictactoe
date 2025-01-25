#ifndef __TICTACTOE_H__
#define __TICTACTOE_H__

#include <gtk/gtk.h>
#include "grid.h"
#include "case.h"

void changeMenu(GtkWidget *widget, gpointer data);
void gameMenu();
void mainMenu();
Grid* getGrid();
void finGame();
void graphical();

#endif
