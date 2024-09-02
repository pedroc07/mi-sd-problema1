#include <stdio.h>
#include <intelfgaup/video.h>

int main(void) {
    if (video_open() != 1) {
        return 1;
    }

    int colunas, linhas, tColunas, tLinhas;

    if (video_read(&colunas, &linhas, &tColunas, &tLinhas) != 1) {
        video_close();
        return 1;
    }
    video_clear();

    video_box(20, 20, 80, 60, video_WHITE);

    video_show();

    sleep(10);

    video_close();

    return 0;
}
