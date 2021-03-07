#pragma once
#include <vector>
#include <string>

class Sudoku{
    private:
        std::vector< std::vector<int> > grid;
        bool stop_recursion;
    public:
        Sudoku();
        Sudoku(Sudoku *S);
        // Sudoku(std::string filepath);
        ~Sudoku();
        void random_filling(int n_numbers);
        void random_deletion(int n_numbers);
        void solve(bool print);
        bool is_possible(int y_val, int x_val, int number) const;
        bool is_solved();
        void print_grid_stdio() const;
        void set_value(int y_val, int x_val, int number);
        void clear_value(int y_val, int x_val);
};