#pragma once
#include <vector>

class Sudoku{
    private:
        std::vector< std::vector<int> > grid;
        bool solved;
    public:
        Sudoku();
        Sudoku(Sudoku *S);
        ~Sudoku();
        void random_filling(int n_numbers);
        void random_deletion(int n_numbers);
        // void solve();
        bool is_possible(int y_val, int x_val, int number) const;
        // bool is_solved() const;
        void print_grid_stdio() const;
        void set_value(int y_val, int x_val, int number);
};