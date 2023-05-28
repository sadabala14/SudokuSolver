#ifndef SUDOKU_H 
#define SUDOKU_H

#include <stdio.h>
#include <stdlib.h>


extern int UNSOLVED;
extern int SIZE_ROWS;
extern int SIZE_COLUMNS;

typedef struct Sudoku {
    struct Square *** squares;
    struct Box ** boxes;
} Sudoku;

typedef struct Box {
    struct Square ** squares;
    int numbers;
    int possible[9];
    int solvable;
    struct Box* next;
} Box;

typedef struct Square {
    int number;
    int possible[9];
    int solvable;
    Box* box;
    int row;
    int col;
} Square;


int ** createPuzzle();
void printPuzzle(Square *** puzzle);
int solveSquare(Square * square);
Sudoku * setUpPuzzle(int** puzzle);

Sudoku * createSudoku(Square *** puzzle, Box ** boxes);
int updateSudoku(Square ***sudoku, int i , int j);
int checkPuzzle(Square *** sudoku, Box ** boxes);

Box ** createBoxes();
int boxSingles(Square *** sudoku, Box ** boxes);
int updateBoxes(Square *** sudoku, int i, int j);
int checkRows(Square *** sudoku, Box ** boxes);

#endif