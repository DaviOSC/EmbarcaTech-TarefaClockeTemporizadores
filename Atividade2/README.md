# Projeto: Temporizador de Um Disparo (One Shot)

Este projeto implementa um sistema de temporização para o acionamento de LEDs utilizando o microcontrolador Raspberry Pi Pico W, três LEDs (azul, vermelho e verde), três resistores de 330 Ω (ambiente simulado) e um botão (pushbutton). O sistema atua a partir do clique no botão, ligando os LEDs e alternando entre os estados a cada 3 segundos.

## Requisitos

1. **Acionamento dos LEDs pelo botão**: Ao clicar no botão, os três LEDs serão ligados (todos em nível alto). A partir da primeira rotina de atraso, ocorrerá uma mudança de estado para dois LEDs ligados e, em seguida, apenas um.
2. **Temporização de 3 segundos**: O temporizador do alarme é ajustado para um atraso de 3.000 ms entre os estados de acionamento dos LEDs.
3. **Callback do temporizador**: A mudança de estado dos LEDs é implementada em funções de callback do temporizador.
4. **Controle do botão**: O botão só pode alterar o estado dos LEDs quando o último LED for desligado. Durante a execução das rotinas de temporização, o botão não pode iniciar uma nova chamada da função callback.
5. **Experimento com BitDogLab**: Utilize o LED RGB – GPIOs 11, 12 e 13 e o Botão A, GPIO 05.
6. **Debounce do botão (Opcional)**: Implementar uma rotina em software para atenuação do efeito bouncing no botão.

## Configuração do Hardware

- Conecte o LED azul ao GPIO 12.
- Conecte o LED vermelho ao GPIO 13.
- Caso necessário, Conecte o LED verde ao GPIO 11.
- Conecte os resistores de 330 Ω aos catodos dos LEDs e ao GND.
- Conecte o botão ao GPIO 5.

## Compilação e Execução

1. Clone o repositório do projeto.
2. Configure o ambiente de desenvolvimento do Raspberry Pi Pico.
3. Compile o código usando o CMake:
   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```
4. Carregue o binário no Raspberry Pi Pico.

## Estrutura do Código

### Função `routine_callback`

A função `routine_callback` é chamada pelo temporizador a cada 3 segundos. Ela alterna o estado dos LEDs conforme a sequência:

- Estado 0: Desliga o LED azul e muda para o próximo estado.
- Estado 1: Desliga o LED vermelho e muda para o próximo estado.
- Estado 2: Desliga o LED verde e reseta o estado.

### Função `main`

A função `main` inicializa a comunicação serial e os pinos dos LEDs como saída. Em seguida, configura o pino do botão como entrada com pull-up. A rotina principal verifica se o botão foi pressionado e, se os LEDs não estão ativos, liga todos os LEDs e inicia a rotina de temporização.

#### Debounce do Botão

Para evitar múltiplas leituras do botão devido ao efeito bouncing, foi implementada uma rotina de debounce. Após detectar um clique no botão, o programa espera 50 ms e verifica novamente o estado do botão para confirmar a leitura. Isso garante que apenas cliques válidos sejam processados.

#### Trava do Acionamento da Rotina

Durante a execução das rotinas de temporização, o botão não pode iniciar uma nova chamada da função callback. Isso é controlado pela variável `led_active`, que impede que o botão altere o estado dos LEDs enquanto a rotina de temporização está em andamento.