#include "sudoku.h"

int ** createPuzzle() {
    int ** returnPuzzle;
    int i;
    int j;
int array[9][9]=     {0, 1, 9,      0, 0, 2,     0, 0, 0,
                      4, 7, 0,      6, 9, 0,     0, 0, 1,
                      0, 0, 0,      4, 0, 0,     0, 9, 0,

                      8, 9, 4,      5, 0, 7,     0, 0, 0,
                      0, 0, 0,      0, 0, 0,     0, 0, 0,
                      0, 0, 0,      2, 0, 1,     9, 5, 8,

                      0, 5, 0,      0, 0, 6,     0, 0, 0,
                      6, 0, 0,      0, 2, 8,     0, 7, 9,
                      0, 0, 0,      1, 0, 0,     8, 6, 0 };

    returnPuzzle = (int **) malloc(sizeof(int *) * 9);

    for (i = 0; i < 9; i++) {
        returnPuzzle[i] = (int *) malloc (sizeof(int) * 9);
        for (j = 0; j < SIZE_COLUMNS; j++) {
            returnPuzzle[i][j] = array[i][j];
        }
    }
    return returnPuzzle;

}

void printPuzzle(Square *** puzzle) {
    int i;
    int j;
    printf("-------------------------------\n");
    for (i = 0; i < SIZE_ROWS; i++) {
        printf("|");
        for (j = 0; j < SIZE_COLUMNS; j++) {
            printf(" %d ", puzzle[i][j]->number);
            if (((j + 1)) % 3 == 0) {
                printf("|");
            }
        }
        printf("\n");
        if (((i+ 1) % 3) == 0) {
            printf("-------------------------------\n");
        }
    }

}

Sudoku * setUpPuzzle(int ** puzzle) {
    Square *** sudoku;
    Box ** boxes;
    int i, j, x;
    int currentBox = 0;

    sudoku = (Square ***) malloc(sizeof(Square**) * 9);
    boxes = createBoxes();

    for (i = 0; i < SIZE_ROWS; i++) { // loop rows
        sudoku[i] = (Square **) malloc(sizeof(Square*) * 9);
        for (j = 0; j < SIZE_COLUMNS; j++) { // loop cols
            //malloc for each square
            sudoku[i][j] = (Square *) malloc(sizeof(Square) * 9);
            //assign number to existing squares 
            sudoku[i][j]->number = puzzle[i][j];
            //assign row/col nums to squares
            sudoku[i][j]->row = i;
            sudoku[i][j]->col = j;
            sudoku[i][j]->solvable = 9;

            boxes[currentBox]->squares[boxes[currentBox]->numbers] = sudoku[i][j];
            sudoku[i][j]->box = boxes[currentBox];
            boxes[currentBox]->numbers++;
            
            for (x = 0; x < SIZE_ROWS; x++) {
                sudoku[i][j]->possible[x] = 0;
            }
            if (j == 2) {
                currentBox++;
            } 
            if (j == 5) {
                currentBox++;
            }
        }
        currentBox -= 2;
        if (i == 2) {
            currentBox = 3;
        }
        if (i == 5) {
            currentBox = 6;
        }
    }

    for (i = 0; i < SIZE_ROWS; i++) {
        for (j = 0; j < SIZE_COLUMNS; j++) {
            if (sudoku[i][j]->number != 0) {
                sudoku[i][j]->solvable = 0;
                updateSudoku(sudoku, i , j);
                updateBoxes(sudoku, i, j);
                UNSOLVED--;
            }
        }
    }
    return createSudoku(sudoku, boxes);
}


int updateSudoku(Square ***sudoku, int i , int j) {
    int x;
    int number = sudoku[i][j]->number;

    for (x = 0; x < SIZE_ROWS; x ++) {
        if (sudoku[x][j]->possible[number - 1] == 0) {
            sudoku[x][j]->solvable--;
        }
        sudoku[x][j]->possible[number - 1] = 1;
    }

    for (x = 0; x < SIZE_COLUMNS; x ++) {
        if (sudoku[i][x]->possible[number - 1] == 0) {
            sudoku[i][x]->solvable--;
        }
        sudoku[i][x]->possible[number - 1] = 1;
    }
    return 1;
}

int checkPuzzle(Square *** sudoku, Box ** boxes) {
    int i, j, x;
    for (int i = 0; i < SIZE_ROWS; i++) {
        for (int j = 0; j < SIZE_COLUMNS; j++) {
            if (sudoku[i][j]->solvable == 1) {
                solveSquare(sudoku[i][j]);
                updateSudoku(sudoku, i, j);
                updateBoxes(sudoku, i, j);

                return 1;
            }
        }
    }
    if (boxSingles(sudoku, boxes)) {
        return 1;
    } // solve vs unsolve something

    return checkRows(sudoku, boxes);
}

Sudoku * createSudoku(Square *** squares, Box ** boxes) {
    Sudoku * sudoku;
    sudoku = malloc(sizeof(Sudoku));
    sudoku->squares = squares;
    sudoku->boxes = boxes;
    return sudoku;
}