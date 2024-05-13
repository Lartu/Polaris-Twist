#include "polaris_dev.h"
#include <chrono>
#include <thread>

// Comand: wait
void com_sleep_handler(size_t interpreter_id)
{
    char * value = polaris_pop_value_from_intr(interpreter_id, "sleep");
    long milliseconds = stol(std::string(value));
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    free(value);
}

// --- Polaris Extension Entrypoint ---
extern "C" void polaris_ext_entrypoint(size_t interpreter_id, POLARIS_EP_ARGS)
{
    // --- Setup ---
    polaris_ext_setup(POLARIS_EXTSETUP_PARS);

    // --- Link words to handlers ---
    polaris_link_handler(interpreter_id, "sleep", com_sleep_handler);
}