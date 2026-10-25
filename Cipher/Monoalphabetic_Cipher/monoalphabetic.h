#ifndef MONOALPHABETIC_H
#define MONOALPHABETIC_H

#include "cipher.h"

#include <map>
using std::map;

#include <vector>
using std::vector;

#include <string>
using std::string;

class Monoalphabetic: public Cipher {
public:
    Monoalphabetic();
    
    std::string encrypt(const std::string& message) const override;
    std::string decrypt(const std::string& ciphertext) const override;

private:
    void key_gen();
    void key_inverse_gen();
    map<char, int> secret_key_;
    map<int, char> secret_key_inverse_;

};

#endif
