#include "polaris.hpp"

size_t interpreter_counter = 0;
std::map<size_t, PolarisInterpreter> interpreters;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    else if (argc >= 2 && std::string(argv[1]) == "-v")
    {
        std::cout << std::endl;
        std::cout << " Pure, Minimal..." << std::endl;
        std::cout << " This is Polaris Twist version " << POLARIS_VERSION << "!" << std::endl;
        std::cout << std::endl;
        std::cout << " Copyright (c) Lartu (www.lartu.net), 2020-2024." << std::endl;
        std::cout << " Polaris Twist may be copied only under the terms of the Apache License" << std::endl;
        std::cout << " Version 2.0, which can be found in the Polaris Twist repository." << std::endl;
        std::cout << std::endl;
        std::cout << " This interpreter was compiled on " << COMPILEDATE << " at " << COMPILEHOUR << "." << std::endl;
        std::cout << std::endl;
        return 0;
    }

    else
    {
        size_t intr_id = new_interpreter();
        PolarisInterpreter *intr = get_interpreter_by_id(intr_id);
        register_default_commands(*intr);
        intr->run_code(intr->load_source_file(argv[1]));
    }

    return 0;
}

size_t get_new_interpreter_id()
{
    size_t new_intr_id = interpreter_counter;
    interpreter_counter += 1;
    return new_intr_id;
}

size_t new_interpreter()
{
    size_t new_intr_id = get_new_interpreter_id();
    PolarisInterpreter new_intr = PolarisInterpreter(new_intr_id);
    interpreters.insert(std::make_pair(new_intr_id, new_intr));
    return new_intr_id;
}

extern "C" size_t new_child_interpreter(size_t parent_intr_id)
{
    size_t new_intr_id = get_new_interpreter_id();
    PolarisInterpreter &parent_intr = *get_interpreter_by_id(parent_intr_id);
    PolarisInterpreter new_intr = PolarisInterpreter(new_intr_id, parent_intr.variables, parent_intr.command_words);
    interpreters.insert(std::make_pair(new_intr_id, new_intr));
    return new_intr_id;
}

extern "C" void run_code_in_interpreter(size_t intr_id, const char *code)
{
    get_interpreter_by_id(intr_id)->run_code(code);
}

extern "C" char *pop_value_from_interpreter(size_t intr_id, const char *word)
{
    char *popped_value = strdup(get_interpreter_by_id(intr_id)->pop_value(word).c_str());
    return popped_value;
}

extern "C" void push_value_to_interpreter(size_t intr_id, const char *value)
{
    get_interpreter_by_id(intr_id)->push_value(value);
}

extern "C" size_t get_interpreter_stack_size(size_t intr_id)
{
    return get_interpreter_by_id(intr_id)->execution_stack.size();
}

PolarisInterpreter *get_interpreter_by_id(size_t intr_id)
{
    std::map<size_t, PolarisInterpreter>::iterator it = interpreters.find(intr_id);
    if (it != interpreters.end())
    {
        return &(it->second);
    }
    return nullptr;
}

extern "C" void link_command_for_interpreter(size_t intr_id, const char *word, PolarisHandler handler)
{
    get_interpreter_by_id(intr_id)->link_command_word(word, handler);
}