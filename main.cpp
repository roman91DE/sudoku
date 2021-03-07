#include "sudoku.h"
#include <iostream>




int main() {
    Sudoku s;
    s.random_filling(15);
    s.print_grid_stdio();
    s.solve(true);
    return 0;
}