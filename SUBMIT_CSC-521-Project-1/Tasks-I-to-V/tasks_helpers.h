#ifndef TASKS_HELPERS_H
#define TASKS_HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>
#include <unistd.h>

#define MAGIC_NUM_1 654321
#define MAGIC_NUM_2 98765

/* Struct for storing RSA key exchange n, e, and d */
typedef struct RSA_instance {
   mpz_t pub_key; /* P x Q */
   mpz_t pub_exp; /* Public Exponent */
   mpz_t priv_key; /* priv_key = pub_exp^(-1) mod λ(pub_key) */

} RSA_instance;

/* Call tasks */
void taskI();
void taskII();
void taskIII();
void taskIV();
void taskV();

/* Helpers */
void generate_random_number(mpz_t *rand_num, unsigned long int seed);
int gcd_small_ints(int num1, int num2);
void random_prime(mpz_t *num);
void generate_RSA_instance(RSA_instance *new_session);
void encrypt(mpz_t message, RSA_instance *cur_session, mpz_t *cipher);
void decrypt(mpz_t cipher, RSA_instance *cur_session, mpz_t *decrypted_message);
int hex_to_ascii(char c, char d);
void error(char *message, char *file_name, int line);

#endif /* tasks_helpers.h */
