import base64

def append_to_file(to_scrub):
    for line in to_scrub:
        if line == 'null\n':
            continue
        no_quotes_line = line[1:-2]
        print(base64.b64decode(no_quotes_line))

if __name__ == '__main__':
    scrub_this_1 = open('server_key_exchange_moduli.txt', 'r')
    scrub_this_2 = open('subject_key_info_moduli.txt', 'r')
    scrub_this_3 = open('chain_server_key_info_moduli.txt', 'r')

    append_to_file(scrub_this_1)
    append_to_file(scrub_this_2)
    append_to_file(scrub_this_3)

    scrub_this_1.close()
    scrub_this_2.close()
    scrub_this_3.close()

    # open file
        # get each line
        # if "null" move on
        # otherwise, scrub quotes
        # convert to decimal string
