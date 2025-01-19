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
    {'*', '0', '#', 'D'}};
int pinos_colunas[4] = {5, 4, 3, 2};
int pinos_linhas[4] = {9, 8, 7, 6};

// Variáveis globais para senha
int senha_atual[4] = {0};            // Array para armazenar a senha digitada
int senha_correta[4] = {1, 2, 3, 4}; // Senha correta (1234 como exemplo)
int pos_senha = 0;                   // Posição atual da senha sendo digitada
bool modo_senha = false;             // Flag para controlar se está no modo de inserção de senha
char tecla;                          // Variável que armazena o caractere lido
bool exibicao_habilitada = true;     // Flag para controlar a exibição de saída do teclado

// Habilita o stdout para impressão no terminal
void habilitar_exibicao()
{
    stdio_set_driver_enabled(&stdio_usb, true);
    stdio_set_driver_enabled(&stdio_uart, true);
    exibicao_habilitada = true;
}

// Desabilita o stdout para impressão no terminal
void desabilitar_exibicao()
{
    stdio_set_driver_enabled(&stdio_usb, false);
    stdio_set_driver_enabled(&stdio_uart, false);
    exibicao_habilitada = false;
}

// Função para acionamento do buzzer
void acionamento_buzzer(int duration)
{
    duration /= 2; // Divide a duração por 2 para gerar pulsos mais curtos
    for (int i = 0; i < duration; i++)
    {
        gpio_put(PINO_BUZZER, 1);
        sleep_us(500); // Meio período do ciclo
        gpio_put(PINO_BUZZER, 0);
        sleep_us(500); // Meio período do ciclo
    }
}

// Função para verificar a senha
bool verificar_senha()
{
    for (int i = 0; i < 4; i++)
    {
        if (senha_atual[i] != senha_correta[i])
        {
            return false;
        }
    }
    return true;
}

// Função para resetar a senha atual
void resetar_senha()
{
    pos_senha = 0;
    for (int i = 0; i < 4; i++)
    {
        senha_atual[i] = 0;
    }
    modo_senha = false;
}

// Função para acender LEDs com base na tecla
void acender_led(char tecla)
{
    switch (tecla)
    {
    case 'A':
        gpio_put(LED_VERDE, 1); // Liga o LED verde
        sleep_ms(500);
        gpio_put(LED_VERDE, 0);
        break;
    case 'B':
        gpio_put(LED_AZUL, 1); // Liga o LED azul
        sleep_ms(500);
        gpio_put(LED_AZUL, 0);
        break;
    case 'C':
        gpio_put(LED_VERMELHO, 1); // Liga o LED vermelho
        sleep_ms(500);
        gpio_put(LED_VERMELHO, 0);
        break;
    case 'D':
        gpio_put(LED_VERMELHO, 1); // Liga todos os LEDs
        gpio_put(LED_VERDE, 1);
        gpio_put(LED_AZUL, 1);
        sleep_ms(500);
        gpio_put(LED_VERMELHO, 0);
        gpio_put(LED_VERDE, 0);
        gpio_put(LED_AZUL, 0);
        break;
    default:
        gpio_put(LED_VERMELHO, 0); // Desliga todos
        gpio_put(LED_AZUL, 0);
        gpio_put(LED_VERDE, 0);
        sleep_ms(500);

        break;
    }
}

// Função para inicializar os pinos do teclado matricial
void inicializar_teclado(int colunas[4], int linhas[4])
{
    for (int i = 0; i < 4; i++)
    {
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
char ler_teclado()
{
    char leitura = 0;
    for (int linha = 0; linha < 4; linha++)
    {
        gpio_put(pinos_linhas[linha], 0); // Define a linha como LOW
        uint32_t estados_gpio = gpio_get_all();
        for (int coluna = 0; coluna < 4; coluna++)
        {
            if (!(estados_gpio & (1u << pinos_colunas[coluna])))
            { // Verifica se a tecla foi pressionada
                leitura = teclado[linha][coluna];
                sleep_ms(100); // Debounce simples
            }
        }
        gpio_put(pinos_linhas[linha], 1); // Restaura a linha para HIGH
    }
    return leitura; // Retorna o caractere pressionado
}

// Função principal
int main()
{
    // Inicialização do stdio
    stdio_init_all();
    // Inicialização do teclado
    inicializar_teclado(pinos_colunas, pinos_linhas);

    // Configuração dos LEDs
    gpio_init(LED_VERMELHO);
    gpio_init(LED_VERDE);
    gpio_init(LED_AZUL);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_set_dir(LED_AZUL, GPIO_OUT);

    // Configuração do buzzer
    gpio_init(PINO_BUZZER);
    gpio_set_dir(PINO_BUZZER, GPIO_OUT);

    while (true)
    {
        tecla = ler_teclado();

        if (tecla != 0)
        { // Se alguma tecla foi pressionada
            printf("Tecla retornada: %c \n", tecla);
            acionamento_buzzer(100); // Aciona o buzzer por 1s
            switch (tecla)
            {
            case '0':
                if (!modo_senha)
                {
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
                if (modo_senha && pos_senha < 4)
                {
                    senha_atual[pos_senha] = tecla - '0'; // Converte char para int
                    pos_senha++;

                    if (pos_senha == 4)
                    {
                        printf("\n");
                        if (verificar_senha())
                        {
                            printf("Senha correta!\n");
                            gpio_put(LED_VERDE, 1);
                            sleep_ms(1000);
                            gpio_put(LED_VERDE, 0);
                        }
                        else
                        {
                            printf("Senha incorreta!\n");
                            gpio_put(LED_VERMELHO, 1);
                            sleep_ms(1000);
                            gpio_put(LED_VERMELHO, 0);
                        }
                        resetar_senha();
                    }
                }
                break;
            case '*':
                // verifica se a exibição de saída do teclado está habilitada
                if (exibicao_habilitada)
                {
                    printf("\nDesabilitando a exibição de saída do teclado\n");
                    desabilitar_exibicao();
                }
                else
                {
                    habilitar_exibicao();
                    printf("\nHabilitando a exibição de saída do teclado\n");
                }
                break;
            case '#':
                if (modo_senha)
                {
                    printf("\nEntrada de senha cancelada\n");
                    resetar_senha();
                }
                break;
            case 'A':
                acender_led(tecla);
                break;
            case 'B':
                acender_led(tecla);
                break;
            case 'C':
                acender_led(tecla);
                break;
            case 'D':
                acender_led(tecla);
                break;
            }
        }
        sleep_ms(100); // Pequeno atraso
    }
}