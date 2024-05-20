#include "../include/BigInt.hpp"
#include "../include/polaris_dev.h"

#define COM_ADD "+"
#define COM_SUB "-"
#define COM_MUL "*"
#define COM_DIV "/"
#define COM_MOD "%"
#define COM_ABS "abs"
#define COM_POW10 "10^"
#define COM_GCD "gcd"
#define COM_LCM "lcm"
#define COM_POW "^"
#define COM_SQRT "intsqrt"
#define COM_RND "randint"
#define COM_LE "<="
#define COM_LT "<"
#define COM_GE "?>="
#define COM_GT "?>"

// Comand: +
void com_add_handler(size_t interpreter_id)
{
    char *operand2 = polaris_pop_value_from_intr(interpreter_id, COM_ADD);
    char *operand1 = polaris_pop_value_from_intr(interpreter_id, COM_ADD);
    BigInt bigOperand1 = std::string(operand1);
    BigInt bigOperand2 = std::string(operand2);
    polaris_push_value_to_intr(interpreter_id, (bigOperand1 + bigOperand2).to_string().c_str());
    free(operand1);
    free(operand2);
}

// Comand: -
void com_sub_handler(size_t interpreter_id)
{
    char *operand2 = polaris_pop_value_from_intr(interpreter_id, COM_SUB);
    char *operand1 = polaris_pop_value_from_intr(interpreter_id, COM_SUB);
    BigInt bigOperand1 = std::string(operand1);
    BigInt bigOperand2 = std::string(operand2);
    polaris_push_value_to_intr(interpreter_id, (bigOperand1 - bigOperand2).to_string().c_str());
    free(operand1);
    free(operand2);
}

// Comand: *
void com_mul_handler(size_t interpreter_id)
{
    char *operand2 = polaris_pop_value_from_intr(interpreter_id, COM_MUL);
    char *operand1 = polaris_pop_value_from_intr(interpreter_id, COM_MUL);
    BigInt bigOperand1 = std::string(operand1);
    BigInt bigOperand2 = std::string(operand2);
    polaris_push_value_to_intr(interpreter_id, (bigOperand1 * bigOperand2).to_string().c_str());
    free(operand1);
    free(operand2);
}

// Comand: /
void com_div_handler(size_t interpreter_id)
{
    char *operand2 = polaris_pop_value_from_intr(interpreter_id, COM_DIV);
    char *operand1 = polaris_pop_value_from_intr(interpreter_id, COM_DIV);
    BigInt bigOperand1 = std::string(operand1);
    BigInt bigOperand2 = std::string(operand2);
    polaris_push_value_to_intr(interpreter_id, (bigOperand1 / bigOperand2).to_string().c_str());
    free(operand1);
    free(operand2);
}

// Comand: %
void com_mod_handler(size_t interpreter_id)
{
    char *operand2 = polaris_pop_value_from_intr(interpreter_id, COM_MOD);
    char *operand1 = polaris_pop_value_from_intr(interpreter_id, COM_MOD);
    BigInt bigOperand1 = std::string(operand1);
    BigInt bigOperand2 = std::string(operand2);
    polaris_push_value_to_intr(interpreter_id, (bigOperand1 % bigOperand2).to_string().c_str());
    free(operand1);
    free(operand2);
}

// Comand: abs
void com_abs_handler(size_t interpreter_id)
{
    char *operand = polaris_pop_value_from_intr(interpreter_id, COM_ABS);
    polaris_push_value_to_intr(interpreter_id, abs(std::string(operand)).to_string().c_str());
    free(operand);
}

// Comand: pow^
void com_pow10_handler(size_t interpreter_id)
{
    char *operand = polaris_pop_value_from_intr(interpreter_id, COM_POW10);
    long exp = stol(std::string(operand));
    polaris_push_value_to_intr(interpreter_id, big_pow10(exp).to_string().c_str());
    free(operand);
}

// Comand: gcd
void com_gcd_handler(size_t interpreter_id)
{
    char *operand2 = polaris_pop_value_from_intr(interpreter_id, COM_GCD);
    char *operand1 = polaris_pop_value_from_intr(interpreter_id, COM_GCD);
    BigInt bigOperand1 = std::string(operand1);
    BigInt bigOperand2 = std::string(operand2);
    polaris_push_value_to_intr(interpreter_id, gcd(bigOperand1, bigOperand2).to_string().c_str());
    free(operand1);
    free(operand2);
}

// Comand: lcm
void com_lcm_handler(size_t interpreter_id)
{
    char *operand2 = polaris_pop_value_from_intr(interpreter_id, COM_LCM);
    char *operand1 = polaris_pop_value_from_intr(interpreter_id, COM_LCM);
    BigInt bigOperand1 = std::string(operand1);
    BigInt bigOperand2 = std::string(operand2);
    polaris_push_value_to_intr(interpreter_id, lcm(bigOperand1, bigOperand2).to_string().c_str());
    free(operand1);
    free(operand2);
}

