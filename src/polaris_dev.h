#ifndef POLARIS_DEV_DEFS
#define POLARIS_DEV_DEFS
#include "polaris_dev_types.h"

// This is the function that polaris will call when loading an extension, so it's the
// entrypoint for your extension. Any preparations should be done here (such as calling
// polaris_ext_setup()).
extern "C" void polaris_ext_entrypoint(size_t interpreter_id, POLARIS_EP_ARGS);

// These are all the functions that get automatically defined when you
// execute polaris_ext_setup
PolarisLinkHandler polaris_link_handler;
PolarisNewChildInterpreter polaris_launch_child_intr;
PolarisRunCodeInInterpreter polaris_run_code_in_intr;
PolarisPushValueToInterpreter polaris_push_value_to_intr;
PolarisPopValueFromInterpreter polaris_pop_value_from_intr;
PolarisGetInterpreterStackSize polaris_get_intr_stack_size;

// This is the function that magically sets up all function pointers for your extension
void polaris_ext_setup(POLARIS_EP_ARGS)
{
    polaris_link_handler = _polaris_link_handler;
    polaris_launch_child_intr = _polaris_launch_child_intr;
    polaris_run_code_in_intr = _polaris_run_code_in_intr;
    polaris_push_value_to_intr = _polaris_push_value_to_intr;
    polaris_pop_value_from_intr = _polaris_pop_value_from_intr;
    polaris_get_intr_stack_size = _polaris_get_intr_stack_size;
}

#endif