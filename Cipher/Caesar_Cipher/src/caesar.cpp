#include "caesar.h"
#include "alpha_map.h"

#include <random>
#include <string>

// Constructor
Caesar::Caesar() : Cipher("Caesar Cipher"), secret_key_(key_gen()) {}

// --------------------------
// ENCRYPTION ALGORITHM
// --------------------------

// Encrypt by shifting each character forward by the secret key.
std::string Caesar::encrypt(const std::string& message) const {
    static const int key_space_size = get_key_space_size();
    std::string ciphertext;

    for (char letter : message) {
        const int number = get_num(letter);
        const int shifted = (number + secret_key_) % key_space_size;
        ciphertext += get_char(shifted);
    }

    return ciphertext;
}

// --------------------------
// DECRYPTION ALGORITHM
// --------------------------

// Decrypt by shifting each character backward by the secret key.
std::string Caesar::decrypt(const std::string& ciphertext) const {
    static const int key_space_size = get_key_space_size();
    std::string message;

    for (char letter : ciphertext) {
        const int number = get_num(letter);
        const int shifted = ((number - secret_key_) % key_space_size + key_space_size) % key_space_size;
        message += get_char(shifted);
    }

    return message;
}


// --------------------------
// KEY GENERATION ALGORITHM
// --------------------------

// Sample a key from the key space 0-94.
int Caesar::key_gen() {
    static std::mt19937 gen(std::random_device{}());
    const int key_space_size = get_key_space_size();
    std::uniform_int_distribution<> distrib(0, key_space_size - 1);
    return distrib(gen);
}
