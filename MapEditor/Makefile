COMPILER_FLAGS = -std=c++17 -masm=intel -fconcepts -mlong-double-128 -ggdb3 -Wpedantic -Wall -Wextra -Wconversion -Wsign-conversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
OBJECTS_GLOB = screen.o ground_element.o
OBJECTS_LOC = editor_ui.o
FINAL = fuzzyWaddle_Editor
CC = g++

all: $(FINAL) clean

$(FINAL): *.cpp $(OBJECTS_GLOB) $(OBJECTS_LOC)
	$(CC) $^ $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $@

screen.o: ../src/screen.cpp
	$(CC) $(FLAGS) $< -c

ground_element.o: ../src/ground_element.cpp
	$(CC) $(FLAGS) $< -c

%.o: src/%.cpp
	$(CC) $(FLAGS) $< -c

clean :
	rm -f *.o

mrproper: clean
	rm -f $(FINAL)

.PHONY: clean mrproper
