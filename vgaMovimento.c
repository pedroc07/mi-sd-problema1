#include <stdio.h>
#include <intelfpgaup/video.h>

int main(void) {
    if (video_open() != 1) {
        return 1;
    }

    int colunas, linhas, tColunas, tLinhas;

    if (video_read(&colunas, &linhas, &tColunas, &tLinhas) != 1) {
        video_close();
        return 1;
    }

    int x = 20;
    int y = 20;
    int velocidadeX = 2;
    int velocidadeY = 2;

    while (1) {
        video_clear();

        // Verifica se o quadrado está da tela
        if (x < 0 || x >= colunas - 60 || y < 0 || y >= linhas - 40) {
            // Inverte a direção do quadrado
            velocidadeX = -velocidadeX;
            velocidadeY = -velocidadeY;
        }

        // Atualiza a posição do quadrado
        x += velocidadeX;
        y += velocidadeY;

        video_box(x, y, x + 60, y + 40, video_BLUE);

        video_show();

        usleep(10000);
    }

    video_close();

    return 0;
}
