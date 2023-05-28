all: 
	gcc sudoku.c row.c box.c puzzle.c square.c -o sudoku
	./sudoku

clean:
	rm sudoku