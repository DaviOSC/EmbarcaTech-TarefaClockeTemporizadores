#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

#define LED_PIN_GREEN 11
#define LED_PIN_RED 13
#define LED_PIN_BLUE 12
bool led_active = false;
const uint BUTTON_PIN = 5;

int state = 0;

int64_t routine_callback(alarm_id_t id, void *user_data) {
    switch (state) {
        case 0:
            gpio_put(LED_PIN_BLUE, false);
            printf("Estado 1: LED Azul DESLIGADO\n");
            state = 1;
            add_alarm_in_ms(3000, routine_callback, NULL, false);
            break;
        case 1:
            gpio_put(LED_PIN_RED, false);
            printf("Estado 2: LED Vermelho DESLIGADO\n");
            state = 2;
            add_alarm_in_ms(3000, routine_callback, NULL, false);
            break;
        case 2:
            gpio_put(LED_PIN_GREEN, false);
            printf("Estado 3: LED Verde DESLIGADO\n");
            led_active = false;
            state = 0;
            break;
    }
    return 0;
}

int main() {
    stdio_init_all();

    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    while (true) {
        if (gpio_get(BUTTON_PIN) == 0 && !led_active) {
            sleep_ms(50);
            if (gpio_get(BUTTON_PIN) == 0) {
                gpio_put(LED_PIN_GREEN, true);
                gpio_put(LED_PIN_RED, true);
                gpio_put(LED_PIN_BLUE, true);
                printf("Botão pressionado: Todos os LEDs LIGADOS\n");
                led_active = true;
                add_alarm_in_ms(3000, routine_callback, NULL, false);
            }
        }
        sleep_ms(10);
    }
    return 0;
}