
#include <ctype.h>
#include <string.h>

const char* char_to_morse( const char c );
const char* translate_to_morse( const char* text, const int buff_size );

static const char* ROSSETTA[36] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
                                   "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
                                    "..-", "...-", ".--", "-..-", "-.--", "--..", "-----", ".----", "..---",
                                    "...--", "....-", ".....", "-....", "--...", "---..", "----."};

