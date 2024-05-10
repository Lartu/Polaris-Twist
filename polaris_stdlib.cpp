#include "polaris_stdlib.hpp"

void link_polaris_handlers(PolarisInterpreter &intr)
{
    intr.link_command_word("stack", com_stack_handler);
}

void com_stack_handler(PolarisInterpreter &intr, const std::string &word)
{
    intr.print_stack();
}
