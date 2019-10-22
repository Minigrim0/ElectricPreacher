COMPILER_FLAGS = -std=c++17 -masm=intel -fconcepts -mlong-double-128 -ggdb3 -Wpedantic -Wall -Wextra -Wconversion -Wsign-conversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer libjsoncpp.a
OBJECTS = screen.o image_set.o map_manager.o ground_element.o wall_element.o map_element.o chunk.o
FINAL = fuzzyWaddle
CC = g++

all: $(FINAL) clean

$(FINAL): *.cpp $(OBJECTS)
	$(CC) $^ $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $@

%.o: src/%.cpp
	$(CC) $(COMPILER_FLAGS) $< -c

clean :
	rm -f *.o

mrproper: clean
	rm -f $(FINAL)

.PHONY: clean mrproper
