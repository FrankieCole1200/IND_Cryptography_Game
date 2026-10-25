#include "challenger.h"

#include <string>
using std::string;

#include <random>
 
// This function encrypts a random message out of the 2 given too us (m0 or m1)
string Challenger::encrypt_random_message(const string& m0, const string& m1) {
    static std::mt19937 gen(std::random_device{}()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(0, 1);
    int choice = distrib(gen); // uniform choice between 0 and 1

    string c;
    // encrypt message corresponding to challengers choice
    if (choice == 0) {
        c = cipher.encrypt(m0);
        random_message_choice = 0;
    } else {
        c = cipher.encrypt(m1);
        random_message_choice = 1;
    }

    return c;
}

// This function checks if a guess is the same as the random choice challenger made.
int Challenger::check_bit(int adversary_guess) {
    return (adversary_guess == random_message_choice); // returns 1 if true
}