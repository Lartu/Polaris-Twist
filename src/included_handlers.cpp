#include "included_handlers.hpp"

/*
These included handlers cheat a bit because they can access the Polaris
Interpreter class. Other libraries implemented outside this scope will
have to make do with the exposed Polaris ABI functions.
*/

void register_default_commands(PolarisInterpreter &interpreter)
{
    interpreter.link_command_word(ERROR_COM, com_error_handler);
    interpreter.link_command_word(SET_COM, com_set_handler);
    interpreter.link_command_word(GET_COM, com_get_handler);
    interpreter.link_command_word(VAREX_COM, com_varex_handler);
    interpreter.link_command_word(PRINT_COM, com_print_handler);
    interpreter.link_command_word(FPRINT_COM, com_fprint_handler);
    interpreter.link_command_word(STACK_COM, com_stack_handler);
    interpreter.link_command_word(EVAL_COM, com_eval_handler);
    interpreter.link_command_word(JOIN_COM, com_join_handler);
    interpreter.link_command_word(FJOIN_COM, com_fjoin_handler);
    interpreter.link_command_word(COPY_COM, com_copy_handler);
    interpreter.link_command_word(DEL_COM, com_del_handler);
    interpreter.link_command_word(SWAP_COM, com_swap_handler);
    interpreter.link_command_word(INPUT_COM, com_input_handler);
    interpreter.link_command_word(IF_COM, com_if_handler);
    interpreter.link_command_word(WHILE_COM, com_while_handler);
    interpreter.link_command_word(EQ_COM, com_eq_handler);
    interpreter.link_command_word(NEQ_COM, com_neq_handler);
    interpreter.link_command_word(NOT_COM, com_not_handler);
    interpreter.link_command_word(AND_COM, com_and_handler);
    interpreter.link_command_word(OR_COM, com_or_handler);
    interpreter.link_command_word(LOAD_COM, com_load_handler);
    interpreter.link_command_word(VERSION_COM, com_version_handler);
    interpreter.link_command_word(LEN_COM, com_len_handler);
}

// Command: error
void com_error_handler(size_t interpreter_id)
{
    PolarisInterpreter *intr = get_interpreter_by_id(interpreter_id);
    intr->throw_error(intr->pop_value(ERROR_COM));
}

// Command: set
void com_set_handler(size_t interpreter_id)
{
    PolarisInterpreter *intr = get_interpreter_by_id(interpreter_id);
    std::string var_name = intr->pop_value(SET_COM);
    std::string value = intr->pop_value(SET_COM);
    intr->set_variable(var_name, value);
}

// Command: get
void com_get_handler(size_t interpreter_id)
{
    PolarisInterpreter *intr = get_interpreter_by_id(interpreter_id);
    std::string var_name = intr->pop_value(GET_COM);
    intr->push_value(intr->get_variable(var_name));
}

// Command: varex
void com_varex_handler(size_t interpreter_id)
{
    PolarisInterpreter *intr = get_interpreter_by_id(interpreter_id);
    std::string var_name = intr->pop_value(VAREX_COM);
    intr->push_value(intr->variables.count(var_name) > 0 ? "1" : "0");
}

// Command: print
void com_print_handler(size_t interpreter_id)
{
    PolarisInterpreter *intr = get_interpreter_by_id(interpreter_id);
    std::cout << intr->pop_value(PRINT_COM) << std::endl;
}

// Command: fprint
void com_fprint_handler(size_t interpreter_id)
{
    PolarisInterpreter *intr = get_interpreter_by_id(interpreter_id);
    std::string res = "";
    while (intr->execution_stack.size() > 0)
    {
        res = intr->pop_value(FPRINT_COM) + res;
    }
    std::cout << res << std::endl;
}

// Command: stack
void com_stack_handler(size_t interpreter_id)
{
    get_interpreter_by_id(interpreter_id)->print_stack();
}

// Command: eval
void com_eval_handler(size_t interpreter_id)
{
    char *code = pop_value_from_interpreter(interpreter_id, EVAL_COM);
    get_interpreter_by_id(interpreter_id)->run_code(code);
    free(code);
}

// Command: join
void com_join_handler(size_t interpreter_id)
{
    PolarisInterpreter *intr = get_interpreter_by_id(interpreter_id);
    std::string b = intr->pop_value(JOIN_COM);
    std::string a = intr->pop_value(JOIN_COM);
    intr->push_value(a + b);
}

// Command: fjoin
void com_fjoin_handler(size_t interpreter_id)
{
    PolarisInterpreter *intr = get_interpreter_by_id(interpreter_id);
    std::string res = "";
    while (intr->execution_stack.size() > 0)
    {
        res = intr->pop_value(FJOIN_COM) + res;
    }
    intr->push_value(res);
}

// Command: copy
void com_copy_handler(size_t interpreter_id)
{
    PolarisInterpreter *intr = get_interpreter_by_id(interpreter_id);
    std::string a = intr->pop_value(COPY_COM);
    intr->push_value(a);
    intr->push_value(a);
}

