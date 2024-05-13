#include "polaris_dev.h"

// Comand: pito (pushea un pito al stack)
void com_pito_handler(size_t interpreter_id)
{
    polaris_push_value_to_intr(interpreter_id, "<===3");
}

// --- Polaris Extension Entrypoint ---
extern "C" void polaris_ext_entrypoint(size_t interpreter_id, POLARIS_EP_ARGS)
{
    // --- Setup ---
    polaris_ext_setup(POLARIS_EXTSETUP_PARS);

    // --- Link words to handlers ---
    polaris_link_handler(interpreter_id, "pito", com_pito_handler);
}