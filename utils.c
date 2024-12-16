// utils.h
// Funções diversas
#include "utils.h"

// DEFINES
#define CLEAR "\033[H\033[2J" // Comando do terminal para limpar a tela do console
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define REVERSE "\033[7m"
#define FG_WHITE "\033[37m"
#define BG_BLUE "\033[44m"
#define BG_WHITE "\033[47m"
#define FG_BLACK "\033[30m"

// Funções -----------------------------------------------------------------------

/* Função clrscr(): limpa a tela (UNIX) */
void clrscr(){
    printf(CLEAR);
}

/* Posiciona o cursor na posição coluna x linha y */
void gotoxy(int x, int y){
    printf("\e[%d;%df", y, x);
    fflush(stdout);
}

// Função para formatar uma string com tamanho fixo
void _format_num(const char *num, char *saida, int largura) {
   int len = strlen(num);
   int padding = largura - len; // Espaços para completar
   if (padding < 0) padding = 0; // Evita valores negativos
   snprintf(saida, largura + 1, "%s%*s", num, padding, ""); // Adiciona espaços ao final
}

// Função para formatar uma string com tamanho fixo
void _format_margin(const char *margin, char *saida, int largura) {
   int len = strlen(margin);
   int padding = largura - len; // Espaços para completar
   if (padding < 0) padding = 0; // Evita valores negativos
   snprintf(saida, largura + 1, "%s%*s", margin, padding, "-"); // Adiciona espaços ao final
}

/* Cria janela do jogo */
void create_window(int size, int mudou, int init_x, int init_y, int margin_size, char *line){
    size += 1;
    int xl = init_x, ys = init_y;
    int xd = xl + (size);
    int yi = ys + size;
    
    printf(BG_WHITE FG_BLACK BOLD);

    // print top bottom lines
    gotoxy(xl+1, ys);
    for(int i = xl+1; i < xd; i++){
        char formatted_[10];
        _format_margin(line, formatted_, margin_size);
        printf("%s", formatted_);
    }
    printf("+");
    
    // print lateral lines
    for(int i = ys+1; i < yi+1; i++){
        gotoxy(xl, i);
        printf("|");
        for(int i = xl+1; i < xd; i++){
            char formatted_[10];
            _format_margin(line, formatted_, margin_size);
            printf("%s", formatted_);
        }
        printf("|");
    }

    gotoxy(xl+1, yi);
    //printf("+");
    for(int i = xl+1; i < xd; i++){
        char formatted_[10];
        _format_margin(line, formatted_, margin_size);
        printf("%s", formatted_);
    }
    printf("+");

    // Print margins
    gotoxy(xl, ys);
    printf("+");
    gotoxy(xl, yi);
    printf("+");

    // Criar números
    int num = 1;
    for(int i = ys+1; i < yi; i++){
            gotoxy(xl+1, i);
        for(int j = xl+1; j < xd; j++){
            //for(int i = 0; i < max_digits; i++){ printf(" ");}
            //TODO ARRUMAR ESPAÇOS
            printf(BG_BLUE FG_WHITE BOLD);

            char formatted_num[3];
            char s_num[3];
            sprintf(s_num, "%d", num);

            _format_num(s_num, formatted_num, margin_size);

            printf("%s", formatted_num);
            num++;
            if(num == size*size){
                break;
            }
        }
    }
    
    printf(RESET "\n");
    printf("\n\n\n");
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
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

/* Verifica se uma tecla foi pressionada */
int keypress(){
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF){
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}