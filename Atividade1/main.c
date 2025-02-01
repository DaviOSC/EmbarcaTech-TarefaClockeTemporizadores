#include <stdio.h>
#include "pico/stdlib.h"   // Inclui a biblioteca padrão para funcionalidades básicas como GPIO, temporização e comunicação serial.
#include "hardware/timer.h" // Inclui a biblioteca para gerenciamento de temporizadores de hardware.

#define LED_PIN_GREEN 11
#define LED_PIN_RED 13
#define LED_PIN_BLUE 12

// Variáveis globais para controlar o estado dos LEDs.
bool led_red_on = true;
bool led_blue_on = false;
bool led_green_on = false;


// Função de callback que será chamada repetidamente pelo temporizador
bool repeating_timer_callback(struct repeating_timer *t) {
    //Se for para acender o led vermelho
    if(led_red_on){
        printf("LED VERMELHO\n");
        gpio_put(LED_PIN_RED,1);
        gpio_put(LED_PIN_GREEN,0);
        gpio_put(LED_PIN_BLUE,0);
        //Atualiza o estado dos proximos leds (azul aceso)
        led_red_on = false;
        led_green_on = false;
        led_blue_on = true;
    }
    //Se for para acender o led azul
    else if(led_blue_on)
    {
        printf("LED AZUL\n");
        gpio_put(LED_PIN_RED,0);
        gpio_put(LED_PIN_GREEN,0);
        gpio_put(LED_PIN_BLUE,1);
        //Atualiza o estado dos proximos leds (verde aceso)
        led_red_on = false;
        led_green_on = true;
        led_blue_on = false;
    }
    //Se for para acender o led verde
    else if(led_green_on)
    {
        printf("LED VERDE\n");
        gpio_put(LED_PIN_RED,0);
        gpio_put(LED_PIN_GREEN,1);
        gpio_put(LED_PIN_BLUE,0);
        //Atualiza o estado dos proximos leds (vermelho aceso)
        led_red_on = true;
        led_green_on = false;
        led_blue_on = false;
    }
    return true;    
}

int main() {
    // Inicializa a comunicação serial, permitindo o uso de funções como printf.
    stdio_init_all();

    // Inicializar os pinos dos LEDs como saída.
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED,true);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN,true);
    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE,true);

    // Declaração de uma estrutura de temporizador de repetição.
    struct repeating_timer timer;

    // Configura o temporizador para chamar a função de callback a cada 3000 ms (3 segundos).
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop infinito que mantém o programa em execução para que o temporizador possa chamar a função de callback.
    while (true) {
        sleep_ms(1000);
        printf("Um segundo se passou.\n");
    }
    return 0;
}
