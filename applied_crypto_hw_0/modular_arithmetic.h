#pragma once
#include <gmpxx.h>

extern mpz_class mod_reduction(const mpz_class& a, const mpz_class& m);

extern mpz_class repeated_squaring(mpz_class a, mpz_class b, const mpz_class& m);

struct EgcdResult {
    mpz_class gcd_a_b;
    mpz_class x;
    mpz_class y;
};

extern EgcdResult egcd(mpz_class a, mpz_class b);

extern mpz_class mod_inverse(const mpz_class& a, const mpz_class& m);

extern mpz_class sample_key(const mpz_class& n);