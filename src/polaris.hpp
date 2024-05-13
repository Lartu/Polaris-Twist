#ifndef POLARIS_ENVIRONMENT
#define POLARIS_ENVIRONMENT
#include "polaris_interpreter.hpp"
#include "included_handlers.hpp"
#include "polaris_dev_types.h"
#include <iostream>
#include <map>
#include <dlfcn.h>
#include <string.h>

#ifndef POLARIS_VERSION
#define POLARIS_VERSION "Unknown"
#endif

#ifndef COMPILEDATE
#define COMPILEDATE "a date"
#endif

#ifndef COMPILEHOUR
#define COMPILEHOUR "a lovely hour"
#endif

int main(int argc, char *argv[]);
PolarisInterpreter *get_interpreter_by_id(size_t intr_id);
size_t new_interpreter();
size_t get_new_interpreter_id();

// Polaris ABI
extern "C" void link_command_for_interpreter(size_t intr_id, const char *word, PolarisHandler handler);
extern "C" size_t new_child_interpreter(size_t parent_intr_id);
extern "C" void run_code_in_interpreter(size_t intr_id, const char *code);
extern "C" void push_value_to_interpreter(size_t intr_id, const char *value);
extern "C" char *pop_value_from_interpreter(size_t intr_id, const char *word);
extern "C" size_t get_interpreter_stack_size(size_t intr_id);
#endif