#include "game.h"
#include "util.h"

// Variaveis Globais
int **MATRIX; // Matriz em tempo real com os valores
int **MATRIX_TEMPLATE; // Matriz de 0 e 1 que determina se o numero ixj esta na posicao correta ou nao
int INIT_POS, MARGIN_SIZE, SIZE_X, SIZE_Y, MATRIX_POINTS = 0, MVT_COUNTER = 0; // variaveis globais para as configuracoes do tabuleiro
int PLAYER_X, PLAYER_Y, PLAYER_POINTS = 0, PLAYER_IS_DEAD = 0; // Variaveis globais do jogador
char PLAYER[] = "\u25A0"; // Icone do jogador em unicode (3 caracteres)

// Funções Do Jogo Principal -----------------------------------------------------------------------

/* Start function */
void start(int x, int y, int init_pos, int margin_size){ // Inicializa tudo necessario para comecar o jogo

    // Variaveis globais
    SIZE_X = x;
    SIZE_Y = y;
    INIT_POS = init_pos;
    MARGIN_SIZE = margin_size;
    MATRIX_POINTS = (SIZE_X * SIZE_Y) - 1;

    // Generate Matrix
    // Save Matrix
    _create_matrix(x, y);

    // Show Original Matrix before randomize
    show_original_matrix(5);

    // Randomize matrix
    randomize_matrix();

    // Create Window First time
    create_window();
}

/* Show original matrixz before randomize */
void show_original_matrix(int wait_time){
    for(int i = wait_time; i > 0; i--){
        create_window();
        printf("STARTING IN... %d\n", i);

        usleep(1000000); // Wait 1 second each loop
    }
}

/* Cria janela do jogo */
void create_window(){
    clrscr();
    int size_x = SIZE_X + 1;
    int size_y = SIZE_Y + 1;
    int xl = INIT_POS, ys = INIT_POS;
    int xd = xl + (size_x);
    int yi = ys + size_y;
    PLAYER_POINTS = 0;

    printf(BG_BLACK FG_WHITE BOLD);

    // print top lines
    gotoxy(xl+1, ys);
    for(int i = xl+1; i < xd; i++){
        char formatted_[10];
        _formatar_opcao("", formatted_, MARGIN_SIZE+1, "-");
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
            _formatar_opcao("", formatted_, MARGIN_SIZE+1, "");
            printf("%s", formatted_);
        }

        printf("%s", formatted_);
    }

    // print bottom lines
    gotoxy(xl+1, yi);
    for(int i = xl+1; i < xd; i++){
        char formatted_[10];
        _formatar_opcao("", formatted_, MARGIN_SIZE+1, "-");
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

            if(num == 0){ // [e o player
                printf("%s| %s |",BG_PLAYER FG_PLAYER BOLD, formatted_num);
                MATRIX_TEMPLATE[i_m][j_m] = 0; // Marca ponto como local do player
            }else if(num == j_m+1 + (SIZE_X * i_m)){ // se for o n[umero certo na matrix
                printf("%s|%s|", BG_WHITE_2 FG_GREEN BOLD, formatted_num);
                MATRIX_TEMPLATE[i_m][j_m] = 1; // Marca ponto como correto
            }else{ // n[umero no lugar errado da matrix
            	printf("|%s|", formatted_num);
                MATRIX_TEMPLATE[i_m][j_m] = 0; // Marca ponto como errado
            }

            PLAYER_POINTS += 1 * MATRIX_TEMPLATE[i_m][j_m]; // Contabiliza os pontos

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
    printf(FG_GREEN BOLD);
    printf("TOTAL MOVEMENTS: %d\n", MVT_COUNTER);
    printf(RESET);
}

/* Handle movement actions */
void handle_movement(char key){
  if(key == '\033'){
    getch();
    // Special keys (arrows)
      switch(getch()){
          case KEY_UP:
              _move_up();
              break;
          case KEY_DOWN:
              _move_down();
              break;
          case KEY_LEFT:
              _move_left();
              break;
          case KEY_RIGHT:
              _move_right();
              break;
      }
      return;
  }
  // WASD keys
  switch(key){
    case KEY_W:
      _move_up();
      break;
    case KEY_S:
      _move_down();
      break;
    case KEY_A:
      _move_left();
      break;
    case KEY_D:
      _move_right();
      break;
    case KEY_F:
      PLAYER_IS_DEAD = 1;
      break;
  }
}

