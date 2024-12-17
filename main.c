#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "util.h"

int main(){
    int size_x;
    int size_y;
    int init_pos = 3;
    int margin_size = 6;
    char line[1] = "";
    scanf("%d %d", &size_x, &size_y);

    clrscr();
    start(size_x, size_y, init_pos, margin_size, line);

    while(1) {
        char key = getch();

        //printf("%c\n", key);
        handle_movement(key);
        create_window();

        //usleep(100000); // Wait 100000 microseconds = 100ms
    }

    return 0;
}