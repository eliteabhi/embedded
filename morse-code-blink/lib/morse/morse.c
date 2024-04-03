#include "morse.h"

const char* char_to_morse( const char letter ) {

  if ( c >= 'a' && c <= 'z' ) {

     return ROSSETTA[c - 'a'];
    
  }
    
  else if ( c >= '0' && c <= '9' ) {
  
    return ROSSETTA[c - '0' + 26];
    
  }

  else if ( c == ' ' ) {

    return "\\";  

  }

  else {

    return ""; // Return empty string for other characters
  
  }

}

const char* translate_to_morse( const char* text, const int text_length, const int buffer_size ) {

  char* morse_output[ buffer_size ] = "";

  int buffer_free = 0;

for ( int i = 0; i < text_length; i++ ) {

    const char* text_morse = &char_to_morse( text[ 0 ] );
    const int text_morse_size = sizeof( text_morse ) / sizeof( text_morse[ 0 ] )

    if ( buffer_free >= 0 && buffer_free < buffer_size ) {
   
      buffer_free = snprintf( morse_output + buffer_free, buffer_size - buffer_free, "%s\\", char_to_morse( text[ i ] ) );
  
    }
  
  }

  return morse_output;

}

