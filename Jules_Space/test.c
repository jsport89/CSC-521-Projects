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
/*
const mpz_t n0 = 16586219440392868678950493674373228226755023453566380544778827468536293369070578005044103018679897826666988847478111125894645738617945022721399003187371315095776714268710828111900839935166040593805812450444207971154277250135488735224052767242108711688695472665535393219411816441863936671931207229988569378091;
const mpz_t n1 = 40551717335634282796188595809907574636047497578447239742728984932123966624413413502767149538720812803461325270023373882379621912810451972080538881907407663962222269155722813641736702957601282436859549047516678171448999396597860674018511185283001161464214443896828880085703268792922456861374890446256379858691;
const mpz_t n2 = 4584858127334481888956949636814087178936709594206799808830668511090245484755459879886892333675036017220400875215068783286641235741086763296223761930083971649736933265062126998568066740316971527362949091536302591669771961571588299188524997328196439934550567284781621727929881967179779863875897111578886729511;
const mpz_t n3 = 1570766449183627979100442662913287727772274846158509712811172039635344158746614069049986886478456900415278603117372769010036993903189733563405201678779117407772760573607468969353204845625961421626699057281709281387675084326564182607013228649375460421593546978553700073337461128259564002885644923212654351738733;
const mpz_t n4 = 20206959438259854707096595471756105531930316075003167441731682706437219837341080908001111386293866032342626326848774263655678734593467631039894350313079615694852898024651578877719067806299113646594515472905349384536141736001255892484345636015474986800809610322697749058964984183679288924809293079735255754321;
const mpz_t n5 = 29824288303830669783641470318274489446681455929555569506212122576585040522591135570183377808244939609277778037167531249368105830574116003529097192484725011003242620065129581649476948641802290844900777295888790511736032138377077257780102810765337767474301386906507194607400736153806431242852566523065854979187;
*/
static void generate_random_number(mpz_t *rand_num, unsigned long int seed);
static int gcd_small_ints(int num1, int num2);