// Command: del
void com_del_handler(size_t interpreter_id)
{
    get_interpreter_by_id(interpreter_id)->pop_value(DEL_COM);
}

// Command: swap
void com_swap_handler(size_t interpreter_id)
{
    PolarisInterpreter *intr = get_interpreter_by_id(interpreter_id);
    std::string a = intr->pop_value(SWAP_COM);
    std::string b = intr->pop_value(SWAP_COM);
    intr->push_value(a);
    intr->push_value(b);
}

// Command: input
void com_input_handler(size_t interpreter_id)
{
    std::string input;
    std::cin >> input;
    push_value_to_interpreter(interpreter_id, input.c_str());
}

// Command: if
void com_if_handler(size_t interpreter_id)
{
    PolarisInterpreter *intr = get_interpreter_by_id(interpreter_id);
    std::string c = intr->pop_value(IF_COM);
    std::string b = intr->pop_value(IF_COM);
    std::string a = intr->pop_value(IF_COM);
    intr->run_code(a);
    std::string d = intr->pop_value(IF_COM);
    if (d != "0")
    {
        intr->run_code(b);
    }
    else
    {
        intr->run_code(c);
    }
}

// Command: while
void com_while_handler(size_t interpreter_id)
{
    PolarisInterpreter *intr = get_interpreter_by_id(interpreter_id);
    std::string b = intr->pop_value(WHILE_COM);
    std::string a = intr->pop_value(WHILE_COM);
execute_check:
    intr->run_code(a);
    std::string c = intr->pop_value(WHILE_COM);
    if (c != "0")
    {
        intr->run_code(b);
        if (!intr->execution_halted)
        {
            goto execute_check;
        }
    }
}

// Command: =
void com_eq_handler(size_t interpreter_id)
{
    PolarisInterpreter *intr = get_interpreter_by_id(interpreter_id);
    std::string b = intr->pop_value(EQ_COM);
    std::string a = intr->pop_value(EQ_COM);
    intr->push_value(a == b ? "1" : "0");
}

// Command: !=
void com_neq_handler(size_t interpreter_id)
{
    PolarisInterpreter *intr = get_interpreter_by_id(interpreter_id);
    std::string b = intr->pop_value(NEQ_COM);
    std::string a = intr->pop_value(NEQ_COM);
    intr->push_value(a == b ? "0" : "1");
}

// Command: !
void com_not_handler(size_t interpreter_id)
{
    PolarisInterpreter *intr = get_interpreter_by_id(interpreter_id);
    std::string a = intr->pop_value(NOT_COM);
    intr->push_value(a != "0" ? "0" : "1");
}

// Command: &
void com_and_handler(size_t interpreter_id)
{
    PolarisInterpreter *intr = get_interpreter_by_id(interpreter_id);
    std::string a = intr->pop_value(AND_COM);
    std::string b = intr->pop_value(AND_COM);
    intr->push_value(a != "0" && b != "0" ? "1" : "0");
}

// Command: |
void com_or_handler(size_t interpreter_id)
{
    PolarisInterpreter *intr = get_interpreter_by_id(interpreter_id);
    std::string a = intr->pop_value(OR_COM);
    std::string b = intr->pop_value(OR_COM);
    intr->push_value(a != "0" || b != "0" ? "1" : "0");
}

// Command: load
void com_load_handler(size_t interpreter_id)
{
    PolarisInterpreter *intr = get_interpreter_by_id(interpreter_id);
    std::string lib_name = intr->pop_value(LOAD_COM) + ".plib";
    void *handle = dlopen(lib_name.c_str(), RTLD_LAZY);
    if (!handle)
    {
        intr->throw_error("Cannot link library: " + lib_name);
        return;
    }

    // Load the symbol
    dlerror(); // Reset errors
    PolarisExtEntrypoint call_link_handlers = (PolarisExtEntrypoint)dlsym(handle, "polaris_ext_entrypoint");
    const char *dlsym_error = dlerror();
    if (dlsym_error)
    {
        dlclose(handle);
        intr->throw_error("Cannot load symbol 'polaris_ext_entrypoint': " + (std::string)dlsym_error);
        return;
    }

    call_link_handlers(interpreter_id,
                       link_command_for_interpreter,
                       new_child_interpreter,
                       run_code_in_interpreter, push_value_to_interpreter,
                       pop_value_from_interpreter,
                       get_interpreter_stack_size);
}

// Command: polaris_version
void com_version_handler(size_t interpreter_id)
{
    PolarisInterpreter *intr = get_interpreter_by_id(interpreter_id);
    intr->push_value(POLARIS_VERSION);
}

// Command: len
void com_len_handler(size_t interpreter_id)
{
    PolarisInterpreter *intr = get_interpreter_by_id(interpreter_id);
    std::string a = intr->pop_value(LEN_COM);
    intr->push_value(number_to_string(a.length()));
}