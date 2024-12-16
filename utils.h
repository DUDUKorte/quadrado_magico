// utils.h
// Funções diversas
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

// Funções -----------------------------------------------------------------------

/* Função clrscr(): limpa a tela (UNIX) */
void clrscr();

/* Posiciona o cursor na posição coluna x linha y */
void gotoxy(int x, int y);

/* Função para formatar uma string com tamanho fixo */
void _format_num(const char *num, char *saida, int largura);

/* Função para formatar uma string com tamanho fixo */
void _format_margin(const char *margin, char *saida, int largura);

/* Cria janela do jogo */
void create_window(int size, int mudou, int init_x, int init_y, int margin_size, char *line);

/* Recebe uma tecla sem precisar digitar [enter] */
char getch();

/* Verifica se uma tecla foi pressionada */
int keypress();

