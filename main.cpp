#include "sudoku.h"
#include <iostream>

int main() {
    Sudoku s("txt_files/grid.txt");
    s.solve();
    return 0;
}