#include "tasks_helpers.h"

/* Global mpz_t's */
mpz_t n0, n1, n2, n3, n4, n5, biggest_divisor;

void taskI() {
   unsigned long int seed, seed2;
   mpz_t rand_num, rand_num2, rand_num3;

   seed = MAGIC_NUM_1;
   seed2 = MAGIC_NUM_2;

   printf("***Task 1***\n\n");

   /* Generates a pseudo 512-bit integer */
   printf("Part 1: Generates a pseudo 512-bit integer.\n");
   generate_random_number(&rand_num, seed);
   generate_random_number(&rand_num2, seed2);
   gmp_printf("Result: %Zd\n\n", rand_num);
   gmp_printf("Result: %Zd\n\n\n", rand_num2);

   /* Checks if int is prime */
   /*
   * 0 = NOT prime
   * 1 = Maybe prime
   * 2 = Definitely prime
   */
   printf("Part 2: Check if int is prime\n");
   int val = mpz_probab_prime_p(rand_num, 30);
   printf("Probabilistically prime result: %d\n\n", val);

   /* Print large int to stdout */
   printf("Part 3: Print mpz_t to stdout.\n");
   mpz_out_str(stdout, 2, rand_num);
   printf("\n\n\n");

   /* Reading & writing larger integers from/to disk */
   printf("Part 4: RW mpz_t from/to disk\n");
   size_t res;
   FILE *opened_file1, *opened_file2;

   opened_file1 = fopen("write_file","w+");
   if (!opened_file1)
      error("Bad write file: Testing_RW_file", __FILE__, __LINE__);

   res = mpz_out_str(opened_file1, 2, rand_num);
   if (!res)
      error("Couldn't write to file", __FILE__, __LINE__);

   opened_file2 = fopen("read_file","r");
   if (!opened_file2)
      error("Bad read file: Reading file", __FILE__, __LINE__);


   mpz_init(rand_num3);
   /* NOTE: Last param of mpz_inp_str is the base*/
   res = mpz_inp_str(rand_num3, opened_file2, 10);
   if (!res)
      error("Couldn't read from file", __FILE__, __LINE__);

   gmp_printf("rand_num3 (after read): %Zd\n\n", rand_num3);
   fclose(opened_file1);
   fclose(opened_file2);

   /* Adding and subtracting two large integers */
   printf("Part 5: Add and Sub two mpz_t's\n");
   mpz_t sum, difference;
   mpz_init(sum);
   mpz_init(difference);
   mpz_add(sum, rand_num, rand_num2);
   mpz_sub(difference, rand_num, rand_num2);
   gmp_printf("Sum: %Zd\n\n", sum);
   gmp_printf("Diff: %Zd\n\n", difference);

   /* Multiplying two large integers */
   printf("Part 6: Mult two mpz_t's\n");
   mpz_t product;
   mpz_init(product);
   mpz_mul(product, rand_num, rand_num2);
   gmp_printf("Product: %Zd\n\n", product);

   /* Performs modular exponentiation on large integesrs (i.e. a^b mod c) */
   printf("Part 7: Perform mod exp on mpz_t's\n");
   mpz_t result, exp, mod;
   mpz_init(result);
   mpz_init(exp);
   mpz_set_si(exp, 2);
   mpz_init(mod);
   mpz_set_si(mod, 10000000000000);
   mpz_powm(result, rand_num, exp, mod);
   gmp_printf("Result: %Zd\n\n\n", result);
}


void taskII() {
   printf("***Task 2***\n\n");
   printf("Apply own GCD function.\n\n");
   int first_num, sec_num;
   first_num = 18;
   sec_num = 30;
   printf("\nGCD of %d and %d: ", first_num, sec_num);
   printf("%d\n\n\n", gcd_small_ints(first_num, sec_num));
}


