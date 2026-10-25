#include "monoalphabetic.h"
#include "alpha_map.h"

#include <string>
using std::string;

#include <map>
using std::map;

#include <utility>
using std::pair;

#include <vector>
using std::vector;

#include <algorithm>

#include <random>

// Constructor
Monoalphabetic::Monoalphabetic() : Cipher("Monoalphabetic Cipher") {
    key_gen();
    key_inverse_gen();
}

// --------------------------
// ENCRYPTION ALGORITHM
// --------------------------

/*
    - The encryption algorithm for the monoalphabetic cipher uses the key to
    map each character in the message to each character in the ciphertext 
*/
string Monoalphabetic::encrypt(const std::string& message) const {
    string c;

    for (char l: message) {
        c += get_char(secret_key_.at(l));
    }

    return c;
}

// --------------------------
// DECRYPTION ALGORITHM
// --------------------------

string Monoalphabetic::decrypt(const std::string& ciphertext) const {
    string m;

    for (char l: ciphertext) {
        m += secret_key_inverse_.at(get_num(l));
    }

    return m;
}

// --------------------------
// KEY GENERATION ALGORITHM
// --------------------------

/*
    - The KGen algorithm for a monoalphabetic cipher requires us to create a
    bijection of our message space to itself.
    - This means for every character in our message space, we randomly choose
    any unchosen character from the message space itself.
*/
void Monoalphabetic::key_gen() {
    map<char, int> key = get_alpha_to_num();
    
    vector<int> values; // all the values the characters in key are assigned to
    for (const auto&p: key) {
        values.push_back(p.second);
    }

    static std::mt19937 gen(std::random_device{}()); // mersenne_twister_engine seeded with rd()
    std::shuffle(values.begin(), values.end(), gen); // shuffle all the values randomly

    auto value = values.begin(); 
    for (pair<const char, int>& p: key) {
        p.second = *value++;
    }

    secret_key_ = key;
}

void Monoalphabetic::key_inverse_gen() {
    map<int, char> key_inverse;

    for (auto& p: secret_key_) {
        key_inverse.emplace(pair<int, char>(p.second, p.first));
    }

    secret_key_inverse_ = key_inverse;
}
