#ifndef CIPHER_H
#define CIPHER_H

#include <string>
using std::string;

// Common interface for secret-key encryption schemes.
// Each implementation manages its own secret key.
class Cipher {
public:
    explicit Cipher(const string& cipher_name) : name(cipher_name) {}
    const string name;

    virtual ~Cipher() = default;

    virtual string encrypt(const string& message) const = 0;
    virtual string decrypt(const string& ciphertext) const = 0;
};

#endif