void taskIII() {
   printf("***Task 3***\n\n");
   printf("Apply built-in GCD to RSA moduli.\n\n");
   mpz_init_set_str(n0, "16586219440392868678950493674373228226755023453566380544778827468536293369070578005044103018679897826666988847478111125894645738617945022721399003187371315095776714268710828111900839935166040593805812450444207971154277250135488735224052767242108711688695472665535393219411816441863936671931207229988569378091", 10);
   mpz_init_set_str(n1, "40551717335634282796188595809907574636047497578447239742728984932123966624413413502767149538720812803461325270023373882379621912810451972080538881907407663962222269155722813641736702957601282436859549047516678171448999396597860674018511185283001161464214443896828880085703268792922456861374890446256379858691", 10);
   mpz_init_set_str(n2, "4584858127334481888956949636814087178936709594206799808830668511090245484755459879886892333675036017220400875215068783286641235741086763296223761930083971649736933265062126998568066740316971527362949091536302591669771961571588299188524997328196439934550567284781621727929881967179779863875897111578886729511", 10);
   mpz_init_set_str(n3, "1570766449183627979100442662913287727772274846158509712811172039635344158746614069049986886478456900415278603117372769010036993903189733563405201678779117407772760573607468969353204845625961421626699057281709281387675084326564182607013228649375460421593546978553700073337461128259564002885644923212654351738733", 10);
   mpz_init_set_str(n4, "20206959438259854707096595471756105531930316075003167441731682706437219837341080908001111386293866032342626326848774263655678734593467631039894350313079615694852898024651578877719067806299113646594515472905349384536141736001255892484345636015474986800809610322697749058964984183679288924809293079735255754321", 10);
   mpz_init_set_str(n5, "29824288303830669783641470318274489446681455929555569506212122576585040522591135570183377808244939609277778037167531249368105830574116003529097192484725011003242620065129581649476948641802290844900777295888790511736032138377077257780102810765337767474301386906507194607400736153806431242852566523065854979187", 10);

   mpz_init(biggest_divisor);
   mpz_gcd(biggest_divisor, n4, n1);
   gmp_printf("\nGCD: %Zd\n\n", biggest_divisor);

   int val;
   val = mpz_probab_prime_p(biggest_divisor, 30);
   printf("Probabilistically prime?: %d\n\n", val);

   int i, j, array_size;
   array_size = 6;
   mpz_t big_ints[array_size], another_big_div;

   for (i = 0; i < array_size; i++)
     mpz_init(big_ints[i]);

   mpz_init(another_big_div);
   mpz_set(big_ints[0], n0);
   mpz_set(big_ints[1], n1);
   mpz_set(big_ints[2], n2);
   mpz_set(big_ints[3], n3);
   mpz_set(big_ints[4], n4);
   mpz_set(big_ints[5], n5);

   for (i = 0; i < array_size; i++) {
     for (j = i; j < array_size; j++) {
       mpz_gcd(another_big_div, big_ints[i], big_ints[j]);
       val = mpz_probab_prime_p(another_big_div, 30);
       gmp_printf("\n#'s: %d and %d\nPrimeness: %d.\n\n", i, j, val);
     }
   }
}


void taskIV() {
   printf("***Task 4***\n\n");
   printf("Implement RSA.\n\n");
   /*
    * 1. key generation
    * 2. encryption & decryption functions
    * Use a 1024-bit modulus and set e = 65537
    */

   RSA_instance new_session;
   generate_RSA_instance(&new_session);

   mpz_t message, cipher, decrypted_message;
   mpz_init_set_str(message, "1234", 10);
   mpz_init(decrypted_message);
   mpz_init(cipher);

   gmp_printf("\nMessage: %Zd\n\n", message);

   encrypt(message, &new_session, &cipher);

   gmp_printf("\nAfter encrypt: %Zd\n\n", cipher);

   decrypt(cipher, &new_session, &decrypted_message);

   gmp_printf("\nAfter decrypt: %Zd\n\n", decrypted_message);
}


void taskV() {
   printf("***Task 5***\n\n");
   printf("Decipher given cipher.\n");
   RSA_instance n1_session;
   mpz_t p1, p4, p1_min_one, q_min_one, lambda, new_cipher, original_message;

   mpz_init(n1_session.pub_key);
   mpz_init(n1_session.pub_exp);
   mpz_init(n1_session.priv_key);
   mpz_init(p1);
   mpz_init(p1_min_one);
   mpz_init(q_min_one);
   mpz_init(p4);
   mpz_init(lambda);
   mpz_init(original_message);
   mpz_init_set_str(new_cipher,"21146360143304879584870745425454388339130123805805568677708774327812403952131165797204738467133149361047649013024046635077706337064012827612590921151908148059770846065742477880796909563967180928127867305091668302606535495924923769855539541035294698913180720693428844640760225771248139707088375991239007140103", 10);

   mpz_set_str(n1_session.pub_exp, "65537", 10);
   mpz_divexact(p1, n1, biggest_divisor);
   mpz_set(n1_session.pub_key, n1);

   mpz_sub_ui(p1_min_one, p1, 1);
   mpz_sub_ui(q_min_one, biggest_divisor, 1);

   mpz_lcm(lambda, p1_min_one, q_min_one);
   mpz_invert(n1_session.priv_key, n1_session.pub_exp, lambda);

   decrypt(new_cipher, &n1_session, &original_message);
   gmp_printf("\noriginal_message: %Zd\n\n", original_message);

   /* Hex to ascii */
   printf("Message in ASCII: ");
   char buff [100];
   char * big_num_as_hex_string;
   big_num_as_hex_string = mpz_get_str(buff, 16, original_message);
   char *p = big_num_as_hex_string;
   while(*p != '\0'){
      char first = *p++;
      char second = *p++;
      printf("%c", hex_to_ascii(first, second));
   }
   printf("\n\n");

}
