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

rm polaris

# Compile objects
g++ -std=c++98 -c tokenizer.cpp -o tokenizer.o -Ofast -march=native
g++ -std=c++98 -c polaris_definitions.cpp -o polaris_definitions.o -Ofast -march=native -fPIC
g++ -std=c++98 -c polaris.cpp -o polaris.o -Ofast -march=native

# Compile Interpreter
g++ -std=c++98 tokenizer.o polaris_definitions.o polaris.o -o polaris -Ofast -march=native

# Compile PolarisInterpreter implementation into a shared library
g++ -std=c++98 -fPIC -c polaris_definitions.cpp -o PolarisInterpreter.o -Ofast -march=native
g++ -shared -o libpolaris.dl PolarisInterpreter.o tokenizer.o

# Compile basic.plib and link it against libpolaris.dylib
g++ -std=c++98 -fPIC -shared -o basic.plib polaris_stdlib.cpp -Ofast -march=native

# Assuming 'tokenizer.cpp' and other parts don't need the shared lib
# g++ -std=c++98 -c polaris.cpp -o polaris.o -Ofast -march=native
# g++ -std=c++98 -o polaris polaris.o -L. -lpolaris -Ofast -march=native

# Compile Basic Library
rm -f *.o