# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <intelfpgaup/video.h>

int main(){
    char msg_buffer[9] = "game over";
    int screen_x, screen_y, char_x, char_y;

    video_open();
    video_read (&screen_x, &screen_y, &char_x, &char_y);
    video_text (char_x-strlen(msg_buffer), char_y - 1, msg_buffer);
    video_show ();
    video_close ();
    printf ("\nExiting sample program\n");
    return 0;
}

