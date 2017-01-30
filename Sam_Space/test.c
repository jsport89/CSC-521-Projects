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
   mpz_t rand_num, rand_num2;
   gmp_randstate_t rand_state, rand_state2;
  //  mpz_t rand_num2;
  //  gmp_randstate_t rand_state2;
   seed = 123456;
   seed2 = 654321;

   generate_random_number(&rand_num, seed, &rand_state);
   printf("\n");
   generate_random_number(&rand_num2, seed2, &rand_state2);
   printf("\n");

   /*
   * 2. Checking to see if that integer is (probabilistically) prime
   * Returns 2 if def prime, 1 if prob prime, 0 if def not prime
   */

   int val = mpz_probab_prime_p(rand_num, 30);
   printf("Probabilistically prime?: %d\n", val);

   /*
   * 3. Printing large integers to stdout
   * What filestream to print to and what base
   */
   mpz_out_str(stdout, 2, rand_num);
   printf("\n\n");
   /*
   * 4. Reading & writing larger integers from/to disk
   */


   /*
   * 5. Adding and subtracting two large integers
   */
   mpz_t sum, difference;
   mpz_init(sum);
   mpz_init(difference);
   mpz_add(sum, rand_num, rand_num2);
   mpz_sub(difference, rand_num, rand_num2);

   gmp_printf("Sum: %Zd\n\n", sum);
   gmp_printf("Diff: %Zd\n\n", difference);

   /*
   * 6. Multiplying two large integers
   */
   mpz_t product;
   mpz_init(product);
   mpz_mul(product, rand_num, rand_num2);
   gmp_printf("Product: %Zd\n\n", product);

   /*
   * 7. Performs modular exponentiation on large integesrs (i.e. a^b mod c)
   */
   mpz_t result, exp, mod;
   mpz_init(result);
   mpz_init(exp);
   mpz_set_si(exp, 2);
   mpz_init(mod);
   mpz_set_si(mod, 10000000000000);
   //void mpz_powm(rop, base, exp, mod);
   mpz_powm(result, rand_num, exp, mod);
   gmp_printf("Result: %Zd\n\n", result);
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
