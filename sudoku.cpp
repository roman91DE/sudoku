#include "sudoku.h"
#include <iostream>
#include <random>
#include <cstdlib>


Sudoku::Sudoku(): grid(std::vector<std::vector<int> >{}), stop_recursion(false) {
    srand(time(NULL));
    for(unsigned int i = 0; i<9; ++i) {
        grid.push_back(std::vector<int>{0,0,0,0,0,0,0,0,0});
    }
}

Sudoku::Sudoku(Sudoku *S) : grid(S->grid), stop_recursion(false) {}

Sudoku::~Sudoku() {}

bool Sudoku::is_possible(int y_val, int x_val, int number) const {
    for (unsigned int ind = 0; ind<9; ++ind) {
        if((grid[ind][x_val] == number) || (grid[y_val][ind] == number)){
            return false;
        }
    }
    int x0 = (x_val/3)*3;
    int y0 = (y_val/3)*3;
    for(unsigned int xi = x0; xi<(x0+3); ++xi) {
        for (unsigned int yi = y0; yi<(y0+3); ++yi) {
            if(grid[yi][xi] == number) {return false;}
        }
    }
    return true;
}

bool Sudoku::is_solved() {
    for (auto &row: grid) {
        for (auto &val: row) {
            if(val==0) return false;
        }
    }
    return true;
}

void Sudoku::set_value(int y_val, int x_val, int number) {
    grid[y_val][x_val] = number;
}

void Sudoku::clear_value(int y_val, int x_val, int number) {
    grid[y_val][x_val] = 0;
}


void Sudoku::random_filling(int n_numbers) {
    int nums_filled = 0;
    while(nums_filled<n_numbers) {
        int zv_y = rand()%9;
        int zv_x = rand()%9;
        int zv_n = rand()%9 +1;
        if((grid[zv_y][zv_x] == 0) && (is_possible(zv_y, zv_x, zv_n))) {
            set_value(zv_y, zv_x, zv_n);
            ++nums_filled;
        }
    }
}

void Sudoku::random_deletion(int n_numbers) {
    int nums_deleted = 0;
    while(nums_deleted<n_numbers) {
        int zv_y = rand()%9;
        int zv_x = rand()%9;
        if((grid[zv_y][zv_x] > 0)) {
            set_value(zv_y, zv_x, 0);
            ++nums_deleted;
        }
    }
}
 

void Sudoku::print_grid_stdio() const {
    std::cout << "  1-2-3-4-5-6-7-8-9-";
    for (unsigned int y = 0; y<9; ++y) {
        std::cout << '\n' << y+1 << "|";
        for (unsigned int x = 0; x<9; ++x) {
            std::cout << grid[y][x] << ' ';
        }
    }
    std::cout << "\n\n";
} 

void Sudoku::solve(bool print) {
    char finish = 'y';
    // base case
    if(is_solved()) {
        if(print) {
            std::cout << "Solved!\n";
            print_grid_stdio();
        }
        std::cout << "Try another Solution(y/n)?";
        std::cin >> finish;
        if(finish=='n') { stop_recursion = true; }
        return;
    }
    // recursive backtracking algorithm
    for (int y = 0; y<9; ++y) {
        for (int x = 0; x<9; ++x) {
            if(grid[y][x] == 0) {
                // try numbers for empty position
                for (int num = 1; num<10; ++num) {
                    if (is_possible(y,x,num)) {
                        set_value(y,x,num);
                        if(print) { print_grid_stdio(); }
                        solve(print);
                        if   (!stop_recursion) { clear_value(y,x,num); }
                        else { return; }
                    }
                }
                return;
            }
        }
    }
}
