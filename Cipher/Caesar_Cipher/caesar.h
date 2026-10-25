#ifndef CAESAR_H
#define CAESAR_H

#include "cipher.h"

#include <string>
using std::string;

class Caesar : public Cipher {
public:
    Caesar();

    std::string encrypt(const std::string& message) const override;
    std::string decrypt(const std::string& ciphertext) const override;

private:
    static int key_gen();
    int secret_key_;
};

#endif
