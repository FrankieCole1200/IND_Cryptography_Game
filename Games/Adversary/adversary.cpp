#include "adversary.h"

#include <string>
using std::string;

#include <utility>
using std::pair;

#include <random>

// choose a random message from a message space (english language)
pair<string, string> Adversary::choose_messages() {
    string m0 = "Hello";
    string m1 = "World";

    return {m0, m1};
}

// a funcition that tries to guess which message was encrypted.
int Adversary::guess_message(const string& c) {
    //return random_guess();
    return frequency_analysis_v1(c);
}

int Adversary::random_guess() {
    static std::mt19937 gen(std::random_device{}()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(0, 1);
    int choice = distrib(gen); // uniform choice between 0 and 1

    return choice;
}

// In this version, since string m0 contains 2 l's side-by-side, 
// I will check if the ciphertext contains 2 identical letters side-by-side
int Adversary::frequency_analysis_v1(const string& c) {
    char prev = ' ';
    for (char l: c) {
        if (l == prev) {
            return 0; // guess that m0 was encrypted
        }
        prev = l;
    }
    return 1; // if there where no identical letters side-by-side it must be m1
}