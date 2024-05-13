#ifndef POLARIS_DEV_TYPES
#define POLARIS_DEV_TYPES
#include <stddef.h>

// These are all the arguments for both the entrypoint and setup functions
#define POLARIS_EP_ARGS PolarisLinkHandler _polaris_link_handler, PolarisNewChildInterpreter _polaris_launch_child_intr, PolarisRunCodeInInterpreter _polaris_run_code_in_intr, PolarisPushValueToInterpreter _polaris_push_value_to_intr, PolarisPopValueFromInterpreter _polaris_pop_value_from_intr, PolarisGetInterpreterStackSize _polaris_get_intr_stack_size
#define POLARIS_EXTSETUP_PARS _polaris_link_handler, _polaris_launch_child_intr, _polaris_run_code_in_intr, _polaris_push_value_to_intr, _polaris_pop_value_from_intr, _polaris_get_intr_stack_size

// Function pointer type definitions
extern "C"
{
    // This is the signature of a handler function
    typedef void (*PolarisHandler)(size_t intr_id);

    // This is the function passed to an extension so it can link its handlers to words
    typedef void (*PolarisLinkHandler)(size_t intr_id, const char *word, PolarisHandler handler);

    // This is the function passed to an extension so it can launch a new
    // child Polaris interpreter
    typedef size_t (*PolarisNewChildInterpreter)(size_t parent_intr_id);

    // This is the function passed to an extension so it can run code in a Polaris interpreter
    typedef void (*PolarisRunCodeInInterpreter)(size_t intr_id, const char *code);

    // This is the function passed to an extension so it can push a value in a Polaris interpreter
    typedef void (*PolarisPushValueToInterpreter)(size_t intr_id, const char *value);

    // This is the function passed to an extension so it can pop a value from a Polaris interpreter
    typedef char *(*PolarisPopValueFromInterpreter)(size_t intr_id, const char *word);

    // This is the function passed to an extension so it read the size of the stack of
    // a Polaris Interpreter
    typedef size_t (*PolarisGetInterpreterStackSize)(size_t intr_id);

    // Function type of the entrypoint
    typedef void (*PolarisExtEntrypoint)(size_t interpreter_id, POLARIS_EP_ARGS);
}
#endif