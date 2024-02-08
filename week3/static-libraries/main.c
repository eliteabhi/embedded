#include "lib_int_arithmetic/lib/int_arithmetic.h"
#include "lib_float_arithmetic/lib/float_arithmetic.h"
#include <stdio.h>
int main() {

    printf( "%d\n", add(2, 2) );
    printf( "%d\n", sub(2, 2) );
    printf( "%d\n", mul(2, 2) );
    printf( "%d\n", div(2, 2) );

    printf( "%0.3f\n", f_add(2.0, 3.0) );
    printf( "%0.3f\n", f_sub(2.0, 3.0) );
    printf( "%0.3f\n", f_mul(2.0, 3.0) );
    printf( "%0.3f\n", f_div(2.0, 3.0) );

    return 0;

}
