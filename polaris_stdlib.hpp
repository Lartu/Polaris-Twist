#include "polaris_definitions.hpp"
#include <iostream>

extern "C" void link_polaris_handlers(PolarisInterpreter &intr);
void com_stack_handler(PolarisInterpreter &intr, const std::string &word);
