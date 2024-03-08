#ifndef main_h
#define main_h

#define LED_PIN_R 10
#define LED_PIN_G 11
#define LED_PIN_B 12
#define LED_PIN_Y 13

#define BTN_PIN_R 6
#define BTN_PIN_G 7
#define BTN_PIN_B 8
#define BTN_PIN_Y 9
#define BTN_PIN_START 5

#define BUZZER_PIN 15
#define freq_r 800
#define freq_g 293
#define freq_b 329
#define freq_y 349

volatile int btn_r = 0;
volatile int btn_g = 0;
volatile int btn_b = 0; 
volatile int btn_y = 0;
volatile int btn_start = 0;
volatile int list[20] = {4,3,2,4,1,3,2,4,1,3,1,3,2,4,1,3,2,4,1,3};

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

#define NOTE_D4  293
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_G4  392
#define NOTE_D5  587
#define REST  0

volatile int melody[] = {
        // Pirates of the Caribbean - He's a Pirate
        NOTE_D4, -4, NOTE_A4, -4, NOTE_AS4, -4, NOTE_A4, -4, NOTE_G4, -4, NOTE_D5, -4, NOTE_D4, -4
    };

volatile int notes = sizeof(melody) / sizeof(int);

#endif