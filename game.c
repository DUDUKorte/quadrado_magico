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
int start(int x, int y, int init_pos, int margin_size){ // Inicializa tudo necessario para comecar o jogo

    // Variaveis globais
    SIZE_X = x;
    SIZE_Y = y;
    INIT_POS = init_pos;
    MARGIN_SIZE = margin_size;
    MATRIX_POINTS = (SIZE_X * SIZE_Y) - 1;

    // Generate Matrix
    // Save Matrix
    int allocation_failure = _create_matrix(x, y); // Retorna True(1) se houver erros

    if(allocation_failure){
        // INTERROMPER INICIALIZAÇÃO
        return 1;
    }

    // Show Original Matrix before randomize
    show_original_matrix(5);

    // Randomize matrix
    randomize_matrix();

    // Create Window First time
    create_window();
    PLAYER_IS_DEAD = 0;

    return 0; // NENHUM ERRO
}

/* Show original matrixz before randomize */
void show_original_matrix(int wait_time){
    create_window();
    printf("PRESS ANY KEY...\n");
    char pressed_key = getch();
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

    // Format Margin simbols
    char _plus_formatted[4];
    _format_margin_side("+", _plus_formatted, MARGIN_SIZE);

    char formatted_margin[8];
    _formatar_opcao("", formatted_margin, MARGIN_SIZE+1, "-");

    char side_formatted[4];
    _format_margin_side("|", side_formatted, MARGIN_SIZE);

    // print top/bottom lines
    for(int i = xl+1; i < xd+((SIZE_X-1)*MARGIN_SIZE); i+=MARGIN_SIZE+1){
      	gotoxy(i, ys);
        printf("%s", formatted_margin);
        gotoxy(i, yi);
        printf("%s", formatted_margin);
    }

    // print lateral lines
    for(int i = ys+1; i < yi+1; i++){
        gotoxy(xl-2, i);
        printf("%s", side_formatted);

		gotoxy(xd+(SIZE_X*MARGIN_SIZE), i);
        printf("%s", side_formatted);
    }

    // Print corner margins
    gotoxy(xl-2, ys);
    printf("%s", _plus_formatted);
    gotoxy(xl-2, yi);
    printf("%s", _plus_formatted);
    gotoxy(xd+(SIZE_X*MARGIN_SIZE), ys);
    printf("%s", _plus_formatted);
    gotoxy(xd+(SIZE_X*MARGIN_SIZE), yi);
    printf("%s", _plus_formatted);

    // Criar números
    int i_m = 0, j_m = 0; // index i e j da matriz
    for(int i = ys+1; i < yi; i++){
            gotoxy(xl+1, i);
        for(int j = xl+1; j < xd; j++){
            printf(BG_RED FG_GREEN BOLD);
            int num = MATRIX[i_m][j_m];

            char formatted_num[3];
            char s_num[3];
            sprintf(s_num, "%d", num);

            _format_num(num == 0 ? PLAYER : s_num, formatted_num, MARGIN_SIZE);

            if(num == 0){ // is the player
                printf("%s| %s |",BG_PLAYER FG_PLAYER BOLD, formatted_num);
                MATRIX_TEMPLATE[i_m][j_m] = 0; // Marca ponto como local do player
            }else if(num == j_m+1 + (SIZE_X * i_m)){ // se for o numero certo na matrix
                printf("%s|%s|", BG_WHITE_2 FG_GREEN BOLD, formatted_num);
                MATRIX_TEMPLATE[i_m][j_m] = 1; // Marca ponto como correto
            }else{ // numero no lugar errado da matrix
            	printf("|%s|", formatted_num);
                MATRIX_TEMPLATE[i_m][j_m] = 0; // Marca ponto como errado
            }

            PLAYER_POINTS += 1 * MATRIX_TEMPLATE[i_m][j_m]; // Contabiliza os pontos

            if(num == size_x*size_y){ // Chegou no ultimo numero da matriz
                break;
            }
            j_m++;
        }
        i_m++;
        j_m = 0;
    }

    // Prints ao final da janela
    printf(RESET "\n\n");
    printf(FG_GREEN BOLD "TOTAL MOVEMENTS: %d\n", MVT_COUNTER);
    printf("Press F to Give Up\n");
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
int _create_matrix(int x, int y){
    // Cria o ponteiro para a matrix dependendo do tamanho dela
    MATRIX = (int **)malloc(sizeof (int*) * y);
    if(!MATRIX){
        // ERRO NA ALOCAÇÃO
        return 1;
    }
    for (int i = 0; i < y; i++) {
        MATRIX[i] = (int *)malloc(sizeof (int) * x);
        if(!MATRIX[i]){
            // ERRO NA ALOCAÇÃO
            return 1;
        }
    }

    // Cria o ponteiro para a matrix template dependendo do tamanho dela
    MATRIX_TEMPLATE = (int **)malloc(sizeof (int*) * y);
    if(!MATRIX_TEMPLATE){
        return 1;
    }
    for (int i = 0; i < y; i++) {
        MATRIX_TEMPLATE[i] = (int *)malloc(sizeof (int) * x);
        if(!MATRIX_TEMPLATE[i]){
            return 1;
        }
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

    return 0;
}

void randomize_matrix(){
	srand(time(NULL)); // Randomize seed
	char movements[4] = {'w', 'a', 's', 'd'}; // possible movements
    int qtd_movements[4] = {0}; // how many movements made with i key
	int min, max;
    min = SIZE_X*SIZE_Y*3;
    max = SIZE_X*SIZE_Y*5;

    int num = rand() % (max - min + 1) + min; // select random numver of movements
    //printf("RANDOM NUMBER: %d\n", num);

    char tmp_movement = ' ';

    for(int i = 0; i < num; i++){
      int movement_choice = rand() % 4; // choose a movement
      qtd_movements[movement_choice] += 1; // add movement to i key

      if(movement_choice != tmp_movement){ // Caso tenha mudado a tecla antes de fazer 3 movimentos seguidos
        qtd_movements[tmp_movement] = 0;
      }

      // Algoritmo para evitar fazer mais de 3 movimentos iguais seguidos
      if(qtd_movements[movement_choice] > 3){
		do{
			movement_choice = rand() % 4;
			if(!(movement_choice == tmp_movement)){
            	qtd_movements[tmp_movement] = 0;
			}
		}while(qtd_movements[movement_choice] > 3); // Escolhe um numero aleatorio ate ser um diferente do anterior
      }

      handle_movement(movements[movement_choice]);
      tmp_movement = movement_choice;
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
