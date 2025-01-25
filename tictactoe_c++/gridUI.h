#ifndef __GRIDUI_H__
#define __GRIDUI_H__

#include <gtk/gtk.h>
#include "grid.h"
#include "case.h"

/**
 * Représente la grille d'un tictactoe
 */
class GridUI
{
private:
    GtkWidget* gridDessins[3][3];
    GtkWidget* gridEvents[3][3];
public:
    /**
     * 
     */
    GridUI(GtkWidget* grid, bool interract);
};

void setCount0();

#endif