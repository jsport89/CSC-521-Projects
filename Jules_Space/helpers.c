#include "tasks_helpers.h"

void error(char *message, char *file_name, int line) {
   fprintf(stderr, "%s. In file: %s. Line: %d.\n", message,
           file_name, line);
   exit(EXIT_FAILURE);
}

int hex_to_ascii(char c, char d){
    char hex[5], *stop;
    hex[0] = '0'; hex[1] = 'x'; hex[2] = c; hex[3] = d; hex[4] = 0;
    return strtol(hex, &stop, 16);
}

void encrypt(mpz_t message, RSA_instance *cur_session, mpz_t *cipher) {
  printf("\n In encrypt:\n");
  gmp_printf("\nbase: %Zd\n\n", message);
  gmp_printf("\nexp: %Zd\n\n", cur_session->pub_exp);
  gmp_printf("\nto_mod_by: %Zd\n\n", cur_session->priv_key);
  mpz_powm(*cipher, message, cur_session->pub_exp, cur_session->pub_key);
}

void decrypt(mpz_t cipher, RSA_instance *cur_session, mpz_t *decrypted_message) {
  printf("\n In decrypt:\n");
  gmp_printf("\nbase: %Zd\n\n", cipher);
  gmp_printf("\nexp: %Zd\n\n", cur_session->priv_key);
  gmp_printf("\nto_mod_by: %Zd\n\n", cur_session->pub_key);
  mpz_powm(*decrypted_message, cipher, cur_session->priv_key, cur_session->pub_key);
}

void generate_RSA_instance(RSA_instance *new_session) {
  int result;
  mpz_t p, q, lambda, p_min_one, q_min_one, gcd;
  mpz_init(p);
  mpz_init(q);
  mpz_init(lambda);
  mpz_init(p_min_one);
  mpz_init(q_min_one);
  mpz_init(gcd);
  result = 0;

  mpz_init(new_session->pub_key);
  mpz_init(new_session->priv_key);
  mpz_init_set_str(new_session->pub_exp, "65537", 10);

  do {
    random_prime(&p);                      // p
    random_prime(&q);                      // q

    mpz_sub_ui(p_min_one, p, 1);           // p - 1
    mpz_sub_ui(q_min_one, q, 1);           // q - 1

    mpz_lcm(lambda, p_min_one, q_min_one); // Lambda

    mpz_gcd(gcd, new_session->pub_exp, lambda);
    result = mpz_cmp_ui(gcd, 1);


  } while (result != 0);

  mpz_mul(new_session->pub_key, p, q);
  result = mpz_invert(new_session->priv_key, new_session->pub_exp, lambda);

  printf("\nIn generate instance. \nmpz_invert result(want non-zero): %d\n", result);
  gmp_printf("\npub_key: %Zd\n\n", new_session->pub_key);
  gmp_printf("\npub_exp: %Zd\n\n", new_session->pub_exp);
  gmp_printf("\npriv_key: %Zd\n\n", new_session->priv_key);

  gmp_printf("\np: %Zd\n\n", p);
  gmp_printf("\nq: %Zd\n\n", q);
  gmp_printf("\nlambda: %Zd\n\n", lambda);
  gmp_printf("\np_min_one: %Zd\n\n", p_min_one);
  gmp_printf("\nq-1: %Zd\n\n", q_min_one);
}

void generate_random_number(mpz_t *rand_num, unsigned long int seed) {
   gmp_randstate_t rand_state;
   gmp_randinit_default (rand_state);        /* Init rand_state */
   gmp_randseed_ui(rand_state, seed);        /* Init seed */
   mpz_init(*rand_num);                      /* Init mpz (contains num) */
   mpz_urandomb(*rand_num, rand_state, 512); /* Generate random 512bit # */
}

int gcd_small_ints(int num1, int num2){
  int gcd;

  if (num1 < num2)
    gcd = num1;
  else
    gcd = num2;

  while (gcd > 1) {
    if (num1 % gcd == 0 && num2 % gcd == 0)
      return gcd;

    gcd--;
  }
  return 1;
}

void random_prime(mpz_t *num){
  mpz_t random_number, prime;
  mpz_init(random_number);
  mpz_init(prime);
  srand(time(NULL));
  generate_random_number(&random_number, rand());
  mpz_nextprime(prime, random_number);
  mpz_set(*num, prime);
  sleep(1);
}
