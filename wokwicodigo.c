#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/gpio.h"

// Defina os pinos do LED RGB
const uint LED_RED = 11;
const uint LED_YELLOW = 12;
const uint LED_GREEN = 13;

// Estados do semáforo
enum TrafficLightState { RED, YELLOW, GREEN };
enum TrafficLightState current_state = RED;

// Função de call-back do temporizador
bool repeating_timer_callback(struct repeating_timer *t) { // Remova o argumento 'void *arg'
    // Alterne o estado dos LEDs com base no estado atual do semáforo
    switch (current_state) {
        case RED:
            gpio_put(LED_RED, 1);
            gpio_put(LED_YELLOW, 0);
            gpio_put(LED_GREEN, 0);
            current_state = YELLOW;
            break;
        case YELLOW:
            gpio_put(LED_RED, 0);
            gpio_put(LED_YELLOW, 1);
            gpio_put(LED_GREEN, 0);
            current_state = GREEN;
            break;
        case GREEN:
            gpio_put(LED_RED, 0);
            gpio_put(LED_YELLOW, 0);
            gpio_put(LED_GREEN, 1);
            current_state = RED;
            break;
    }
    return true;
}

int main() {
    // Inicialize os LEDs como saídas
    gpio_init(LED_RED);
    gpio_init(LED_YELLOW);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_YELLOW, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    // Crie um temporizador que dispara a cada 3 segundos
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    int contador = 0;
    while (true) {
        // Imprima uma mensagem a cada segundo
        printf("Tempo atual: %d segundos\n", contador);
        contador++;
        sleep_ms(1000);
    }

    return 0;
}
