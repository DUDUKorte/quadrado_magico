#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

#define RESET "\033[0m"
#define BOLD "\033[1m"
#define REVERSE "\033[7m"
#define FG_WHITE "\033[37m"
#define BG_BLUE "\033[44m"

// Configuração para teclas
#define KEY_UP 65
#define KEY_DOWN 66
#define KEY_ENTER 10

// Comprimento máximo de uma linha do menu
#define MENU_WIDTH 10 

// Configuração de terminal
void configurar_terminal(struct termios *old) {
   struct termios new;
   tcgetattr(STDIN_FILENO, old);
   new = *old;
   new.c_lflag &= ~(ICANON | ECHO);
   tcsetattr(STDIN_FILENO, TCSANOW, &new);
}

void restaurar_terminal(struct termios *old) {
   tcsetattr(STDIN_FILENO, TCSANOW, old);
}

// Função para exibir o cabeçalho
void exibir_cabecalho(const char *titulo) {
   printf("\033[H\033[J"); // Limpa a tela
   printf(BG_BLUE FG_WHITE BOLD); // Estilo do cabeçalho
   printf(" %s ", titulo);
   printf(RESET "\n\n"); // Reseta estilos após o cabeçalho
}

// Função para formatar uma string com tamanho fixo
void formatar_opcao(const char *opcao, char *saida, int largura) {
   int len = strlen(opcao);
   int padding = largura - len; // Espaços para completar
   if (padding < 0) padding = 0; // Evita valores negativos
   snprintf(saida, largura + 1, "%s%*s", opcao, padding, ""); // Adiciona espaços ao final
}

// Função para exibir o menu interativo
int mostrar_menu_interativo(const char *opcoes[], int n, const char *titulo) {
   int selecionado = 0;
   struct termios terminal_original;

   configurar_terminal(&terminal_original);

   while (1) {
      exibir_cabecalho(titulo); // Mostra o cabeçalho

      // Exibe as opções do menu
      for (int i = 0; i < n; i++) {
         char opcao_formatada[MENU_WIDTH + 1];
         formatar_opcao(opcoes[i], opcao_formatada, MENU_WIDTH);

         if (i == selecionado) {
            printf(REVERSE " %s " RESET "\n", opcao_formatada); // Destaca a opção com vídeo reverso
         } else {
            printf(" %s\n", opcao_formatada);
         }
      }

      // Lê a tecla pressionada
      int ch = getchar();
      if (ch == '\033') { // Tecla especial (setas)
         getchar(); // Ignora '['
         switch (getchar()) {
            case KEY_UP:
               if (selecionado > 0) selecionado--;
               else selecionado = n-1;
               break;
            case KEY_DOWN:
               if (selecionado < n - 1) selecionado++;
               else selecionado = 0;
               break;
         }
      } else if (ch == KEY_ENTER) {
         break; // Sai do loop ao pressionar Enter
      }
   }
   restaurar_terminal(&terminal_original);
   return selecionado;
}

int main() {
   // Configuração do menu
   const char *titulo = "MENU PRINCIPAL";
   const char *opcoes[] = {
      "Start",
      "Options",
      "Exit"
   };
   int n = sizeof(opcoes) / sizeof(opcoes[0]);

   // Mostra o menu e obtém a escolha
   int escolha = mostrar_menu_interativo(opcoes, n, titulo);

   // Exibe a escolha selecionada
   exibir_cabecalho("VOCÊ ESCOLHEU");
   printf("Opção selecionada: %s\n\n", opcoes[escolha]);
   return 0;
}
