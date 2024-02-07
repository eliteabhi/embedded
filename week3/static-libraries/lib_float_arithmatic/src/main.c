#include "../lib/float_arithmetic.h"
#include <stdio.h>

int main() {

    printf( "%0.3f\n", f_add(2.0, 3.0) );
    printf( "%0.3f\n", f_sub(2.0, 3.0) );
    printf( "%0.3f\n", f_mul(2.0, 3.0) );
    printf( "%0.3f\n", f_div(2.0, 3.0) );

    return 0;

}
