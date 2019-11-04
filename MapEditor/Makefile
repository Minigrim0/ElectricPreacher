COMPILER_FLAGS = -std=c++17 -Wpedantic -Wall -Wextra -Wconversion -Wsign-conversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer ../libjsoncpp.a
OBJECTS_GLOB = screen.o map_element.o ground_element.o scenery_element.o wall_element.o chunk.o image_set.o
OBJECTS_LOC = src/editor_ui.o src/button.o
FINAL = fuzzyWaddle_Editor
CC = g++

all: $(FINAL)

$(FINAL): *.cpp $(OBJECTS_GLOB) $(OBJECTS_LOC)
	$(CC) $^ $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $@

src/%.o: src/%.cpp
	$(CC) $(COMPILER_FLAGS) $< -c; mv $(subst src/,,$@) $@

%.o: ../src/%.cpp
	$(CC) $(COMPILER_FLAGS) $< -c

clean:
	rm -f *.o; rm -f src/*.o

mrproper: clean
	rm -f $(FINAL)

.PHONY: clean mrproper
