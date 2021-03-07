#include "sudoku.h"
#include <iostream>

int main() {
    Sudoku s;
    s.random_filling(40);
    s.print_grid_stdio();
    s.random_deletion(30);
    s.print_grid_stdio();
    

    return 0;
}