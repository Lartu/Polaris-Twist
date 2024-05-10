from typing import Tuple, List
from words import StringType, Word

        
def is_whitespace(char: str) -> bool:
    return char in [' ', '\n', '\t']


def add_word(word: str, type: StringType, tokens_list: List[Word]):
    if type == StringType.REGULAR:
        if len(word) == 0:
            return
        if len(word) > 1 and word[0] == ">":
            word = word[1:]
            tokens_list.append(Word(word, type))
            tokens_list.append(Word("set", type))
        elif len(word) > 1 and word[0] == "@":
            word = word[1:]
            tokens_list.append(Word(word, type))
            tokens_list.append(Word("get", type))
        elif len(word) > 1 and word[-1] == "%":
            word = word[0:-1]
            tokens_list.append(Word(word, type))
            tokens_list.append(Word("get", type))
            tokens_list.append(Word("eval", type))
        else:
            tokens_list.append(Word(word, type))
    else:
        tokens_list.append(Word(word, type))



def split_words(code: str) -> Tuple[Word]:
    tokens = []
    current_token = ""
    in_string = False
    block_string_depth = 0
    in_comment = False
    escaping_char = False
    for char in code:
        if char == '"' and not escaping_char and not in_comment and not in_string and block_string_depth == 0:
            # Si empieza un string, pusheo token y empiezo el string.
            add_word(current_token, StringType.REGULAR, tokens)
            current_token = ""
            in_string = True
        elif char == '"' and not escaping_char and not in_comment and in_string and block_string_depth == 0:
            # Si cierra un string, pusheo token y cierro el string.
            add_word(current_token, StringType.QUOTED, tokens)
            current_token = ""
            in_string = False
        elif char == '(' and not escaping_char and not in_comment and not in_string:
            # Si empieza un string, pusheo token y empiezo el string.
            if block_string_depth == 0:
                add_word(current_token, StringType.REGULAR, tokens)
                current_token = ""
            else:
                current_token += char
            block_string_depth += 1
        elif char == ')' and not escaping_char and not in_comment and not in_string and block_string_depth > 0:
            # Si cierra un string, pusheo token y cierro el string.
            block_string_depth -= 1
            if block_string_depth == 0:
                add_word(current_token, StringType.BLOCK, tokens)
                current_token = ""
            else:
                current_token += char
        elif char == '[' and not escaping_char and not in_comment and not in_string and block_string_depth == 0:
            # Si empieza un comment, pusheo token y empiezo el comment.
            add_word(current_token, StringType.REGULAR, tokens)
            current_token = ""
            in_comment = True
        elif char == ']' and not escaping_char and in_comment and not in_string and block_string_depth == 0:
            # Si cierra un comment, solo cierro el comment.
            in_comment = False
        elif is_whitespace(char) and not in_comment and not in_string and block_string_depth == 0:
            # Si es espacio, pusheo token
            add_word(current_token, StringType.REGULAR, tokens)
            current_token = ""
        elif not in_comment and escaping_char:
            # Si estoy escapando un char, appendeo char escapado y dejo de escapar
            current_token += char
            escaping_char = False
        elif not in_comment and not escaping_char:
            if char == "\\":
                escaping_char = True
            else:
                current_token += char

    # Push last token
    add_word(current_token, StringType.REGULAR, tokens)

    # Checks
    if in_comment:
        raise Exception("Open commend.")
    if in_string:
        raise Exception("Open string.")
    if block_string_depth > 0:
        raise Exception("Open block string.")
    if escaping_char:
        raise Exception("Open escape.")

    return tokens