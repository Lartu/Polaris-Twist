#include <fstream>
#include <iostream>
#include <sstream>

#include "polaris_interpreter.hpp"
#include "tokenizer.hpp"

PolarisWord::PolarisWord(std::string word, StringType type)
{
    this->_word = word;
    this->_type = type;
}

const std::string &PolarisWord::get_word() const
{
    return this->_word;
}

StringType PolarisWord::get_type() const
{
    return this->_type;
}

PolarisInterpreter::PolarisInterpreter(size_t id)
{
    this->self_intr_id = id;
    this->execution_halted = false;
}

PolarisInterpreter::PolarisInterpreter(size_t id, const std::map<std::string, std::string> &parent_variables, const std::map<std::string, PolarisHandler> &parent_commands)
{
    this->self_intr_id = id;
    this->variables = parent_variables;
    this->command_words = parent_commands;
    this->execution_halted = false;
}

void PolarisInterpreter::throw_error(const std::string &message)
{
    std::cout << std::endl;
    std::cout << "--- Polaris Error ---" << std::endl;
    std::cout << message << std::endl;
    if (this->code_words.size() > 0)
    {
        std::cout << "When executing word: ";
        std::cout << (*this->code_words.top())[this->program_counters.top()].get_word();
        std::cout << std::endl;
        std::cout << "In context:" << std::endl;
        size_t spaces = 0;
        for (long i = this->program_counters.top() - 5; i <= this->program_counters.top() + 5; ++i)
        {
            if (i < 0)
                continue;
            else if (i >= (*this->code_words.top()).size())
                break;
            if (i < this->program_counters.top())
            {
                spaces += (*this->code_words.top())[i].get_word().length() + 1;
            }
            std::cout << (*this->code_words.top())[i].get_word() << " ";
        }
        std::cout << std::endl;
        for (size_t i = 0; i < spaces; ++i)
        {
            std::cout << " ";
        }
        const size_t word_length = (*this->code_words.top())[this->program_counters.top()].get_word().length();
        for (size_t i = 0; i < word_length; ++i)
        {
            std::cout << "^";
        }
        std::cout << std::endl;
    }
    std::cout << "Stack at moment of failure:" << std::endl;
    this->print_stack();
    this->halt_execution();
}

void PolarisInterpreter::halt_execution()
{
    this->execution_halted = true;
    std::cout << "Interpreter execution halted." << std::endl;
}

void PolarisInterpreter::push_value(const std::string &value)
{
    this->execution_stack.emplace_back(value);
}

std::string PolarisInterpreter::pop_value(const std::string &word)
{
    if (this->execution_stack.empty())
    {
        this->throw_error("Empty stack pop when executing word: " + word);
        return "";
    }
    else
    {
        const std::string value = this->execution_stack.back();
        this->execution_stack.pop_back();
        return value;
    }
}

void PolarisInterpreter::print_stack() const
{
    if (this->execution_stack.empty())
    {
        std::cout << "(the stack is empty)" << std::endl;
    }
    else
    {
        std::cout << "(top): ";
        for (long i = this->execution_stack.size() - 1; i >= 0; --i)
        {
            std::cout << this->execution_stack[i];
            if (i > 0)
            {
                std::cout << ", ";
            }
            else
            {
                std::cout << std::endl;
            }
        }
    }
}

bool PolarisInterpreter::is_command_word(const std::string &word) const
{
    return this->command_words.count(word) > 0;
}

void PolarisInterpreter::execute_command_word(const std::string &word)
{
    this->command_words[word](this->self_intr_id);
}

void PolarisInterpreter::set_variable(const std::string &var_name, const std::string &value)
{
    this->variables[var_name] = value;
}

std::string PolarisInterpreter::get_variable(const std::string &var_name)
{
    if (this->variables.count(var_name) > 0)
    {
        return this->variables[var_name];
    }
    else
    {
        this->throw_error("Variable " + var_name + " not found in this context.");
        return "";
    }
}

void PolarisInterpreter::run_code(const std::string &code)
{
    if(this->execution_halted){
        return;
    }
    std::pair<bool, std::vector<PolarisWord> *> tokenized_words = split_words(*this, code);
    if (tokenized_words.first) // No errors during tokenization
    {
        this->code_words.push(tokenized_words.second);
        this->program_counters.push(0);
        while (this->program_counters.top() < (*this->code_words.top()).size() && !this->execution_halted)
        {
            const PolarisWord &word = (*this->code_words.top())[this->program_counters.top()];
            if (word.get_type() == sWORD)
            {
                if (this->is_command_word(word.get_word()))
                {
                    this->execute_command_word(word.get_word());
                }
                else
                {
                    this->push_value(word.get_word());
                }
            }
            else
            {
                this->push_value(word.get_word());
            }
            this->program_counters.top()++;
        }
        this->program_counters.pop();
        delete this->code_words.top();
        this->code_words.pop();
    }
}

std::string PolarisInterpreter::load_source_file(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        this->throw_error("Could not open source file '" + filename + "'.");
        return "";
    }
    else
    {
        std::string line;
        std::string source = "";
        while (std::getline(file, line))
        {
            source += line + "\n";
        }
        file.close();
        return source;
    }
}

void PolarisInterpreter::link_command_word(const std::string &word, PolarisHandler handler)
{
    this->command_words[word] = handler;
}
