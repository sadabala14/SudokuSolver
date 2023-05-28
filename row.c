#include "sudoku.h"

int checkRows(Square *** sudoku, Box ** boxes) {
    printf("reached here!\n");
    int i, j, k;
    int sum[9];
    int place[9];

    for (i = 0; i < 9; i++) { //loop through rows
        for (j = 0; j < 9; j++) { //initialize sum spots to 0
            place[j] = 0;
            sum[j] = 0;
        }

        for (j = 0; j < 9; j++) { //loop through each square in row
            if (sudoku[i][j]->number != 0) {
                continue;
            }

            //loop through the possible nums for spot
            for (k = 0; k < 9; k++) {
                if (sudoku[i][j]->possible[k] == 0) {
                    sum[k]++;
                    place[k] = j; //where it is solvable, col
                }
            }
        }

        for (k = 0; k < 9; k++) {
            if (sum[k] == 1) {
                sudoku[i][place[k]]->number = k + 1;
                sudoku[i][place[k]]->solvable = 0;
                UNSOLVED--;

                updateSudoku(sudoku, i, place[k]);
                updateBoxes(sudoku, i, place[k]);

                return 1;

        }
    }
    }
    

    return 0;

}