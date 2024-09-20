# include <intelfpgaup/video.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

int main(){
    char msg_buffer[80] = "game over";
    int screen_x, screen_y, char_x, char_y;

    video_open();
    video_read (&screen_x, &screen_y, &char_x, &char_y);
    video_text (100, 150, msg_buffer);
    video_show ();
    video_close ();
    printf ("\nExiting sample program\n");
    return 0;
}