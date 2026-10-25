#ifndef IND_EAV_H
#define IND_EAV_H

#include "adversary.h"
#include "challenger.h"

#include <string>
using std::string;

class IND_EAV {
    private:
    Adversary& adversary;
    Challenger& challenger;

    public:
    // Constructor
    IND_EAV(Adversary& a, Challenger& c) : 
        adversary(a), challenger(c) {}

    int play() {
        auto [m0, m1] = adversary.choose_messages(); // Adversary chooses 2 messages from message space

        string c = challenger.encrypt_random_message(m0, m1); // challenger returns the ciphertext of a randomly chosen message adversary gave it 

        int bit = adversary.guess_message(c); // Adversary guesses if m0 or m1 was encrypted

        int check = challenger.check_bit(bit); // Challenger confirms the guess.
    
        return (check == 1); // returns true (1) if the guess was correct
    }

};

#endif