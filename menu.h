#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

// Comprimento máximo de uma linha do menu
#define MENU_WIDTH 10

// Funções Do Menu Principal -----------------------------------------------------------------------

// Função para exibir o cabeçalho
void _exibir_cabecalho(const char *titulo);

// Função para exibir o menu interativo
int _mostrar_menu_interativo(const char *opcoes[], int n, const char *titulo);

// Função para exibir o menu interativo de opcoes
int _mostrar_options(const char *opcoes[], int n, const char *titulo, int *variaveis);

// Height e Width getters
int get_height();
int get_width();

int start_menu();