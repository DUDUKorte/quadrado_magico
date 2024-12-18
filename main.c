#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "util.h"
#include "menu.h"
#include "game.h"

int start_game(int x, int y) {
    int size_x = x;
    int size_y = y;
    int init_pos = 3;
    int margin_size = 6;
    char line[1] = "";

    fflush(stdin); // Limpa o buffer para evitar carregar teclas pressionadas no menu

    clrscr();
    start(size_x, size_y, init_pos, margin_size);

    while(1) {
        char key = getch();

        handle_movement(key);

        create_window();

        // Prints ao final da janela
        printf("Press F to Exit\n");

        if (on_player_win()) {
            for (int i = 5; i > 0; i--) {
                printf("%d\n", i);
                usleep(500000);
                create_window();
                printf("PLAYER WINS\n");
            }
            break;
        }else if (on_player_lose()) {
            for (int i = 5; i > 0; i--) {
                printf("%d\n", i);
                usleep(500000);
                create_window();
                printf("PLAYER GIVE UP\n");
            }
            break;
        }
    }

    close_game();

    return 0;
}

int main(){

    while (1) {
        int start = start_menu(); // Menu principal

        if (start) {
            start_game(get_width(), get_height()); // Inicia o jogo principal com as variaveis do menu
        }else {
            break;
        }
    }

    return 0;
}

