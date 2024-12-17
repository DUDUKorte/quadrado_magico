// Funções diversas
#include "util.h"

// DEFINES
#define CLEAR "\033[H\033[2J" // Comando do terminal para limpar a tela do console
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define REVERSE "\033[7m"
#define BG_BLUE "\033[44m"
#define BG_WHITE "\033[107m"
#define BG_PLAYER "\033[47m"
#define BG_BLACK "\033[40m"
#define BG_GREEN "\033[42m"
#define BG_RED "\033[41m"
#define FG_GREEN "\033[92m"
#define FG_RED "\033[91m"
#define FG_WHITE "\033[37m"
#define FG_BLACK "\033[30m"
#define FG_PLAYER "\033[92m"
int **MATRIX;
int INIT_POS, MARGIN_SIZE, SIZE_X, SIZE_Y;
char *LINE;
int PLAYER_X, PLAYER_Y;
char PLAYER[] = "\u25A0";
// Funções -----------------------------------------------------------------------

void start(int x, int y, int init_pos, int margin_size, char *line){
  // Variables
  SIZE_X = x;
  SIZE_Y = y;
  INIT_POS = init_pos;
  MARGIN_SIZE = margin_size;
  LINE = line;

  // Generate Matrix
  // Save Matrix
  _create_matrix(x, y);

  // Create Window First time
  create_window();
}

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
   int padding_l = (len == (largura/2) ? 1 : 2) + len; // Espaços para completar
   int padding_r = len == (largura/2) ? 1 : 2;
   if (padding_l < 0) padding_l = 0; // Evita valores negativos
   snprintf(saida, largura, "%*s%*s", padding_l, num, padding_r, ""); // Adiciona espaços ao final
}

// Função para formatar uma string com tamanho fixo
void _format_margin(const char *margin, char *saida, int largura) {
   largura += 1;
   int len = strlen(margin);
   int padding = largura - len; // Espaços para completar
   if (padding < 0) padding = 0; // Evita valores negativos
   snprintf(saida, largura + 1, "%s%*s", margin, padding, "-"); // Adiciona espaços ao final
}
void _format_margin_side(const char *margin, char *saida, int largura) {
    largura += 1;
    int len = strlen(margin);
    int padding = largura - len; // Espaços para completar
    if (padding < 0) padding = 0; // Evita valores negativos
    snprintf(saida, largura + 1, "%*s%*s", 2, margin, 1, ""); // Adiciona espaços ao final
}

/* Cria janela do jogo */
void create_window(){
    clrscr();
    int size_x = SIZE_X + 1;
    int size_y = SIZE_Y + 1;
    int xl = INIT_POS, ys = INIT_POS;
    int xd = xl + (size_x);
    int yi = ys + size_y;

    printf(BG_BLACK FG_WHITE BOLD);

    // print top bottom lines
    gotoxy(xl+1, ys);
    for(int i = xl+1; i < xd; i++){
        char formatted_[10];
        _format_margin(LINE, formatted_, MARGIN_SIZE);
        printf("%s", formatted_);
    }
    char _plus_formatted[4];
    _format_margin_side("+", _plus_formatted, MARGIN_SIZE);
    printf("%s", _plus_formatted);

    // print lateral lines
    for(int i = ys+1; i < yi+1; i++){
        gotoxy(xl-2, i);
        char formatted_[4];
        _format_margin_side("|", formatted_, MARGIN_SIZE);
        printf("%s", formatted_);
        for(int i = xl+1; i < xd; i++){
            char formatted_[10];
            _format_margin(LINE, formatted_, MARGIN_SIZE);
            printf("%s", formatted_);
        }

        printf("%s", formatted_);
    }

    gotoxy(xl+1, yi);
    //printf("+");
    for(int i = xl+1; i < xd; i++){
        char formatted_[10];
        _format_margin(LINE, formatted_, MARGIN_SIZE);
        printf("%s", formatted_);
    }
    printf("%s", _plus_formatted);

    // Print margins
    gotoxy(xl-2, ys);
    printf("%s", _plus_formatted);
    gotoxy(xl-2, yi);
    printf("%s", _plus_formatted);

    // Criar números
    int i_m = 0, j_m = 0;
    for(int i = ys+1; i < yi; i++){
            gotoxy(xl+1, i);
        for(int j = xl+1; j < xd; j++){
            //for(int i = 0; i < max_digits; i++){ printf(" ");}
            printf(BG_RED FG_GREEN BOLD);
            int num = MATRIX[i_m][j_m];

            char formatted_num[3];
            char s_num[3];
            sprintf(s_num, "%d", num);

            _format_num(num == 0 ? PLAYER : s_num, formatted_num, MARGIN_SIZE);
            if(num == 0){
                printf("%s| %s |",BG_PLAYER FG_PLAYER BOLD, formatted_num);
            }else{
                printf("|%s|", formatted_num);
            }

            if(num == size_x*size_y){
                break;
            }
            j_m++;
        }
        i_m++;
        j_m = 0;
    }

    printf(RESET "\n");
    printf("\n\n");
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
    //tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restaura o terminal (deixa desligado)

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
        //ungetc(ch, stdin);
        return 1; // Tecla pressionada
    }
    return 0; // Nenhuma tecla pressionada
}

/* Handle movement actions */
void handle_movement(char key){
  if(key == '\033'){
    getch();
    // Special keys (arrows)
      switch(getch()){
          case 'A':
              _move_up();
              break;
          case 'B':
              _move_down();
              break;
          case 'D':
              _move_left();
              break;
          case 'C':
              _move_right();
              break;
      }
      return;
  }
  // WASD keys
  switch(key){
    case 'w':
      _move_up();
      break;
    case 's':
      _move_down();
      break;
    case 'a':
      _move_left();
      break;
    case 'd':
      _move_right();
      break;
  }
}

/* Movement Actions */
void _move_up(){
    printf("UP");
}
void _move_down(){
    printf("DOWN");
}
void _move_left(){
    printf("LEFT");
}
void _move_right(){
    printf("RIGHT");
}

/* Matrix Functions */
void _create_matrix(int x, int y){
    // Cria o ponteiro para a matrix dependendo do tamanho dela
    MATRIX = (int **)malloc(sizeof (int*) * y);
    for (int i = 0; i < y; i++) {
        MATRIX[i] = (int *)malloc(sizeof (int) * x);
    }

    // Default Matrix values
    int num = 1;
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){
            MATRIX[i][j] = num;
            num++;

            if(num == x*y){
                PLAYER_X = j;
                PLAYER_Y = i;
                break;
            }
        }
    }

}
