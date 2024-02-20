#include "lib_int_arithmetic/lib/int_arithmetic.h"
#include "lib_float_arithmetic/lib/float_arithmetic.h"
#include <stdio.h>

int main() {

    int lib, stop, counter;
    float num_one, num_two, ans = 0.0f;
    char operator;
    char is_float;
    char cont;

    stop = 0;

    while( stop == 0 ) {

        printf( "Are you going to input any floats? [y/N]: ");
        scanf("%c", &is_float);

        lib = ( is_float == 'y' || is_float == 'Y' ) ? 1 : 0;

        printf( "Please enter your first number: ");
        scanf("%f", &num_one);

        while((getchar()) != '\n');

        printf("\nPlease enter an operator ( +, -, *, / ): ");
        scanf("%c", &operator);

        printf( "\nPlease enter your second number: ");
        scanf("%f", &num_two);

        if ( !lib ) {

            switch( operator ) {

                case ( '+' ):
                    ans = add( num_one, num_two );
                    break;

                case ( '-' ):
                    ans = sub( num_one, num_two );
                    break;

                case ( '*' ):
                    ans = mul( num_one, num_two );
                    break;

                case ( '/' ):
                    ans = div( num_one, num_two );
                    break;
            
            }

        }

        else {

            switch( operator ) {

                case ( '+' ):
                    ans = f_add( num_one, num_two );
                    break;

                case ( '-' ):
                    ans = f_sub( num_one, num_two );
                    break;

                case ( '*' ):
                    ans = f_mul( num_one, num_two );
                    break;

                case ( '/' ):
                    ans = f_div( num_one, num_two );
                    break;
                
            }

        }

        if ( lib ) {

            printf( "\n%0.2f %c %0.2f = %0.2f", num_one, operator, num_two, ans );

        }

        else {
        
            printf( "\n%d %c %d = %d", ( int ) num_one, operator, ( int ) num_two, ( int ) ans );
        
        }

        while((getchar()) != '\n');

        printf("\n\nCalculate again? [Y/n]: ");
        scanf("%c", &cont);
         
        stop = ( cont == 'n' || cont == 'N' ) ? 1 : 0;

        if ( !stop && cont != '\n' )
            while((getchar()) != '\n');

        printf("\n");

        counter++;

    }

    printf("You calculated %d expressions, Goodbye!", counter);
    return 0;
    
}