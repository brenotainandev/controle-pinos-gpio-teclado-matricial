#include <stdio.h>
#include "pico/stdlib.h"


#define led_pin_red 13
#define led_pin_blue 12
#define led_pin_green 11
#define buzzer_pin 27

char keypad[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

int colunas[4] = {3,2,1,0};
int linhas[4] = {8,7,6,4};

void kaypad_init(int colunas[4], int linhas[4]); //Função inicialização dos pinos do keypad
char read_keypad(); //Função leitura do keypad

char key; //Variável quer armazena o caracter lido
int main() {
  kaypad_init(colunas, linhas);
  stdio_init_all();

  while (true) {
    key = read_keypad();
    printf("Caracter retornado %c \n", key);
    switch (key){
      case '1':
        break;
      case '2':
        break;
      case '3':
        break;
      default:

    }
    sleep_ms(100);
  }
}

void kaypad_init(int colunas[4], int linhas[4]){
  for (int i = 0; i < 4; i++){
  // Colunas [entradas]
  gpio_init(colunas[i]);
  gpio_set_dir(colunas[i], GPIO_IN);
  gpio_pull_up(colunas[i]); //Iniciando todos em nível alto
  //Linahs [saidas]
  gpio_init(linhas[i]);
  gpio_set_dir(linhas[i], GPIO_OUT);
  gpio_put(linhas[i], 1); //Iniciando todos em nível alto
  printf("Valor de i: %d \n", i);
  }
}

char read_keypad() {
    char leitura = 0;

    for(int Nlin = 0; Nlin < 4; Nlin ++) {
        gpio_put(linhas[Nlin], 0);
        uint32_t gpio_states = gpio_get_all();
        for(int Ncol = 0; Ncol < 4; Ncol++) {
            if(!(gpio_states & (1u << colunas[Ncol]))) {
                leitura = keypad[Nlin][Ncol];
                sleep_ms(100);
            }
        }
        gpio_put(linhas[Nlin], 1);
    }
    return leitura;
}
