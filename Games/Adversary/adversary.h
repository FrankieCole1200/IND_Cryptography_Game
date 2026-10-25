#ifndef ADVERSARY_H
#define ADVERSARY_H

#include <string>

#include <utility>
using std::string;

class Adversary {
    public:
    Adversary() = default;
    
    std::pair<string, string> choose_messages();
    int guess_message(const string& c);

    private:
    int random_guess();
    int frequency_analysis_v1(const string& c);

};

#endif
