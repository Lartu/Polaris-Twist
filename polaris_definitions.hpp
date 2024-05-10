#ifndef POLARIS
#define POLARIS

// This is the only Polaris header you should include to write Polaris extensions.

#include <stack>
#include <vector>
#include <string>
#include <map>

#define StringType uint8_t
#define sWORD 1
#define sQUOTED 2
#define sBLOCK 3

class PolarisInterpreter;
typedef void (*PolarisHandler)(PolarisInterpreter &intr, const std::string &word);
typedef void (*LinkPolarisHandlers)(PolarisInterpreter &intr);

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
    // Methods
    PolarisInterpreter();
    PolarisInterpreter(const std::map<std::string, std::string> & parent_variables, const std::map<std::string, PolarisHandler> & parent_commands);
    void throw_error(const std::string &message);
    void halt_execution();
    void run_code(const std::string &code);
    void push_value(const std::string &value);
    std::string pop_value(const std::string &word);
    void print_stack() const;
    bool is_command_word(const std::string &word) const;
    void execute_command_word(const std::string &word);
    double string_to_number(const std::string &value) const;
    bool string_is_number(const std::string &value) const;
    std::string number_to_string(double value) const;
    void set_variable(const std::string &var_name, const std::string &value);
    std::string get_variable(const std::string &var_name);
    std::string load_source_file(const std::string &filename);
    void link_command_word(const std::string & word, PolarisHandler handler);
};
#endif
