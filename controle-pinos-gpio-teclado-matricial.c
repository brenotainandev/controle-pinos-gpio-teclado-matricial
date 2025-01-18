#include <stdio.h>
#include "pico/stdlib.h"


// Definição dos pinos de LEDs e buzzer
#define LED_VERMELHO 13
#define LED_AZUL 12
#define LED_VERDE 11
#define PINO_BUZZER 27

// Configuração do teclado matricial
#define COLUNAS 4
#define LINHAS 4

char mapa_teclado[16] = {
  '1', '2', '3', 'A',
  '4', '5', '6', 'B',
  '7', '8', '9', 'C',
  '*', '0', '#', 'D'
};

int pinos_colunas[COLUNAS] = {3, 2, 1, 0};
int pinos_linhas[LINHAS] = {8, 7, 6, 4};

// Inicializa o teclado matricial
void inicializar_teclado(int colunas[], int linhas[]) {
    // Colunas [entradas]
    for (int i = 0; i < LINHAS; i++) {
        gpio_init(linhas[i]);
        gpio_set_dir(linhas[i], GPIO_OUT);
        gpio_put(linhas[i], 1); // Linha inicializada em HIGH
    }
    // Linhas [saídas]
    for (int i = 0; i < COLUNAS; i++) {
        gpio_init(colunas[i]);
        gpio_set_dir(colunas[i], GPIO_IN);
        gpio_pull_up(colunas[i]); // Coluna com pull-up ativado
    }
}

// === Funções de Controle ===

// Lê o teclado e retorna o caractere pressionado
char ler_teclado(int colunas[], int linhas[], char mapa[]) {
    for (int linha = 0; linha < LINHAS; linha++) {
        gpio_put(linhas[linha], 0); // Define a linha como LOW

        for (int coluna = 0; coluna < COLUNAS; coluna++) {
            if (gpio_get(colunas[coluna]) == 0) { // Verifica se a tecla foi pressionada
                while (gpio_get(colunas[coluna]) == 0); // Aguarda a tecla ser liberada
                gpio_put(linhas[linha], 1); // Restaura a linha para HIGH
                return mapa[linha * COLUNAS + coluna];
            }
        }

        gpio_put(linhas[linha], 1); // Restaura a linha para HIGH
    }

    return 0; // Nenhuma tecla pressionada
}

// Pisca os LEDs com base no número de vezes
void piscar_leds(int vezes) {
    for (int i = 0; i < vezes; i++) {
        gpio_put(LED_VERMELHO, 1);
        gpio_put(LED_AZUL, 1);
        gpio_put(LED_VERDE, 1);
        sleep_ms(500);

        gpio_put(LED_VERMELHO, 0);
        gpio_put(LED_AZUL, 0);
        gpio_put(LED_VERDE, 0);
        sleep_ms(500);
    }
}

int main(){

    printf("Inicializando o sistema...\n");
    inicializar_leds(); // Configura os LEDs
    inicializar_teclado(pinos_colunas, pinos_linhas); // Configura o teclado
    stdio_init_all();

  while (true) {
    printf("Hello Wokwi! \n");
    sleep_ms(250);
  }
}