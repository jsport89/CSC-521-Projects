/*
 * test.c - Contains Task 1 of Project 1
 * 1. Generating a pseudo-random 512-bit integer
 * 2. Checking to see if that integer is (probabilistically) prime
 * 3. Printing large integers to stdout
 * 4. Reading & writing larger integers from/to disk
 * 5. Adding and subtracting two large integers
 * 6. Multiplying two large integers
 * 7. Performs modular exponentiation on large integers (i.e. ab mod c)
 */

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <stdarg.h>  /* For protos with va_list ie gmp_vprintf */
#include <obstack.h> /* For struct obstack */

int main() {
   mpz_t rand_Num;
   unsigned long int i, seed;
   gmp_randstate_t r_state;

   seed = 123456;

    gmp_randinit_default (r_state);
    gmp_randseed_ui(r_state, seed);

    mpz_init(rand_Num);

    for(i = 0; i < 10; ++i) {
       mpz_urandomb(rand_Num,r_state, 2);
       gmp_printf("%Zd\n", rand_Num);
    }

    gmp_randclear(r_state);
    mpz_clear(rand_Num);
    return 0;
}
