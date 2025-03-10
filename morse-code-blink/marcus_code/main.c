#include <stdio.h>

#include "../marcus_code/morse.h"

#define BUFSIZE 100

int main()
{
    char text[] = "eye";
    char morseOutput[BUFSIZE] = {0};
    printf("%s\n", text);

    // Fill in the code for `translate_to_morse`
    translate_to_morse(text, morseOutput, BUFSIZE - 1);
    printf("Morse Code: %s\n", morseOutput);

    // Passe `morseOutput` to the morse_blink_led function
    // Update the morse_blink_led to blink accordingly
    morse_blink_led(morseOutput);

    return 0;
}
