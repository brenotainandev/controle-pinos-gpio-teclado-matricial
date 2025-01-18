#include <stdio.h>
#include "pico/stdlib.h"

// Definição dos pinos de LEDs e buzzer
#define LED_VERMELHO 13
#define LED_AZUL 12
#define LED_VERDE 11
#define PINO_BUZZER 27

// Configuração do teclado matricial
char teclado[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

int pinos_colunas[4] = {3, 2, 1, 0};
int pinos_linhas[4] = {8, 7, 6, 4};

// Prototipação das funções
void inicializar_teclado(int colunas[4], int linhas[4]); // Função para inicializar os pinos do teclado
char ler_teclado(); // Função para ler o teclado

char tecla; // Variável que armazena o caractere lido

// Função principal
int main() {
    inicializar_teclado(pinos_colunas, pinos_linhas); // Inicializa o teclado
    stdio_init_all(); // Inicializa a saída padrão

    while (true) {
        tecla = ler_teclado(); // Lê o caractere do teclado
        printf("Tecla retornada: %c \n", tecla);
        switch (tecla) {
            case '1':
                break;
            case '2':
                break;
            case '3':
                break;
            default:
                break;
        }
        sleep_ms(100); // Pequeno atraso
    }
}

// Função para inicializar os pinos do teclado matricial
void inicializar_teclado(int colunas[4], int linhas[4]) {
    for (int i = 0; i < 4; i++) {
        // Configuração das colunas como entradas
        gpio_init(colunas[i]);
        gpio_set_dir(colunas[i], GPIO_IN);
        gpio_pull_up(colunas[i]); // Configura pull-up interno

        // Configuração das linhas como saídas
        gpio_init(linhas[i]);
        gpio_set_dir(linhas[i], GPIO_OUT);
        gpio_put(linhas[i], 1); // Configura o estado inicial como HIGH
    }
}

// Função para ler o caractere pressionado no teclado matricial
char ler_teclado() {
    char leitura = 0;

    for (int linha = 0; linha < 4; linha++) {
        gpio_put(pinos_linhas[linha], 0); // Define a linha como LOW
        uint32_t estados_gpio = gpio_get_all();

        for (int coluna = 0; coluna < 4; coluna++) {
            if (!(estados_gpio & (1u << pinos_colunas[coluna]))) { // Verifica se a tecla foi pressionada
                leitura = teclado[linha][coluna];
                sleep_ms(100); // Debounce simples
            }
        }

        gpio_put(pinos_linhas[linha], 1); // Restaura a linha para HIGH
    }

    return leitura; // Retorna o caractere pressionado
}
