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