#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

// Definição dos pinos dos LEDs
#define LED_PIN_GREEN 11
#define LED_PIN_RED 13
#define LED_PIN_BLUE 12

// Variável para indicar se o LED está ativo
bool led_active = false;

// Definição do pino do botão
const uint BUTTON_PIN = 5;

// Variável para armazenar o estado atual
int state = 0;

// Função de callback para a rotina de temporização
int64_t routine_callback(alarm_id_t id, void *user_data) {
    switch (state) {
        case 0:
            // Desliga o LED azul e muda para o próximo estado
            gpio_put(LED_PIN_BLUE, false);
            printf("Estado 1: LED Azul DESLIGADO\n");
            state = 1;
            add_alarm_in_ms(3000, routine_callback, NULL, false);
            break;
        case 1:
            // Desliga o LED vermelho e muda para o próximo estado
            gpio_put(LED_PIN_RED, false);
            printf("Estado 2: LED Vermelho DESLIGADO\n");
            state = 2;
            add_alarm_in_ms(3000, routine_callback, NULL, false);
            break;
        case 2:
            // Desliga o LED verde e reseta o estado
            gpio_put(LED_PIN_GREEN, false);
            printf("Estado 3: LED Verde DESLIGADO\n");
            led_active = false;
            state = 0;
            break;
    }
    return 0;
}

int main() {
    // Inicializa a entrada e saída padrão
    stdio_init_all();

    // Inicializa os pinos dos LEDs como saída
    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);

    // Inicializa o pino do botão como entrada com pull-up
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    while (true) {
        // Verifica se o botão foi pressionado e os LEDs não estão ativos
        if (gpio_get(BUTTON_PIN) == 0 && !led_active) {
            // Debounce do botão
            sleep_ms(50);
            if (gpio_get(BUTTON_PIN) == 0) {
                // Liga todos os LEDs e inicia a rotina de temporização
                gpio_put(LED_PIN_GREEN, true);
                gpio_put(LED_PIN_RED, true);
                gpio_put(LED_PIN_BLUE, true);
                printf("Botão pressionado: Todos os LEDs LIGADOS\n");
                // Marca o LED como ativo e inicia a rotina de temporização
                led_active = true;
                add_alarm_in_ms(3000, routine_callback, NULL, false);
            }
        }
        // Pequena pausa para evitar uso constante da CPU
        sleep_ms(10);
    }
    return 0;
}