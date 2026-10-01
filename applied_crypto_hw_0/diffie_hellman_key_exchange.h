#include <gmpxx.h>

#include "modular_arithmetic.h"
#include "group_parameters.h"

struct Keys{
    mpz_class k_b;
    mpz_class shared_key;
};

extern Keys dh_key_exchange(GroupParameters params, const mpz_class& public_key_A);