int main() {
  unsigned long int seed, seed2;
  mpz_t rand_num, rand_num2, rand_num3;
  //  mpz_t rand_num2;
  //  gmp_randstate_t rand_state2;
  seed = 654321;
  seed2 = 98765;

/* Task I */
  printf("***Task 1***\n\n");

  /*
  * 1. Generates a pseudo 512-bit integer
  */
  printf("Part 1:\n");
  generate_random_number(&rand_num, seed);
  generate_random_number(&rand_num2, seed2);
  gmp_printf("Result: %Zd\n\n\n", rand_num);
  gmp_printf("Result: %Zd\n\n\n", rand_num2);
  /*
  * 2. Checking to see if that integer is (probabilistically) prime
  * Returns 2 if def prime, 1 if prob prime, 0 if def not prime
  */
  printf("Part 2:\n");
  /*
   * 0 = NOT prime
   * 1 = Maybe prime
   * 2 = Definitely prime
   */
  int val = mpz_probab_prime_p(rand_num, 30);
  printf("Probabilistically prime?: %d\n\n", val);

  /*
  * 3. Printing large integers to stdout
  * mpz_out_str([what filestream to print to]
  *             [what base]
  *             [rand_num]);
  */
  printf("Part 3:\n");
  mpz_out_str(stdout, 2, rand_num);
  printf("\n\n\n");

  /*
  * 4. Reading & writing larger integers from/to disk
  */
  printf("Part 4:\n");
  size_t res;
  FILE *opened_file1, *opened_file2;

  opened_file1 = fopen("write_file","w+");
  if (!opened_file1) {
     fprintf(stderr, "Bad write file: %s\n", "testing_RW_file");
     exit(EXIT_FAILURE);
  }
  /* mpz_out_str(file stream, base, #) */
  res = mpz_out_str(opened_file1, 2, rand_num);
  if (!res) {
    fprintf(stderr, "Couldn't write to file.\n");
    exit(EXIT_FAILURE);
  }
  opened_file2 = fopen("read_file","r");
  if (!opened_file2) {
     fprintf(stderr, "Bad read file: %s\n", "read_file");
     exit(EXIT_FAILURE);
  }
  mpz_init(rand_num3);
  /* NOTE: make sure the num in file is same base
   * as what you're trying to read. */
  res = mpz_inp_str(rand_num3, opened_file2, 10);
  if (!res) {
    fprintf(stderr, "Couldn't read from file.\n");
    exit(EXIT_FAILURE);
  }
  gmp_printf("rand_num3 (after read): %Zd\n\n", rand_num3);
  fclose(opened_file1);
  fclose(opened_file2);

  /*
  * 5. Adding and subtracting two large integers
  */
  printf("Part 5:\n");
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
  printf("Part 6:\n");
  mpz_t product;
  mpz_init(product);
  mpz_mul(product, rand_num, rand_num2);
  gmp_printf("Product: %Zd\n\n", product);

  /*
  * 7. Performs modular exponentiation on large integesrs (i.e. a^b mod c)
  */
  printf("Part 7:\n");
  mpz_t result, exp, mod;
  mpz_init(result);
  mpz_init(exp);
  mpz_set_si(exp, 2);                  /* si = signed integer */
  mpz_init(mod);
  mpz_set_si(mod, 10000000000000);
  /* void mpz_powm(rop, base, exp, mod); */
  mpz_powm(result, rand_num, exp, mod);
  gmp_printf("Result: %Zd\n\n\n", result);

/* Task II */
  printf("***Task 2***");
  int first_num, sec_num;
  first_num = 18;
  sec_num = 30;
  printf("\nGCD of %d and %d: ", first_num, sec_num);
  printf("%d\n\n\n", gcd_small_ints(first_num, sec_num));

/* Task III */
   printf("***Task 3***");
   mpz_t n0, n1, n2, n3, n4, n5;
   mpz_init_set_str(n0, "16586219440392868678950493674373228226755023453566380544778827468536293369070578005044103018679897826666988847478111125894645738617945022721399003187371315095776714268710828111900839935166040593805812450444207971154277250135488735224052767242108711688695472665535393219411816441863936671931207229988569378091", 10);
   mpz_init_set_str(n1, "40551717335634282796188595809907574636047497578447239742728984932123966624413413502767149538720812803461325270023373882379621912810451972080538881907407663962222269155722813641736702957601282436859549047516678171448999396597860674018511185283001161464214443896828880085703268792922456861374890446256379858691", 10);
   mpz_init_set_str(n2, "4584858127334481888956949636814087178936709594206799808830668511090245484755459879886892333675036017220400875215068783286641235741086763296223761930083971649736933265062126998568066740316971527362949091536302591669771961571588299188524997328196439934550567284781621727929881967179779863875897111578886729511", 10);
   mpz_init_set_str(n3, "1570766449183627979100442662913287727772274846158509712811172039635344158746614069049986886478456900415278603117372769010036993903189733563405201678779117407772760573607468969353204845625961421626699057281709281387675084326564182607013228649375460421593546978553700073337461128259564002885644923212654351738733", 10);
   mpz_init_set_str(n4, "20206959438259854707096595471756105531930316075003167441731682706437219837341080908001111386293866032342626326848774263655678734593467631039894350313079615694852898024651578877719067806299113646594515472905349384536141736001255892484345636015474986800809610322697749058964984183679288924809293079735255754321", 10);
   mpz_init_set_str(n5, "29824288303830669783641470318274489446681455929555569506212122576585040522591135570183377808244939609277778037167531249368105830574116003529097192484725011003242620065129581649476948641802290844900777295888790511736032138377077257780102810765337767474301386906507194607400736153806431242852566523065854979187", 10);

   mpz_t biggest_divisor;
   mpz_init(biggest_divisor);
   mpz_gcd(biggest_divisor, n4, n1);
   gmp_printf("\nGCD: %Zd\n\n", biggest_divisor);

   val = mpz_probab_prime_p(biggest_divisor, 30);
   printf("Probabilistically prime?: %d\n\n", val);

   /* Task IV */
   printf("***Task 4***");
   /* 1. key generation
      2. encryption & decryption functions
      Use a 1024-bit modulus and set e = 65537
   */



   return 0;
}

static void generate_random_number(mpz_t *rand_num, unsigned long int seed) {
   gmp_randstate_t rand_state;
   gmp_randinit_default (rand_state);       /* Init rand_state */
   gmp_randseed_ui(rand_state, seed);       /* Init seed */
   mpz_init(*rand_num);                      /* Init mpz (contains num) */
   mpz_urandomb(*rand_num, rand_state, 512); /* Generate random 512bit # */
}

static int gcd_small_ints(int num1, int num2){
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

// static void random_prime(mpz_t *num){
//
//   while(1){
//     //initialize num
//     mpz_init(*num);
//     //generate random number
//     generate_random_number(num, );
//     //if its prime, return
//   }
//
// }
