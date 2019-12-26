COMPILER_FLAGS= -std=c++17 -Wpedantic -Wall -Wextra -Wconversion -Wsign-conversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override
LINKER_FLAGS= -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer ../libjsoncpp.a
OBJECTS_GLOB_tmp= button.o screen.o map_element.o ground_element.o widgets.o scenery_element.o wall_element.o chunk.o image_set.o
OBJECTS_LOC_tmp= src/editor_ui.o
OBJECTS_GLOB= $(OBJECTS_GLOB_tmp:%=build/%)
OBJECTS_LOC= $(OBJECTS_LOC_tmp:src/%=build/loc/%)

EXECUTABLE= fuzzyWaddle_Editor
CC = g++ -g

all: print $(EXECUTABLE)

print:
	@echo "\e[0;32m============== Compiling  =============\e[0m"


$(EXECUTABLE): main.cpp $(OBJECTS_GLOB) $(OBJECTS_LOC)
	$(CC) $^ $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $@

build/loc/%.o: src/%.cpp
	@mkdir -p build
	@mkdir -p build/loc/
	$(CC) $(COMPILER_FLAGS) -c $^ -o $@

build/%.o: ../src/%.cpp
	@mkdir -p build
	$(CC) $(COMPILER_FLAGS) -c $^ -o $@

clean:
	clear
	@echo "\e[0;33m============== Cleaning  ==============\e[0m"
	rm -f build/*.o
	rm -f build/loc/*

run: all
	@echo "\e[0;31m================= Run ================\e[0m"
	./$(EXECUTABLE)

mrproper: clean
	rm -f $(FINAL)

.PHONY: clean mrproper
