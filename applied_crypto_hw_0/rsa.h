#pragma once
#include <gmpxx.h>

#include "modular_arithmetic.h"

extern mpz_class rsa_encrypt(const mpz_class& N, const mpz_class& public_key, const mpz_class& message);

extern mpz_class rsa_decrypt(const mpz_class& N, const mpz_class& secret_key, const mpz_class& ciphertext);