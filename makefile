all:game

game: game.c
	gcc game.c -o game -lintelfpgaup