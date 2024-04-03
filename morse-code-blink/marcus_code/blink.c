#include <stdio.h>


#include "blink.h"


#define LED_PIN 25
// Fill in the three functions to
// 1.) enable the output mode for onboard LED
// 2.) set the led to high
// 3.) set the led to low


// Write code to enable led
void initialize_led()
{
   // pinMode(LED_PIN, mock_initialize_led);
}


// Write code to turn led on
void turn_on_led()
{
   // digitalWrite(LED_PIN, mock_led_high);
}


// Write code to turn led off
void turn_off_led()
{
   // digitalWrite(LED_PIN, mock_led_low);
}


// This code that helps with testing
// no need to change unles you
// want to completely customize
void mock_initialize_led()
{
   printf("Mock Initialize LED\n");
}
void mock_led_high()
{
   printf("Mock LED ON\n");
}
void mock_led_low()
{
   printf("Mock LED OFF\n");
}
