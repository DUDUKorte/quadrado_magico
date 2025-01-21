// Funções Do Jogo Principal -----------------------------------------------------------------------

/* Start function */
int start(int x, int y, int init_pos, int margin_size);

/* Show original matrixz before randomize */
void show_original_matrix(int wait_time);

/* Cria janela do jogo */
void create_window();

/* Handle movement actions */
void handle_movement(char key);

/* Movement Actions */
void _move_up();
void _move_down();
void _move_left();
void _move_right();

/* Matrix Functions */
int _create_matrix(int x, int y);
void randomize_matrix();

/* Player functions */
int on_player_win();
int on_player_lose();

/* Free matrix allocations */
void close_game();