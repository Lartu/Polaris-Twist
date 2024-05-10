from enum import Enum


class StringType(Enum):
    REGULAR = 1
    QUOTED = 2
    BLOCK = 3


class Word:
    def __init__(self, word: str, type: StringType):
        self._word = word
        self._type = type

    def get_word(self) -> str:
        return self._word
    
    def get_type(self) -> StringType:
        return self._type
    
    def __repr__(self) -> str:
        return self._word