// Comand: ^
void com_pow_handler(size_t interpreter_id)
{
    char *operand2 = polaris_pop_value_from_intr(interpreter_id, COM_POW);
    char *operand1 = polaris_pop_value_from_intr(interpreter_id, COM_POW);
    BigInt bigOperand1 = std::string(operand1);
    long bigOperand2 = stol(std::string(operand2));
    polaris_push_value_to_intr(interpreter_id, pow(bigOperand1, bigOperand2).to_string().c_str());
    free(operand1);
    free(operand2);
}

// Comand: intsqrt
void com_intsqrt_handler(size_t interpreter_id)
{
    char *operand = polaris_pop_value_from_intr(interpreter_id, COM_SQRT);
    polaris_push_value_to_intr(interpreter_id, sqrt(std::string(operand)).to_string().c_str());
    free(operand);
}

// Comand: randint
void com_randint_handler(size_t interpreter_id)
{
    char *digitcount = polaris_pop_value_from_intr(interpreter_id, COM_POW);
    int digitcountval = stoi(std::string(digitcount));
    polaris_push_value_to_intr(interpreter_id, big_random(digitcountval).to_string().c_str());
    free(digitcount);
}

// Comand: <=
void com_le_handler(size_t interpreter_id)
{
    char *operand2 = polaris_pop_value_from_intr(interpreter_id, COM_LE);
    char *operand1 = polaris_pop_value_from_intr(interpreter_id, COM_LE);
    BigInt bigOperand1 = std::string(operand1);
    BigInt bigOperand2 = std::string(operand2);
    polaris_push_value_to_intr(interpreter_id, bigOperand1 <= bigOperand2 ? "1" : "0");
    free(operand1);
    free(operand2);
}

// Comand: <
void com_lt_handler(size_t interpreter_id)
{
    char *operand2 = polaris_pop_value_from_intr(interpreter_id, COM_LT);
    char *operand1 = polaris_pop_value_from_intr(interpreter_id, COM_LT);
    BigInt bigOperand1 = std::string(operand1);
    BigInt bigOperand2 = std::string(operand2);
    polaris_push_value_to_intr(interpreter_id, bigOperand1 < bigOperand2 ? "1" : "0");
    free(operand1);
    free(operand2);
}

// Comand: >=
void com_ge_handler(size_t interpreter_id)
{
    char *operand2 = polaris_pop_value_from_intr(interpreter_id, COM_GE);
    char *operand1 = polaris_pop_value_from_intr(interpreter_id, COM_GE);
    BigInt bigOperand1 = std::string(operand1);
    BigInt bigOperand2 = std::string(operand2);
    polaris_push_value_to_intr(interpreter_id, bigOperand1 >= bigOperand2 ? "1" : "0");
    free(operand1);
    free(operand2);
}

// Comand: >
void com_gt_handler(size_t interpreter_id)
{
    char *operand2 = polaris_pop_value_from_intr(interpreter_id, COM_GT);
    char *operand1 = polaris_pop_value_from_intr(interpreter_id, COM_GT);
    BigInt bigOperand1 = std::string(operand1);
    BigInt bigOperand2 = std::string(operand2);
    polaris_push_value_to_intr(interpreter_id, bigOperand1 > bigOperand2 ? "1" : "0");
    free(operand1);
    free(operand2);
}

// --- Polaris Extension Entrypoint ---
extern "C" void polaris_ext_entrypoint(size_t interpreter_id, POLARIS_EP_ARGS)
{
    // --- Setup ---
    polaris_ext_setup(POLARIS_EXTSETUP_PARS);

    // --- Link words to handlers ---
    polaris_link_handler(interpreter_id, COM_ADD, com_add_handler);
    polaris_link_handler(interpreter_id, COM_SUB, com_sub_handler);
    polaris_link_handler(interpreter_id, COM_MUL, com_mul_handler);
    polaris_link_handler(interpreter_id, COM_DIV, com_div_handler);
    polaris_link_handler(interpreter_id, COM_MOD, com_mod_handler);
    polaris_link_handler(interpreter_id, COM_ABS, com_abs_handler);
    polaris_link_handler(interpreter_id, COM_POW10, com_pow10_handler);
    polaris_link_handler(interpreter_id, COM_GCD, com_gcd_handler);
    polaris_link_handler(interpreter_id, COM_LCM, com_lcm_handler);
    polaris_link_handler(interpreter_id, COM_POW, com_pow_handler);
    polaris_link_handler(interpreter_id, COM_SQRT, com_intsqrt_handler);
    polaris_link_handler(interpreter_id, COM_RND, com_randint_handler);
    polaris_link_handler(interpreter_id, COM_LE, com_le_handler);
    polaris_link_handler(interpreter_id, COM_LT, com_lt_handler);
    polaris_link_handler(interpreter_id, COM_GE, com_ge_handler);
    polaris_link_handler(interpreter_id, COM_GT, com_gt_handler);
}