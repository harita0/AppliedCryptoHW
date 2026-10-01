#include <gmpxx.h>
#include <fstream>

#include "modular_arithmetic.h"
#include "group_parameters.h"

struct Ciphertexts{
    mpz_class c1;
    mpz_class c2;
};

extern Ciphertexts elgamal_encrypt(GroupParameters params, const mpz_class& public_key, const mpz_class& message);

extern mpz_class elgamal_decrypt(GroupParameters params, const mpz_class& secret_key, const Ciphertexts& ciphertexts);