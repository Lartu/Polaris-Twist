#ifndef POLARIS_HANDLERS
#define POLARIS_HANDLERS
#include "polaris.hpp"
#include <iostream>

// Register Function
void register_default_commands(PolarisInterpreter &interpreter);

// Words
#define ERROR_COM "error"
#define SET_COM "set"
#define GET_COM "get"
#define PRINT_COM "print"
#define FPRINT_COM "fprint"
#define STACK_COM "stack"
#define EVAL_COM "eval"
#define JOIN_COM "join"
#define FJOIN_COM "fjoin"
#define COPY_COM "copy"
#define DEL_COM "del"
#define SWAP_COM "swap"
#define INPUT_COM "input"
#define IF_COM "if"
#define WHILE_COM "while"
#define EQ_COM "="
#define NEQ_COM "!="
#define NOT_COM "!"
#define AND_COM "&"
#define OR_COM "|"
#define LOAD_COM "load"

// Handlers
void com_error_handler(size_t interpreter_id);
void com_set_handler(size_t interpreter_id);
void com_get_handler(size_t interpreter_id);
void com_print_handler(size_t interpreter_id);
void com_fprint_handler(size_t interpreter_id);
void com_stack_handler(size_t interpreter_id);
void com_eval_handler(size_t interpreter_id);
void com_join_handler(size_t interpreter_id);
void com_fjoin_handler(size_t interpreter_id);
void com_copy_handler(size_t interpreter_id);
void com_del_handler(size_t interpreter_id);
void com_swap_handler(size_t interpreter_id);
void com_input_handler(size_t interpreter_id);
void com_if_handler(size_t interpreter_id);
void com_while_handler(size_t interpreter_id);
void com_eq_handler(size_t interpreter_id);
void com_neq_handler(size_t interpreter_id);
void com_not_handler(size_t interpreter_id);
void com_and_handler(size_t interpreter_id);
void com_or_handler(size_t interpreter_id);
void com_load_handler(size_t interpreter_id);
#endif

/*double PolarisInterpreter::string_to_number(const std::string &value) const
{
    return stod(value);
}

bool PolarisInterpreter::string_is_number(const std::string &value) const
{
    std::istringstream iss(value);
    double d;
    char c;
    return iss >> d && !(iss >> c);
}*/