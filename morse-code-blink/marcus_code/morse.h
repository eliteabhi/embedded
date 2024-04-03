#ifndef MORSE_H
#define MORSE_H

#define DOT_DELAY 17
#define DASH_DELAY 27
#define SPACE_DELAY 51

void translate_to_morse(const char *input, char *output, int output_size);
void morse_blink_led(const char *input);

#endif
