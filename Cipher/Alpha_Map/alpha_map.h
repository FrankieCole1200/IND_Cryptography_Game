#ifndef ALPHA_MAP_H
#define ALPHA_MAP_H

#include <vector>
using std::vector;

#include <map>
using std::map;

int get_num(char c);
char get_char(int n);
int get_key_space_size();
vector<char> get_message_space();
map<char, int> get_alpha_to_num();
map<int, char> get_num_to_alpha();

#endif
