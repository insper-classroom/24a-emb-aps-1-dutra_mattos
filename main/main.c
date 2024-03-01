/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "main.h"

void btn_callback(uint gpio, uint32_t events) {
    if (gpio == BTN_PIN_R) {
        btn_r = !btn_r;
    } else if (gpio == BTN_PIN_G) {
        btn_g = !btn_g;
    } else if (gpio == BTN_PIN_B) {
        btn_b = !btn_b;
    } else if (gpio == BTN_PIN_Y) {
        btn_y = !btn_y;
    } else if (gpio == BTN_PIN_START) {
        btn_start = !btn_start;
    }
}

void buzzer_sound(int duration_ms, int FREQUENCY) {
    int delay = 1000000 / (FREQUENCY * 2); // Calcula o atraso necessário para a frequência desejada

    for (int i = 0; i < (duration_ms * 1000) / (delay * 2); i++) {
        gpio_put(BUZZER_PIN, 1); // Liga o buzzer
        sleep_us(delay); // Espera meio período
        gpio_put(BUZZER_PIN, 0); // Desliga o buzzer
        sleep_us(delay); // Espera meio período
    }
}
 

 int main() {
    stdio_init_all();

    // Definindo os Botões

    gpio_init(BTN_PIN_R);
    gpio_set_dir(BTN_PIN_R, GPIO_IN);
    gpio_pull_up(BTN_PIN_R);

    gpio_init(BTN_PIN_G);
    gpio_set_dir(BTN_PIN_G, GPIO_IN);
    gpio_pull_up(BTN_PIN_G);

    gpio_init(BTN_PIN_B);
    gpio_set_dir(BTN_PIN_B, GPIO_IN);
    gpio_pull_up(BTN_PIN_B);

    gpio_init(BTN_PIN_Y);
    gpio_set_dir(BTN_PIN_Y, GPIO_IN);
    gpio_pull_up(BTN_PIN_Y);

    gpio_init(BTN_PIN_START);
    gpio_set_dir(BTN_PIN_START, GPIO_IN);
    gpio_pull_up(BTN_PIN_START);

    // Definindo os LEDs

    gpio_init(LED_PIN_R);
    gpio_set_dir(LED_PIN_R, GPIO_OUT);
    
    gpio_init(LED_PIN_G);
    gpio_set_dir(LED_PIN_G, GPIO_OUT);

    gpio_init(LED_PIN_B);
    gpio_set_dir(LED_PIN_B, GPIO_OUT);

    gpio_init(LED_PIN_Y);
    gpio_set_dir(LED_PIN_Y, GPIO_OUT);

    gpio_init(LED_PIN_PASS);
    gpio_set_dir(LED_PIN_PASS, GPIO_OUT);

    gpio_init(LED_PIN_FAIL);
    gpio_set_dir(LED_PIN_FAIL, GPIO_OUT);

    // Definindo o Buzzer

    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);

    // Funcao de callback para os botoes

    gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true, &btn_callback);
    gpio_set_irq_enabled(BTN_PIN_G, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(BTN_PIN_B, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(BTN_PIN_Y, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(BTN_PIN_START, GPIO_IRQ_EDGE_FALL, true);
    
    int list[6] = {1,3,2,4,1,3};
    while (true) {
        int rodada = 1;
        while (btn_start == 1) {
            btn_r = 0;
            btn_g = 0;
            btn_b = 0;
            btn_y = 0;
            int tempo = 500;
            for (int i = 0; i < rodada; i++) {
                if (list[i] == 1) {
                    gpio_put(LED_PIN_R, 1);
                    buzzer_sound(200, freq_r);
                    sleep_ms(500);
                    gpio_put(LED_PIN_R, 0);
                    sleep_ms(500);
                } else if (list[i] == 2) {
                    gpio_put(LED_PIN_G, 1);
                    buzzer_sound(200, freq_g);
                    sleep_ms(500);
                    gpio_put(LED_PIN_G, 0);
                    sleep_ms(500);
                } else if (list[i] == 3) {
                    gpio_put(LED_PIN_B, 1);
                    buzzer_sound(200, freq_b);
                    sleep_ms(500);
                    gpio_put(LED_PIN_B, 0);
                    sleep_ms(500);
                } else if (list[i] == 4) {
                    gpio_put(LED_PIN_Y, 1);
                    buzzer_sound(200, freq_y);
                    sleep_ms(500);
                    gpio_put(LED_PIN_Y, 0);
                    sleep_ms(500);
                }
            }           
            for (int i = 0; i < rodada; i++) {
                while (!(btn_r == 1 || btn_g == 1 || btn_b == 1 || btn_y == 1)) {
                }
                if (btn_r == 1) {
                    if (list[i] == 1) {
                        gpio_put(LED_PIN_R, 1);
                        buzzer_sound(200, freq_r);
                        sleep_ms(500);
                        gpio_put(LED_PIN_R, 0);
                        sleep_ms(500);
                    } else {
                        btn_start = 0;
                        break;
                    }
                    btn_r = 0;
                } else if (btn_g == 1) {
                    if (list[i] == 2) {
                        gpio_put(LED_PIN_G, 1);
                        buzzer_sound(200, freq_g);
                        sleep_ms(500);
                        gpio_put(LED_PIN_G, 0);
                        sleep_ms(500);
                    } else {
                        btn_start = 0;
                        break;
                    }
                    btn_g = 0;
                } else if (btn_b == 1) {
                    if (list[i] == 3) {
                        gpio_put(LED_PIN_B, 1);
                        buzzer_sound(200, freq_b);  
                        sleep_ms(500);
                        gpio_put(LED_PIN_B, 0);
                        sleep_ms(500);
                    } else {
                        btn_start = 0;
                        break;
                    }
                    btn_b = 0;
                } else if (btn_y == 1) {
                    if (list[i] == 4) {
                        gpio_put(LED_PIN_Y, 1);
                        buzzer_sound(200, freq_y);
                        sleep_ms(500);
                        gpio_put(LED_PIN_Y, 0);
                        sleep_ms(500);
                    } else {
                        btn_start = 0;
                        break;
                    }
                    btn_y = 0;
                }
            }
            tempo -= 20;
            rodada++;
            if (rodada > sizeof(list)/sizeof(list[0])) {
                btn_start = 0;
            }
        }
    }
}