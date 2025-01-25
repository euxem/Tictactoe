#ifndef __GRID_H__
#define __GRID_H__

#include "case.h"
#include <gtk/gtk.h>

enum Mode {
    H,
    V,
    ALL
};

/**
 * Représente la grille d'un tictactoe
 */
class Grid
{
private:
    Case grid[3][3];
    int coup = 0;
    Case neighWin(unsigned int ligne, unsigned int colone, Mode mode);
public:
    void resetGrid();
    void setCase(unsigned int ligne, unsigned int colone, Case state);

    Case* getCase(unsigned int ligne, unsigned int colone);

    Case checkWin();

    int getCoup();
};

#endif