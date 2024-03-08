#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "main.h"
#include <time.h>
#include <stdlib.h>

volatile int btn_r = 0;
volatile int btn_g = 0;
volatile int btn_b = 0; 
volatile int btn_y = 0;
volatile int btn_start = 0;
volatile int list[20] = {4,3,2,4,1,3,2,4,1,3,1,3,2,4,1,3,2,4,1,3};

volatile int melody[] = {
        NOTE_D4, -4, NOTE_A4, -4, NOTE_AS4, -4, NOTE_A4, -4, NOTE_G4, -4, NOTE_D5, -4, NOTE_D4, -4
    };
volatile int notes = sizeof(melody) / sizeof(int);

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
    // Definindo o Buzzer
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);

    // Funcao de callback para os botoes
    gpio_set_irq_enabled_with_callback(BTN_PIN_START, GPIO_IRQ_EDGE_FALL, true, &btn_callback);
    gpio_set_irq_enabled(BTN_PIN_G, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(BTN_PIN_B, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(BTN_PIN_Y, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true);

    srand(time(NULL));

    while (true) {
        int rodada = 1;
        int tempo = 250;

        for (int i = 0; i < sizeof(list)/sizeof(list[0]); i++) {
            list[i] = rand() % 4 + 1;
        }

        while (btn_start == 0) {
            for (int i = 0; (i < notes) && (btn_start == 0); i++) {
                int note = melody[i];
                int duration = 1000 / abs(melody[i + 1]);

                if (note != REST) {
                    buzzer_sound(duration, note);
                    for (int j = 0; (j < duration) && (btn_start == 0); j += 10) {
                        sleep_ms(10);
                    }
                } else {
                    for (int j = 0; (j < duration) && (btn_start == 0); j += 10) {
                        sleep_ms(10);
                    }
                }
            }
            sleep_ms(50);
        }

        while (btn_start == 1) {
            sleep_ms(250);
            btn_r = 0;
            btn_g = 0;
            btn_b = 0;
            btn_y = 0;
            for (int i = 0; (i < rodada) && (btn_start == 1); i++) {
                if (list[i] == 1) {
                    gpio_put(LED_PIN_R, 1);
                    buzzer_sound(200, freq_r);
                    sleep_ms(tempo);
                    gpio_put(LED_PIN_R, 0);
                    sleep_ms(tempo);
                } else if (list[i] == 2) {
                    gpio_put(LED_PIN_G, 1);
                    buzzer_sound(200, freq_g);
                    sleep_ms(tempo);
                    gpio_put(LED_PIN_G, 0);
                    sleep_ms(tempo);
                } else if (list[i] == 3) {
                    gpio_put(LED_PIN_B, 1);
                    buzzer_sound(200, freq_b);
                    sleep_ms(tempo);
                    gpio_put(LED_PIN_B, 0);
                    sleep_ms(tempo);
                } else if (list[i] == 4) {
                    gpio_put(LED_PIN_Y, 1);
                    buzzer_sound(200, freq_y);
                    sleep_ms(tempo);
                    gpio_put(LED_PIN_Y, 0);
                    sleep_ms(tempo);
                }
            }           
            for (int i = 0; (i < rodada) && (btn_start == 1); i++) {
                while (!(btn_r == 1 || btn_g == 1 || btn_b == 1 || btn_y == 1 || btn_start == 0)) {
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
                    }
                    btn_y = 0;
                } else {
                    break;
                }
            }

            tempo -= 23;
            rodada++;

            if ((rodada > sizeof(list)/sizeof(list[0])) || (btn_start == 0)) {
                btn_start = 0;
                gpio_put(LED_PIN_R, 1);
                gpio_put(LED_PIN_G, 1);
                gpio_put(LED_PIN_B, 1);
                gpio_put(LED_PIN_Y, 1);
                sleep_ms(1000);
                gpio_put(LED_PIN_R, 0);
                gpio_put(LED_PIN_G, 0);
                gpio_put(LED_PIN_B, 0);
                gpio_put(LED_PIN_Y, 0);
                sleep_ms(1000);
                break;
            } else {
                for (int i = 0; i < rodada-1; i++){
                    gpio_put(LED_PIN_R, 1);
                    gpio_put(LED_PIN_G, 1);
                    gpio_put(LED_PIN_B, 1);
                    gpio_put(LED_PIN_Y, 1);
                    sleep_ms(200);
                    gpio_put(LED_PIN_R, 0);
                    gpio_put(LED_PIN_G, 0);
                    gpio_put(LED_PIN_B, 0);
                    gpio_put(LED_PIN_Y, 0);
                    sleep_ms(200);
                }
            }
        }
    }
 }