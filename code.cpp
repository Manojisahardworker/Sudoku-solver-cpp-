#include <bits/stdc++.h>   // Includes all standard C++ libraries
using namespace std;

// Class to encapsulate Sudoku solving logic
class SudokuSolver {
    vector<vector<int>> board;   // 9x9 Sudoku board
    // Bitsets to track used numbers in rows, columns, and boxes
    array<bitset<9>, 9> rowMask, colMask, boxMask;

    // Helper function to compute which 3x3 box a cell belongs to
    int getBoxIndex(int r, int c) {
        return (r / 3) * 3 + (c / 3);
    }

    // Recursive backtracking function to solve Sudoku
    bool solve(int r = 0, int c = 0) {
        // Base case: if we reach row 9, board is solved
        if (r == 9) return true;

        // If we reach column 9, move to next row
        if (c == 9) return solve(r + 1, 0);

        // If cell is already filled, move to next column
        if (board[r][c] != 0) return solve(r, c + 1);

        // Find which 3x3 box this cell belongs to
        int box = getBoxIndex(r, c);

        // Try placing numbers 1–9
        for (int num = 1; num <= 9; num++) {
            // Check if 'num' is unused in row, column, and box
            if (!rowMask[r][num-1] && !colMask[c][num-1] && !boxMask[box][num-1]) {
                // Place number
                board[r][c] = num;
                // Mark number as used in row, column, and box
                rowMask[r][num-1] = colMask[c][num-1] = boxMask[box][num-1] = true;

                // Recursively try to solve next cell
                if (solve(r, c + 1)) return true;

                // Backtrack: undo placement
                board[r][c] = 0;
                rowMask[r][num-1] = colMask[c][num-1] = boxMask[box][num-1] = false;
            }
        }
        // If no number fits, return false (backtrack further)
        return false;
    }

public:
    // Constructor: initialize board and masks
    SudokuSolver(vector<vector<int>> input) : board(input) {
        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                int num = board[r][c];
                if (num != 0) {
                    int box = getBoxIndex(r, c);
                    // Mark existing numbers in masks
                    rowMask[r][num-1] = colMask[c][num-1] = boxMask[box][num-1] = true;
                }
            }
        }
    }

    // Public function to start solving
    void solveSudoku() {
        solve();
    }

    // Print the solved board
    void printBoard() {
        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                cout << board[r][c] << " ";
            }
            cout << "\n";
        }
    }
};

int main() {
    // Create a 9x9 board initialized with zeros
    vector<vector<int>> board(9, vector<int>(9));

    // Input unsolved Sudoku from terminal
    cout << "Enter the Sudoku board (0 for empty cells):\n";
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            cin >> board[r][c];   // Read each cell
        }
    }

    // Create solver object with input board
    SudokuSolver solver(board);

    // Solve the Sudoku
    solver.solveSudoku();

    // Print the solved Sudoku
    cout << "\nSolved Sudoku:\n";
    solver.printBoard();
    return 0;
}
