import threading
from typing import List, Tuple, Dict, Callable, Set, Optional
from tokenizer import split_words
from words import StringType, Word
from time import sleep

# Hacer Haiku Style icon

class StackInterpreter:
    def __init__(self, parent_variables: Dict[str, str], parent_command: Dict[str, Callable]):
        self.code_tokens: List[Tuple[Word]] = []
        self.stack: List[str] = []
        self.variables: Dict[str, str] = parent_variables.copy()
        self.command_words: Dict[str, Callable] = parent_command.copy()
        self.program_counter: List[int] = [0]
        self.halted = False

    def throw_error(self, error_message: str):
        print("")
        print(f"--- Polaris Error ---")
        print(f"{error_message}")
        if len(self.code_tokens) > 0:
            print(f"When executing word: {self.code_tokens[-1][self.program_counter[-1]]}")
            print(f"In context:")
            spaces: int = 0
            for i in range(self.program_counter[-1] - 5, self.program_counter[-1] + 6):
                if i < 0:
                    continue
                elif i >= len(self.code_tokens[-1]):
                    break
                if i < self.program_counter[-1]:
                    spaces += len(self.code_tokens[-1][i].get_word()) + 1
                print(self.code_tokens[-1][i].get_word(), end=" ")
            print("")
            print(spaces * " ", end="")
            print(len(self.code_tokens[-1][self.program_counter[-1]].get_word()) * "^")
        print(f"Stack at moment of failure:")
        self._printstack()
        self.halted = True


    def run_code(self, code: str) -> str:
        try:
            self.code_tokens.append(split_words(code))
            self._run_code()
        except Exception as e:
            self.throw_error(f"{e}")
            self.halted = True

    def _run_code(self):
        self.program_counter.append(0)
        while self.program_counter[-1] < len(self.code_tokens[-1]) and not self.halted:
            word: Word = self.code_tokens[-1][self.program_counter[-1]]
            if word.get_type() == StringType.REGULAR:
                if self._is_command_word(word.get_word()):
                    self._execute_command_word(word.get_word())
                else:
                    self._push_value(word.get_word())
            else:
                self._push_value(word.get_word())
            self.program_counter[-1] += 1
        self.program_counter.pop()
        self.code_tokens.pop()

    def _push_value(self, value: str):
        self.stack.append(value)

    def _printstack(self):
        if len(self.stack) > 0:
            print("(top): ", end="")
            for i in range(len(self.stack) - 1, -1, -1):
                if i > 0:
                    print(f"{self.stack[i]}, ", end="")
                else:
                    print(self.stack[i])
        else:
            print("(the stack is empty)")

    def _is_command_word(self, word: str) -> bool:
        return word in self.command_words
    
    def _execute_command_word(self, word: str) -> None:
        self.command_words[word](self, word)

    def _pop_from_stack(self, word: str) -> str:
        if len(self.stack) == 0:
            self.throw_error(f"Empty stack pop when executing {word}.")
        else:
            return self.stack.pop()
        
    def to_floating_point_number(self, string_val: str) -> float:
        try:
            return float(string_val)
        except:
            self.throw_error(f"{string_val} is not a valid floating point number.")
        
    def to_integer_number(self, string_val: str) -> int:
        try:
            return int(string_val)
        except:
            self.throw_error(f"{string_val} is not a valid integer number.")

    def set_variable(self, var_name: str, value: str):
        self.variables[var_name] = value

    def get_variable(self, var_name: str) -> Optional[str]:
        if var_name in self.variables:
            return self.variables[var_name]
        else:
            self.throw_error(f"Variable {var_name} not found this context.")



# -------

DEFAULT_VARIABLES = {}
DEFAULT_COMMANDS = {}
active_threads: Set[threading.Thread] = set()

def com_stack_handler(intr: StackInterpreter, word: str) -> None:
    intr._printstack()

def com_print_handler(intr: StackInterpreter, word: str) -> None:
    print(intr._pop_from_stack(word))

def com_wait_handler(intr: StackInterpreter, word: str) -> None:
    seconds: float = intr.to_floating_point_number(intr._pop_from_stack(word))
    sleep(seconds)

def com_exec_handler(intr: StackInterpreter, word: str) -> None:
    intr.run_code(intr._pop_from_stack(word))

def com_thread_handler(intr: StackInterpreter, word: str) -> None:
    global active_threads
    new_interpreter = StackInterpreter(intr.variables, intr.command_words)
    t = threading.Thread(target=new_interpreter.run_code, args = (intr._pop_from_stack(word),))
    t.daemon = True
    t.start()
    active_threads.add(t)

def com_join_handler(intr: StackInterpreter, word: str) -> None:
    b: str = intr._pop_from_stack(word)
    a: str = intr._pop_from_stack(word)
    intr._push_value(f"{a}{b}")

def com_set_handler(intr: StackInterpreter, word: str) -> None:
    var_name: str = intr._pop_from_stack(word)
    intr.set_variable(var_name, intr._pop_from_stack(word))

def com_get_handler(intr: StackInterpreter, word: str) -> None:
    intr._push_value(f"{intr.get_variable(intr._pop_from_stack(word))}")

def com_fjoin_handler(intr: StackInterpreter, word: str) -> None:
    # Full Join
    joined: str = ""
    while len(intr.stack) > 0:
        joined = f"{intr._pop_from_stack(word)}{joined}"
    intr._push_value(joined)

def com_print_handler(intr: StackInterpreter, word: str) -> None:
    # Full Print
    joined: str = ""
    while len(intr.stack) > 0:
        joined = f"{intr._pop_from_stack(word)}{joined}"
    print(joined)


if __name__ == "__main__":
    DEFAULT_COMMANDS["stack"] = com_stack_handler
    DEFAULT_COMMANDS["print"] = com_print_handler
    DEFAULT_COMMANDS["fprint"] = com_print_handler
    DEFAULT_COMMANDS["sleep"] = com_wait_handler
    DEFAULT_COMMANDS["eval"] = com_exec_handler
    DEFAULT_COMMANDS["thread"] = com_thread_handler
    DEFAULT_COMMANDS["join"] = com_join_handler
    DEFAULT_COMMANDS["fjoin"] = com_fjoin_handler
    DEFAULT_COMMANDS["set"] = com_set_handler
    DEFAULT_COMMANDS["get"] = com_get_handler
    interpreter = StackInterpreter(DEFAULT_VARIABLES, DEFAULT_COMMANDS)
    code = ""
    with open("test.stack", "r") as f:
        code = f.read()
    interpreter.run_code(code)

    # Wait for all threads before closing
    for thread in active_threads:
        if thread.is_alive():
            thread.join()