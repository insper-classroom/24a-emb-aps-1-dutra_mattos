#ifndef main_h
#define main_h

#define LED_PIN_R 17
#define LED_PIN_G 20
#define LED_PIN_B 22
#define LED_PIN_Y 28
#define LED_PIN_PASS 5
#define LED_PIN_FAIL 6

#define BTN_PIN_R 15
#define BTN_PIN_G 12
#define BTN_PIN_B 7
#define BTN_PIN_Y 10
#define BTN_PIN_START 8

#define BUZZER_PIN 27
#define freq_r 800
#define freq_g 293
#define freq_b 329
#define freq_y 349

volatile int btn_r = 0;
volatile int btn_g = 0;
volatile int btn_b = 0; 
volatile int btn_y = 0;
volatile int btn_start = 0;

#endif