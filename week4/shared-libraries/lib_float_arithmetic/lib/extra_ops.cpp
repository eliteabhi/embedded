#include "float_arithmetic.h"

float f_inv_sqrt(float num) { // I used the code that was used in `DOOM` for this... I just think it's cool so I wanted to use it :)

    // The basis behind this code is from using the property that `log_b( 1/sqrt(x) ) = log_b( x^(-1/2) ) = (-1/2) * log_b( x )`
    // It was created by Chris Lomont

    long fixed_point_ans;
    float x2, ans;
    const float threehalfs = 1.5f;
    int magic_num = 0x5f3759df; // This magic number was derived by brute force lol

    x2 = num * 0.5f;
    ans = num;

    // Cast float into a long, it keeps mantissa and exponent the same but changes the type the compiler thinks it is
    fixed_point_ans  = * ( long * ) &ans;

    // Subtracting ( `fixed_point_ans` >> 1 ) from the `magic_num` results in a number close to the sqrt
    fixed_point_ans  = magic_num - ( fixed_point_ans >> 1 ); 

    ans  = * ( float * ) &fixed_point_ans; // Re-cast as a float


    ans  = ans * ( threehalfs - ( x2 * ans * ans ) ); // Use Newton's method to find the ans = 1/sqrt(ans) - x = 0

    ans  = ans * ( threehalfs - ( x2 * ans * ans ) );   // 2nd iteration, this can be removed ( For more precision )

    return ans;

}

float f_fabs(float num) { return num < 0 ? -1 * num : num; }

float f_sqrt(float num) { return 1 / f_inv_sqrt( num ); }

float f_pow(float num, int p) {

    int ans = 1;

    switch ( p ) {

        case ( 1 ):
            ans = num;
            break;

        case( 2 ):
            ans = num * num;
            break;

        case( 3 ):
            ans = num * num * num;
            break;

        case( 4 ):
            ans = num * num * num * num;
            break;

        default:
            for ( int i = 0; i < p; i++ ) ans *= num;
            break;

    }

    return ans;

}

