#pragma once
#include <gmpxx.h>

struct GroupParameters {
    mpz_class p;
    mpz_class g;
    mpz_class q;
};