#include <stdio.h>
#include "pico/stdlib.h"

// Definição dos pinos de LEDs
#define LED_VERMELHO 13
#define LED_AZUL 12
#define LED_VERDE 11

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
int senha_atual[4] = {0};      // Armazena a senha digitada
int senha_correta[4] = {1, 2, 3, 4}; // Senha correta (1234)
int pos_senha = 0;             // Posição atual da senha
bool modo_senha = false;       // Controle do modo de senha

// Prototipação das funções
void inicializar_teclado(int colunas[4], int linhas[4]);
char ler_teclado();
bool verificar_senha();
void resetar_senha();
void acender_led(char tecla);
void inicializar_leds();
void piscar_leds(int vezes);

// === Função Principal ===
int main() {
    // Inicializações
    inicializar_teclado(pinos_colunas, pinos_linhas);
    inicializar_leds();
    stdio_init_all();

    printf("Sistema inicializado. Aguardando comandos...\n");

    while (true) {
        char tecla = ler_teclado();

        if (tecla != 0) { // Se alguma tecla foi pressionada
            printf("Tecla retornada: %c \n", tecla);

            switch (tecla) {
                case '0': // Ativar modo senha
                    if (!modo_senha) {
                        modo_senha = true;
                        pos_senha = 0;
                        printf("Modo senha ativado. Digite a senha de 4 dígitos:\n");
                    }
                    break;

                case '1' ... '9': // Entrada de senha ou piscar LEDs
                    if (modo_senha) {
                        if (pos_senha < 4) {
                            senha_atual[pos_senha] = tecla - '0'; // Converte char para int
                            pos_senha++;
                            printf("Dígito %d registrado.\n", tecla - '0');

                            if (pos_senha == 4) { // Quando 4 dígitos forem digitados
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
                    } else {
                        piscar_leds(tecla - '0');
                    }
                    break;

                case '*': // Cancelar entrada de senha
                    if (modo_senha) {
                        printf("Entrada de senha cancelada.\n");
                        resetar_senha();
                    }
                    // caso não esteja no modo senha, pode chamar uma função para ativar o buzzer
                    break;

                case 'A':
                case 'B':
                case 'C':
                case 'D':
                    acender_led(tecla);
                    break;

                default:
                    printf("Nenhuma ação associada à tecla %c.\n", tecla);
            }
        }
        sleep_ms(100);
    }
}

// === Funções Auxiliares ===

// Inicializa os pinos do teclado matricial
void inicializar_teclado(int colunas[4], int linhas[4]) {
    for (int i = 0; i < 4; i++) {
        // Configura as colunas como entradas
        gpio_init(colunas[i]);
        gpio_set_dir(colunas[i], GPIO_IN);
        gpio_pull_up(colunas[i]);

        // Configura as linhas como saídas
        gpio_init(linhas[i]);
        gpio_set_dir(linhas[i], GPIO_OUT);
        gpio_put(linhas[i], 1);
    }
}

// Lê o caractere pressionado no teclado matricial
char ler_teclado() {
    char leitura = 0;
    for (int linha = 0; linha < 4; linha++) {
        gpio_put(pinos_linhas[linha], 0); // Define a linha como LOW
        for (int coluna = 0; coluna < 4; coluna++) {
            if (gpio_get(pinos_colunas[coluna]) == 0) { // Verifica se a tecla foi pressionada
                leitura = teclado[linha][coluna];
                while (gpio_get(pinos_colunas[coluna]) == 0); // Aguarda a tecla ser liberada
                gpio_put(pinos_linhas[linha], 1); // Restaura a linha para HIGH
                return leitura;
            }
        }
        gpio_put(pinos_linhas[linha], 1); // Restaura a linha para HIGH
    }
    return leitura;
}

// Inicializa os LEDs
void inicializar_leds() {
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_put(LED_VERMELHO, 0);

    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_put(LED_AZUL, 0);

    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_put(LED_VERDE, 0);
}

// Verifica se a senha digitada está correta
bool verificar_senha() {
    for (int i = 0; i < 4; i++) {
        if (senha_atual[i] != senha_correta[i]) {
            return false;
        }
    }
    return true;
}

// Reseta a senha atual e sai do modo senha
void resetar_senha() {
    pos_senha = 0;
    for (int i = 0; i < 4; i++) {
        senha_atual[i] = 0;
    }
    modo_senha = false;
}

// Acende LEDs com base na tecla pressionada
void acender_led(char tecla) {
    switch (tecla) {
        case 'A':
            gpio_put(LED_VERDE, 1);
            sleep_ms(500);
            gpio_put(LED_VERDE, 0);
            break;
        case 'B':
            gpio_put(LED_AZUL, 1);
            sleep_ms(500);
            gpio_put(LED_AZUL, 0);
            break;
        case 'C':
            gpio_put(LED_VERMELHO, 1);
            sleep_ms(500);
            gpio_put(LED_VERMELHO, 0);
            break;
        case 'D':
            gpio_put(LED_VERDE, 1);
            gpio_put(LED_AZUL, 1);
            gpio_put(LED_VERMELHO, 1);
            sleep_ms(500);
            gpio_put(LED_VERDE, 0);
            gpio_put(LED_AZUL, 0);
            gpio_put(LED_VERMELHO, 0);
            break;
    }
}

// Pisca todos os LEDs um número de vezes
void piscar_leds(int vezes) {
    for (int i = 0; i < vezes; i++) {
        gpio_put(LED_VERDE, 1);
        gpio_put(LED_AZUL, 1);
        gpio_put(LED_VERMELHO, 1);
        sleep_ms(500);
        gpio_put(LED_VERDE, 0);
        gpio_put(LED_AZUL, 0);
        gpio_put(LED_VERMELHO, 0);
        sleep_ms(500);
    }
}
