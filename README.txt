Update (2/12/2017):
- Scans of top million sites from scans.io is huge. Couldn't find a
  smaller set of scans (we only need a couple 1000).
- Moving on, I took a couple entries from the .json file from scans.io
  to see how I could extract the RSA modulus. It's in Base64 so that
  needs to be converted to decimal for factoring. The other thing is,
  the json library I tried to use in a short python program. It doesn't like
  the formatting of the .json file from scans.io. As in, the .json file needs to
  be encapsulated with a set of "[ ]" and each object needs to be delimited
  by a " , ". THEN when you call json.load(data_file) it'll print.
- Figured out how to operate on arrays of mpz_t. Simply init each index
  in the array then set each one.
~Jules
