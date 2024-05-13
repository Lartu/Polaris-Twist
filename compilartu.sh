#!/bin/bash
set -e  # Exit if any command fails

# Compile Polaris
#echo "Compiling Polaris"
#g++ -std=c++98 -c tokenizer.cpp -o tokenizer.o -Ofast -march=native 
#g++ -std=c++98 -c polaris_definitions.cpp -o polaris_definitions.o -Ofast -march=native 
#g++ -std=c++98 -c polaris.cpp -o polaris.o -Ofast -march=native 
#g++ -std=c++98 tokenizer.o polaris_definitions.o polaris.o -o polaris -Ofast -march=native

# Compile Standard Libraries

#echo "Done!"

#exit

rm -f polaris
rm -f *.o

# Compile objects
g++ -std=c++98 -c tokenizer.cpp -o tokenizer.o -Ofast -march=native
g++ -std=c++98 -c polaris_interpreter.cpp -o polaris_interpreter.o -Ofast -march=native -fPIC
g++ -std=c++98 -c polaris.cpp -o polaris.o -Ofast -march=native
g++ -std=c++98 -c included_handlers.cpp -o included_handlers.o -Ofast -march=native

# Compile Interpreter
g++ -std=c++98 tokenizer.o polaris_interpreter.o polaris.o included_handlers.o -o polaris -Ofast -march=native

# Compile PolarisInterpreter implementation into a shared library
# g++ -std=c++98 -fPIC -c polaris_definitions.cpp -o PolarisInterpreter.o -Ofast -march=native
# g++ -shared -o libpolaris.dl PolarisInterpreter.o tokenizer.o

# Compile basic.plib and link it against libpolaris.dylib
# g++ -std=c++98 -fPIC -shared -o basic.plib polaris_stdlib.cpp -Ofast -march=native

# Assuming 'tokenizer.cpp' and other parts don't need the shared lib
# g++ -std=c++98 -c polaris.cpp -o polaris.o -Ofast -march=native
# g++ -std=c++98 -o polaris polaris.o -L. -lpolaris -Ofast -march=native

# Compile Test Library
g++ -std=c++98 -o test.plib -shared -fPIC testlib.cpp -Ofast -march=native 

rm -f *.o