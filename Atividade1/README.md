# Projeto: Semáforo com Temporizador Periódico

Este projeto implementa um semáforo utilizando o microcontrolador Raspberry Pi Pico W, três LEDs (vermelho, amarelo e verde) e três resistores de 330 Ω. O semáforo alterna entre as cores vermelho, amarelo e verde a cada 3 segundos, utilizando a função `add_repeating_timer_ms()` da ferramenta Pico SDK.

## Requisitos

1. **Início na cor vermelha**: O semáforo inicia com o LED vermelho aceso.
2. **Temporização de 3 segundos**: O temporizador é ajustado para um atraso de 3.000 ms.
3. **Callback do temporizador**: A mudança de estado dos LEDs é implementada na função de callback do temporizador, `repeating_timer_callback()`.
4. **Mensagens na porta serial**: A rotina principal imprime uma mensagem a cada segundo (1.000 ms) na porta serial.
5. **GPIOs utilizados**: Os LEDs são conectados aos GPIOs 11, 12 e 13.

## Configuração do Hardware

- Conecte o LED vermelho ao GPIO 13.
- Conecte o LED amarelo ao GPIO 12.
- Conecte o LED verde ao GPIO 11.
- Caso necessário, Conecte os resistores de 330 Ω aos catodos dos LEDs e ao GND.

## Compilação e Execução

1. Clone o repositório do projeto.
2. Configure o ambiente de desenvolvimento do Raspberry Pi Pico.
3. Compile o código usando o CMake:
4. Carregue o binário no Raspberry Pi Pico.

## Estrutura do Código

### Função `repeating_timer_callback`

A função `repeating_timer_callback` é chamada pelo temporizador a cada 3 segundos. Ela alterna o estado dos LEDs conforme a sequência do semáforo:

- Vermelho -> Amarelo(Azul) -> Verde -> Vermelho

### Função `main`

A função `main` inicializa a comunicação serial e os pinos dos LEDs como saída. Em seguida, configura o temporizador para chamar a função de callback a cada 3 segundos. A rotina principal imprime uma mensagem na porta serial a cada segundo.
