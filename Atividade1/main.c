#include <stdio.h>
#include "pico/stdlib.h"   // Inclui a biblioteca padrão para funcionalidades básicas como GPIO, temporização e comunicação serial.
#include "hardware/timer.h" // Inclui a biblioteca para gerenciamento de temporizadores de hardware.

#define LED_PIN_GREEN 11
#define LED_PIN_RED 13
#define LED_PIN_BLUE 12
bool led_red_on = true;
bool led_blue_on = false;
bool led_green_on = false;


// Função de callback que será chamada repetidamente pelo temporizador
// O tipo bool indica que a função deve retornar verdadeiro ou falso para continuar ou parar o temporizador.
bool repeating_timer_callback(struct repeating_timer *t) {
    // Imprime uma mensagem na saída serial indicando que 1 segundo se passou.
    if(led_red_on){
        printf("LED VERMELHO\n");
        gpio_put(LED_PIN_RED,1);
        gpio_put(LED_PIN_GREEN,0);
        gpio_put(LED_PIN_BLUE,0);
        led_red_on = false;
        led_green_on = false;
        led_blue_on = true;
    }
    else if(led_blue_on)
    {
        printf("LED AZUL\n");
        gpio_put(LED_PIN_RED,0);
        gpio_put(LED_PIN_GREEN,0);
        gpio_put(LED_PIN_BLUE,1);
        led_red_on = false;
        led_green_on = true;
        led_blue_on = false;
    }
    else if(led_green_on)
    {
        printf("LED VERDE\n");
        gpio_put(LED_PIN_RED,0);
        gpio_put(LED_PIN_GREEN,1);
        gpio_put(LED_PIN_BLUE,0);
        led_red_on = true;
        led_green_on = false;
        led_blue_on = false;
    }
    return true;    
}

int main() {
    // Inicializa a comunicação serial, permitindo o uso de funções como printf.
    stdio_init_all();

    // Inicializar o pino GPIO11
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED,true);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN,true);
    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE,true);

    // Declaração de uma estrutura de temporizador de repetição.
    // Esta estrutura armazenará informações sobre o temporizador configurado.
    struct repeating_timer timer;

    // Configura o temporizador para chamar a função de callback a cada 1 segundo.
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop infinito que mantém o programa em execução.
    while (true) {
        sleep_ms(1000);
        printf("Um segundo se passou.\n");
    }
    return 0;
}
