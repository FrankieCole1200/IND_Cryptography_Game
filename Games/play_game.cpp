#include "adversary.h"
#include "challenger.h"
#include "caesar.h"
#include "monoalphabetic.h"
#include "ind_eav.h"

#include <iostream>
using std::cout;

int play_multiple(int amount, IND_EAV& game) {
    int success = 0; // How many games adversary won

    for (int i=0; i<amount; i++) {
        success += game.play();
    }

    return success;
}

int main() {
    Caesar caesar;
    Monoalphabetic monoalphabetic;

    Cipher& scheme = monoalphabetic; // Change to monoalphabetic to select that cipher.

    Adversary adversary; // Adversary communicates with challenger
    Challenger challenger(scheme); // challenger communicates with SKE scheme

    IND_EAV ind_eav(adversary, challenger); // The game to play

    int amount = 1000;
    int result = play_multiple(amount, ind_eav);
    float percent = ((float)result / amount) * 100;

    cout << "Adversary played " << amount << " against " << scheme.name << "\n";
    cout << "Adversary won " << percent << "% of games (" << result << "/" << amount << ").";
}
