#include "sudoku.h"
#include <iostream>
#include <fstream>
#include <random>
#include <cstdlib>


Sudoku::Sudoku(): grid(std::vector<std::vector<int> >{}), stop_recursion(false) {
    srand(time(NULL));
    for(unsigned int i = 0; i<9; ++i) {
        grid.push_back(std::vector<int>{0,0,0,0,0,0,0,0,0});
    }
}


Sudoku::Sudoku(Sudoku *S) : grid(S->grid), stop_recursion(false) {}


Sudoku::Sudoku(std::string filepath): stop_recursion(false) {
    std::ifstream file_grid;
    int buffer;
    file_grid.open(filepath);
    if(!file_grid.is_open()) {
        std::cout << "Error - Could not open File!\n";
    }
    else {
    for(unsigned int i = 0; i<9; ++i) {
        std::vector<int> row;
        for (unsigned int j = 0; j<9; ++j) {
            file_grid >> buffer;
            row.push_back(buffer);
        }
        grid.push_back(row);
    }
    file_grid.close();
    // std::cout << "Succesfully read from File!\n";
    }
}


Sudoku& Sudoku::operator=(const Sudoku &rhs) {
    grid = rhs.grid;
    stop_recursion = false;
    return *this;
}


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

bool Sudoku::is_solved() const {
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

void Sudoku::clear_value(int y_val, int x_val) {
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
    std::cout << " -1-2-3-4-5-6-7-8-9-";
    for (unsigned int y = 0; y<9; ++y) {
        std::cout << '\n' << y+1 << "|";
        for (unsigned int x = 0; x<9; ++x) {
            std::cout << grid[y][x] << ' ';
        }
    }
    std::cout << "\n\n";
} 


void Sudoku::solve(bool print) {
    char keep_backtracking = 'y';
    if(is_solved()) {
        if(print) {
            std::cout << "Solved!\n";
            print_grid_stdio();
        }
        std::cout << "Try another Solution [y/n]?";
        std::cin >> keep_backtracking;
        if(keep_backtracking=='n') { stop_recursion = true; }
        return;
    }
    for (int y = 0; y<9; ++y) {
        for (int x = 0; x<9; ++x) {
            if(grid[y][x] == 0) {
                for (int num = 1; num<10; ++num) {
                    if (is_possible(y,x,num)) {
                        set_value(y,x,num);
                        if(print) { print_grid_stdio(); }
                        solve(print);
                        if   (stop_recursion) { return; }
                        else { clear_value(y,x); }
                    }
                }
                return;
            }
        }
    }
}


void Sudoku::solve_once()  {
    if(is_solved()) {
            std::cout << "Solved!\n";
            return;
    }
    for (int y = 0; y<9; ++y) {
        for (int x = 0; x<9; ++x) {
            if(grid[y][x] == 0) {
                for (int num = 1; num<10; ++num) {
                    if (is_possible(y,x,num)) {
                        set_value(y,x,num);
                        solve_once();
                        if   (is_solved()) { return; }
                        else { clear_value(y,x); }
                    }
                }
                return;
            }
        }
    }
}


void generateSudoku(std::string filename) {

}
