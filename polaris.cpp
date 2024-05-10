#include "polaris_definitions.hpp"
#include <iostream>
#include <dlfcn.h>

void load_module_handler(PolarisInterpreter &intr, const std::string &word)
{
    std::string lib_name = intr.pop_value(word) + ".plib";
    void *handle = dlopen(lib_name.c_str(), RTLD_LAZY);
    if (!handle)
    {
        intr.throw_error("Cannot link library: " + lib_name);
        return;
    }

    // Load the symbol
    dlerror(); // Reset errors
    LinkPolarisHandlers call_link_handlers = (LinkPolarisHandlers)dlsym(handle, "link_polaris_handlers");
    const char *dlsym_error = dlerror();
    if (dlsym_error)
    {
        dlclose(handle);
        intr.throw_error("Cannot load symbol 'link_polaris_handlers': " + (std::string)dlsym_error);
        return;
    }
    
    call_link_handlers(intr);
}

void com_stack_handler(PolarisInterpreter &intr, const std::string &word)
{
    intr.print_stack();
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    PolarisInterpreter intr;
    intr.link_command_word("link", load_module_handler);
    intr.run_code("basic link");
    intr.run_code(intr.load_source_file(argv[1]));

    return 0;
}
