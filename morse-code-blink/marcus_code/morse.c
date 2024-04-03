#include "morse.h"
#include "delay.h"
#include "blink.h"

char *char_to_morse(char c)
{
   // Define Morse code for each alphabet and digit
   static char *morseCode[36] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
                                       "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
                                       "..-", "...-", ".--", "-..-", "-.--", "--..", "-----", ".----", "..---",
                                       "...--", "....-", ".....", "-....", "--...", "---..", "----."};


  if (tolower(c) >= 'a' && tolower(c) <= 'z')
  {
    return morseCode[tolower( c ) - 'a'];
  }

  else if ( c >= '0' && c <= '9' )
  {
    return morseCode[ c - '0' + 26 ];
  }
  else if ( c == ' ' ) {

    return "/";

  }
  else
  {
       return ""; // Return empty string for other characters
  }

}


// Function to convert a word to Morse code
// Use the delimiter / for any spaces between words
void translate_to_morse(const char *text, char *morseOutput, int morseOutputSize)
{
   // Loop through the text to convert each
   // charactor to morse code.
   // char_to_morse function is provided above but may not
   // handle all cases.
  int text_length = strlen( text );

  int index = 0;
  
  for( int i = 0; i < text_length; i++ ) {

    char* morse = char_to_morse( text[ i ] );

    sprintf( morseOutput, "%s%s", morseOutput, morse );
    
    if ( i < text_length - 1 ) {

    sprintf( morseOutput, "%s ", morseOutput );

    }

  }

}

void morse_blink_led(const char *morseCode)
{
   while(*morseCode){
       switch (*morseCode){
           case '.':
               LED_HIGH();
               DELAY(1000);
               LED_LOW();
               DELAY(1000);
               break;
           case '-':
               DELAY(3000);
               LED_LOW();
               DELAY(1000);
               break;
           case ' ':
               DELAY(6000);
               break;
           default:
               break;
       }
      
       morseCode++;
  
   }


}
