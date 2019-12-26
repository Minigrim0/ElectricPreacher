COMPILER_FLAGS= -std=c++17 -masm=intel -fconcepts -mlong-double-128 -ggdb3 -Wpedantic -Wall -Wextra -Wconversion -Wsign-conversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override
LINKER_FLAGS= -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer libjsoncpp.a
EXECUTABLE=fuzzyWaddle
CXX=g++ -ggdb

HEADER=$(wildcard includes/*.hpp)
SOURCES=$(wildcard src/*.cpp)
TMP_OBJECTS=$(SOURCES:.cpp=.o)
OBJECTS=$(TMP_OBJECTS:src/%=build/%)

all: print $(EXECUTABLE)


print:
	@echo "\e[0;32m============== Compiling  =============\e[0m"

$(EXECUTABLE): main.cpp $(OBJECTS)
	$(CXX) $^ $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $@

build/%.o: src/%.cpp
	@mkdir -p build
	$(CXX) $(COMPILER_FLAGS) -c $^ -o $@

clean :
	clear
	@echo "\e[0;33m============== Cleaning  ==============\e[0m"
	rm -f build/*.o

run: all
	@echo "\e[0;31m================= Run ================\e[0m"
	./$(EXECUTABLE)

valrun: all
	@echo "\e[0;31m============ Valgrind Run ============\e[0m"
	valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all --error-limit=no --gen-suppressions=all --log-file=supdata.log ./$(EXECUTABLE)

mrproper: clean
	rm -f $(FINAL)

.PHONY: clean mrproper
