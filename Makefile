COMPILER_FLAGS= -std=c++17 -masm=intel -mlong-double-128 -ggdb3 -Wpedantic -Wall -Wextra -Wconversion -Wsign-conversion -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override
LINKER_FLAGS= -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
EXECUTABLE=ElectricPreacher
CXX=g++ -ggdb

HEADER=$(wildcard includes/*.hpp)
SOURCES=$(wildcard src/*.cpp)
TMP_OBJECTS=$(SOURCES:.cpp=.o)
OBJECTS=$(TMP_OBJECTS:src/%=build/%)

all: pre bin/$(EXECUTABLE) post


pre:
	@echo -e "\e[0;32m============== Compiling  =============\e[0m"
	@mkdir -p bin build

post:
	@echo -e "\e[0;32m============= Adding files ============\e[0m"
ifeq ($(OS),Windows_NT)
	@cp lib/*.dll bin
endif
	@cp -r assets bin/

bin/$(EXECUTABLE): main.cpp $(OBJECTS) $(HEADER)
	@echo -e "\e[1;32mcompiling final $@\e[0m"
	@$(CXX) $^ $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $@

build/%.o: src/%.cpp
	@echo -e "\e[1;33m >> $^ -> $@\e[0m"
	@$(CXX) $(COMPILER_FLAGS) -c $^ -o $@

clean :
	clear
	@echo -e "\e[0;33m============== Cleaning  ==============\e[0m"
	rm -f build/*.o

run: all
	@echo -e "\e[0;31m================= Run ================\e[0m"
	@echo -e "\e[0;31m"
	@./bin/$(EXECUTABLE)
	@echo "\e[0m"

valrun: all
	@echo -e "\e[0;31m============ Valgrind Run ============\e[0m"
	valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all --error-limit=no --gen-suppressions=all --log-file=supdata.log ./$(EXECUTABLE)

mrproper: clean
	rm -f bin/$(EXECUTABLE)

.PHONY: clean mrproper