/* Movement Actions */
void _move_up(){
    if(PLAYER_Y+1 >= SIZE_Y){
      return;
    }

    MATRIX[PLAYER_Y][PLAYER_X] = MATRIX[PLAYER_Y+1][PLAYER_X];
    MATRIX[PLAYER_Y+1][PLAYER_X] = 0;
    PLAYER_Y++;
    MVT_COUNTER += 1;

}
void _move_down(){
    if(PLAYER_Y-1 < 0){
      return;
    }

    MATRIX[PLAYER_Y][PLAYER_X] = MATRIX[PLAYER_Y-1][PLAYER_X];
    MATRIX[PLAYER_Y-1][PLAYER_X] = 0;
    PLAYER_Y--;
    MVT_COUNTER += 1;

}
void _move_left(){
    if(PLAYER_X+1 >= SIZE_X){
      return;
    }

    MATRIX[PLAYER_Y][PLAYER_X] = MATRIX[PLAYER_Y][PLAYER_X+1];
    MATRIX[PLAYER_Y][PLAYER_X+1] = 0;
    PLAYER_X++;
    MVT_COUNTER += 1;

}
void _move_right(){
    if(PLAYER_X-1 < 0){
      return;
    }

    MATRIX[PLAYER_Y][PLAYER_X] = MATRIX[PLAYER_Y][PLAYER_X-1];
    MATRIX[PLAYER_Y][PLAYER_X-1] = 0;
    PLAYER_X--;
    MVT_COUNTER += 1;

}

/* Matrix Functions */
void _create_matrix(int x, int y){
    // Cria o ponteiro para a matrix dependendo do tamanho dela
    MATRIX = (int **)malloc(sizeof (int*) * y);
    for (int i = 0; i < y; i++) {
        MATRIX[i] = (int *)malloc(sizeof (int) * x);
    }

    // Cria o ponteiro para a matrix template dependendo do tamanho dela
    MATRIX_TEMPLATE = (int **)malloc(sizeof (int*) * y);
    for (int i = 0; i < y; i++) {
        MATRIX_TEMPLATE[i] = (int *)malloc(sizeof (int) * x);
    }

    // Default Matrix values
    int num = 1;
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){
            if(num == x*y){
                PLAYER_X = j;
                PLAYER_Y = i;
                break;
            }

            MATRIX[i][j] = num;
            MATRIX_TEMPLATE[i][j] = 0;
            num++;
        }
    }

}

void randomize_matrix(){
	srand(time(NULL));
	char movements[4] = {'w', 'a', 's', 'd'};
    int qtd_movements[4] = {0};
	int min, max;
    min = SIZE_X*SIZE_Y*3;
    max = SIZE_X*SIZE_Y*5;

    int num = rand() % (max - min + 1) + min;
    printf("RANDOM NUMBER: %d\n", num);


    for(int i = 0; i < num; i++){
      int movement_choice = rand() % 4;
      qtd_movements[movement_choice] += 1;

      if(qtd_movements[movement_choice] > 3){
        char tmp_movement = movement_choice;
		do{
			movement_choice = rand() % 4;
			if(!(movement_choice == tmp_movement)){
            	qtd_movements[tmp_movement] = 0;
			}
		}while(qtd_movements[movement_choice] > 3);
      }

      handle_movement(movements[movement_choice]);
    }
    MVT_COUNTER = 0;

}

/* Player functions */
int on_player_win(){
	return PLAYER_POINTS >= MATRIX_POINTS;
}

int on_player_lose(){
    return PLAYER_IS_DEAD;
}

/* Free matrix allocations */
void close_game(){
    for(int i = 0; i < SIZE_Y; i++){
      free(MATRIX[i]);
    }
    free(MATRIX);

    for(int i = 0; i < SIZE_Y; i++){
        free(MATRIX_TEMPLATE[i]);
    }
    free(MATRIX_TEMPLATE);
}
