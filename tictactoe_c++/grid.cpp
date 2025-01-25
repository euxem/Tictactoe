#include "grid.h"
#include <iostream>

#define CENTER this->grid[1][0] == this->grid[1][1] && this->grid[1][2] == this->grid[1][1] || \
               this->grid[0][1] == this->grid[1][1] && this->grid[2][1] == this->grid[1][1] || \
               this->grid[0][0] == this->grid[1][1] && this->grid[2][2] == this->grid[1][1] || \
               this->grid[0][2] == this->grid[1][1] && this->grid[2][0] == this->grid[1][1]

void Grid::resetGrid() {
    this->coup = 0;
    for (size_t lig = 0; lig < 3; lig++) {
        for (size_t col = 0; col < 3; col++) {
            this->grid[lig][col] = EMPTY;
        }
    }
}

int Grid::getCoup(){
    return ++this->coup;
}

void Grid::setCase(unsigned int ligne, unsigned int colone, Case state) {
    this->grid[colone][ligne] = state;
}

Case* Grid::getCase(unsigned int ligne, unsigned int colone) {
    return &(this->grid[colone][ligne]);
}

Case Grid::neighWin(unsigned int ligne, unsigned int colone, Mode mode) {
    switch (mode)
    {
    case H:
        return this->grid[ligne][colone] == this->grid[ligne][colone + 1] &&
               this->grid[ligne][colone] == this->grid[ligne][colone - 1] ? this->grid[ligne][colone] : EMPTY;
    case V:
        return this->grid[ligne][colone] == this->grid[ligne + 1][colone] &&
               this->grid[ligne][colone] == this->grid[ligne - 1][colone] ? this->grid[ligne][colone] : EMPTY;
    default:
        return CENTER ? this->grid[1][1] : EMPTY;
    }
}

Case Grid::checkWin(){
    return (Case)(neighWin(0, 1, H) + neighWin(1, 0, V) + neighWin(1, 2, V) + neighWin(1, 1, ALL) + neighWin(2, 1, H));
}
