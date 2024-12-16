#include <stdio.h>

// "\033[0;0;0m"   reset/normal - desliga todos os atributos

// Tabela de cores

// Foreground
// BLACK    30 
// RED      31
// GREEN    32 
// YELLOW   33
// BLUE     34
// MAGENTA  35
// CYAN     36 
// WHITE    37

// Foreground Brilhante
// BRIGHT_BLACK 90
// BRIGHT_RED      91
// BRIGHT_GREEN    92 
// BRIGHT_YELLOW   93
// BRIGHT_BLUE     94
// BRIGHT_MAGENTA  95
// BRIGHT_CYAN     96
// BRIGHT_WHITE    97

//Background
// BLACK     40 
// RED       41
// GREEN     42 
// YELLOW    43
// BLUE      44
// MAGENTA   45
// CYAN      46 
// WHITE     47

// background Brilhante
// BRIGHT_BLACK    100
// BRIGHT_RED      101
// BRIGHT_GREEN    102 
// BRIGHT_YELLOW   103
// BRIGHT_BLUE     104
// BRIGHT_MAGENTA  105
// BRIGHT_CYAN     106
// BRIGHT_WHITE    107

int main() {
   printf("\033[0;0;0m");
   printf("Atributos normais\n");
   printf("\033[0;0;1m");
   printf("Negrito\n");
   printf("\033[0;0;2m");
   printf("Faint\n");
   printf("\033[0;0;2m");
   printf("Itálico\n"); // no GDB é o mesmo que Faint
   printf("\033[0;0;4m");
   printf("Sublinhado\n");
   printf("\033[0;0;5m");
   printf("Slow blink\n"); // não suportado no GDB
   printf("\033[0;0;6m");
   printf("Rapid blink\n"); // não suportado no GDB
   printf("\033[0;0;7m");
   printf("Reverse video\n"); // não suportado no GDB
   printf("\033[0;0;8m");
   printf("Conceal\n"); // não suportado no GDB
   printf("\033[0;0;9m");
   printf("Crossed-out\n"); // não suportado no GDB
   printf("\033[0;0;0m");
   printf("Default font\n"); // não suportado no GDB
   // troque as cores e efeitos abaixo trocando as constantes
   printf("\033[30;41;1m");
   printf("Hello World\n");
   printf("\033[31;42;2m");
   printf("Hello World\n");
   printf("\033[32;43;3m");
   printf("Hello World\n");
   printf("\033[33;44;4m");
   printf("Hello World");
   
   printf("\033[0;0;0m");
   return 0;
}