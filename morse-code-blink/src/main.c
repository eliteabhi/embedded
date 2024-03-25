#include "../include/definitions.h"

void morse_blink_led( const char* morse, const int morse_size ) {

  for ( int i = 0; i < morse_size; i++ ) {

     //! Pseudo Code

    if ( morse[ i ] == '\\' ) {

      wait( WORD_SPACE );

    }

    if ( morse[ i ] == '.' ) {
    
      pinState( LED_PIN, HIGH );
      wait( DIT_TIME );
      pinState( LED_PIN, LOW );
      wait( SYLLABLE_SPACE );

    }

    if ( morse[ i ] == '-' ) {

      pinState( LED_PIN, HIGH );
      wait( DAH_TIME );
      pinState( LED_PIN, LOW );
      wait( SYLLABLE_SPACE );

    }

  }

}

int main( int argc, char** argv ) {

  char text[] = "hello";
  int text_length = sizeof( text ) / sizeof( text[ 0 ] )
  char morseOutput[ BUFFER_SIZE ] = "";

  // Fill in the code for `translate_to_morse`
  morseOutput = translate_to_morse( text, text_length, BUFFER_SIZE);
  printf( "Morse Code: %s\n", morseOutput );

  // Passe `morseOutput` to the morse_blink_led function
  // Update the morse_blink_led to blink accordingly
  morse_blink_led( morseOutput );

  return 0;

}

