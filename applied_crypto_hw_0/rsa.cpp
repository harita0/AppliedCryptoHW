#include <gmpxx.h>

#include "modular_arithmetic.h"

mpz_class rsa_encrypt(const mpz_class& N, const mpz_class& public_key, const mpz_class& message){
    mpz_class ciphertext = repeated_squaring(message, public_key, N);
    return ciphertext;
}

mpz_class rsa_decrypt(const mpz_class& N, const mpz_class& secret_key, const mpz_class& ciphertext){
    mpz_class message = repeated_squaring(ciphertext, secret_key, N);
    return message;
}
