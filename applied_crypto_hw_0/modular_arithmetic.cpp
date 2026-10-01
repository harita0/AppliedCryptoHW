#include <gmpxx.h>
#include <vector>
#include <fstream>
#include <iostream>

mpz_class mod_reduction(const mpz_class& a, const mpz_class& m){
    mpz_class r = a % m;
    
    if(r < 0){
        r = r + m;
    }

    return r;
}

// Modular exponentiation was done via iterative repeated squaring.
// Algorithm for repeated squaring: https://www.cs.toronto.edu/~denisp/csc373/docs/repeated_squaring_binary_search.pdf
mpz_class repeated_squaring(mpz_class a, mpz_class b, const mpz_class& m){
    
    mpz_class t = 1;
    a = mod_reduction(a, m);

    while (b > 0){
        if (b % 2 == 1){
            t = (t * a) % m;
            b = b - 1;
        }
        else{
            a = (a * a) % m;
            b = b/2;
        }
    }

    return (t % m);
}


struct EgcdResult {
    mpz_class gcd_a_b;
    // Bezout coefficient of a
    mpz_class x;
    // Bezout coefficient of b
    mpz_class y;
};

EgcdResult egcd(mpz_class a, mpz_class b){
    if(a == 0){
        return {b, 0, 1};
    }

    mpz_class x_prev = 1;
    mpz_class y_prev = 0;

    mpz_class x_cur = 0;
    mpz_class y_cur = 1;

    while (b != 0){
        mpz_class q = a / b;
        
        mpz_class rem = a - (q * b);
        a = b;
        b = rem;

        mpz_class temp = x_prev - q * x_cur;
        x_prev = x_cur;
        x_cur = temp;

        temp = y_prev - q * y_cur;
        y_prev = y_cur;
        y_cur = temp;
    }

    return {a, x_prev, y_prev};
}

mpz_class mod_inverse(const mpz_class& a, const mpz_class& m){
    EgcdResult res = egcd(mod_reduction(a, m), m);

    // May be unnecessary because the HW spec specifies that we wouldn't need to worry about this case (as we will be given valid input).  
    if(res.gcd_a_b != 1){
        throw std::invalid_argument("Error: a is not invertible mod m.");
    }

    return mod_reduction(res.x, m);
}

mpz_class sample_key(const mpz_class& n) {
    size_t num_bits  = mpz_sizeinbase(n.get_mpz_t(), 2);
    // Given that num_bits may not be a multiple of 8, and that we can only read raw binary bytes from urandom, num_bits is rounded up to a multiple of 8.
    size_t num_bytes = (num_bits + 7) / 8;
    std::vector<unsigned char> key_buff(num_bytes);
 
    std::ifstream urandom("/dev/urandom", std::ios::in | std::ios::binary);
    if (!urandom) {
        throw std::runtime_error("Error: Cannot open /dev/urandom. Access to this stream is necessary to randomly sample keys.");
    }
    
    mpz_class key = 0;
    // The random bit vector sampled from urandom will very likely be longer than the length expected for the key (as the key is an element in a group whose order is n, and the num of bits needed to represent n might not be a multiple of 8).
    // NIST standards (NIST SP 800-56A Rev. 3) for key generation (e.g. in Diffie Hellman) specify that selected key should be in range [1, n - 1] (so key = 0 isn't valid). https://nvlpubs.nist.gov/nistpubs/SpecialPublications/NIST.SP.800-56Ar3.pdf
    while(key >= n || key == 0)
    {
        urandom.read(reinterpret_cast<char*>(key_buff.data()), num_bytes);
        if(urandom){
            mpz_import(key.get_mpz_t(), num_bytes, 1, 1, 0, 0, key_buff.data());
            // Trims extra random bits from key (still preserves the randomness of the generated key, since the bits are sampled independently).
            mpz_fdiv_r_2exp(key.get_mpz_t(), key.get_mpz_t(), num_bits);
        }
        else{
            throw std::runtime_error("Error: Cannot read from /dev/urandom. Read access to this stream is necessary to randomly sample keys.");
        }
    }
    urandom.close();
    return key;
}
