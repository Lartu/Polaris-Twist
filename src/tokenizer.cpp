#include "tokenizer.hpp"

void add_word(std::string &word, StringType type, std::vector<PolarisWord> *word_list)
{
    if (type == sWORD)
    {
        if (word.length() > 0)
        {
            if (word[0] == '>' && word.length() >= 2)
            {
                word = word.substr(1);
                word_list->push_back(PolarisWord(word, sBLOCK));
                word_list->push_back(PolarisWord("set", sWORD));
            }
            else if (word[0] == '@' && word.length() >= 2)
            {
                word = word.substr(1);
                word_list->push_back(PolarisWord(word, sBLOCK));
                word_list->push_back(PolarisWord("get", sWORD));
            }
            else if (word.back() == '%' && word.length() >= 2)
            {
                word = word.substr(0, word.length() - 1);
                word_list->push_back(PolarisWord(word, sBLOCK));
                word_list->push_back(PolarisWord("get", sWORD));
                word_list->push_back(PolarisWord("eval", sWORD));
            }
            else
            {
                word_list->push_back(PolarisWord(word, type));
            }
        }
    }
    else
    {
        word_list->push_back(PolarisWord(word, type));
    }
    word = "";
}

std::pair<bool, std::vector<PolarisWord> *> parsing_error(PolarisInterpreter &intr, const std::string &message, std::vector<PolarisWord> *word_list)
{
    delete word_list;
    intr.throw_error(message);
    return std::pair<bool, std::vector<PolarisWord> *>(false, nullptr);
}

std::pair<bool, std::vector<PolarisWord> *> split_words(PolarisInterpreter &intr, const std::string &code)
{
    std::vector<PolarisWord> *tokens = new std::vector<PolarisWord>();
    std::string current_token = "";
    bool in_string = false;
    size_t block_string_depth = 0;
    size_t comment_depth = 0;
    bool escaping_char = false;
    for (size_t i = 0; i < code.length(); ++i)
    {
        char current_char = code[i];
        if (current_char == '"' && !escaping_char && comment_depth == 0 && !in_string && block_string_depth == 0)
        {
            add_word(current_token, sWORD, tokens);
            in_string = true;
        }
        else if (current_char == '"' && !escaping_char && comment_depth == 0 && in_string && block_string_depth == 0)
        {
            add_word(current_token, sQUOTED, tokens);
            in_string = false;
        }
        else if (current_char == '(' && !escaping_char && comment_depth == 0 && !in_string)
        {
            if (block_string_depth == 0)
            {
                add_word(current_token, sWORD, tokens);
            }
            else
            {
                current_token += current_char;
            }
            ++block_string_depth;
        }
        else if (current_char == ')' && !escaping_char && comment_depth == 0 && !in_string)
        {
            if (block_string_depth == 0)
            {
                return parsing_error(intr, ") found without opening (", tokens);
            }
            else
            {
                --block_string_depth;
                if (block_string_depth == 0)
                {
                    add_word(current_token, sBLOCK, tokens);
                }
                else
                {
                    current_token += current_char;
                }
            }
        }
        else if (current_char == '[' && !escaping_char && !in_string && block_string_depth == 0)
        {
            if (comment_depth == 0)
            {
                add_word(current_token, sWORD, tokens);
            }
            ++comment_depth;
        }
        else if (current_char == ']' && !escaping_char && !in_string && block_string_depth == 0)
        {
            if (comment_depth == 0)
            {
                return parsing_error(intr, "] found without opening [", tokens);
            }
            else
            {
                --comment_depth;
            }
        }
        else if (isspace(current_char) && comment_depth == 0 && !in_string && block_string_depth == 0)
        {
            add_word(current_token, sWORD, tokens);
        }
        else if (comment_depth == 0 && in_string && escaping_char && block_string_depth == 0)
        {
            current_token += current_char;
            escaping_char = false;
        }
        else if (comment_depth == 0 && !escaping_char)
        {
            if (in_string && current_char == '\\')
            {
                escaping_char = true;
            }
            else
            {
                current_token += current_char;
            }
        }
    }

    // Push a potential last token
    add_word(current_token, sWORD, tokens);

    // Sanity Checks:
    if (comment_depth > 0)
    {
        return parsing_error(intr, "Open comment without terminating ']'.", tokens);
    }
    if (in_string)
    {
        return parsing_error(intr, "Open string without terminating '\"'.", tokens);
    }
    if (block_string_depth > 0)
    {
        return parsing_error(intr, "Open block string without terminating ')' (depth: " + number_to_string(block_string_depth) + ").", tokens);
    }
    if (escaping_char)
    {
        return parsing_error(intr, "Dangling \\ without any characters to escape.", tokens);
    }

    return std::pair<bool, std::vector<PolarisWord> *>(true, tokens);
}

std::string number_to_string(double value)
{
    std::string str = std::to_string(value);
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    str.erase(str.find_last_not_of('.') + 1, std::string::npos);
    return str;
}