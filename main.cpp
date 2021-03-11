#include "sudoku.h"
#include <iostream>

int main() {
    // Sudoku s("txt_files/grid.txt");
    // s.solve(true);
    Sudoku s;
    s.solve_once();
    s.print_grid_stdio();

    return 0;
}