#include "menu.h"
#include "util.h"

// Configuracoes do menu options
int GAME_WIDTH = 3;
int GAME_HEIGHT = 3;

// Função para exibir o cabeçalho
void _exibir_cabecalho(const char *titulo) {
   clrscr(); // Limpa a tela
   printf(BG_BLACK FG_GREEN BOLD); // Estilo do cabeçalho
   printf(" %s ", titulo);
   printf(RESET "\n\n"); // Reseta estilos após o cabeçalho
}

// Função para exibir o menu interativo apenas com opcoes para selecionar
int _mostrar_menu_interativo(const char *opcoes[], int n, const char *titulo) {
   int selecionado = 0;

   while (1) {
      _exibir_cabecalho(titulo); // Mostra o cabeçalho

      // Exibe as opções do menu
      for (int i = 0; i < n; i++) {
         char opcao_formatada[MENU_WIDTH + 1];
         _formatar_opcao(opcoes[i], opcao_formatada, MENU_WIDTH, "");

         if (i == selecionado) {
            printf( BG_BBLACK FG_GREEN " %s " RESET "\n", opcao_formatada); // Destaca a opção com vídeo reverso
         } else {
            printf( BG_BLACK FG_WHITE " %s\n" RESET, opcao_formatada);
         }
      }

      // Lê a tecla pressionada
      int ch = getch();

      if (ch == '\033') { // Tecla especial (setas)
         getch(); // Ignora '['
         ch = getch();
      }else if (ch == KEY_ENTER) {
         break;
      }

      switch (ch) {
         case KEY_UP:
         case KEY_W:
            if (selecionado > 0) selecionado--;
            else selecionado = n-1;
            break;
         case KEY_DOWN:
         case KEY_S:
            if (selecionado < n - 1) selecionado++;
            else selecionado = 0;
            break;
      }
   }

   return selecionado;
}

// Função para exibir o menu interativo de opcoes
// Menu especial, com opcoes de valores que podem ser alterados
int _mostrar_options(const char *opcoes[], int n, const char *titulo, int *variaveis) {
   int selecionado = 0;

   while (1) {
      _exibir_cabecalho(titulo); // Mostra o cabeçalho

      // Exibe as opções do menu
      for (int i = 0; i < n; i++) {
         char opcao_formatada[MENU_WIDTH + 1];
         _formatar_variavel(opcoes[i], opcao_formatada, MENU_WIDTH, variaveis[i]);

         if (i == selecionado) {
            printf(BG_BBLACK FG_GREEN " %s " RESET "\n", opcao_formatada); // Destaca a opção com vídeo reverso
         } else {
            printf(BG_BLACK FG_WHITE " %s\n" RESET, opcao_formatada);
         }
      }
      printf("Press Enter to confirm\n");

      // Lê a tecla pressionada
      int ch = getch();

      if (ch == '\033') { // Tecla especial (setas)
         getch(); // Ignora '['
         ch = getch();
      }else if (ch == KEY_ENTER) {
         break;
      }

      switch (ch) {
         case KEY_UP:
         case KEY_W:
            if (selecionado > 0) selecionado--;
            else selecionado = n-1; // Para "Rolagem infinita" no menu funcionar
         break;
         case KEY_DOWN:
         case KEY_S:
            if (selecionado < n - 1) selecionado++;
            else selecionado = 0; // Para "Rolagem infinita" no menu funcionar
         break;
         case KEY_RIGHT:
         case KEY_D:
            variaveis[selecionado] < 20 ? variaveis[selecionado]++ : 0; // Limita o valor maximo das variaveis
         break;
         case KEY_LEFT:
         case KEY_A:
            variaveis[selecionado] <= 3 ? 0 : variaveis[selecionado]--; // Limita o valor minimo das variaveis
         break;
      }
   }

   return selecionado;
}

// Height e Width getters
int get_height(){
  return GAME_HEIGHT;
}
int get_width(){
  return GAME_WIDTH;
}

int start_menu() {
   // Configuração do menu
   const char *titulo = "QUADRADO MÁGICO";
   const char *opcoes[] = {
      "Start",
      "Options",
      "Exit"
   };
   const char *options[] = {
      "Width",
      "Height"
   };

   int variaveis[] = {
      GAME_WIDTH,
       GAME_HEIGHT,
   };

   while (1) {
      int n = sizeof(opcoes) / sizeof(opcoes[0]);

      // Mostra o menu e obtém a escolha
      int escolha = _mostrar_menu_interativo(opcoes, n, titulo);

      // Resultado de cada opcao escolhida
      if(!strcmp(opcoes[escolha], "Options")){
         int options_menu = _mostrar_options(options, 2, titulo, variaveis); // Carrega Menu de opcoes
      }else if(!strcmp(opcoes[escolha], "Start")){
         GAME_WIDTH = variaveis[0]; // Atualiza as variaveis do tamanho do tabuleiro do jogo
         GAME_HEIGHT = variaveis[1];
         return 1; // Retorna 1 para iniciar o jogo
      }else{
         break;
      }
   }

   return 0;
}
