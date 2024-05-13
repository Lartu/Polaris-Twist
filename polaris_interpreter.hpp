#ifndef POLARIS_INTR
#define POLARIS_INTR

#include <stack>
#include <vector>
#include <string>
#include <map>
#include "polaris_dev_types.h"

#define StringType uint8_t
#define sWORD 1
#define sQUOTED 2
#define sBLOCK 3

class PolarisInterpreter;

class PolarisWord
{
private:
    std::string _word;
    StringType _type;

public:
    PolarisWord(std::string word, StringType type);
    const std::string &get_word() const;
    StringType get_type() const;
};

class PolarisInterpreter
{
public:
    // Properties
    std::vector<std::string> execution_stack;
    std::stack<std::vector<PolarisWord> *> code_words;
    std::map<std::string, std::string> variables;
    std::map<std::string, PolarisHandler> command_words;
    std::stack<size_t> program_counters;
    bool execution_halted;
    size_t self_intr_id;
    // Methods
    PolarisInterpreter(size_t id);
    PolarisInterpreter(size_t id, const std::map<std::string, std::string> & parent_variables, const std::map<std::string, PolarisHandler> & parent_commands);
    void throw_error(const std::string &message);
    void halt_execution();
    void run_code(const std::string &code);
    void push_value(const std::string &value);
    std::string pop_value(const std::string &word);
    void print_stack() const;
    bool is_command_word(const std::string &word) const;
    void execute_command_word(const std::string &word);
    void set_variable(const std::string &var_name, const std::string &value);
    std::string get_variable(const std::string &var_name);
    std::string load_source_file(const std::string &filename);
    void link_command_word(const std::string & word, PolarisHandler handler);
};
#endif
