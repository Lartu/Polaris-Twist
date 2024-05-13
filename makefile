# +----------+
# | MAKEFILE |
# +----------+

# --- Version Information ---
POLARIS_VERSION = '"1.0"'  #Polaris Version

# --- Options ---
#PREFIX is environment variable, but if it is not set, then set default value
ifeq ($(PREFIX),)
PREFIX := /usr/local
endif

# --- Makefile Data ---
SOURCE = tokenizer.cpp polaris_interpreter.cpp polaris.cpp included_handlers.cpp
OUT = polaris

# --- Compilation Flags ---
OBJ_FLAGS = -Wall -std=gnu++98 -Ofast -march=native -DPOLARIS_VERSION=$(POLARIS_VERSION)  -DCOMPILEDATE='"$(shell date +%Y-%m-%d)"' -DCOMPILEHOUR='"$(shell date +%H:%M:%S)"'

# --- Build Rules ---
all:
	cd src && $(CXX) -c $(SOURCE) $(OBJ_FLAGS)
	cd src && $(CXX) *.o -o $(OUT)
	cd src && rm -f *.o
	mkdir -p build
	mv src/$(OUT) build

clean:
	rm -rf build

install: build/$(OUT)
	install -d $(DESTDIR)$(PREFIX)/bin/
	install -m 775 build/$(OUT) $(DESTDIR)$(PREFIX)/bin/
	
uninstall:
	rm $(DESTDIR)$(PREFIX)/bin/$(OUT)