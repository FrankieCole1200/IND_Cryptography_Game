// A basic encryption algorithm following the Caesar Cipher

#include <iostream>
using std::cout;
using std::cin;

#include <string>
using std::string;

#include "caesar.h"

/*
    A Caesar Cipher is a type of SecretKey Encryption scheme (SKE). It is made up of 3 algorithms:

    Each Caesar object generates and stores its own secret key privately.
    encrypt(message) returns ciphertext; decrypt(ciphertext) recovers the message
    when called on the same object.
*/

// Get a message from the user to encrypt.
string getMessage() {
    string m;

    cout << "Welcome, please enter a message you wish to be encrypted: ";
    getline(cin, m);

    return m;
}

void execute_1() {
    Caesar cipher;

    // message to encrypt 
    string m = getMessage();
    cout << "Message: " << m << "\n";
    
    // encrypt message
    string c = cipher.encrypt(m);
    cout << "Ciphertext: " << c << "\n";

    // decrypt message
    string M = cipher.decrypt(c);
    cout << "Decrypted: " << M << "\n";
}

int main() {

    execute_1();

    return 0;
}
