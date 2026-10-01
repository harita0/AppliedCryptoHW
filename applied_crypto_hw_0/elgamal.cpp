#include <gmpxx.h>
#include <fstream>

#include "modular_arithmetic.h"
#include "group_parameters.h"

struct Ciphertexts{
    mpz_class c1;
    mpz_class c2;
};

Ciphertexts elgamal_encrypt(GroupParameters params, const mpz_class& public_key, const mpz_class& message){
    mpz_class y = sample_key(params.q);
    mpz_class c1 = repeated_squaring(params.g, y, params.p);
    mpz_class shared_secret_key = repeated_squaring(public_key, y, params.p);
    mpz_class c2 = mod_reduction(message * shared_secret_key, params.p);
    return {c1, c2};
}

mpz_class elgamal_decrypt(GroupParameters params, const mpz_class& secret_key, const Ciphertexts& ciphertexts){
    mpz_class shared_secret_key = repeated_squaring(ciphertexts.c1, secret_key, params.p);
    return mod_reduction(ciphertexts.c2 * mod_inverse(shared_secret_key, params.p), params.p);
}