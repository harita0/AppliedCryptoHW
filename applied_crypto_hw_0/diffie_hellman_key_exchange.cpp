#include <gmpxx.h>
#include <fstream>

#include "modular_arithmetic.h"
#include "group_parameters.h"

struct Keys{
    mpz_class k_b;
    mpz_class shared_key;
};

Keys dh_key_exchange(GroupParameters params, const mpz_class& public_key_A){
    mpz_class k_b = sample_key(params.q);
    mpz_class public_key_B = repeated_squaring(params.g, k_b, params.p);
    mpz_class shared_key = repeated_squaring(public_key_A, k_b, params.p);
    return {k_b, shared_key};
}