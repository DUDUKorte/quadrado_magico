// Funções diversas
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

// Funções -----------------------------------------------------------------------

/* Start function */
void start(int x, int y, int init_pos, int margin_size, char *line);

/* Função clrscr(): limpa a tela (UNIX) */
void clrscr();

/* Posiciona o cursor na posição coluna x linha y */
void gotoxy(int x, int y);

/* Função para formatar uma string com tamanho fixo */
void _format_num(const char *num, char *saida, int largura);

/* Função para formatar uma string com tamanho fixo */
void _format_margin(const char *margin, char *saida, int largura);

/* Função para formatar uma string com tamanho fixo */
void _format_margin_side(const char *margin, char *saida, int largura);

/* Cria janela do jogo */
void create_window();

/* Recebe uma tecla sem precisar digitar [enter] */
char getch();

/* Verifica se uma tecla foi pressionada */
int keypress();

/* Handle movement actions */
void handle_movement(char key);

/* Movement Actions */
void _move_up();
void _move_down();
void _move_left();
void _move_right();

/* Matrix Functions */
void _create_matrix(int x, int y);
