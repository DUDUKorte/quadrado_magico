// Funções diversas
#include "util.h"

// Utils Functions -----------------------------------------------

/* Função clrscr(): limpa a tela (UNIX) */
void clrscr(){
    printf(CLEAR);
}

/* Posiciona o cursor na posição coluna x linha y */
void gotoxy(int x, int y){
    printf("\e[%d;%df", y, x);
    fflush(stdout);
}

// Função para formatar os numeros com tamanho fixo
void _format_num(const char *num, char *saida, int largura) {
   int len = strlen(num);
   int padding_l = (len == (largura/2) ? 1 : 2) + len; // Espaços para completar a esquerda
   int padding_r = len == (largura/2) ? 1 : 2; // Espacos parar completar a direita
   if (padding_l < 0) padding_l = 0; // Evita valores negativos
   snprintf(saida, largura, "%*s%*s", padding_l, num, padding_r, ""); // Adiciona espaços a esquerda e direita para centralizar os numeros
}

// Função para formatar uma string com tamanho fixo
void _formatar_opcao(const char *opcao, char *saida, int largura, char *separator) {
   int len = strlen(opcao);
   int padding = largura - len; // Espaços para completar
   if (padding < 0) padding = 0; // Evita valores negativos
   snprintf(saida, largura + 1, "%s%*s", opcao, padding, separator); // Adiciona espaços ao final
}

// Função para formatar uma string com tamanho fixo e variavel ao lado
void _formatar_variavel(const char *opcao, char *saida, int largura, int variavel) {
   int len = strlen(opcao);
   int padding = largura - len; // Espaços para completar
   if (padding < 0) padding = 0; // Evita valores negativos
   snprintf(saida, largura + 1, "%s %d%*s", opcao, variavel, padding, ""); // Adiciona espaços ao final
}

/* Função para formatar as margens laterais centralizadas */
void _format_margin_side(const char *margin, char *saida, int largura) {
    largura += 1;
    int len = strlen(margin);
    int padding = largura - len; // Espaços para completar
    if (padding < 0) padding = 0; // Evita valores negativos
    snprintf(saida, largura + 1, "%*s%*s", 2, margin, 1, ""); // Adiciona espaços ao final
}

/* Recebe uma tecla sem precisar digitar [enter] */
char getch(){
    // le um caracter da entrada padrão sem o bloqueio de entrada
    // (não necessita apertar enter)
    int ch;
    struct termios oldt;
    struct termios newt;

    tcgetattr(STDIN_FILENO,&oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restaura o terminal (deixa desligado)

    return ch;
}
