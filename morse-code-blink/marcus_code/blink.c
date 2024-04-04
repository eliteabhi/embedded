#include "blink.h"

// Fill in the three functions to
// 1.) enable the output mode for onboard LED
// 2.) set the led to high
// 3.) set the led to low

#if defined(RELEASE) || defined(DEBUG)
// Write code to enable led
void initialize_led()
{
  if ( wiringXSetup("duo", NULL) == -1 ) {

    wiringXGC();

  }

  if( wiringXValidGPIO(LED_PIN) != 0 ) {

    printf("Invalid GPIO Pin \'%d\'%n", LED_PIN);

  }

  pinMode(LED_PIN, PINMODE_OUTPUT);
}


// Write code to turn led on
void turn_on_led()
{
   digitalWrite(LED_PIN, HIGH);
}


// Write code to turn led off
void turn_off_led()
{
   digitalWrite(LED_PIN, LOW);
}

#endif

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
