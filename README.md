# Controle de Pinos GPIO com Teclado Matricial e Raspberry Pi Pico W

## Descrição do Projeto

Este projeto demonstra o controle de pinos GPIO de um microcontrolador RP2040 (Raspberry Pi Pico W) utilizando um teclado matricial 4x4. A aplicação simulada no Wokwi aciona LEDs RGB e um buzzer com base nas teclas pressionadas.

Este projeto foi realizado como parte da Unidade 4 - Microcontroladores, com foco no aprendizado e na aplicação de conceitos fundamentais de GPIO utilizando Git e GitHub, além da colaboração em equipe. Durante o desenvolvimento, foram seguidas boas práticas de engenharia de software, incluindo:

* Criação de filiais para funcionalidades específicas.
* Realização de commits regulares e bem documentados.
* Uso de pull requests para integração das alterações.
* Comunicação e organização eficiente entre os membros do grupo.

## Objetivo

* Controlar LEDs RGB e um buzzer através de um teclado matricial.
* Familiarizar-se com o desenvolvimento em C utilizando o Pico SDK.
* Utilizar o simulador Wokwi para prototipagem rápida.
* Aprender sobre versionamento de código com Git.

## Membros do Grupo

* Matheus Pereira Alves
* Rodrigo Damasceno Sampaio
* Erick Barros Ferreira Gomes
* João Vitor de Siqueira Santana Costa
* Natália Freitas Tolentino
* Eduarda da Silva Santos
* Breno Tainan Aguiar

## Tecnologias Utilizadas

* **Software:**
  * **Linguagem de programação:** C
  * **IDE:** Visual Studio Code
  * **SDK:** Pico SDK
  * **Simulador:** Wokwi
  * **Controle de versão:** Git
  * **Plataforma de hospedagem:** GitHub

## Estrutura do Projeto
```
projeto_gpio/
├── .github
│   └── workflows
│       └── ci.yml
├── .vscode
│   ├── c_cpp_properties.json
│   ├── cmake-kits.json
│   ├── extensions.json
│   ├── launch.json
│   ├── settings.json
│   └── tasks.json
├── build
│   ├── CMakeFiles
│   ├── generated
│   ├── pico-sdk
│   ├── ninja_deps
│   ├── .ninja_log
│   ├── bs2_default.elf.map
│   ├── build.ninja
│   ├── cmake_install.cmake
│   ├── CMakeCache.txt
│   ├── compile_commands.json
│   ├── pico_flash_region.ld
│   └── output
├── .gitignore
├── CMakeLists.txt
├── controle-pinos-gpio-teclado-matricial.c
├── diagram.json
├── pico_sdk_import.cmake
├── README.md
└── wokwi.toml
```
## Como Utilizar (Simulação Wokwi)

# Teclado matricial 4x4
1. **Botão 1 9:** As Luzes das leds piscana quantidade do numero correspondente e retorna o número. 
2. **Botão 0:** Modo senha ativado.
    * Se digitar a senha correta, mostra a mensagem: Senha correta!
    * Se digitar a senha incorreta, mostra a mensagem: Senha incorreta!
3. **Botão A:** Acende a luz da led verde.
4. **Botão B:** Acende a luz da led azul.
5. **Botão C:** Acende a luz da led vermelha.
6. **Botão D:** Acende as luzes das tres ledsapenas uma vez.
7. **Botão '*':** Habilitar/Desabilitar a exibição de saída.
8. **Botão #:** Tocar a música do Mario.

## Vídeo de Apresentação

-Vídeo: [YouTube](https://youtu.be/ny9ieWJVeYY)


