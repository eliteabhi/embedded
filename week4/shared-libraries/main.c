#include "lib_int_arithmetic/lib/int_arithmetic.h"
#include "lib_float_arithmetic/lib/float_arithmetic.h"
#include <stdio.h>

enum OPS_t {

    ADD = '+',
    SUB = '-',
    MUL = '*',
    DIV = '/',

    // Special Ops
    ABS = 'a',
    POW = 'p',
    SQRT = 'q',
    INV_SQRT = 'i'

} OPS;

int main() {

    int lib, stop, counter = 0;
    float num_one, num_two, ans = 0.0f;
    char operator;
    char is_float;
    char cont;

    while( stop == 0 ) {

        printf( "Are you going to input any floats? [y/N]: ");
        scanf("%c", &is_float);

        if ( is_float == 'y' || is_float == 'Y' ) lib = 1;

        printf( "Please enter your first number: ");
        scanf("%f", &num_one);

        while((getchar()) != '\n');

        printf("\nPlease enter an operator ( +, -, *, /, (a)bs, (p)ow, s(q)rt, (i)nv_sqrt ): ");
        scanf("%c", &operator);

        if ( (int) operator > 64  && operator != POW ) lib = 1;

        else {

            printf( "\nPlease enter your second number: ");
            scanf("%f", &num_two);

        }

        if ( !lib ) {

            switch( operator ) {

                case ( ADD ):
                    ans = add( num_one, num_two );
                    break;

                case ( SUB ):
                    ans = sub( num_one, num_two );
                    break;

                case ( MUL ):
                    ans = mul( num_one, num_two );
                    break;

                case ( DIV ):
                    ans = div( num_one, num_two );
                    break;
            
            }

        }

        else {

            switch( operator ) {

                case ( ADD ):
                    ans = f_add( num_one, num_two );
                    break;

                case ( SUB ):
                    ans = f_sub( num_one, num_two );
                    break;

                case ( MUL ):
                    ans = f_mul( num_one, num_two );
                    break;

                case ( DIV ):
                    ans = f_div( num_one, num_two );
                    break;

                case ( ABS ):
                    ans = f_fabs( num_one );
                    break;
                
                case ( POW ):
                    ans = f_pow( num_one, (int) num_two );
                    break;

                case ( SQRT ):
                    ans = f_sqrt( num_one );
                    break;

                case ( INV_SQRT ):
                    ans = f_inv_sqrt( num_one );
                
            }

        }

        if ( lib ) {

            if ( (int) operator > 64 ) {
                
                switch ( operator ) {

                    case ( ABS ):
                        printf( "\n| %0.2f | = %0.2f", num_one, ans );
                    break;
                
                case ( POW ):
                        printf( "\n%0.2f ^ ( %0.2f ) = %0.2f", num_one, num_two, ans );
                    break;

                case ( SQRT ):
                        printf( "\nsqrt( %0.2f ) = %0.2f", num_one, ans );
                    break;

                case ( INV_SQRT ):
                        printf( "\n1 / sqrt( %0.2f ) = %0.2f", num_one, ans );

                }
            
            }

            else {

                printf( "\n%0.2f %c %0.2f = %0.2f", num_one, operator, num_two, ans );

            }

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