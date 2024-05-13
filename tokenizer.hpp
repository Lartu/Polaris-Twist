#ifndef POLARIS_TOKENIZER
#define POLARIS_TOKENIZER
#include "polaris_interpreter.hpp"
#include <ctype.h>
#include <iostream>

void add_word(std::string &word, StringType type, std::vector<PolarisWord> *word_list);
std::pair<bool, std::vector<PolarisWord> *> parsing_error(PolarisInterpreter &intr, const std::string &message, std::vector<PolarisWord> *word_list);
std::pair<bool, std::vector<PolarisWord> *> split_words(PolarisInterpreter &intr, const std::string &code);
std::string number_to_string(double value);
#endif