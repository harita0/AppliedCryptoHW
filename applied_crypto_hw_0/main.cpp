#include <iostream>
#include <sstream>
#include <string>
#include <gmpxx.h>
#include <string_view>
#include <ranges>

#include "group_parameters.h"
#include "diffie_hellman_key_exchange.h"
#include "elgamal.h"
#include "rsa.h"
using namespace std;

mpz_class hex_to_int(std::string hex_string){
    if (hex_string.size() >= 2 && hex_string[0] == '0' && (hex_string[1] == 'x' || hex_string[1] == 'X')) {
        hex_string = hex_string.substr(2);
    }
    return mpz_class(hex_string, 16);
}

std::string int_to_hex(const mpz_class& n) {
    // n does not have prefix "0x".
    return n.get_str(16);
}

mpz_class read_hex(std::istringstream& hex_stream) {
    std::string hex_string;
    hex_stream >> hex_string;
    return hex_to_int(hex_string);
}

int main() {
    GroupParameters params;
    std::string line;

    std::cout << "Welcome! Please enter a sequence of newline separated commands, starting with setup_params!\nHere is an example sequence:\n\tsetup_params p g q\n\trsa_encrypt N publicKey message\n\trsa_decrypt N secretKey ciphertext\n\texit\nPlease type exit to finish your command sequence." << std::endl;
    std::vector<std::string> commands;
    while (std::getline(std::cin, line) && line!="exit") {
        commands.push_back(line);
    }
    std::cout << "\n\nResults:" << std::endl;
    for(std::vector<std::string>::iterator command = commands.begin(); command != commands.end(); command++){
        std::istringstream in(*command);
        std::string command_component;
        std::vector<std::string> command_components;
        while (in >> command_component) {
            command_components.push_back(command_component);
        }

        if (command_components[0] == "setup_params") {
            params.p = hex_to_int(command_components[1]);
            params.g = hex_to_int(command_components[2]);
            params.q = hex_to_int(command_components[3]);
        }
        else if (command_components[0] == "rsa_encrypt") {
            mpz_class N = hex_to_int(command_components[1]);
            mpz_class publicKey = hex_to_int(command_components[2]);
            mpz_class message = hex_to_int(command_components[3]);
            std::cout << "\nRSA Encryption:\nCiphertext: " << int_to_hex(rsa_encrypt(N, publicKey, message)) << std::endl;
        }
        else if (command_components[0] == "rsa_decrypt") {
            mpz_class N = hex_to_int(command_components[1]);
            mpz_class secretKey = hex_to_int(command_components[2]);
            mpz_class ciphertext = hex_to_int(command_components[3]);
            std::cout << "\nRSA Decryption:\nPlaintext: " << int_to_hex(rsa_decrypt(N, secretKey, ciphertext)) << std::endl;
        }
        else if (command_components[0] == "dh_key_exchange") {
            mpz_class publicKeyA = hex_to_int(command_components[1]);
            Keys res = dh_key_exchange(params, publicKeyA);
            std::cout << "\nDiffie-Hellman Key Exchange:\nPrivate key kb: " << int_to_hex(res.k_b) << "\nShared secret key: " << int_to_hex(res.shared_key) << std::endl;
        }
        else if (command_components[0] == "elgamal_encrypt") {
            mpz_class publicKey = hex_to_int(command_components[1]);
            mpz_class message = hex_to_int(command_components[2]);
            Ciphertexts ciphertexts = elgamal_encrypt(params, publicKey, message);
            std::cout << "\nElGamal Encryption:\nCiphertext 1: " << int_to_hex(ciphertexts.c1) << "\nCiphertext 2: " << int_to_hex(ciphertexts.c2) << std::endl;
        }
        else if (command_components[0] == "elgamal_decrypt") {
            mpz_class secretKey = hex_to_int(command_components[1]);
            mpz_class c1 = hex_to_int(command_components[2]);
            mpz_class c2 = hex_to_int(command_components[3]);
            std::cout << "\nElGamal Decryption:\nPlaintext: " << int_to_hex(elgamal_decrypt(params, secretKey, {c1, c2})) << std::endl;
        }
        else {
            std::cerr << "Error: unknown command " << command_components[0] << std::endl;
        }
    }

    return 0;
}