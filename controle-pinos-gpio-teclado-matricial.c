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

// Variáveis globais para senha
int senha_atual[4] = {0}; // Array para armazenar a senha digitada
int senha_correta[4] = {1, 2, 3, 4}; // Senha correta (1234 como exemplo)
int pos_senha = 0; // Posição atual da senha sendo digitada
bool modo_senha = false; // Flag para controlar se está no modo de inserção de senha

// Prototipação das funções
void inicializar_teclado(int colunas[4], int linhas[4]);
char ler_teclado();
bool verificar_senha();
void resetar_senha();

char tecla; // Variável que armazena o caractere lido

// Função para verificar a senha
bool verificar_senha() {
    for (int i = 0; i < 4; i++) {
        if (senha_atual[i] != senha_correta[i]) {
            return false;
        }
    }
    return true;
}

// Função para resetar a senha atual
void resetar_senha() {
    pos_senha = 0;
    for (int i = 0; i < 4; i++) {
        senha_atual[i] = 0;
    }
    modo_senha = false;
}

// Função principal
int main() {
    // Inicialização
    inicializar_teclado(pinos_colunas, pinos_linhas);
    stdio_init_all();
    
    // Configuração dos LEDs
    gpio_init(LED_VERMELHO);
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    while (true) {
        tecla = ler_teclado();
        
        if (tecla != 0) { // Se alguma tecla foi pressionada
            printf("Tecla retornada: %c \n", tecla);
            
            switch (tecla) {
                case '0':
                    if (!modo_senha) {
                        modo_senha = true;
                        pos_senha = 0;
                        printf("Modo senha ativado. Digite a senha de 4 digitos:\n");
                    }
                    break;
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    if (modo_senha && pos_senha < 4) {
                        senha_atual[pos_senha] = tecla - '0'; // Converte char para int
                        pos_senha++;
                        
                        if (pos_senha == 4) {
                            printf("\n");
                            if (verificar_senha()) {
                                printf("Senha correta!\n");
                                gpio_put(LED_VERDE, 1);
                                sleep_ms(1000);
                                gpio_put(LED_VERDE, 0);
                            } else {
                                printf("Senha incorreta!\n");
                                gpio_put(LED_VERMELHO, 1);
                                sleep_ms(1000);
                                gpio_put(LED_VERMELHO, 0);
                            }
                            resetar_senha();
                        }
                    }
                    break;
                case '*': // Cancelar a entrada da senha
                    if (modo_senha) {
                        printf("\nEntrada de senha cancelada\n");
                        resetar_senha();
                    }
                    break;
            }
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