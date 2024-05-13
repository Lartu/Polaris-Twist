#!/bin/bash
set -e  # Exit if any command fails

rm -f polaris
rm -f *.o
rm -f *.plib

# Compile objects
g++ -std=c++98 -c tokenizer.cpp -o tokenizer.o -Ofast -march=native
g++ -std=c++98 -c polaris_interpreter.cpp -o polaris_interpreter.o -Ofast -march=native
g++ -std=c++98 -c polaris.cpp -o polaris.o -Ofast -march=native
g++ -std=c++98 -c included_handlers.cpp -o included_handlers.o -Ofast -march=native

# Compile Interpreter
g++ -std=c++98 tokenizer.o polaris_interpreter.o polaris.o included_handlers.o -o polaris -Ofast -march=native

# Compile Test Library
g++ -std=c++11 -o test.plib -shared -fPIC testlib.cpp -Ofast -march=native 

rm -f *.o