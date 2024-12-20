#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

// COLOR DEFINES
#define CLEAR "\033[H\033[2J" // Comando do terminal para limpar a tela do console
#define RESET "\033[0m"
#define REVERSE "\033[7m"
#define BOLD "\033[1m"
#define REVERSE "\033[7m"
#define BG_BLUE "\033[44m"
#define BG_WHITE "\033[107m"
#define BG_WHITE_2 "\033[47m"
#define BG_PLAYER "\033[107m"
#define BG_BLACK "\033[40m"
#define BG_BBLACK "\033[100m"
#define BG_GREEN "\033[42m"
#define BG_RED "\033[41m"
#define FG_GREEN "\033[92m"
#define FG_RED "\033[91m"
#define FG_WHITE "\033[37m"
#define FG_BLACK "\033[30m"
#define FG_PLAYER "\033[92m"

// KEYS DEFINES
#define KEY_UP 65
#define KEY_W 119
#define KEY_DOWN 66
#define KEY_S 115
#define KEY_LEFT 68
#define KEY_A 97
#define KEY_RIGHT 67
#define KEY_D 100
#define KEY_ENTER 10
#define KEY_ESC 0
#define KEY_F 102

// Utils Functions -----------------------------------------------

/* Função clrscr(): limpa a tela (UNIX) */
void clrscr();

/* Posiciona o cursor na posição coluna x linha y */
void gotoxy(int x, int y);

/* Função para formatar os numeros com tamanho fixo */
void _format_num(const char *num, char *saida, int largura);

/* Função para formatar uma string com tamanho fixo */
void _formatar_opcao(const char *opcao, char *saida, int largura, char *separator);

/* Função para formatar uma string com tamanho fixo e variavel ao lado */
void _formatar_variavel(const char *opcao, char *saida, int largura, int variavel);

/* Função para formatar as margens laterais centralizadas */
void _format_margin_side(const char *margin, char *saida, int largura);

/* Recebe uma tecla sem precisar digitar [enter] */
char getch();
