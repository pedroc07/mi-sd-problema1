all: game acccel video_txt

game: game.c
	gcc game.c -o game -lintelfpgaup -lpthread
	
acccel: acccel.c
	gcc acccel.c -o accel
	
video_txt: video_txt.c
	gcc video_txt.c -o video -lintelfpgaup
