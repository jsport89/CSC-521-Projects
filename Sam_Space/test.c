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
static void generate_random_number(mpz_t *rand_num,
                                               unsigned long int seed,
                                               gmp_randstate_t *rand_state);

int main() {
   unsigned long int seed, seed2;
   mpz_t rand_num;
   gmp_randstate_t rand_state;
  //  mpz_t rand_num2;
  //  gmp_randstate_t rand_state2;
   seed = 123456;
   seed2 = 654321;

   generate_random_number(&rand_num, seed, &rand_state);
   printf("\n");
   generate_random_number(&rand_num, seed2, &rand_state);
   printf("\n");
   //gmp_printf("%Zd\n", rand_num);
   //check if probabilistically prime
   int val = mpz_probab_prime_p(rand_num, 30);
   int val2 = mpz_probab_prime_p(rand_num, 30);
   printf("%d\n", val);
   printf("%d\n", val2);

   return 0;
}

static void generate_random_number(mpz_t *rand_num,
                                               unsigned long int seed,
                                               gmp_randstate_t *rand_state) {
   printf("Generated \"random\" number:\n");
   gmp_randinit_default (*rand_state);
   gmp_randseed_ui(*rand_state, seed);
   mpz_init(*rand_num);

   mpz_urandomb(*rand_num,*rand_state, 512);
   gmp_printf("%Zd\n", *rand_num);

  //  gmp_randclear(*rand_state);
  //  mpz_clear(*rand_num);

}
