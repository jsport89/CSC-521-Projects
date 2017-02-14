import multiprocessing
import gmpy2
from gmpy2 import mpz
import time

def load_keys(keys):
    mpz_array_local = []
    num_of_keys = 0

    # Parse each key into an array
    for key_string in keys:
        key_mpz = mpz(key_string[:-1])
        mpz_array_local.append(key_mpz)
        num_of_keys += 1

    return mpz_array_local


def gcds_on_keys(mpz_array, start_index, core_count):
    # Perform GCDs on every key
    for key in range(start_index, len(mpz_array), core_count):
        for other_key in range(key + 1, len(mpz_array)):
            gcd_found = gmpy2.gcd(mpz_array[key], mpz_array[other_key])
            if (gcd_found != 1) and gmpy2.is_prime(gcd_found):
                return (key, other_key, gcd_found)


    # Output only the gcds > 1 and their corresponding index #


def gcds_multi_core(mpz_array, core_count):
    pool = multiprocessing.Pool()
    tasks = []
    num = 0

    while num < core_count:
        tasks.append((mpz_array, num, core_count))
        num += 1

    results = [pool.apply_async(gcds_on_keys, t) for t in tasks]

    for result in results:
        print result.get()


if __name__ == '__main__':

    ## Load das keys
    keys = open('keys.txt', 'r')
    mpz_array = load_keys(keys)
    core_count = multiprocessing.cpu_count()

    ## No parallelization
    start = time.time()
    result = gcds_on_keys(mpz_array, 0, 1)
    end = time.time()
    print "No parallelization:"
    print (end - start)

    ## With parallelization
    start = time.time()
    gcds_multi_core(mpz_array, core_count)
    end = time.time()
    print "With parallelization:"
    print (end - start)
