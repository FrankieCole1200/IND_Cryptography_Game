#ifndef CHALLENGER_H
#define CHALLENGER_H

#include "cipher.h"

class Challenger {
    private:
    Cipher& cipher;
    int random_message_choice;

    public:
    explicit Challenger(Cipher& scheme) : cipher(scheme) {}

    string encrypt_random_message(const string& m0, const string& m1);
    int check_bit(int adversary_guess);
};


#endif
