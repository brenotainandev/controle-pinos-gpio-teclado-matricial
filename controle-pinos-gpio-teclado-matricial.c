#include <stdio.h>
#include "pico/stdlib.h"


#define led_pin_red 13
#define led_pin_blue 12
#define led_pin_green 11
#define buzzer_pin 27

char keypad[16] = {
  '1', '2', '3', 'A',
  '4', '5', '6', 'B',
  '7', '8', '9', 'C',
  '*', '0', '#', 'D'
};

int colunas[4] = {3,2,1,0};
int linhas[4] = {8,7,6,4};


int main() {
  stdio_init_all();

  
  while (true) {
    printf("Hello, Wokwi!\n");
    sleep_ms(250);
  }
}